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

void front_arm_drive(int direction) {
    if (direction > 0) {
        arm_front.move(-arm_voltage);
    } else if (direction < 0) {
        arm_front.move(arm_voltage);
    } else {
        arm_front.move(0);
    }
}

void rear_arm_drive(int direction) {
    if (direction > 0) {
        arm_rear.move(-arm_voltage);
    } else if (direction < 0) {
        arm_rear.move(arm_voltage);
    } else {
        arm_rear.move(0);
    }
}