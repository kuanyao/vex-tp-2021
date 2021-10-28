#include "main.h"
#include "api.h"
#include "okapi/api.hpp"

pros::Motor chassis_left_front(CHASSIS_LEFT_FRONT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_left_rear(CHASSIS_LEFT_REAR, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_right_front(CHASSIS_RIGHT_FRONT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_right_rear(CHASSIS_RIGHT_REAR, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Distance distance_sensor_front(DISTANCE_SENSOR_FRONT_PORT);
pros::Optical opticial_sensor(COLOR_SENSOR_PORT);
pros::Imu imu_sensor(GYRO_SENSOR_PORT);
pros::Vision vision_sensor(VISION_SENSOR_PORT);

pros::ADIDigitalIn bumper_switch('A');