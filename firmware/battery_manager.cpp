#include "battery_manager.h"
#include <algorithm>
#include <iostream>

// @nema:get:https://app.nemasystems.io/nema-public-demo/default/requirements-demo/data/8
static constexpr double MAX_OPERATING_TEMP_F = 45.0;

// @nema:get:https://app.nemasystems.io/nema-public-demo/default/requirements-demo/data/7
static constexpr double MIN_OPERATING_TEMP_F = -10.0;

// @nema:get:https://app.nemasystems.io/nema-public-demo/default/requirements-demo/data/2
static constexpr double BATTERY_CAPACITY_KWH = 15.0;

static constexpr double MAX_OPERATING_TEMP_C = (MAX_OPERATING_TEMP_F - 32.0) * 5.0 / 9.0;
static constexpr double MIN_OPERATING_TEMP_C = (MIN_OPERATING_TEMP_F - 32.0) * 5.0 / 9.0;


/**
 * @brief Helper function to apply temperature-based derating of battery usage.
 *
 * If temperature is outside [-10, 45] °C, we increase consumption by 20%.
 */
static double applyTemperaturePenalty(double consumptionNow, double ambientTempC) {
    // If out of safe range (PARAM-LINK #16 & #17), increase usage 20%
    if (ambientTempC < MIN_OPERATING_TEMP_C || ambientTempC > MAX_OPERATING_TEMP_C) {
        return consumptionNow * 1.20;
    }
    return consumptionNow;
}

void updateBatteryUsage(RobotState& state, double timeDelta_s) {
    // Baseline consumption rate example:
    //   - 0.005 kWh/s at full speed (2 m/s).
    //   - If speed < 2.0, scale consumption proportionally.
    static constexpr double BASE_CONSUMPTION_AT_FULL_SPEED = 0.005; // kWh/s

    double speedFactor = std::min(state.currentSpeed_m_s / MAX_ROBOT_SPEED_MS, 1.0);
    double consumptionPerSecond = BASE_CONSUMPTION_AT_FULL_SPEED * speedFactor;

    // Apply any penalty if temperature is too low or too high
    consumptionPerSecond = applyTemperaturePenalty(consumptionPerSecond, state.ambientTemp_C);

    double deltaUsage = consumptionPerSecond * timeDelta_s;
    state.batteryUsage_kWh += deltaUsage;

    // Check capacity (PARAM-LINK: #11 => 15 kWh)
    if (state.batteryUsage_kWh >= BATTERY_CAPACITY_KWH) {
        std::cout << "[ALERT] Battery capacity exhausted!\n";
        state.batteryUsage_kWh = BATTERY_CAPACITY_KWH; // clamp
        state.currentSpeed_m_s = 0.0;  // forced stop or shut down
        state.emergencyStopActive = true;
    }
}
