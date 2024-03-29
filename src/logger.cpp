#include "logger.hpp"

#include <Arduino.h>

namespace obc {

namespace {

constexpr uint8_t sd_chip_select = PB10;
constexpr std::size_t buzzer_ind_fix_fetched = 2;

String flight_path_folder;

File file;

void init_flight_path_folder()
{
    unsigned int flight_id = 1;
    do {
        flight_path_folder = "/F_" + String(flight_id);
        ++flight_id;
    } while (SD.exists(flight_path_folder));
}

void file_appendln(const char* file_name, const char* data)
{
    // NOLINTNEXTLINE (hicpp-signed-bitwise)
    file = SD.open(file_name, O_CREAT | O_WRITE | O_APPEND);
    file.println(data);
    file.close();
}

[[maybe_unused]] void file_appendln(const char* file_name, const String& data)
{
    file_appendln(file_name, data.c_str());
}

[[maybe_unused]] void file_appendln(const String& file_name, const char* data)
{
    file_appendln(file_name.c_str(), data);
}

[[maybe_unused]] void file_appendln(const String& file_name, const String& data)
{
    file_appendln(file_name.c_str(), data.c_str());
}

}  // namespace

Result<Unit, Errc> sd_init()
{
    if (not SD.begin(sd_chip_select)) { return Err{Errc::Busy}; }

    init_flight_path_folder();
    if (not SD.mkdir(flight_path_folder)) { return Err{Errc::Busy}; }

    log_boot("Booting time: " + String(millis()) + "ms");

    constexpr auto logs_legend =
        "Time\tSystem time\tFix\tQuality\tLatitude\tLongtitude\tSpeed (km/h)\t"
        "Altitude(gps)\tSatellites\tTemperature\tPressure\tAltitude(gps)\t"
        "Acceleration X\tAcceleration Y\tAcceleration Z";

    log_data(logs_legend);

    return Ok{Unit{}};
}

void log_boot(const char* msg)
{
    file_appendln(flight_path_folder + "/boot.txt", msg);
}

void log_data(const char* msg)
{
    file_appendln(flight_path_folder + "/logs.csv", msg);
}

void log_error(const char* msg)
{
    file_appendln(flight_path_folder + "/errors.txt", msg);
}

void log_error_and_panic(const char* msg, SourceLocation loc)
{
    file_appendln(flight_path_folder + "/errors.txt", msg);
    panic(msg, loc);
}

void serialize_into(String& buf, const GpsTime& data)
{
    if (not has_tens_digit(data.hour)) { buf += '0'; }
    buf += data.hour;
    buf += ':';
    if (not has_tens_digit(data.minute)) { buf += '0'; }
    buf += data.minute;
    buf += ':';
    if (not has_tens_digit(data.seconds)) { buf += '0'; }
    buf += data.seconds;
    buf += ':';
    if (not has_hundreds_digit(data.milliseconds)) {
        if (not has_tens_digit(data.milliseconds)) { buf += "00"; }
        else {
            buf += '0';
        }
    }
    buf += data.milliseconds;
    buf += "\t";
    buf += millis();
    buf += "\t";
}

void serialize_into(String& buf, const GpsPosition& data)
{
    buf += static_cast<int>(data.fix);
    buf += "\t";
    buf += static_cast<int>(data.fixquality);
    buf += "\t";
    if (data.fix) {
        buf += String(data.latitude, 4);
        buf += data.lat;
        buf += ", ";
        buf += String(data.longitude, 4);
        buf += data.lon;
        buf += "\t";
        buf += data.speed / mph_to_kph_conversion;
        buf += "\t";
        buf += data.altitude;
        buf += "\t";
        buf += static_cast<int>(data.satelites);
        buf += "\t";
        obc::buzzer(buzzer_ind_fix_fetched);
    }
    else {
        for (int i = 0; i < 4; ++i) { buf += "0\t"; }
    }
}

void serialize_into(String& buf, const GpsDate& data)
{
    buf += " Date: ";
    buf += data.day;
    buf += '/';
    buf += data.month;
    buf += "/20";
    if (not has_tens_digit(data.year)) { buf += '0'; }
    buf += data.year;
}

void serialize_into(String& buf, const BmpMeasurements& data)
{
    buf += data.temperature;
    buf += "\t";
    buf += data.pressure;
    buf += "\t";
    buf += data.altitude;
    buf += "\t";
}

void serialize_into(String& buf, const Acceleration& data)
{
    buf += data.x;
    buf += "\t";
    buf += data.y;
    buf += "\t";
    buf += data.z;
    buf += "\t";
}

void serialize_into(String& buf, const Packet& data)
{
    serialize_into(buf, data.time);
    serialize_into(buf, data.position);
    serialize_into(buf, data.bmp_measurements);
    serialize_into(buf, data.acclr_measurements);
}

}  // namespace obc