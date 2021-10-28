/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2021, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convienent for most student programmers.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS

#include "api.h"

/**
 * You should add more #includes here
 */
#include "okapi/api.hpp"
//#include "pros/api_legacy.h"

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
// using namespace pros;
// using namespace pros::literals;
using namespace okapi;

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

const int CHASSIS_LEFT_FRONT    = 11;
const int CHASSIS_LEFT_REAR     = 20;
const int CHASSIS_RIGHT_FRONT   = 1;
const int CHASSIS_RIGHT_REAR    = 10;

const int DISTANCE_SENSOR_FRONT_PORT = 2;
// const int DISTANCE_SENSOR_REAR_PORT = 2;
const int GYRO_SENSOR_PORT = 19;
const int COLOR_SENSOR_PORT = 12;
const int VISION_SENSOR_PORT = 13;

extern pros::Motor chassis_left_front;
extern pros::Motor chassis_left_rear;
extern pros::Motor chassis_right_front;
extern pros::Motor chassis_right_rear;

extern pros::Distance distance_sensor_front;
extern pros::Distance distance_sensor_rear;
extern pros::Optical opticial_sensor;
extern pros::Imu imu_sensor;
extern pros::Vision vision_sensor;

extern pros::Controller master;
extern pros::ADIDigitalIn bumper_switch;

#ifdef __cplusplus
extern "C" {
#endif
void chassis_drive(int x, int y);
void front_arm_drive(int d);
void rear_arm_drive(int d);
void front_claw_drive(bool c);
void chassis_turn(double degree);
void chassis_drive_distance(int unit, int speed);
void chassis_drive_until_distance(int stop_distance, int speed);
void chassis_drive_until_level();
#ifdef __cplusplus
}
#endif


#endif  // _PROS_MAIN_H_
