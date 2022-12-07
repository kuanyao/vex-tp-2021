#include "main.h"
#include "api.h"
#include "okapi/api.hpp"

pros::Motor chassis_left_front(CHASSIS_LEFT_FRONT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_left_rear(CHASSIS_LEFT_REAR, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_right_front(CHASSIS_RIGHT_FRONT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor chassis_right_rear(CHASSIS_RIGHT_REAR, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);


pros::Motor intake_front(INTAKE_FRONT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake_back(INTAKE_BACK, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor flywheel_left(FLYWHEEL_LEFT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor flywheel_right(FLYWHEEL_RIGHT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Controller master(pros::E_CONTROLLER_MASTER);


pros::ADIDigitalOut pto('B');
pros::ADIDigitalOut indexer('A');
pros::ADIDigitalOut endgame('C');


// okapi::MotorGroup chassis_mg_left(lg);
int auton_selector = 0;