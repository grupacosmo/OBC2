#include <Arduino.h>

#include "accelerometer.hpp"
#include "barometer.hpp"
#include "gps.hpp"
#include "logger.hpp"

HardwareSerial Serial2{PA3, PA2};

Adafruit_GPS gps{&Serial2};

void setup()
{
    // put your setup code here, to run once:
}

void loop()
{
    // put your main code here, to run repeatedly:
}