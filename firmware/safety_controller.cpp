#include "safety_controller.h"
#include <iostream>
#include <cmath>

// @nema:get:https://app.nemasystems.io/nema-public-demo/default/requirements-demo/data/10
static constexpr double SAFETY_STOP_DISTANCE_FT = 0.5;
static constexpr double SAFETY_STOP_DISTANCE_M = SAFETY_STOP_DISTANCE_FT * 0.3048;

// @nema:get:https://app.nemasystems.io/nema-public-demo/default/requirements-demo/data/4
static constexpr double MAX_ROBOT_SPEED_MS = 2;

/**
 * @brief Calculates approximate braking distance with a fixed deceleration.
 *        Formula: distance = v^2 / (2*a).
 */
static double calculateBrakingDistance(double speed_m_s) {
    // Example deceleration of 2.5 m/s^2
    constexpr double DECELERATION = 2.5;
    return (speed_m_s * speed_m_s) / (2.0 * DECELERATION);
}

void checkSafetyStop(RobotState& state) {
    // Braking distance from current speed
    double brakingDist = calculateBrakingDistance(state.currentSpeed_m_s);

    // Include the safety stop distance margin (PARAM-LINK: #19 => 0.5 m)
    double totalNeededDist = brakingDist + SAFETY_STOP_DISTANCE_M;

    if (state.distanceToObstacle_m < totalNeededDist) {
        std::cout << "[WARN] Obstacle too close for safe stop!\n";
        state.emergencyStopActive = true;
        state.currentSpeed_m_s = 0.0; // immediate stop
    }
}

void enforceSpeedLimit(RobotState& state) {
    // Check if robot speed exceeds maximum speed (PARAM-LINK: #13 => 2.0 m/s)
    if (state.currentSpeed_m_s > MAX_ROBOT_SPEED_MS) {
        std::cout << "[INFO] Speed exceeded limit (" << state.currentSpeed_m_s
                  << " m/s). Limiting to " << MAX_ROBOT_SPEED_MS << " m/s.\n";
        state.currentSpeed_m_s = MAX_ROBOT_SPEED_MS;
    }
}
