#include "utils.hpp"

namespace utl {

void handle_mode(Modes mode)
{
    switch (mode) {
        case Modes::Idle:
            return handle_idle();
        case Modes::Measurements:
            return handle_measurements();
        case Modes::Experiment:
            return handle_experiment();
        case Modes::Uplink:
            return handle_uplink();
        default:
            break;
    }
}

void handle_idle() {}

void handle_measurements() {}

void handle_experiment() {}

void handle_uplink() {}

}  // namespace utl