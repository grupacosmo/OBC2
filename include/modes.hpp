#ifndef OBC_MODES_HPP
#define OBC_MODES_HPP

#include "utils.hpp"

namespace mds {

auto handle_mode();
auto mode_idle();
auto mode_measurements();
auto mode_experiment();
auto mode_uplink();

}  // namespace mds

#endif