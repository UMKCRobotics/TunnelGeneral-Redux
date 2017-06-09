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

// calibrate on sides TODO
String TunnelRobot::calibrateOnLeft() {
	return "1";
}

String TunnelRobot::calibrateOnRight() {
	return "1";
}

String TunnelRobot::calibrateOnBack() {
	return "1";
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
