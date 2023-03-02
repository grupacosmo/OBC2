#include "utils.hpp"

#include "accelerometer.hpp"
#include "barometer.hpp"
#include "buzzer.hpp"
#include "devices.hpp"
#include "gps.hpp"
#include "logger.hpp"
#include "lora.hpp"

extern Adafruit_GPS gps;
extern MMA8452Q accelerometer;
extern BMP280 bmp;

namespace utl {

namespace {
constexpr auto logs_interval = 2000;
constexpr auto lora_interval = 60000;
constexpr std::size_t buzzer_ind_fix_not_fetched = 1;

uint32_t timer = millis();
uint32_t lora_timer = millis();

bool is_date_appended = false;

}  // namespace

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

void handle_measurements()
{
    if (obc::measure(gps).is_ok() and millis() - timer > logs_interval) {
        obc::Packet logs = {{}, {}, {}, {}, {}};
        const auto acclr = obc::measure(accelerometer);
        const auto bmp_measurements = obc::measure(bmp);
        logs.time = obc::read_time(gps);
        logs.position = obc::read_position(gps);

        if (acclr.is_ok()) { logs.acclr_measurements = acclr.unwrap(); }
        if (bmp_measurements.is_ok()) {
            logs.bmp_measurements = bmp_measurements.unwrap();
        }

        if (not is_date_appended) {
            obc::log_boot(obc::serialize(obc::read_date(gps)));
            is_date_appended = true;
        }

        obc::log_data(obc::serialize(logs));

        if (millis() - lora_timer > lora_interval) {
            obc::send_packet(obc::lora_packet(logs));
            lora_timer = millis();
        }

        if (not logs.position.fix) { obc::buzzer(buzzer_ind_fix_not_fetched); }

        timer = millis();
    }
}

void handle_experiment() {}

void handle_uplink() {}

}  // namespace utl