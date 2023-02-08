#include "accelerometer.hpp"

#include <Arduino.h>

namespace acc {

obc::Result<obc::Unit, err::Errc> init(MMA8452Q& accelerometer)
{
    Wire.begin();
    if (not accelerometer.begin()) { return obc::Err{err::Errc::Busy}; }
    return obc::Ok{obc::Unit{}};
}

obc::Result<Acceleration, err::Errc> measure(MMA8452Q& accelerometer)
{
    if (accelerometer.available() == 0) { return obc::Err{err::Errc::Busy}; }
    return obc::Ok{Acceleration{
        accelerometer.getX(),
        accelerometer.getY(),
        accelerometer.getZ()}};
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

}  // namespace acc