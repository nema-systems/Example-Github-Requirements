#ifndef SAFETY_CONTROLLER_H
#define SAFETY_CONTROLLER_H

#include "robot_state.h"

/**
 * @brief Checks whether the robot must enforce an emergency stop due to obstacles.
 *
 * @param state Robot state (speed, distance, etc.). Modified if E-Stop is triggered.
 */
void checkSafetyStop(RobotState& state);

/**
 * @brief Ensures the robot's speed does not exceed the maximum allowed speed.
 *
 * @param state Robot state (speed might be clamped).
 */
void enforceSpeedLimit(RobotState& state);

#endif // SAFETY_CONTROLLER_H
