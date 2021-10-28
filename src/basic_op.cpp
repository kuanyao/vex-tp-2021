#include "main.h"

const int chass_power_threshold = 3;
const int arm_voltage = 127;

void chassis_drive(int left_power, int right_power) {

    if (abs(left_power) < chass_power_threshold) {
        left_power = 0;
    }
    if (abs(right_power) < chass_power_threshold) {
        right_power = 0;
    }

    chassis_left_front.move(left_power);
    chassis_left_middle.move(left_power);
    chassis_left_rear.move(left_power);
    chassis_right_front.move(right_power);
    chassis_right_middle.move(right_power);
    chassis_right_rear.move(right_power);
}
bool testFrontArm = true;
int armStage = 0;
void front_arm_drive(int direction) {
    if (direction > 0) {
        testFrontArm = true;
        if(armStage == 0) {
            arm_front.move_absolute(-620, - arm_voltage);
            arm_front.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            armStage=1;
        } else {
            arm_front.move_absolute(-900,-arm_voltage);
            arm_front.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        }

    } else if (direction < 0) {
        testFrontArm = false;
        armStage=0;
        arm_front.move_absolute(0,arm_voltage);
        arm_front.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    } else if (!(direction > 0)&& testFrontArm && !(armStage == 0)){
        arm_front.move(0);
    }
}

void rear_arm_drive(int position) {

    if (position == 0) {
        arm_rear.move_absolute(-20,arm_voltage);
        arm_rear.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    } else if (position == 1) {
        arm_rear.move_absolute(670, arm_voltage);
        arm_rear.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    } else if (position == 2) {
        arm_rear.move_absolute(300, arm_voltage);
        arm_rear.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    } 

}

void front_claw_drive(bool close) {
    if (close) {
        claw_front.set_value(1);
    } else {
        claw_front.set_value(0);
    }
}