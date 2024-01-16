import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    CONF_CURRENT,
    CONF_ENERGY,
    CONF_ID,
    CONF_VOLTAGE,
    CONF_FREQUENCY,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_ENERGY,
    DEVICE_CLASS_VOLTAGE,
    DEVICE_CLASS_FREQUENCY,
    STATE_CLASS_MEASUREMENT,
    UNIT_AMPERE,
    UNIT_KILOWATT_HOURS,
    UNIT_KILOVOLT_AMPS_REACTIVE_HOURS,
    UNIT_VOLT,
    UNIT_WATT,
    UNIT_HERTZ,
    STATE_CLASS_TOTAL_INCREASING,
)

# Not yet in esphome
CONF_REACTIVE_ENERGY = "reactive_energy"
DEVICE_CLASS_REACTIVE_ENERGY = "reactive_energy"

DEPENDENCIES = ["uart"]

pima_ns = cg.esphome_ns.namespace("pima")
PIMA = pima_ns.class_("PIMA", uart.UARTDevice, cg.Component)

# PIMA has a ton of repetition. Handle a bit of it more efficiently
def phase_measurement(prefix, sensor_schema):
    return {
        prefix+"_1": sensor_schema,
        prefix+"_2": sensor_schema,
        prefix+"_3": sensor_schema,
    }

def rated_measurement(prefix, sensor_schema):
    return {
        prefix+"_consumed_total": sensor_schema,
        prefix+"_consumed_peak_rate": sensor_schema,
        prefix+"_consumed_intermediate_rate": sensor_schema,
        prefix+"_consumed_off_peak_rate": sensor_schema,
        prefix+"_consumed_d_rate": sensor_schema,
        prefix+"_generated_total": sensor_schema,
        prefix+"_generated_peak_rate": sensor_schema,
        prefix+"_generated_intermediate_rate": sensor_schema,
        prefix+"_generated_off_peak_rate": sensor_schema,
        prefix+"_generated_d_rate": sensor_schema,
    }

procedural_schema_fragment = {
    **phase_measurement(CONF_VOLTAGE, sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
    )),
    **phase_measurement(CONF_CURRENT, sensor.sensor_schema(
        unit_of_measurement=UNIT_AMPERE,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_CURRENT,
        state_class=STATE_CLASS_MEASUREMENT,
    )),
    **rated_measurement(CONF_ENERGY, sensor.sensor_schema(
        unit_of_measurement=UNIT_KILOWATT_HOURS,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_ENERGY,
        state_class=STATE_CLASS_TOTAL_INCREASING,
    )),
    **rated_measurement(CONF_REACTIVE_ENERGY+"_capacitive", sensor.sensor_schema(
        unit_of_measurement=UNIT_KILOVOLT_AMPS_REACTIVE_HOURS,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_REACTIVE_ENERGY,
        state_class=STATE_CLASS_TOTAL_INCREASING,
    )),
    **rated_measurement(CONF_REACTIVE_ENERGY+"_inductive", sensor.sensor_schema(
        unit_of_measurement=UNIT_KILOVOLT_AMPS_REACTIVE_HOURS,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_REACTIVE_ENERGY,
        state_class=STATE_CLASS_TOTAL_INCREASING,
    )),
}

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(PIMA),
            **{ cv.Optional(key) : value for (key,value) in procedural_schema_fragment.items() },
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    for key in list(procedural_schema_fragment.keys()):
        if key_config := config.get(key):
            sens = await sensor.new_sensor(key_config)
            cg.add(var.__getattr__("set_"+key+"_sensor").__call__(sens))

