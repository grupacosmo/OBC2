#include <Arduino.h>

#include "accelerometer.hpp"
#include "barometer.hpp"
#include "gps.hpp"
#include "interval.hpp"
#include "modes.hpp"

auto current_mode = utl::Modes::Idle;

constexpr uint32_t interval_500 = 500;

HardwareSerial Serial2{PA3, PA2};
Adafruit_GPS gps_dev{&Serial2};
BMP280 bmp_dev;
MMA8452Q accelerometer_dev;

obc::Interval interval{interval_500};


void setup()
{
    // put your setup code here, to run once:
}

void loop()
{

    const auto gps_setup = interval.execute(gps::measure, gps_dev);
    const auto acclr = interval.execute(bmp::measure, bmp_dev);
    const auto bmp_measurements =
        interval.execute(acc::measure, accelerometer_dev);

    const auto temp = bmp_measurements.value().is_ok();

    if (temp) {}

    if (gps_setup) {}
    if (acclr) {}
    if (bmp_measurements) {}
}