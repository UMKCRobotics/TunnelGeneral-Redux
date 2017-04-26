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

long TunnelRobot::getAverageIR(int IRpin) {
	int max_count = 10;
	long sum = 0;
	for (int i = 0; i < max_count; i++) {
		sum += analogRead(IRpin);
	}
	return sum/max_count;
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
				if (getAverageIR(FRONT_IR) >= CLOSE_TO_WALL) {
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

//get EMF reading
long TunnelRobot::getReadingEMF() {
	int count = 0; // non-zero samples taken
	long sum = 0; // sum of squares of samples
	long average = 0;
	int reading; // used to store a sample
	for (int i = 0; i < 500; i++) {
		reading = analogRead(EMF_PIN);
		// only care about non-zero readings
		if (reading != 0) {
			count++;
			// add the square of read value
			sum += pow(reading,2);
		}
	}
	// get average of readings, if count is not zero
	if (count > 0)
		average = sum/count;
	return average;
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
