#include "modes.hpp"

extern utl::Modes current_mode;

namespace mds {

auto mode_idle() {}

auto mode_measurements() {}

auto mode_experiment() {}

auto mode_uplink() {}

auto handle_mode()
{
    switch (current_mode) {
        case utl::Modes::Idle:
            mode_idle();
            break;
        case utl::Modes::Measurements:
            mode_measurements();
            break;
        case utl::Modes::Experiment:
            mode_experiment();
            break;
        case utl::Modes::Uplink:
            mode_uplink();
            break;
        default:
            break;
    }
}

}  // namespace mds