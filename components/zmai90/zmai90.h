#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

// Funzione per convertire una stringa di byte in un float
float string_to_float(String payload, int payload_len, float divider);

// Funzione per convertire un numero decimale in una stringa esadecimale
char * decToHexa(int n);

namespace esphome {
namespace zmai_90 {

class zmai_90 :  public PollingComponent, public uart::UARTDevice {
 public:
  void set_voltage_sensor(sensor::Sensor *voltage_sensor) { voltage_sensor_ = voltage_sensor; }
  void set_current_sensor(sensor::Sensor *current_sensor) { current_sensor_ = current_sensor; }
  void set_frequency_sensor(sensor::Sensor *frequency_sensor) { frequency_sensor_ = frequency_sensor; }
  void set_active_power_sensor(sensor::Sensor *active_power_sensor) { active_power_sensor_ = active_power_sensor; }
  void set_reactive_power_sensor(sensor::Sensor *reactive_power_sensor) { reactive_power_sensor_ = reactive_power_sensor; }
  void set_apparent_power_sensor(sensor::Sensor *apparent_power_sensor) { apparent_power_sensor_ = apparent_power_sensor; }
  void set_power_factor_sensor(sensor::Sensor *power_factor_sensor) { power_factor_sensor_ = power_factor_sensor; }
  void set_consumed_energy_sensor(sensor::Sensor *consumed_energy_sensor) { consumed_energy_sensor_ = consumed_energy_sensor; }




  void setup() override;
  void loop() override;
  void update() override;


 private:
  int readline(int readch, char *buffer, int len);

  
 protected:
  sensor::Sensor *voltage_sensor_{nullptr};
  sensor::Sensor *current_sensor_{nullptr};
  sensor::Sensor *frequency_sensor_{nullptr};
  sensor::Sensor *active_power_sensor_{nullptr};
  sensor::Sensor *reactive_power_sensor_{nullptr};
  sensor::Sensor *apparent_power_sensor_{nullptr};
  sensor::Sensor *power_factor_sensor_{nullptr};
  sensor::Sensor *consumed_energy_sensor_{nullptr};
};
}
}

