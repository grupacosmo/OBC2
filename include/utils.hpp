#ifndef OBC_UTILS_HPP
#define OBC_UTILS_HPP

#include <Arduino.h>

#include <type_traits>

namespace utl {

enum class Logger { Debug, Flight };

enum class Modes { Idle, Measurements, Experiment, Uplink };

template <typename Enum>
constexpr auto to_underlying(Enum e)
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

void handle_mode(Modes mode);
void handle_idle();
void handle_measurements();
void handle_experiment();
void handle_uplink();

}  // namespace utl

#endif