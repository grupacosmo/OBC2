#include <Arduino.h>
#include <IWatchdog.h>

#include "devices.hpp"
#include "utils.hpp"

constexpr auto baud_rate = 9600l;
constexpr auto watchdog_interval = 10000000;

<<<<<<< HEAD
auto current_mode = utl::Modes::Measurements;
=======
bool is_date_appended = false;
#include "devices.hpp"
#include "gps.hpp"
#include "logger.hpp"
#include "utils.hpp"

auto current_mode = utl::Modes::Idle;

HardwareSerial Serial2{PA3, PA2};
Adafruit_GPS gps{&Serial2};
MMA8452Q accelerometer;
BMP280 bmp;

uint32_t timer = millis();
uint32_t lora_timer = millis();
>>>>>>> 64afdd0 (added handle_mode())

void setup()
{
    Serial.begin(baud_rate);
    IWatchdog.begin(watchdog_interval);
    obc::init();
}

void loop()
{
<<<<<<< HEAD
    utl::handle_mode(current_mode);
    IWatchdog.reload();
}
=======
    if (obc::measure(gps).is_ok() and millis() - timer > logs_interval) {
        obc::Packet logs = {{}, {}, {}, {}, {}};
        const auto acclr = obc::measure(accelerometer);
        const auto bmp_measurements = obc::measure(bmp);
        logs.time = obc::read_time(gps);
        logs.position = obc::read_position(gps);

        if (acclr.is_ok()) { logs.acclr_measurements = acclr.unwrap(); }
        if (bmp_measurements.is_ok()) {
            logs.bmp_measurements = bmp_measurements.unwrap();
        }

        if (not is_date_appended) {
            obc::log_boot(obc::serialize(obc::read_date(gps)));
            is_date_appended = true;
        }

        obc::log_data(obc::serialize(logs));

        if (millis() - lora_timer > lora_interval) {
            obc::send_packet(obc::lora_packet(logs));
            lora_timer = millis();
        }

        if (not logs.position.fix) { obc::buzzer(buzzer_ind_fix_not_fetched); }

        timer = millis();
        IWatchdog.reload();
    }
}

void setup() { obc::init(); }

void loop() { utl::handle_mode(current_mode); }
>>>>>>> 64afdd0 (added handle_mode())
