#ifndef OBC_ACCELERATION_HPP
#define OBC_ACCELERATION_HPP

#include <Adafruit_MPU6050.h>

#include "error.hpp"
#include "result.hpp"

namespace obc {

struct Acceleration {
    float x;
    float y;
    float z;
};

struct Gyro {
    float x;
    float y;
    float z;
};

struct AcclrMeasurements {
    Acceleration acclr_measurements;
    Gyro gyro_measurements;
};

Result<Unit, Errc> init(Adafruit_MPU6050& accelerometer);
Result<AcclrMeasurements, Errc> measure(Adafruit_MPU6050& accelerometer);
void print(AcclrMeasurements data);

}  // namespace obc

#endif