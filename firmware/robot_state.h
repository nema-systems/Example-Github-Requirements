#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

/**
 * @brief A structure representing the robot's operational state.
 *
 * In real firmware, these fields might be updated from sensors, encoders,
 * or other hardware interfaces. Here, we keep it simple for demonstration.
 */
struct RobotState {
    double currentSpeed_m_s;       // Current linear speed (m/s)
    double distanceToObstacle_m;   // Distance to nearest obstacle in front (meters)
    double batteryUsage_kWh;       // Total used battery energy (kWh)
    double ambientTemp_C;          // Ambient temperature (°C)
    bool   emergencyStopActive;    // True if an immediate stop is triggered
};

#endif // ROBOT_STATE_H
