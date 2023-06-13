#ifndef OBC_ACCELERATION_HPP
#define OBC_ACCELERATION_HPP

#include <Adafruit_MPU6050.h>

#include "error.hpp"
#include "result.hpp"

namespace obc {

struct Acceleration {
    short x;
    short y;
    short z;
};

Result<Unit, Errc> init(Adafruit_MPU6050& accelerometer);
Result<Acceleration, Errc> measure(Adafruit_MPU6050& accelerometer);
void print(Acceleration acclr);

}  // namespace obc

#endif