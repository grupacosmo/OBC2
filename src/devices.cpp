#include "devices.hpp"

#include <Arduino.h>

extern Adafruit_MPU6050 accelerometer;
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

    if (auto result = init_lora(); result.is_err()) {
        log_error_and_panic(
            String("Lora not initialized properly, errc: ")
            + utl::to_underlying(result.unwrap_err()));
    }
    log_boot("Lora Init --- [OK]");

    constexpr auto initialize_device = [&](auto& device, const String& name) {
        if (auto result = init(device); result.is_err()) {
            send_packet(String(name + " [INIT ERROR]"));
            log_error_and_panic(
                String(name + " not initialized properly, errc: ")
                + utl::to_underlying(result.unwrap_err()));
        }
        log_boot(String(name + " Init --- [OK]"));

        send_packet(String(name + " [OK]"));

        delay(10000);
    };

    initialize_device(accelerometer, "Accelerometer");
    initialize_device(bmp, "BMP");
    initialize_device(gps, "GPS");

    log_boot("Devices initialized properly.");
}

}  // namespace obc