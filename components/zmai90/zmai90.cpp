#include "esphome.h"

namespace esphome {
    namespace zmai_90 {

        float zmai_90::extractFloatData(int position, float divider, size_t data_size) {
            if (position + data_size > resp_data.size())
                return 0;
            int data;
            memcpy(&data, resp_data.data() + position, data_size);
            return data / divider;
        }

        void zmai_90::setup() {
            // This will be called by App.setup()
            
            // sent command:
            // [0xfe, 0x01, 0x0f, 0x08, 0x00, 0x00, 0x00, 0x1c]
            // Byte 0: Head byte, must be 0xFE
            // Byte 1..2: Mem Addr 0x01, 0x0f start address of data
            // Byte 3: Amount of Words (4 bytes) to read
            // Byte 4..6: Reserved bytes, must be 0x00 0x00 0x00
            // Byte 7: "checksum", calculated by doing sum of all bytes, inverting it and adding 0x33
            req_command = {0xfe, 0x01, 0x0f, 0x08, 0x00, 0x00, 0x00, 0x1c};
        }
        void zmai_90::update() {
            while (available()) read(); // clean up uart buffer
            resp_data.fill(0); // clean up response buffer
            write_array(req_command.data(), req_command.size()); // write command
        }

        void zmai_90::loop() {
            if (available() < EXPECTED_RESP_LEN)
                return;

            read_array(resp_data.data(), EXPECTED_RESP_LEN);
            // recv data:
            // Byte 0: head byte, must be 0xFE
            // Byte 1: 

            if (this->voltage_sensor_)
                this->voltage_sensor_->publish_state(extractFloatData(3, 10.0));
            if (this->current_sensor_)
                this->current_sensor_->publish_state(extractFloatData(7, 10000.0));
            if (this->frequency_sensor_)
                this->frequency_sensor_->publish_state(extractFloatData(11, 100.0));
            if (this->active_power_sensor_)
                this->active_power_sensor_->publish_state(extractFloatData(15, 100.0));
            if (this->reactive_power_sensor_)
                this->reactive_power_sensor_->publish_state(extractFloatData(19, 100.0));
            if (this->apparent_power_sensor_)
                this->apparent_power_sensor_->publish_state(extractFloatData(23, 100.0));
            if (this->power_factor_sensor_)
                this->power_factor_sensor_->publish_state(extractFloatData(27, 10.0));
            if (this->consumed_energy_sensor_)
                this->consumed_energy_sensor_->publish_state(extractFloatData(31, 100.0));
        }
    }
}
