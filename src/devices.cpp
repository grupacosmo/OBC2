#include "devices.hpp"

#include <Arduino.h>

extern MMA8452Q accelerometer_dev;
extern BMP280 bmp_dev;
extern Adafruit_GPS gps_dev;

namespace obc {

void init()
{
    pinMode(D6, OUTPUT);
    sd_init().expect("SD init failure");

    if (auto result = acc::init(accelerometer_dev); result.is_err()) {
        log_error_and_panic(
            String("Accelerometer not initialized properly, errc: ")
            + utl::to_underlying(result.unwrap_err()));
    }

    if (auto result = bmp::init(bmp_dev); result.is_err()) {
        log_error_and_panic(
            String("Barometer not initialized properly, errc: ")
            + utl::to_underlying(result.unwrap_err()));
    }

    if (auto result = gps::init(gps_dev); result.is_err()) {
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