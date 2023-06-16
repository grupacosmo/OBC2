#include <Arduino.h>
#include <IWatchdog.h>

#include "accelerometer.hpp"
#include "barometer.hpp"
#include "buzzer.hpp"
#include "devices.hpp"
#include "gps.hpp"
#include "logger.hpp"
#include "lora.hpp"
#include "utils.hpp"

constexpr auto baud_rate = 9600l;
constexpr auto logs_interval = 2000;
constexpr auto lora_interval = 60000;
constexpr auto watchdog_interval = 10000000;
constexpr std::size_t buzzer_ind_fix_not_fetched = 1;

bool is_date_appended = false;

HardwareSerial Serial2{ PA3, PA2 };
Adafruit_GPS gps{ &Serial2 };
Adafruit_MPU6050 accelerometer;
BMP280 bmp;

uint32_t timer = millis();
uint32_t lora_timer = millis();

void setup()
{
    Serial.begin(baud_rate);
    obc::init();
    IWatchdog.begin(watchdog_interval);
    obc::buzzer(5);
}

void loop()
{
    if (obc::measure(gps).is_ok() and millis() - timer > logs_interval) {
        obc::Packet logs = { {}, {}, {}, {}, {} };
        const auto acclr = obc::measure(accelerometer);
        const auto bmp_measurements = obc::measure(bmp);
        logs.time = obc::read_time(gps);
        logs.position = obc::read_position(gps);

        if (acclr.is_ok()) { logs.acclr_measurements = acclr.unwrap(); }
        if (bmp_measurements.is_ok()) {
            logs.bmp_measurements = bmp_measurements.unwrap();
        }

        if (not is_date_appended and logs.position.fix) {
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