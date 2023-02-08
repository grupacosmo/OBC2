#ifndef OBC_BAROMETER_HPP
#define OBC_BAROMETER_HPP

#include <BMP280.h>

#include "error.hpp"
#include "result.hpp"

namespace bmp {

struct BmpMeasurements {
    double temperature;
    double pressure;
    double altitude;
};

obc::Result<obc::Unit, err::Errc> init(BMP280& bmp);
obc::Result<BmpMeasurements, err::Errc> measure(BMP280& bmp);
void print(BmpMeasurements measurements);

}  // namespace bmp

#endif