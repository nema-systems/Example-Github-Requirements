#include <iostream>
#include "robot_state.h"
#include "battery_manager.h"
#include "safety_controller.h"

int main() {
    // Initialize a sample robot state
    RobotState robot = {
        /* currentSpeed_m_s */      1.5,
        /* distanceToObstacle_m */  3.0,
        /* batteryUsage_kWh */      0.0,
        /* ambientTemp_C */         20.0,
        /* emergencyStopActive */   false
    };

    std::cout << "=== Robot Firmware Simulation Start ===\n";

    // Simulate 10 time-steps of 1 second each
    for (int tick = 0; tick < 10; ++tick) {
        std::cout << "\n--- TICK " << tick << " ---\n";

        // Enforce max speed, then update battery usage over 1 second
        enforceSpeedLimit(robot);
        updateBatteryUsage(robot, 1.0);

        // Check for safety stop
        checkSafetyStop(robot);

        // Print status
        std::cout << "[STATE] Speed: " << robot.currentSpeed_m_s << " m/s, "
                  << "ObstacleDist: " << robot.distanceToObstacle_m << " m, "
                  << "BatteryUsed: " << robot.batteryUsage_kWh << " kWh, "
                  << "Temp: " << robot.ambientTemp_C << " C, "
                  << "E-Stop: " << (robot.emergencyStopActive ? "YES" : "NO")
                  << "\n";

        // If E-Stop triggered, stop sim
        if (robot.emergencyStopActive) {
            std::cout << "[SYSTEM] Emergency stop triggered! Halting.\n";
            break;
        }

        // Fake scenario: each tick, obstacle moves 0.4 m closer
        robot.distanceToObstacle_m -= 0.4;

        // Fake scenario: operator tries to increase speed by 0.3 m/s each tick
        robot.currentSpeed_m_s += 0.3;
    }

    std::cout << "\n=== Robot Firmware Simulation End ===\n";
    return 0;
}
