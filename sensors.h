#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <stdbool.h>

struct sensor {
    char ID[20];
    unsigned long hash;
    int PID;
    bool time;
    int width;
    float poll;
};

struct sensor support_01 = {
    "SUPPORT1",             // USER-ID
    1687326579,             // Hash-value
    0x00,                   // PID
    0,                      // USER-TIME
    4,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor engine_load = {
    "ENGINELOAD",           // USER-ID
    4279028283,             // Hash-value
    0x04,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor engine_coolant_temp = {
    "ENGINECOOLTEMP",       // USER-ID
    3282382910,             // Hash-value
    0x05,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor short_fuel_trim_1 = {
    "SHORTFUEL1",           // USER-ID
    2712055890,             // Hash-value
    0x06,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor long_fuel_trim_1 = {
    "LONGFUEL1",            // USER-ID
    2388528850,             // Hash-value
    0x07,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor short_fuel_trim_2 = {
    "SHORTFUEL2",           // USER-ID
    2712055891,             // Hash-value
    0x08,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor long_fuel_trim_2 = {
    "LONGFUEL2",            // USER-ID
    2388528851,             // Hash-value
    0x09,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor fuel_pressure = {
    "FUELPRESSURE",         // USER-ID
    3531341578,             // Hash-value
    0x0A,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor manifold_pressure = {
    "MANIFOLDPRESSURE",     // USER-ID
    1621717352,             // Hash-value
    0x0B,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor engine_speed = {
    "ENGINESPEED",          // USER-ID
    3777321708,             // Hash-value
    0x0C,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor vehicle_speed = {
    "VEHICLESPEED",         // USER-ID
    1834597014,             // Hash-value
    0x0D,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor timing_advance = {
    "TIMINGADVANCE",        // USER-ID
    3859013695,             // Hash-value
    0x0E,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor intake_pressure = {
    "INTAKEPRESSURE",       // USER-ID
    3312306810,             // Hash-value
    0x0F,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor mass_airflow = {
    "MASSAIRFLOW",          // USER-ID
    2826001069,             // Hash-value
    0x10,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor throttle = {
    "THROTTLE",             // USER-ID
    1824148667,             // Hash-value
    0x11,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor oxygen_supp = {
    "OXSUPPORT",            // USER-ID
    3697387753,             // Hash-value
    0x13,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor oxygen_1 = {
    "OXYGEN1",              // USER-ID
    2561734608,             // Hash-value
    0x14,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor oxygen_2 = {
    "OXYGEN2",              // USER-ID
    2561734609,             // Hash-value
    0x15,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor oxygen_3 = {
    "OXYGEN3",              // USER-ID
    2561734610,             // Hash-value
    0x16,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor oxygen_4 = {
    "OXYGEN4",              // USER-ID
    2561734611,             // Hash-value
    0x17,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor oxygen_5 = {
    "OXYGEN5",              // USER-ID
    2561734612,             // Hash-value
    0x18,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor oxygen_6 = {
    "OXYGEN6",              // USER-ID
    2561734613,             // Hash-value
    0x19,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor oxygen_7 = {
    "OXYGEN7",              // USER-ID
    2561734614,             // Hash-value
    0x1A,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor oxygen_8 = {
    "OXYGEN8",              // USER-ID
    2561734615,             // Hash-value
    0x1B,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
};
struct sensor run_time = {
    "RUNTIME",              // USER-ID
    2011191433,             // Hash-value
    0x1F,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
};

struct sensor support_02 = {};
struct sensor D_MIL = {};
struct sensor fuel_rail_pressure = {};
struct sensor fuel_rail_gauge = {};
struct sensor oxygen_AB_V_1 = {};
struct sensor oxygen_AB_V_2 = {};
struct sensor oxygen_AB_V_3 = {};
struct sensor oxygen_AB_V_4 = {};
struct sensor oxygen_AB_V_5 = {};
struct sensor oxygen_AB_V_6 = {};
struct sensor oxygen_AB_V_7 = {};
struct sensor oxygen_AB_V_8 = {};
struct sensor EGR = {};
struct sensor EGR_error = {};
struct sensor evap_purge = {};
struct sensor fuel_tank_level = {};
struct sensor vapor_pressure = {};
struct sensor ABP = {};
struct sensor oxygen_AB_C_1 = {};
struct sensor oxygen_AB_C_2 = {};
struct sensor oxygen_AB_C_3 = {};
struct sensor oxygen_AB_C_4 = {};
struct sensor oxygen_AB_C_5 = {};
struct sensor oxygen_AB_C_6 = {};
struct sensor oxygen_AB_C_7 = {};
struct sensor oxygen_AB_C_8 = {};
struct sensor catalyst_temp_11 = {};
struct sensor catalyst_temp_21 = {};
struct sensor catalyst_temp_12 = {};
struct sensor catalyst_temp_22 = {};

struct sensor support_03 = {};
struct sensor control_module_volage = {};
struct sensor absolute_load_value = {};
struct sensor air_fuel_ratio = {};
struct sensor relative_throttle_pos = {};
struct sensor ambient_air_temp = {};
struct sensor throttle_pos_B = {};
struct sensor throttle_pos_C = {};
struct sensor accelerator_pos_D = {};
struct sensor accelerator_pos_E = {};
struct sensor accelerator_pos_F = {};
struct sensor throttle_actuator = {};
struct sensor MAX1 = {};
struct sensor MAX2 = {};
struct sensor fuel_type = {};
struct sensor ethanol_per = {};
struct sensor abs_evap_pressure = {};
struct sensor evap_pressure = {};
struct sensor short_oxygen_13 = {};
struct sensor long_oxygen_13 = {};
struct sensor short_oxygen_24 = {};
struct sensor long_oxygen_24 = {};
struct sensor fuel_rail_abs_pressure = {};
struct sensor relative_accelerator_pos = {};
struct sensor hybrid_bat_life = {};
struct sensor engine_oil_temp = {};
struct sensor fuel_injection_timing = {};
struct sensor engine_fuel_rate = {};

struct sensor support_04 = {};
struct sensor demand_engine_torque = {};
struct sensor actual_engine_torque = {};
struct sensor ref_engine_torque = {};
struct sensor engine_torque_data = {};
struct sensor mass_airflow_sensor = {};
struct sensor engine_coolant_temp2 = {};
struct sensor intake_air_temp = {};
struct sensor EGR_data = {};
struct sensor diesel_data = {};
struct sensor exhaust_circ_temp = {};
struct sensor throttle_data = {};
struct sensor fuel_control_sys = {};
struct sensor injection_pressure = {};
struct sensor turbo_pressure = {};
struct sensor boost_pressure = {};
struct sensor VGT_control = {};
struct sensor waste_gate = {};
struct sensor exhaust_pressure = {};
struct sensor turbo_rpm = {};
struct sensor turbo_temp1 = {};
struct sensor turbo_temp2 = {};
struct sensor charge_air_temp = {};
struct sensor EGT1 = {};
struct sensor EGT2 = {};
struct sensor DPF_diff = {};
struct sensor DPF = {};
struct sensor DPF_temp = {};
struct sensor engine_run_time = {};

struct sensor support_05 = {};
struct sensor AECD1 = {};
struct sensor AECD2 = {};
struct sensor NOx_sensor = {};
struct sensor PM_sensor = {};
struct sensor intake_abs_pressure = {};
struct sensor SCR = {};
struct sensor AECD_run1 = {};
struct sensor AECD_run2 = {};
struct sensor diesel_after = {};
struct sensor oxygen_wide = {};
struct sensor throttle_pos_G = {};
struct sensor engine_friction_torque = {};
struct sensor PM_sensor2 = {};
struct sensor WWHOBD1 = {};
struct sensor WWHOBD2 = {};
struct sensor fuel_system_control = {};
struct sensor WWHOBD3 = {};
struct sensor NOx_warning = {};
struct sensor exhaust_temp1 = {};
struct sensor exhaust_temp2 = {};
struct sensor hybrid_data = {};
struct sensor diesel_exhaust = {};
struct sensor oxygen_data = {};
struct sensor engine_fuel_rate2 = {};
struct sensor engine_exhaust_rate = {};
struct sensor fuel_percent_use = {};

struct sensor support_06 = {};
struct sensor NOx_corrected = {};
struct sensor cylinder_fuel_rate = {};
struct sensor system_vapor_pressure = {};
struct sensor transmission_gear = {};
struct sensor command_diesel_exhaust = {};
struct sensor odometer = {};
struct sensor NOx_concentration = {};
struct sensor NOx_corrected_conc = {};
struct sensor ABS_switch = {};

/* QUERY ALIGNMENT (ID = 7DFh)
 * BYTE NUMBER:
 * 0: # of additional data bytes (2)
 * 1: Service
 * 2: PID code
 * 3: Unused
 * 4: Unused
 * 5: Unused
 * 6: Unused
 * 7: Unused
*/

/* RESPONSE ALIGNMENT (ID = 7E8h)
 * BYTE NUMBER:
 * 0: # of additional data bytes (3-6)
 * 1: Service
 * 2: PID code
 * 3: param byte 0
 * 4: param byte 1
 * 5: param byte 2
 * 6: param byte 3
 * 7: Unused
 */

#endif // _SENSORS_H_