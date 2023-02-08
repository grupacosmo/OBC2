#include "buzzer.hpp"

#include <Arduino.h>

constexpr auto buzzer_pin = LED_BUILTIN;  // PC13

namespace obc {

void buzzer(std::size_t quantity)
{
    for (std::size_t i = 0; i < quantity; ++i) {
        digitalWrite(buzzer_pin, HIGH);
        delay(100);
        digitalWrite(buzzer_pin, LOW);
        delay(200);
    }
}

}  // namespace obc