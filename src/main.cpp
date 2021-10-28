#include "main.h"

using namespace std;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void on_right_button() {
}

void on_left_button() {

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
void competition_initialize() {}

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
void autonomous() {}

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
	int posTwo = -1;
	int frontClawPos = -1;
	while (true) {

		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		bool isRaisingFrontArm = master.get_digital(DIGITAL_R1) == 1;
		bool isDroppingFrontArm = master.get_digital(DIGITAL_R2) == 1;

		bool midArmPos = master.get_digital_new_press(DIGITAL_B) == 1;
		bool isDroppingRearArm = master.get_digital(DIGITAL_L2) == 1;

		bool frontClaw = master.get_digital_new_press(DIGITAL_L1) == 1;

		bool testing_button_pressed = master.get_digital_new_press(DIGITAL_Y) == 1;

		chassis_drive(left, right);

		if (isRaisingFrontArm) {
			front_arm_drive(1);
		} else if (isDroppingFrontArm) {
			front_arm_drive(-1);
		} else {
			front_arm_drive(0);
		}


		if(midArmPos) {
			posTwo=posTwo*-1;
		} 
		if (posTwo==1) {
			rear_arm_drive(2);
		} else if (isDroppingRearArm) {
			rear_arm_drive(1);
		} else if (!isDroppingRearArm) {
			rear_arm_drive(0);
		}

		if(frontClaw) {
			frontClawPos*=-1;
		}
		if (frontClawPos==1) {
			front_claw_drive(true);
		} else if(frontClawPos==-1) {
			front_claw_drive(false);
		}

		if (testing_button_pressed) {
			// chassis_drive_distance(1000, 50);
			// chassis_turn(-90);
			// chassis_drive_until_distance(50, 90);
			chassis_drive_until_level();
		}

		pros::delay(20);
	}
}
