#pragma once

#include "esphome/core/component.h"
#include "esphome/core/datatypes.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "pima_frame_decoder.h"

namespace esphome {
namespace pima {

class PIMA : public Component, public uart::UARTDevice {
public:
  struct PIMA_labels_t {
    uint8_t scope, index;
    double scale;
    const char *label;
    sensor::Sensor* PIMA::* sensor;
  };

protected:
  static const PIMA_labels_t PIMA_labels[];
  PimaFrameDecoder frame;

public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  // Generated by helper.py:
protected:
  sensor::Sensor *voltage_1_{nullptr};
  sensor::Sensor *voltage_2_{nullptr};
  sensor::Sensor *voltage_3_{nullptr};
  sensor::Sensor *current_1_{nullptr};
  sensor::Sensor *current_2_{nullptr};
  sensor::Sensor *current_3_{nullptr};
  sensor::Sensor *energy_consumed_total_{nullptr};
  sensor::Sensor *energy_consumed_peak_rate_{nullptr};
  sensor::Sensor *energy_consumed_intermediate_rate_{nullptr};
  sensor::Sensor *energy_consumed_off_peak_rate_{nullptr};
  sensor::Sensor *energy_consumed_d_rate_{nullptr};
  sensor::Sensor *energy_generated_total_{nullptr};
  sensor::Sensor *energy_generated_peak_rate_{nullptr};
  sensor::Sensor *energy_generated_intermediate_rate_{nullptr};
  sensor::Sensor *energy_generated_off_peak_rate_{nullptr};
  sensor::Sensor *energy_generated_d_rate_{nullptr};
  sensor::Sensor *reactive_energy_capacitive_consumed_total_{nullptr};
  sensor::Sensor *reactive_energy_capacitive_consumed_peak_rate_{nullptr};
  sensor::Sensor *reactive_energy_capacitive_consumed_intermediate_rate_{nullptr};
  sensor::Sensor *reactive_energy_capacitive_consumed_off_peak_rate_{nullptr};
  sensor::Sensor *reactive_energy_capacitive_consumed_d_rate_{nullptr};
  sensor::Sensor *reactive_energy_capacitive_generated_total_{nullptr};
  sensor::Sensor *reactive_energy_capacitive_generated_peak_rate_{nullptr};
  sensor::Sensor *reactive_energy_capacitive_generated_intermediate_rate_{nullptr};
  sensor::Sensor *reactive_energy_capacitive_generated_off_peak_rate_{nullptr};
  sensor::Sensor *reactive_energy_capacitive_generated_d_rate_{nullptr};
  sensor::Sensor *reactive_energy_inductive_consumed_total_{nullptr};
  sensor::Sensor *reactive_energy_inductive_consumed_peak_rate_{nullptr};
  sensor::Sensor *reactive_energy_inductive_consumed_intermediate_rate_{nullptr};
  sensor::Sensor *reactive_energy_inductive_consumed_off_peak_rate_{nullptr};
  sensor::Sensor *reactive_energy_inductive_consumed_d_rate_{nullptr};
  sensor::Sensor *reactive_energy_inductive_generated_total_{nullptr};
  sensor::Sensor *reactive_energy_inductive_generated_peak_rate_{nullptr};
  sensor::Sensor *reactive_energy_inductive_generated_intermediate_rate_{nullptr};
  sensor::Sensor *reactive_energy_inductive_generated_off_peak_rate_{nullptr};
  sensor::Sensor *reactive_energy_inductive_generated_d_rate_{nullptr};
public:
  void set_voltage_1_sensor(sensor::Sensor *s) { voltage_1_ = s; }
  void set_voltage_2_sensor(sensor::Sensor *s) { voltage_2_ = s; }
  void set_voltage_3_sensor(sensor::Sensor *s) { voltage_3_ = s; }
  void set_current_1_sensor(sensor::Sensor *s) { current_1_ = s; }
  void set_current_2_sensor(sensor::Sensor *s) { current_2_ = s; }
  void set_current_3_sensor(sensor::Sensor *s) { current_3_ = s; }
  void set_energy_consumed_total_sensor(sensor::Sensor *s) { energy_consumed_total_ = s; }
  void set_energy_consumed_peak_rate_sensor(sensor::Sensor *s) { energy_consumed_peak_rate_ = s; }
  void set_energy_consumed_intermediate_rate_sensor(sensor::Sensor *s) { energy_consumed_intermediate_rate_ = s; }
  void set_energy_consumed_off_peak_rate_sensor(sensor::Sensor *s) { energy_consumed_off_peak_rate_ = s; }
  void set_energy_consumed_d_rate_sensor(sensor::Sensor *s) { energy_consumed_d_rate_ = s; }
  void set_energy_generated_total_sensor(sensor::Sensor *s) { energy_generated_total_ = s; }
  void set_energy_generated_peak_rate_sensor(sensor::Sensor *s) { energy_generated_peak_rate_ = s; }
  void set_energy_generated_intermediate_rate_sensor(sensor::Sensor *s) { energy_generated_intermediate_rate_ = s; }
  void set_energy_generated_off_peak_rate_sensor(sensor::Sensor *s) { energy_generated_off_peak_rate_ = s; }
  void set_energy_generated_d_rate_sensor(sensor::Sensor *s) { energy_generated_d_rate_ = s; }
  void set_reactive_energy_capacitive_consumed_total_sensor(sensor::Sensor *s) { reactive_energy_capacitive_consumed_total_ = s; }
  void set_reactive_energy_capacitive_consumed_peak_rate_sensor(sensor::Sensor *s) { reactive_energy_capacitive_consumed_peak_rate_ = s; }
  void set_reactive_energy_capacitive_consumed_intermediate_rate_sensor(sensor::Sensor *s) { reactive_energy_capacitive_consumed_intermediate_rate_ = s; }
  void set_reactive_energy_capacitive_consumed_off_peak_rate_sensor(sensor::Sensor *s) { reactive_energy_capacitive_consumed_off_peak_rate_ = s; }
  void set_reactive_energy_capacitive_consumed_d_rate_sensor(sensor::Sensor *s) { reactive_energy_capacitive_consumed_d_rate_ = s; }
  void set_reactive_energy_capacitive_generated_total_sensor(sensor::Sensor *s) { reactive_energy_capacitive_generated_total_ = s; }
  void set_reactive_energy_capacitive_generated_peak_rate_sensor(sensor::Sensor *s) { reactive_energy_capacitive_generated_peak_rate_ = s; }
  void set_reactive_energy_capacitive_generated_intermediate_rate_sensor(sensor::Sensor *s) { reactive_energy_capacitive_generated_intermediate_rate_ = s; }
  void set_reactive_energy_capacitive_generated_off_peak_rate_sensor(sensor::Sensor *s) { reactive_energy_capacitive_generated_off_peak_rate_ = s; }
  void set_reactive_energy_capacitive_generated_d_rate_sensor(sensor::Sensor *s) { reactive_energy_capacitive_generated_d_rate_ = s; }
  void set_reactive_energy_inductive_consumed_total_sensor(sensor::Sensor *s) { reactive_energy_inductive_consumed_total_ = s; }
  void set_reactive_energy_inductive_consumed_peak_rate_sensor(sensor::Sensor *s) { reactive_energy_inductive_consumed_peak_rate_ = s; }
  void set_reactive_energy_inductive_consumed_intermediate_rate_sensor(sensor::Sensor *s) { reactive_energy_inductive_consumed_intermediate_rate_ = s; }
  void set_reactive_energy_inductive_consumed_off_peak_rate_sensor(sensor::Sensor *s) { reactive_energy_inductive_consumed_off_peak_rate_ = s; }
  void set_reactive_energy_inductive_consumed_d_rate_sensor(sensor::Sensor *s) { reactive_energy_inductive_consumed_d_rate_ = s; }
  void set_reactive_energy_inductive_generated_total_sensor(sensor::Sensor *s) { reactive_energy_inductive_generated_total_ = s; }
  void set_reactive_energy_inductive_generated_peak_rate_sensor(sensor::Sensor *s) { reactive_energy_inductive_generated_peak_rate_ = s; }
  void set_reactive_energy_inductive_generated_intermediate_rate_sensor(sensor::Sensor *s) { reactive_energy_inductive_generated_intermediate_rate_ = s; }
  void set_reactive_energy_inductive_generated_off_peak_rate_sensor(sensor::Sensor *s) { reactive_energy_inductive_generated_off_peak_rate_ = s; }
  void set_reactive_energy_inductive_generated_d_rate_sensor(sensor::Sensor *s) { reactive_energy_inductive_generated_d_rate_ = s; }
};

} // namespace pima

} // namespace esphome


