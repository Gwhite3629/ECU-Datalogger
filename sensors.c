#include <stdbool.h>

struct sensor {
    char ID[20];
    unsigned long hash;
    int PID;
    bool time;
    int width;
    float poll;
};

struct sensor SENSORS[25] = {
{
    "SUPPORT1",             // USER-ID
    1687326579,             // Hash-value
    0x00,                   // PID
    0,                      // USER-TIME
    4,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "ENGINELOAD",           // USER-ID
    2131544636,             // Hash-value
    0x04,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "ENGINECOOLTEMP",       // USER-ID
    1134899263,             // Hash-value
    0x05,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "SHORTFUEL1",           // USER-ID
    564572243,              // Hash-value
    0x06,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "LONGFUEL1",            // USER-ID
    241045203,              // Hash-value
    0x07,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "SHORTFUEL2",           // USER-ID
    564572244,              // Hash-value
    0x08,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "LONGFUEL2",            // USER-ID
    241045204,              // Hash-value
    0x09,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "FUELPRESSURE",         // USER-ID
    1383857931,             // Hash-value
    0x0A,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "MANIFOLDPRESSURE",     // USER-ID
    1621717352,             // Hash-value
    0x0B,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "ENGINESPEED",          // USER-ID
    1629838061,             // Hash-value
    0x0C,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "VEHICLESPEED",         // USER-ID
    1834597014,             // Hash-value
    0x0D,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "TIMINGADVANCE",        // USER-ID
    1711530048,             // Hash-value
    0x0E,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "INTAKEPRESSURE",       // USER-ID
    1164823163,             // Hash-value
    0x0F,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "MASSAIRFLOW",          // USER-ID
    678517422,              // Hash-value
    0x10,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "THROTTLE",             // USER-ID
    1824148667,             // Hash-value
    0x11,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "OXSUPPORT",            // USER-ID
    1549904106,             // Hash-value
    0x13,                   // PID
    0,                      // USER-TIME
    1,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "OXYGEN1",              // USER-ID
    414250961,              // Hash-value
    0x14,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "OXYGEN2",              // USER-ID
    414250962,              // Hash-value
    0x15,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "OXYGEN3",              // USER-ID
    414250963,              // Hash-value
    0x16,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "OXYGEN4",              // USER-ID
    414250964,              // Hash-value
    0x17,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "OXYGEN5",              // USER-ID
    414250965,              // Hash-value
    0x18,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "OXYGEN6",              // USER-ID
    414250966,              // Hash-value
    0x19,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "OXYGEN7",              // USER-ID
    414250967,              // Hash-value
    0x1A,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "OXYGEN8",              // USER-ID
    414250968,              // Hash-value
    0x1B,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
},
{
    "RUNTIME",              // USER-ID
    2011191433,             // Hash-value
    0x1F,                   // PID
    0,                      // USER-TIME
    2,                      // Data Bytes
    0.0                     // USER-POLL
}
/*
struct sensor support_02 = {},
struct sensor D_MIL = {},
struct sensor fuel_rail_pressure = {},
struct sensor fuel_rail_gauge = {},
struct sensor oxygen_AB_V_1 = {},
struct sensor oxygen_AB_V_2 = {},
struct sensor oxygen_AB_V_3 = {},
struct sensor oxygen_AB_V_4 = {},
struct sensor oxygen_AB_V_5 = {},
struct sensor oxygen_AB_V_6 = {},
struct sensor oxygen_AB_V_7 = {},
struct sensor oxygen_AB_V_8 = {},
struct sensor EGR = {},
struct sensor EGR_error = {},
struct sensor evap_purge = {},
struct sensor fuel_tank_level = {},
struct sensor vapor_pressure = {},
struct sensor ABP = {},
struct sensor oxygen_AB_C_1 = {},
struct sensor oxygen_AB_C_2 = {},
struct sensor oxygen_AB_C_3 = {},
struct sensor oxygen_AB_C_4 = {},
struct sensor oxygen_AB_C_5 = {},
struct sensor oxygen_AB_C_6 = {},
struct sensor oxygen_AB_C_7 = {},
struct sensor oxygen_AB_C_8 = {},
struct sensor catalyst_temp_11 = {},
struct sensor catalyst_temp_21 = {},
struct sensor catalyst_temp_12 = {},
struct sensor catalyst_temp_22 = {},

struct sensor support_03 = {},
struct sensor control_module_volage = {},
struct sensor absolute_load_value = {},
struct sensor air_fuel_ratio = {},
struct sensor relative_throttle_pos = {},
struct sensor ambient_air_temp = {},
struct sensor throttle_pos_B = {},
struct sensor throttle_pos_C = {},
struct sensor accelerator_pos_D = {},
struct sensor accelerator_pos_E = {},
struct sensor accelerator_pos_F = {},
struct sensor throttle_actuator = {},
struct sensor MAX1 = {},
struct sensor MAX2 = {},
struct sensor fuel_type = {},
struct sensor ethanol_per = {},
struct sensor abs_evap_pressure = {},
struct sensor evap_pressure = {},
struct sensor short_oxygen_13 = {},
struct sensor long_oxygen_13 = {},
struct sensor short_oxygen_24 = {},
struct sensor long_oxygen_24 = {},
struct sensor fuel_rail_abs_pressure = {},
struct sensor relative_accelerator_pos = {},
struct sensor hybrid_bat_life = {},
struct sensor engine_oil_temp = {},
struct sensor fuel_injection_timing = {},
struct sensor engine_fuel_rate = {},

struct sensor support_04 = {},
struct sensor demand_engine_torque = {},
struct sensor actual_engine_torque = {},
struct sensor ref_engine_torque = {},
struct sensor engine_torque_data = {},
struct sensor mass_airflow_sensor = {},
struct sensor engine_coolant_temp2 = {},
struct sensor intake_air_temp = {},
struct sensor EGR_data = {},
struct sensor diesel_data = {},
struct sensor exhaust_circ_temp = {},
struct sensor throttle_data = {},
struct sensor fuel_control_sys = {},
struct sensor injection_pressure = {},
struct sensor turbo_pressure = {},
struct sensor boost_pressure = {},
struct sensor VGT_control = {},
struct sensor waste_gate = {},
struct sensor exhaust_pressure = {},
struct sensor turbo_rpm = {},
struct sensor turbo_temp1 = {},
struct sensor turbo_temp2 = {},
struct sensor charge_air_temp = {},
struct sensor EGT1 = {},
struct sensor EGT2 = {},
struct sensor DPF_diff = {},
struct sensor DPF = {},
struct sensor DPF_temp = {},
struct sensor engine_run_time = {},

struct sensor support_05 = {},
struct sensor AECD1 = {},
struct sensor AECD2 = {},
struct sensor NOx_sensor = {},
struct sensor PM_sensor = {},
struct sensor intake_abs_pressure = {},
struct sensor SCR = {},
struct sensor AECD_run1 = {},
struct sensor AECD_run2 = {},
struct sensor diesel_after = {},
struct sensor oxygen_wide = {},
struct sensor throttle_pos_G = {},
struct sensor engine_friction_torque = {},
struct sensor PM_sensor2 = {},
struct sensor WWHOBD1 = {},
struct sensor WWHOBD2 = {},
struct sensor fuel_system_control = {},
struct sensor WWHOBD3 = {},
struct sensor NOx_warning = {},
struct sensor exhaust_temp1 = {},
struct sensor exhaust_temp2 = {},
struct sensor hybrid_data = {},
struct sensor diesel_exhaust = {},
struct sensor oxygen_data = {},
struct sensor engine_fuel_rate2 = {},
struct sensor engine_exhaust_rate = {},
struct sensor fuel_percent_use = {},

struct sensor support_06 = {},
struct sensor NOx_corrected = {},
struct sensor cylinder_fuel_rate = {},
struct sensor system_vapor_pressure = {},
struct sensor transmission_gear = {},
struct sensor command_diesel_exhaust = {},
struct sensor odometer = {},
struct sensor NOx_concentration = {},
struct sensor NOx_corrected_conc = {},
struct sensor ABS_switch = {}
*/
};

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