#include <Arduino.h>

#include "gps.hpp"

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