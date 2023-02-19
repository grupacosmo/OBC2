#include <Arduino.h>

#include "accelerometer.hpp"
#include "barometer.hpp"
#include "devices.hpp"
#include "gps.hpp"
#include "logger.hpp"
#include "utils.hpp"

auto current_mode = utl::Modes::Idle;

HardwareSerial Serial2{PA3, PA2};
Adafruit_GPS gps{&Serial2};
MMA8452Q accelerometer;
BMP280 bmp;

void setup() { obc::init(); }

void loop() { utl::handle_mode(current_mode); }