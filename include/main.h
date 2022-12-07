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
const int CHASSIS_RIGHT_REAR    = 9;
const int CHASSIS_RIGHT_FRONT   = 8;
const int INTAKE_BACK  = 10;


const int INTAKE_FRONT   = 2;
const int CHASSIS_LEFT_FRONT    = 3;
const int CHASSIS_LEFT_REAR     = 1;




const int FLYWHEEL_RIGHT = 12;
const int FLYWHEEL_LEFT  = 11;


const std::uint8_t INDEXER = 'A';
const std::uint8_t PTO = 'B';
const std::uint8_t ENDGAME = 'C';

extern pros::Motor chassis_left_front;
extern pros::Motor chassis_left_rear;
extern pros::Motor chassis_right_front;
extern pros::Motor chassis_right_rear;

extern pros::Motor intake_front;
extern pros::Motor intake_back;

extern pros::Motor flywheel_left;
extern pros::Motor flywheel_right;

extern pros::Controller master;


extern pros::ADIDigitalOut pto;
extern pros::ADIDigitalOut indexer;
extern pros::ADIDigitalOut endgame;


extern int auton_selector;

#ifdef __cplusplus
extern "C" 
#endif
void chassis_drive(double lSpeed, double rSpeed, bool pto);
void flywheel_drive(int speed);
void intake_drive(int fSpeed, int bSpeed);
void pto_drive(bool extended);
void indexer_drive(bool extended);


void chassis_turn(double degree);
void chassis_drive_distance(int unit, int speed);
void chassis_drive_until_distance(int stop_distance, int speed);
void chassis_drive_until_distance_back(int stop_distance, int speed);
void chassis_drive_until_level();


#ifdef __cplusplus

#endif


#endif  // _PROS_MAIN_H_
