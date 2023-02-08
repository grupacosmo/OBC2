#include "barometer.hpp"

#include <Arduino.h>

namespace bmp {

namespace {

constexpr double ground_lvl_pressure = 1013.25;

}  // namespace

obc::Result<obc::Unit, err::Errc> init(BMP280& bmp)
{
    if (bmp.begin() == 0) { return obc::Err{err::Errc::Busy}; }
    bmp.setOversampling(4);
    return obc::Ok{obc::Unit{}};
}

obc::Result<BmpMeasurements, err::Errc> measure(BMP280& bmp)
{
    char result = bmp.startMeasurment();
    BmpMeasurements temp = {0, 0, 0};

    if (result == 0) { return obc::Err{err::Errc::Busy}; }
    result = bmp.getTemperatureAndPressure(temp.temperature, temp.pressure);

    if (result == 0) { return obc::Err{err::Errc::Busy}; }
    temp.altitude = bmp.altitude(temp.pressure, ground_lvl_pressure);

    return obc::Ok{temp};
}

void print(BmpMeasurements measurements)
{
    Serial.print(measurements.temperature);
    Serial.print("\t");
    Serial.print(measurements.pressure);
    Serial.print("\t");
    Serial.print(measurements.altitude);
    Serial.println();
}

}  // namespace bmp