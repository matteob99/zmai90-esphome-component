import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    CONF_ID,
    UNIT_WATT,
    UNIT_VOLT,
    UNIT_AMPERE,
    UNIT_PERCENT,
    UNIT_HERTZ,
    UNIT_WATT_HOURS,
    ICON_FLASH,
    ICON_CURRENT_AC,
    ICON_POWER,
    ICON_GAUGE,
    DEVICE_CLASS_ENERGY,
    DEVICE_CLASS_VOLTAGE,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_FREQUENCY,
    DEVICE_CLASS_POWER_FACTOR,
    DEVICE_CLASS_REACTIVE_POWER,
    DEVICE_CLASS_APPARENT_POWER,
    STATE_CLASS_TOTAL_INCREASING

)

zmai_90_ns = cg.esphome_ns.namespace("zmai_90")
ZMAI90 = zmai_90_ns.class_("zmai_90", cg.Component, uart.UARTDevice)

CONF_ZMAI90_ID = "zmai_90_id"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(ZMAI90),
            cv.Optional("voltage"): sensor.sensor_schema(
                unit_of_measurement=UNIT_VOLT,
                icon=ICON_FLASH,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_VOLTAGE,
            ),
            cv.Optional("current"): sensor.sensor_schema(
                unit_of_measurement=UNIT_AMPERE,
                icon=ICON_CURRENT_AC,
                accuracy_decimals=3,
                device_class=DEVICE_CLASS_CURRENT,
            ),
            cv.Optional("frequency"): sensor.sensor_schema(
                unit_of_measurement=UNIT_HERTZ,
                icon=ICON_GAUGE,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_FREQUENCY,
            ),
            cv.Optional("active_power"): sensor.sensor_schema(
                unit_of_measurement=UNIT_WATT,
                icon=ICON_POWER,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_ENERGY,
            ),
            cv.Optional("reactive_power"): sensor.sensor_schema(
                unit_of_measurement=UNIT_WATT,
                icon=ICON_POWER,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_REACTIVE_POWER,
            ),
            cv.Optional("apparent_power"): sensor.sensor_schema(
                unit_of_measurement=UNIT_WATT,
                icon=ICON_POWER,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_APPARENT_POWER,
            ),
            cv.Optional("power_factor"): sensor.sensor_schema(
                unit_of_measurement=UNIT_PERCENT,
                accuracy_decimals=1,
                icon=ICON_GAUGE,
                device_class=DEVICE_CLASS_POWER_FACTOR
            ),
            cv.Optional("consumed_energy"): sensor.sensor_schema(
                unit_of_measurement=UNIT_WATT_HOURS,
                icon=ICON_FLASH,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_ENERGY,
                state_class=STATE_CLASS_TOTAL_INCREASING
            ),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.polling_component_schema("10s"))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if "voltage" in config:
        sens = await sensor.new_sensor(config["voltage"])
        cg.add(var.set_voltage_sensor(sens))

    if "current" in config:
        sens = await sensor.new_sensor(config["current"])
        cg.add(var.set_current_sensor(sens))

    if "frequency" in config:
        sens = await sensor.new_sensor(config["frequency"])
        cg.add(var.set_frequency_sensor(sens))

    if "active_power" in config:
        sens = await sensor.new_sensor(config["active_power"])
        cg.add(var.set_active_power_sensor(sens))

    if "reactive_power" in config:
        sens = await sensor.new_sensor(config["reactive_power"])
        cg.add(var.set_reactive_power_sensor(sens))

    if "apparent_power" in config:
        sens = await sensor.new_sensor(config["apparent_power"])
        cg.add(var.set_apparent_power_sensor(sens))

    if "power_factor" in config:
        sens = await sensor.new_sensor(config["power_factor"])
        cg.add(var.set_power_factor_sensor(sens))

    if "consumed_energy" in config:
        sens = await sensor.new_sensor(config["consumed_energy"])
        cg.add(var.set_consumed_energy_sensor(sens))
