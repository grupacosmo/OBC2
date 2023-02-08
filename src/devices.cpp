#include "devices.hpp"

#include <Arduino.h>

extern MMA8452Q accelerometer;
extern BMP280 bmp;
extern Adafruit_GPS gps;

constexpr auto custom_sda = PB9;
constexpr auto custom_scl = PB8;
constexpr auto custom_buzzer_pin = LED_BUILTIN;  // PC13

namespace obc {

void init()
{
    Wire.setSDA(custom_sda);
    Wire.setSCL(custom_scl);

    pinMode(custom_buzzer_pin, OUTPUT);
    sd_init().expect("SD init failure");

    if (auto result = init(accelerometer); result.is_err()) {
        log_error_and_panic(
            String("Accelerometer not initialized properly, errc: ")
            + utl::to_underlying(result.unwrap_err()));
    }

    if (auto result = init(bmp); result.is_err()) {
        log_error_and_panic(
            String("Barometer not initialized properly, errc: ")
            + utl::to_underlying(result.unwrap_err()));
    }

    if (auto result = init(gps); result.is_err()) {
        log_error_and_panic(
            String("GPS not initialized properly, errc: ")
            + utl::to_underlying(result.unwrap_err()));
    }

    if (auto result = init_lora(); result.is_err()) {
        log_error_and_panic(
            String("Lora not initialized properly, errc: ")
            + utl::to_underlying(result.unwrap_err()));
    }

    log_boot("Devices initialized properly.");
}

}  // namespace obc