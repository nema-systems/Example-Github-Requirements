#ifndef BATTERY_MANAGER_H
#define BATTERY_MANAGER_H

#include "robot_state.h"

/**
 * @brief Updates the robot's battery usage based on speed, ambient temperature, and time.
 *
 * This function also handles conditions where battery capacity is exceeded.
 *
 * @param state The robot state struct to update.
 * @param timeDelta_s The time delta over which to calculate usage (in seconds).
 */
void updateBatteryUsage(RobotState& state, double timeDelta_s);

#endif // BATTERY_MANAGER_H
