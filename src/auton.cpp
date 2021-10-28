#include "main.h"

using namespace std;

void auton_climb_bridge() {
    arm_rear.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    auto arm_pos = arm_rear.get_position();
    while (abs(arm_pos - 630) > 5) {
        arm_rear.move(90);
        pros::delay(20);

        arm_pos = arm_rear.get_position();
        cout << "position: " << arm_pos << endl;
    }

    arm_rear.move(0);

    chassis_drive_until_level();
}