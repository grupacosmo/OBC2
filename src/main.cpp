#include <Arduino.h>
#include <IWatchdog.h>

#include "devices.hpp"
#include "utils.hpp"

constexpr auto baud_rate = 9600l;
constexpr auto watchdog_interval = 10000000;

auto current_mode = utl::Modes::Measurements;

void setup()
{
    Serial.begin(baud_rate);
    IWatchdog.begin(watchdog_interval);
    obc::init();
}

void loop()
{
    utl::handle_mode(current_mode);
    IWatchdog.reload();
}