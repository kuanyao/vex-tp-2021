#include "main.h"

using namespace std;

void claw_move(int position) {
    auto arm_pos = arm_rear.get_position();
    while (abs(arm_pos - position) > 5) {
        arm_rear.move(90);
        pros::delay(20);

        arm_pos = arm_rear.get_position();
        cout << "position: " << arm_pos << endl;
    }
}

void auton_climb_bridge() {
    // arm_rear.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    // auto arm_pos = arm_rear.get_position();
    // while (abs(arm_pos - 585) > 5) {
    //     arm_rear.move(90);
    //     pros::delay(20);

    //     arm_pos = arm_rear.get_position();
    //     cout << "position: " << arm_pos << endl;
    // }

    // arm_rear.move(0);

    chassis_drive_until_level();
}

void auton_mobile_goals_right_first() {
    chassis_drive_until_distance(50, 90);
    front_claw_drive(true);

    chassis_drive_distance(1000, 60);
    
    // chassis_turn(102);

    // while (distance_not_met || arm_not_lower) {
    //     if (distance_not_met) {
    //         chassis_motor_run()
    //     }
    //     if (arm_not_lowered) {
    //         arm_motor_run()
    //     }
    //     delay(20);
    //     // check if condition met
    //     if (distance_met) {
    //         distance_not_met = false
    //         stop_chassi_motor();
    //     }
    //     if (arm_lowered) {
    //         arm_not_lowered = false;
    //         stop_arm_motor();
    //     }
    // }

    // // pros::delay(2000);
    // claw_move(630);
    // chassis_drive_distance(500, 60);

}


void auton_mobile_goals_center_first() {

}