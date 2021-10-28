#include "main.h"

using namespace std;

const int chass_power_threshold = 3;
const int arm_voltage = 127;
const double chass_rotate_degree_threshold = 2;

void chassis_drive(int left_power, int right_power) {

    if (abs(left_power) < chass_power_threshold) {
        left_power = 0;
    }
    if (abs(right_power) < chass_power_threshold) {
        right_power = 0;
    }

    chassis_left_front.move(left_power);
    chassis_left_rear.move(left_power);
    chassis_right_front.move(right_power);
    chassis_right_rear.move(right_power);
}

double average_chassis_motor_position() {
    auto l_pos = chassis_left_front.get_position();
    auto r_pos = chassis_right_front.get_position(); 
    return (l_pos + r_pos) / 2;
}

void chassis_drive_distance(int unit, int speed) {

    int direction = speed > 0 ? -1 : 1;
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
    
    auto distance = distance_sensor_front.get();
    chassis_drive(-30, -30);
    pros::delay(200);
    while (distance > (stop_distance + 300)) {
        chassis_drive(-speed, -speed);
        pros::delay(20);

        distance = distance_sensor_front.get();
        auto confidence = distance_sensor_front.get_confidence();
        auto size = distance_sensor_front.get_object_size();

        cout << "distance: " << distance
            << ", confidence: " << confidence
            << ", size: " << size << endl;
    }
    while (distance > stop_distance) {
        chassis_drive(-30, -30);
        pros::delay(20);
        distance = distance_sensor_front.get();
    }
    chassis_drive(0, 0);
}

void chassis_drive_until_level() {
    bool is_chassis_on_bridge = false;
    bool is_chassis_leveled = false;
    while (!is_chassis_on_bridge) {
        chassis_drive(-90, -90);
        pros::delay(20);

        auto roll = imu_sensor.get_roll();
        if (abs(roll) > 5) {
            is_chassis_on_bridge = true;
        }
    }
    pros::delay(1000);
    while (!is_chassis_leveled) {
        chassis_drive(-30, -30);
        pros::delay(20);
        auto roll = imu_sensor.get_roll();
        if (abs(roll) < 5) {
            is_chassis_leveled = true;
        }
    }
    //chassis_drive(50, 50);
    //pros::delay(100);
    chassis_drive(0, 0);
}


void chassis_rotate(int speed, bool clockwise) {
    int speed_modifier = clockwise ? 1 : -1;
    chassis_drive(speed_modifier * speed, -1 * speed_modifier * speed);
}

int calculate_rotate_speed(int delta) {
    // if (std::abs(delta) < 10) {
    //     return 10;
    // }
    // if (std::abs(delta) < 30) {
    //     return 20;
    // }
    return 30;
}

void chassis_turn(double degree) {

    std::cout << "chassis turn " << degree << std::endl;

    double current_pos = imu_sensor.get_heading();
    double target_pos = (int)(current_pos + degree);
    double delta = degree;
    double last_delta = std::abs(delta);

    while (std::abs(delta) > chass_rotate_degree_threshold) {
        int speed = calculate_rotate_speed(delta);
        chassis_rotate(speed, delta < 0);
        pros::delay(10);
        
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
}