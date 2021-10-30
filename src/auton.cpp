#include "main.h"

using namespace std;

void claw_move(int position, int direction) {
    auto arm_pos = arm_rear.get_position();
    while (abs(arm_pos - position) > 5) {
        arm_rear.move(90*direction);
        pros::delay(20);

        arm_pos = arm_rear.get_position();
        cout << "position: " << arm_pos << endl;
    }
}

void claw_move_time(int position, int time) {
    arm_rear.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    arm_rear.move_absolute(position,200);
    pros::delay(time);
    arm_rear.move(0);
}
void claw_stop() {
    arm_rear.move(0);
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

void auton_go_straight_and_get() {
    front_claw_drive(true);
    pros::delay(200);
    front_claw_drive(false);

    chassis_drive_until_distance(50, 90);
    front_claw_drive(true);

    chassis_drive_distance(1000, 60);
}

void auton_mobile_goals_right_first() {
    front_claw_drive(false);

    chassis_drive_until_distance(50, 90);
    front_claw_drive(true);

    rear_arm_drive(1);
    chassis_turn(102);
        
    chassis_drive_distance(500, 60);

    rear_arm_drive(2);

    chassis_drive(150,-150);
    pros::delay(700);
    chassis_drive(0,0);
    chassis_drive_distance(1400, -60);





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


    // pros::delay(2000);
}


void auton_mobile_goals_center_first() {

}