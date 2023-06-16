#include "accelerometer.hpp"

#include <Arduino.h>

namespace obc {

Result<Unit, Errc> init(Adafruit_MPU6050& accelerometer)
{
    Wire.begin();
    if (not accelerometer.begin()) { return Err{ Errc::Busy }; }
    accelerometer.setAccelerometerRange(MPU6050_RANGE_8_G);
    accelerometer.setGyroRange(MPU6050_RANGE_500_DEG);
    accelerometer.setFilterBandwidth(MPU6050_BAND_21_HZ);
    return Ok{ Unit{} };
}

Result<AcclrMeasurements, Errc> measure(Adafruit_MPU6050& accelerometer)
{
    sensors_event_t acclr;
    sensors_event_t gyro;
    sensors_event_t temp;

    if (not accelerometer.getEvent(&acclr, &gyro, &temp)) {
        return Err{ Errc::Busy };
    }

    AcclrMeasurements measurements{
        { acclr.acceleration.x, acclr.acceleration.y, acclr.acceleration.z },
        { gyro.gyro.x, gyro.gyro.y, gyro.gyro.z }
    };

    return Ok{ measurements };
}

void print(AcclrMeasurements data)
{
    Serial.print(data.gyro_measurements.x, 2);
    Serial.print("\t");
    Serial.print(data.gyro_measurements.y, 2);
    Serial.print("\t");
    Serial.print(data.gyro_measurements.z, 2);
    Serial.print("\t");
    Serial.print(data.acclr_measurements.x, 2);
    Serial.print("\t");
    Serial.print(data.acclr_measurements.y, 2);
    Serial.print("\t");
    Serial.print(data.acclr_measurements.z, 2);
    Serial.println();
}

}  // namespace obc