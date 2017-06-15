#include "TunnelRobot.h"


TunnelRobot::TunnelRobot() {
	
}

bool TunnelRobot::performActions() {
	return dualControl.performMovement();
}

bool TunnelRobot::performSet(int left, int right) {
	dualControl.set(left,right);
	// make sure the robot is within tolerance
	while (true) {
		// do movements to put robot within tolerence
		while(!dualControl.performMovement()) {
			delay(DELAYTIME);
		}
		// don't leave loop until motors have settled
		if (dualControl.checkIfNoSpeed())
			break;
	}
	return true;
}

String TunnelRobot::performForwardCommand() {
	dualControl.shiftCount();
	performSet(FORWARD,FORWARD);
	return "1";
}

String TunnelRobot::performForwardWithIRCommand() {
	String toReturn = "1";
	dualControl.shiftCount();
	dualControl.set(FORWARD,FORWARD);
	bool gotTooClose = false;
	// make sure the robot is within tolerance
	while (true) {
		// do movements to put robot within tolerence
		while(!dualControl.performMovement()) {
			if (!gotTooClose) {
				if (sensors.getAverageIR(FRONT_IR) >= CLOSE_TO_WALL) {
					gotTooClose = true;
					dualControl.set(dualControl.getCount());
					toReturn = "I";
				}
			}
			else
				delay(DELAYTIME);
		}
		if (dualControl.checkIfNoSpeed())
			break;
	}
	return toReturn;
}

String TunnelRobot::performBackwardCommand() {
	dualControl.shiftCount();
	performSet(-FORWARD,-FORWARD);
	return "1";
}

String TunnelRobot::performLeftTurnCommand() {
	dualControl.shiftCount();
	performSet(-TURN,TURN);
	return "1";
}

String TunnelRobot::performRightTurnCommand() {
	dualControl.shiftCount();
	performSet(TURN,-TURN);
	return "1";
}

String TunnelRobot::calibrateOnLeft() {
	return calibratePivot(LEFT_IR_L, LEFT_IR_R, LEFT_CALIBRATION_DIFF);
}

String TunnelRobot::calibrateOnRight() {
	return calibratePivot(RIGHT_IR_L, RIGHT_IR_R, RIGHT_CALIBRATION_DIFF);
}

String TunnelRobot::calibrateOnBack() {
	return calibratePivot(BACK_IR_L, BACK_IR_R, BACK_CALIBRATION_DIFF);
	// TODO go to right distance from wall and calibrate again
}

String TunnelRobot::calibratePivot(int left_ir, int right_ir, int calibration_diff) {
	int in_bound_count = 0;
	while (in_bound_count < IS_IN_BOUND_COUNT) {
		while (!doCalibrationMovement(left_ir,right_ir,calibration_diff)) {
			in_bound_count = 0;
			delay(DELAYTIME);
		}
		if (doCalibrationMovement(left_ir,right_ir,calibration_diff))
			in_bound_count += 1;
		else
			in_bound_count = 0;
		delay(DELAYTIME);
	}
	dualControl.stop();
	dualControl.set(0,0);
	dualControl.resetCount();
	dualControl.performMovement();
	return String(sensors.getDifferenceIR(left_ir,right_ir));
}

bool TunnelRobot::doCalibrationMovement(int left_ir, int right_ir, int calibration_diff) {
	int setSpeedTo = 200;
	if (sensors.getDifferenceIR(left_ir,right_ir) < (calibration_diff-IR_TOLERANCE)) {
		//dualControl.shiftCount();
		//dualControl.set(1,-1);
		//dualControl.performMovement();
		dualControl.speedControl1.setControlEnc(setSpeedTo);
		dualControl.speedControl2.setControlEnc(-setSpeedTo);
		dualControl.speedControl1.performMovement();
		dualControl.speedControl2.performMovement();
		return false;
	}
	else if (sensors.getDifferenceIR(left_ir,right_ir) > (calibration_diff+IR_TOLERANCE)) {
		//dualControl.shiftCount();
		//dualControl.set(-1,1);
		//dualControl.performMovement();
		dualControl.speedControl1.setControlEnc(-setSpeedTo);
		dualControl.speedControl2.setControlEnc(setSpeedTo);
		dualControl.speedControl1.performMovement();
		dualControl.speedControl2.performMovement();
		return false;
	}
	else {
		//dualControl.shiftCount();
		//dualControl.performMovement();
		dualControl.speedControl1.setControlEnc(0);
		dualControl.speedControl2.setControlEnc(0);
		dualControl.speedControl1.performMovement();
		dualControl.speedControl2.performMovement();
		return true;
	}
}


// get encoder values
String TunnelRobot::getEncoderValues() {
	String toReturn = "";
	toReturn += String(leftEncoder.getCount());
	toReturn += '|';
	toReturn += String(rightEncoder.getCount());
	return toReturn;
}

// encoder functions; should be triggered by interrupts
void TunnelRobot::leftEncoderFunc() {
	if (digitalRead(LEFT_ENCODER_INTERRUPT) == digitalRead(LEFT_ENCODER_DIGITAL))
		leftEncoder.decrementCount();
	else
		leftEncoder.incrementCount();
}

void TunnelRobot::rightEncoderFunc() {
	if (digitalRead(RIGHT_ENCODER_INTERRUPT) == digitalRead(RIGHT_ENCODER_DIGITAL))
		rightEncoder.decrementCount();
	else
		rightEncoder.incrementCount();
}

// button functions; should be triggered by interrupts
void TunnelRobot::goButtonFunc() {
	if (digitalRead(GO_BUTTON_PIN) == HIGH)
		buttons.pressGoButton();
}

void TunnelRobot::stopButtonFunc() {
	if (digitalRead(STOP_BUTTON_PIN) == HIGH)
		buttons.pressStopButton();
}
