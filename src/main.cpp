#include "main.h"

using namespace std;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	// auton_selector = (auton_selector + 1) % 4;
	if (auton_selector == 0) {
		pros::lcd::set_text(1, "Auton Selection Cleared.");
	} else if (auton_selector == 1) {
		pros::lcd::set_text(1, "Straight and Get");
	} else if (auton_selector == 2) {
		pros::lcd::set_text(1, "Mobile goal right first!");
	} else if (auton_selector == 3) {
		pros::lcd::set_text(1, "Mobile goal center first!");
	}
}

void on_right_button() {
	auton_selector = 1;
	pros::lcd::set_text(1, "Auton Climbing the bridge");
}

void on_left_button() {
	auton_selector = 1;
	pros::lcd::set_text(1, "Auton get mobile goals!");
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn0_cb(on_left_button);
	pros::lcd::register_btn2_cb(on_right_button);

	// cout << "resetting imu sensor ..." << endl;
	// imu_sensor.reset();
	// cout << "imu sensor finished calibrating..." << endl;
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	pto.set_value(false);
	endgame.set_value(false);
	indexer.set_value(false);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	auton_selector = 2;

	if (auton_selector == 1) {

	} else if (auton_selector == 2) {
		chassis_drive(600,600, false);
		pros::delay(100);
		chassis_drive(0,0, false);
	} else if (auton_selector == 3) {
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	int flywheel = -1;
	bool ptoChassis = true;
	while (true) {
		if (master.get_digital(DIGITAL_B) == 1) {
			ptoChassis = true;
			pto_drive(true);
		} 
		if(master.get_digital(DIGITAL_R2) == 1) {
			indexer_drive(true);
		} else {
			indexer_drive(false);
		}



		if(master.get_digital_new_press(DIGITAL_R1)) {
			flywheel*=-1;
		} 
		if(flywheel == 1) {
			flywheel_drive(-12000);
		} else if(flywheel == -1) {
			flywheel_drive(0);
		}


		if(master.get_digital(DIGITAL_L1)) {
			ptoChassis = false;
			pto_drive(false);
			intake_front.move_voltage(-12000);
			intake_back.move_voltage(12000);
		} else if(master.get_digital(DIGITAL_L2)) {;;
			ptoChassis = false;
			pto_drive(false);
			intake_front.move_voltage(12000);
			intake_back.move_voltage(-12000);
		} else if(master.get_digital(DIGITAL_UP)) {
			ptoChassis = false;
			pto_drive(false);
			intake_front.move(-600);
		} else if(!ptoChassis || !master.get_digital(DIGITAL_UP)) {
			intake_front.move(0);
			intake_back.move(0);
		}

		if(master.get_digital(DIGITAL_RIGHT) && master.get_digital(DIGITAL_LEFT)) {
			endgame.set_value(true);
		}


		

		chassis_drive((200/127)*master.get_analog(ANALOG_LEFT_Y), (200/127)*master.get_analog(ANALOG_RIGHT_Y), !ptoChassis);
	}
}
