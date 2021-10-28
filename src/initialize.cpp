#include "main.h"
#include "api.h"
#include "okapi/api.hpp"

pros::Motor chassis_left_front(CHASSIS_LEFT_FRONT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_left_middle(CHASSIS_LEFT_MIDDLE, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_left_rear(CHASSIS_LEFT_REAR, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_right_front(CHASSIS_RIGHT_FRONT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_right_middle(CHASSIS_RIGHT_MIDDLE, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_right_rear(CHASSIS_RIGHT_REAR, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor arm_front(FRONT_ARM, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor arm_rear(REAR_ARM, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::ADIDigitalOut claw_front(CLAW_FRONT, false);
pros::Imu imu_sensor(IMU_SENSOR_PORT);
pros::Distance distance_sensor(DISTANCE_SENSOR_PORT_FRONT);
// auto lg = {chassis_left_front, chassis_left_middle, chassis_left_rear};

// okapi::MotorGroup chassis_mg_left(lg);
int auton_selector = 0;