#ifndef OBC_ERROR_HPP
#define OBC_ERROR_HPP

#include <Arduino.h>

#include "source_location.hpp"

namespace err {

enum class Errc { Busy };

void panic(
    const char* msg,
    obc::SourceLocation loc = obc::SourceLocation::current());

}  // namespace err

#endif