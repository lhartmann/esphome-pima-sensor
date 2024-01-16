#include "pima.h"
#include "esphome/core/log.h"
#include <cinttypes>

namespace esphome {
namespace pima {

static const char *const TAG = "PIMA";

const PIMA::PIMA_labels_t PIMA::PIMA_labels[] = {
    {0x0a, 0x02, 1.0, "kWh_t",        &PIMA::energy_consumed_total_ },
    {0x0a, 0x03, 1.0, "kWh_p",        &PIMA::energy_consumed_peak_rate_},
    {0x0a, 0x04, 1.0, "kWh_r",        &PIMA::energy_consumed_intermediate_rate_ },
    {0x0a, 0x05, 1.0, "kWh_f",        &PIMA::energy_consumed_off_peak_rate_ },
    {0x0a, 0x06, 1.0, "kWh_d",        &PIMA::energy_consumed_d_rate_ },
    {0x0a, 0x07, 1.0, "kVAR_L_t",     &PIMA::reactive_energy_inductive_consumed_total_ },
    {0x0a, 0x08, 1.0, "kVAR_L_p",     &PIMA::reactive_energy_inductive_consumed_peak_rate_ },
    {0x0a, 0x09, 1.0, "kVAR_L_r",     &PIMA::reactive_energy_inductive_consumed_intermediate_rate_ },
    {0x0a, 0x0a, 1.0, "kVAR_L_f",     &PIMA::reactive_energy_inductive_consumed_off_peak_rate_ },
    {0x0a, 0x0b, 1.0, "kVAR_L_d",     &PIMA::reactive_energy_inductive_consumed_d_rate_ },
    {0x0a, 0x0c, 1.0, "kVAR_C_t",     &PIMA::reactive_energy_capacitive_consumed_total_ },
    {0x0a, 0x0d, 1.0, "kVAR_C_p",     &PIMA::reactive_energy_capacitive_consumed_peak_rate_ },
    {0x0a, 0x0e, 1.0, "kVAR_C_r",     &PIMA::reactive_energy_capacitive_consumed_intermediate_rate_ },
    {0x0a, 0x0f, 1.0, "kVAR_C_f",     &PIMA::reactive_energy_capacitive_consumed_off_peak_rate_ },
    {0x0a, 0x10, 1.0, "kVAR_C_d",     &PIMA::reactive_energy_capacitive_consumed_d_rate_ },
    {0x0b, 0x01, 0.1, "V1",           &PIMA::voltage_1_ },
    {0x0b, 0x02, 0.1, "V2",           &PIMA::voltage_2_ },
    {0x0b, 0x03, 0.1, "V3",           &PIMA::voltage_3_ },
    {0x0a, 0x51, 1.0, "kWh_gen_t",    &PIMA::energy_generated_total_ },
    {0x0a, 0x52, 1.0, "kWh_gen_p",    &PIMA::energy_generated_peak_rate_ },
    {0x0a, 0x53, 1.0, "kWh_gen_r",    &PIMA::energy_generated_intermediate_rate_ },
    {0x0a, 0x54, 1.0, "kWh_gen_f",    &PIMA::energy_generated_off_peak_rate_ },
    {0x0a, 0x55, 1.0, "kWh_gen_d",    &PIMA::energy_generated_d_rate_ },
    {0x0a, 0x56, 1.0, "kVAR_gen_L_t", &PIMA::reactive_energy_inductive_generated_total_ },
    {0x0a, 0x57, 1.0, "kVAR_gen_L_p", &PIMA::reactive_energy_inductive_generated_peak_rate_ },
    {0x0a, 0x58, 1.0, "kVAR_gen_L_r", &PIMA::reactive_energy_inductive_generated_intermediate_rate_ },
    {0x0a, 0x59, 1.0, "kVAR_gen_L_f", &PIMA::reactive_energy_inductive_generated_off_peak_rate_ },
    {0x0a, 0x5a, 1.0, "kVAR_gen_L_d", &PIMA::reactive_energy_inductive_generated_d_rate_ },
    {0x0a, 0x5b, 1.0, "kVAR_gen_C_t", &PIMA::reactive_energy_capacitive_generated_total_ },
    {0x0a, 0x5c, 1.0, "kVAR_gen_C_p", &PIMA::reactive_energy_capacitive_generated_peak_rate_ },
    {0x0a, 0x5d, 1.0, "kVAR_gen_C_r", &PIMA::reactive_energy_capacitive_generated_intermediate_rate_ },
    {0x0a, 0x5e, 1.0, "kVAR_gen_C_f", &PIMA::reactive_energy_capacitive_generated_off_peak_rate_ },
    {0x0a, 0x5f, 1.0, "kVAR_gen_C_d", &PIMA::reactive_energy_capacitive_generated_d_rate_ },
};

void PIMA::setup() {
  this->flush();
}

void PIMA::loop() {
  while (this->available()) {
    if (!frame(this->read()))
      continue;

    // Frame is complete and valid. Check agains known scope:indexes...
    sensor::Sensor *sensor{nullptr};
    double value = NAN;
    for (auto label : PIMA_labels) {
      if (label.scope == frame.scope() && label.index == frame.index()) {
        sensor = this->*label.sensor;
        value = frame.payload_bcd() * label.scale;
        break;
      }
    }

    // Skip unkonwn scope:index and unset sensors.
    if (!sensor)
      continue;

    // All is well, publish.
    sensor->publish_state(value);

//    ESP_LOGV(TAG, "PIMA: %s = %f", label.label, value);
  }
}


// Generated by helper.py, for dumpconfig
void PIMA::dump_config() {  // NOLINT(readability-function-cognitive-complexity)
  ESP_LOGCONFIG(TAG, "PIMA:");
/*  LOG_SENSOR("", "voltage_1", this->voltage_1_);
  LOG_SENSOR("", "voltage_2", this->voltage_2_);
  LOG_SENSOR("", "voltage_3", this->voltage_3_);
  LOG_SENSOR("", "current_1", this->current_1_);
  LOG_SENSOR("", "current_2", this->current_2_);
  LOG_SENSOR("", "current_3", this->current_3_);
  LOG_SENSOR("", "energy_consumed_total", this->energy_consumed_total_);
  LOG_SENSOR("", "energy_consumed_peak_rate", this->energy_consumed_peak_rate_);
  LOG_SENSOR("", "energy_consumed_intermediate_rate", this->energy_consumed_intermediate_rate_);
  LOG_SENSOR("", "energy_consumed_off_peak_rate", this->energy_consumed_off_peak_rate_);
  LOG_SENSOR("", "energy_consumed_d_rate", this->energy_consumed_d_rate_);
  LOG_SENSOR("", "energy_generated_total", this->energy_generated_total_);
  LOG_SENSOR("", "energy_generated_peak_rate", this->energy_generated_peak_rate_);
  LOG_SENSOR("", "energy_generated_intermediate_rate", this->energy_generated_intermediate_rate_);
  LOG_SENSOR("", "energy_generated_off_peak_rate", this->energy_generated_off_peak_rate_);
  LOG_SENSOR("", "energy_generated_d_rate", this->energy_generated_d_rate_);
  LOG_SENSOR("", "reactive_energy_capacitive_consumed_total", this->reactive_energy_capacitive_consumed_total_);
  LOG_SENSOR("", "reactive_energy_capacitive_consumed_peak_rate", this->reactive_energy_capacitive_consumed_peak_rate_);
  LOG_SENSOR("", "reactive_energy_capacitive_consumed_intermediate_rate", this->reactive_energy_capacitive_consumed_intermediate_rate_);
  LOG_SENSOR("", "reactive_energy_capacitive_consumed_off_peak_rate", this->reactive_energy_capacitive_consumed_off_peak_rate_);
  LOG_SENSOR("", "reactive_energy_capacitive_consumed_d_rate", this->reactive_energy_capacitive_consumed_d_rate_);
  LOG_SENSOR("", "reactive_energy_capacitive_generated_total", this->reactive_energy_capacitive_generated_total_);
  LOG_SENSOR("", "reactive_energy_capacitive_generated_peak_rate", this->reactive_energy_capacitive_generated_peak_rate_);
  LOG_SENSOR("", "reactive_energy_capacitive_generated_intermediate_rate", this->reactive_energy_capacitive_generated_intermediate_rate_);
  LOG_SENSOR("", "reactive_energy_capacitive_generated_off_peak_rate", this->reactive_energy_capacitive_generated_off_peak_rate_);
  LOG_SENSOR("", "reactive_energy_capacitive_generated_d_rate", this->reactive_energy_capacitive_generated_d_rate_);
  LOG_SENSOR("", "reactive_energy_inductive_consumed_total", this->reactive_energy_inductive_consumed_total_);
  LOG_SENSOR("", "reactive_energy_inductive_consumed_peak_rate", this->reactive_energy_inductive_consumed_peak_rate_);
  LOG_SENSOR("", "reactive_energy_inductive_consumed_intermediate_rate", this->reactive_energy_inductive_consumed_intermediate_rate_);
  LOG_SENSOR("", "reactive_energy_inductive_consumed_off_peak_rate", this->reactive_energy_inductive_consumed_off_peak_rate_);
  LOG_SENSOR("", "reactive_energy_inductive_consumed_d_rate", this->reactive_energy_inductive_consumed_d_rate_);
  LOG_SENSOR("", "reactive_energy_inductive_generated_total", this->reactive_energy_inductive_generated_total_);
  LOG_SENSOR("", "reactive_energy_inductive_generated_peak_rate", this->reactive_energy_inductive_generated_peak_rate_);
  LOG_SENSOR("", "reactive_energy_inductive_generated_intermediate_rate", this->reactive_energy_inductive_generated_intermediate_rate_);
  LOG_SENSOR("", "reactive_energy_inductive_generated_off_peak_rate", this->reactive_energy_inductive_generated_off_peak_rate_);
  LOG_SENSOR("", "reactive_energy_inductive_generated_d_rate", this->reactive_energy_inductive_generated_d_rate_);
*/}

}  // namespace pima
}  // namespace esphome
