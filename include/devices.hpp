#ifndef OBC_DEVICES_HPP
#define OBC_DEVICES_HPP

#include <Arduino.h>
#include <SD.h>

#include "accelerometer.hpp"
#include "barometer.hpp"
#include "gps.hpp"
#include "logger.hpp"
#include "lora.hpp"
#include "utils.hpp"

namespace obc {

void init();

}  // namespace obc

#endif