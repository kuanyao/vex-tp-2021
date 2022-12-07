#include "main.h"

using namespace std;

const int chass_power_threshold = 3;
const int arm_voltage = 127;

void set_cheassis_break_mode(const pros::motor_brake_mode_e_t mode) {
    chassis_left_front.set_brake_mode(mode);
    chassis_left_rear.set_brake_mode(mode);
    chassis_right_front.set_brake_mode(mode);
    chassis_right_rear.set_brake_mode(mode);
}

void chassis_drive(double lSpeed, double rSpeed, bool pto) {
    if(pto) {
        chassis_left_front.move(-lSpeed);
        chassis_left_rear.move(-lSpeed);
        chassis_right_front.move(-rSpeed);
        chassis_right_rear.move(-rSpeed);
    } else {
        chassis_left_front.move(-lSpeed);
        chassis_left_rear.move(-lSpeed);
        intake_front.move(-lSpeed);

        chassis_right_front.move(-rSpeed);
        chassis_right_rear.move(-rSpeed);
        intake_back.move(rSpeed);
    }
}

void flywheel_drive(int speed) {
    flywheel_right.move_voltage(-speed);
    flywheel_left.move_voltage(speed);
}



void intake_drive(int fSpeed, int bSpeed) {
    pto.set_value(true);
    intake_front.move(fSpeed);
    intake_back.move(bSpeed);
}
void pto_drive(bool extended) {
    pto.set_value(extended);
}
void indexer_drive(bool extended) {
    indexer.set_value(extended);
}

