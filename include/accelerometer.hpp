#ifndef OBC_ACCELERATION_HPP
#define OBC_ACCELERATION_HPP

#include <SparkFun_MMA8452Q.h>

#include "error.hpp"
#include "result.hpp"

namespace acc {

struct Acceleration {
    short x;
    short y;
    short z;
};

obc::Result<obc::Unit, err::Errc> init(MMA8452Q& accelerometer);
obc::Result<Acceleration, err::Errc> measure(MMA8452Q& accelerometer);
void print(Acceleration acclr);

}  // namespace acc

#endif