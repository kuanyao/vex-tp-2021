#include "main.h"

using namespace std;

const int chass_power_threshold = 3;
const int arm_voltage = 127;

void set_cheassis_break_mode(const pros::motor_brake_mode_e_t mode) {
    chassis_left_front.set_brake_mode(mode);
    chassis_left_middle.set_brake_mode(mode);
    chassis_left_rear.set_brake_mode(mode);
    chassis_right_front.set_brake_mode(mode);
    chassis_right_middle.set_brake_mode(mode);
    chassis_right_rear.set_brake_mode(mode);
}

void chassis_drive(int left_power, int right_power) {

    // cout << "left: " << left_power << ", right: " << right_power << endl;

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
            arm_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
            armStage=1;
        } else {
            arm_front.move_absolute(-900,-arm_voltage);
            arm_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        }

    } else if (direction < 0) {
        testFrontArm = false;
        armStage=0;
        arm_front.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        arm_front.move_absolute(0,arm_voltage);
        
    } else if (!(direction > 0)&& testFrontArm && !(armStage == 0)){
        arm_front.move(0);
    }
}



void rear_arm_drive(int position) {

    if (position == 0) {
        arm_rear.move_absolute(-14,arm_voltage);
        arm_rear.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    } else if (position == 1) {
        arm_rear.move_absolute(675, arm_voltage);
        arm_rear.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    } else if (position == 2) {
        arm_rear.move_absolute(420, arm_voltage);
        arm_rear.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    } 

}
void rear_arm_preset(int position) {
    
}


void front_claw_drive(bool close) {
    if (close) {
        claw_front.set_value(1);
    } else {
        claw_front.set_value(0);
    }
}


void chassis_rotate(int speed, bool clockwise) {
    int speed_modifier = clockwise ? 1 : -1;
    chassis_drive(speed_modifier * speed, -1 * speed_modifier * speed);
}

int calculate_rotate_speed(int delta) {
    if (std::abs(delta) < 30) {
        return 50;
    }
    return 60;
}

int calculate_rotation_threshold(int degree) {
    degree = abs(degree);
    if (degree >= 90) {
        return 7;
    } else if (degree >= 60) {
        return 6;
    } else if (degree >= 45) {
        return 5;
    } else if (degree >= 30) {
        return 3;
    } 

    return 2;
}

void chassis_turn(double degree) {

    std::cout << "chassis turn " << degree << std::endl;
    set_cheassis_break_mode(pros::E_MOTOR_BRAKE_BRAKE);
    double chass_rotate_degree_threshold = calculate_rotation_threshold(degree);

    imu_sensor.tare_heading();
    double current_pos = imu_sensor.get_heading();
    double target_pos = (int)(current_pos + degree);
    double delta = degree;
    double last_delta = std::abs(delta);

    while (std::abs(delta) > chass_rotate_degree_threshold) {
        int speed = calculate_rotate_speed(delta);
        chassis_rotate(speed, delta > 0);
        pros::delay(20);
        
        current_pos = imu_sensor.get_heading();
        delta = (int)(target_pos - current_pos) % 360;
        cout << "target: " << target_pos 
            << ", current: " << current_pos
            << ", dalta: " << delta 
            << ", rotation: " << imu_sensor.get_rotation() 
            << ", last delta: " << last_delta << endl;
        // if (std::abs(delta) > (last_delta + chass_rotate_degree_threshold)) {
        //     break;
        // }
        last_delta = std::abs(delta);
    }
    cout << "break out from the loop" << endl;
    chassis_drive(0, 0);

    // pros::delay(500);
    // cout << "final!! target: " << target_pos 
    //     << ", current: " << imu_sensor.get_heading() 
    //     << ", dalta: " << delta 
    //     << ", rotation: " << imu_sensor.get_rotation() 
    //     << ", last delta: " << last_delta << endl;

}

double average_chassis_motor_position() {
    auto l_pos = chassis_left_front.get_position();
    auto r_pos = chassis_right_front.get_position(); 

    cout << "left position: " << l_pos
        << ", right position: " << r_pos
        << endl;

    return (l_pos + r_pos) / 2;
}

void chassis_drive_distance(int unit, int speed) {

    set_cheassis_break_mode(pros::E_MOTOR_BRAKE_BRAKE);
    int direction = speed > 0 ? -1 : 1;
    if(speed > 0) {
        int direction = 1;
    } else {
        direction = -1;
    }
    chassis_left_front.tare_position();
    chassis_right_front.tare_position();
    chassis_drive(30 * direction, 30 * direction);
    pros::delay(200);
    while (true) {
        chassis_drive(speed * direction, speed * direction);
        pros::delay(20);
        auto pos = average_chassis_motor_position();
        if ((abs(pos) - unit) >= 400) {
            break;
        }
    }
    while (true) {
        chassis_drive(30 * direction, 30 * direction);
        pros::delay(20);
        auto pos = average_chassis_motor_position();
        if (abs(pos) >= unit) {
            break;
        }
    }
    chassis_drive(0, 0);
}

void chassis_drive_until_distance(int stop_distance, int speed) {
    set_cheassis_break_mode(pros::E_MOTOR_BRAKE_BRAKE);
    auto distance = distance_sensor.get();
    chassis_drive(30, 30);
    pros::delay(200);
    while (distance > (stop_distance + 500)) {
        chassis_drive(speed, speed);
        pros::delay(20);

        distance = distance_sensor.get();
        auto confidence = distance_sensor.get_confidence();
        auto size = distance_sensor.get_object_size();

        cout << "distance: " << distance
            << ", confidence: " << confidence
            << ", size: " << size << endl;
    }
    while (distance > stop_distance) {
        chassis_drive(30, 30);
        pros::delay(20);
        distance = distance_sensor.get();
    }
    chassis_drive(0, 0);

    // pros::delay(500);
    // cout << "final distance: " << distance_sensor.get() << endl;
}

void chassis_drive_until_level() {

    const int pitch_threshold = 10;
    set_cheassis_break_mode(pros::E_MOTOR_BRAKE_BRAKE);
    bool is_chassis_on_bridge = false;
    bool is_chassis_leveled = false;
    double max_pitch = 0;
    while (!is_chassis_on_bridge) {
        chassis_drive(-80, -80);
        pros::delay(20);

        auto pitch = imu_sensor.get_pitch();
        max_pitch = max(max_pitch, abs(pitch));
        cout << "pitch: " << pitch << endl;
        if (abs(pitch) > pitch_threshold) {
            is_chassis_on_bridge = true;
            cout << "on the bridge now" << endl;
        }
    }
    pros::delay(700);
    while (!is_chassis_leveled) {
        // chassis_drive(-50, -50);
        pros::delay(20);
        auto pitch = imu_sensor.get_pitch();
        max_pitch = max(max_pitch, abs(pitch));
        cout << "pitch: " << pitch << ", max pitch: " << max_pitch << endl;
        if (abs(pitch) < max_pitch - 1) {
            is_chassis_leveled = true;
            cout << "on the bridge and leveled now." << endl;
        }
    }
    //chassis_drive(50, 50);
    //pros::delay(100);
    chassis_drive(0, 0);
    pros::delay(100);

    chassis_drive(50, 50);
    // pros::delay(200);

    chassis_drive(0, 0);
    
    pros::delay(1000);
    cout << "final pitch: " << imu_sensor.get_pitch() << endl;
    
    // auto pitch = imu_sensor.get_pitch();
    // while (abs(pitch) > pitch_threshold) {
    //     int direction = pitch > 0 ? 1 : -1;
    //     chassis_drive(direction * 40, direction * 40);
    //     pros::delay(100);
    //     chassis_drive(0, 0);
    //     pros::delay(100);
    //     cout << "pitch: " << pitch << endl;
    // }

    // chassis_drive(0, 0);
    
    // pros::delay(1000);
    // cout << "final pitch: " << imu_sensor.get_pitch() << endl;
    
}