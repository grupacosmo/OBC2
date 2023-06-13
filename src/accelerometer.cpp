#include "accelerometer.hpp"

#include <Arduino.h>

namespace obc {

Result<Unit, Errc> init(Adafruit_MPU6050& accelerometer)
{
    Wire.begin();
    if (not accelerometer.begin()) { return Err{Errc::Busy}; }
    return Ok{Unit{}};
}

Result<Acceleration, Errc> measure(Adafruit_MPU6050& accelerometer)
{
    accelerometer.getClock();
    /*if (accelerometer.available() == 0) { return Err{Errc::Busy}; }
    return Ok{Acceleration{
        accelerometer.getX(),
        accelerometer.getY(),
        accelerometer.getZ()}};*/
    return Ok{Acceleration{0, 0, 0}};
}

void print(Acceleration acclr)
{
    Serial.print(acclr.x);
    Serial.print("\t");
    Serial.print(acclr.y);
    Serial.print("\t");
    Serial.print(acclr.z);
    Serial.println();
}

}  // namespace obc