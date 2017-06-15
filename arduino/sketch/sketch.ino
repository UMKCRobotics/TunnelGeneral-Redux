#include "TunnelRobot.h"

// robot control
TunnelRobot robot = TunnelRobot();
// serial command vars
String command; // general command
String values[MAXVALUES]; // stores values for command
String response; // response returned to main program


void setup() {
	// initialize encoders
	initEncoders();
	// initialize buttons
	initButtons();
	// initialize serial
	Serial.begin(57600);
	Serial.write(1);
	robot.performSet(0,0);
	// initialize display
	robot.display.init();
	//robot.display.turnOnReadyLight();
}

void loop () {
	// perform movement - keeps motors at a set encoder goal
	robot.performActions();

	// if something in serial, parse it
	if(Serial.available()){

		int addTo = 0; // 0 for command, 1 for value

		while (Serial.available() > 0)
		{
			char readIn = (char)Serial.read();
			if (readIn == '\n') {
				break;
			}
			else if (readIn == '|') {
				addTo += 1;
				continue;
			}
			// add to command if no | reached yet
			if (addTo == 0) {
				command += readIn;
			}
			// add to proper value in array
			else if (addTo <= MAXVALUES) {
				values[addTo-1] += readIn;
			}
			// if values exceed max, then stop listening to prevent problems
			else {
				break;
			}
		}
		//clear anything remaining in serial
		while (Serial.available() > 0) {
			Serial.read();
		}
		response = interpretCommand();
		Serial.println(response); //sends response with \n at the end
		// empty out command and value strings
		command = "";
		response = "";
		for (int i = 0; i < MAXVALUES; i++) {
			values[i] = "";
		}
	}
	// small delay
	delay(DELAYTIME);
}


String interpretCommand() {
	String responseString = "n";  // string to be sent to main program
	String returnString = "";     // string received from a subfunction

	// determine what to do:
	
	// check if movement command - make sure length is okay

	// check if button command
	if (command == "B") {
		if (values[0] == "G") {
			responseString = "1";
			returnString += robot.buttons.hasGoBeenPressed();
		}
		else if (values[0] == "S") {
			responseString = "1";
			returnString += robot.buttons.hasStopBeenPressed();
		}
	}
	// check if sensor command
	else if (command == "S") {
		if (values[0] == "E") {
			responseString = "1";
			returnString += String(robot.sensors.getReadingEMF());
		}
	}
	// check if calibration command
	else if (command == "C") {
		if (values[0] == "L") {
			responseString = "1";
			returnString += robot.calibrateOnLeft();
		}
		else if (values[0] == "R") {
			responseString = "1";
			returnString += robot.calibrateOnRight();
		}
		else if (values[0] == "B") {
			responseString = "1";
			returnString += robot.calibrateOnBack();
		}
	}
	// check if 8x8 command
	else if (command == "D") {
		if (values[0] == "R") {
			responseString = "1";
			robot.display.turnOnReadyLight();
		}
		else if (values[1].length() == 2) {
			if (values[0] == "T") {
				responseString = "1";
				robot.display.setToTunnel(values[1].toInt());
			}
			else if (values[0] == "D") {
				responseString = "1";
				robot.display.setToDeadend(values[1].toInt());
			}
			else if (values[0] == "E") {
				responseString = "1";
				robot.display.setToEmpty(values[1].toInt());
			}
		}
	}	
	else if (command == "f") {
		responseString = "1";
		returnString += robot.performForwardCommand();
	}
	else if (command == "F") {
		responseString = "1";
		returnString += robot.performForwardWithIRCommand();
	}
	else if (command == "l") {
		responseString = "1";
		returnString += robot.performLeftTurnCommand();
	}
	else if (command == "r") {
		responseString = "1";
		returnString += robot.performRightTurnCommand();
	}
	else if (command == "b") {
		responseString = "1";
		returnString += robot.performBackwardCommand();
	}
	else if (command == "I") {
		responseString = "1";
		returnString += String(analogRead(FRONT_IR));
	}
	else if (command == "~") {
		responseString = "1";
		returnString += robot.getEncoderValues();
	}
	// protocol commands
	else if (command == "SYNCOUT") {
		responseString = "1";
	}
	else if (command == "STREAMOUT") {
		responseString = "1";
	}


	responseString += returnString;
	return responseString;
}

// initialize encoder interrupt functions
void initEncoders() {
	attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_INTERRUPT),leftEncoderFunc,CHANGE);
	attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_INTERRUPT),rightEncoderFunc,CHANGE);
}

void leftEncoderFunc() {
	robot.leftEncoderFunc();
}

void rightEncoderFunc() {
	robot.rightEncoderFunc();
}

// initialize button interrupt functions
void initButtons() {
	attachInterrupt(digitalPinToInterrupt(GO_BUTTON_PIN), goButtonFunc, CHANGE);
	attachInterrupt(digitalPinToInterrupt(STOP_BUTTON_PIN), stopButtonFunc, CHANGE);
}

void goButtonFunc() {
	robot.goButtonFunc();
}

void stopButtonFunc() {
	robot.stopButtonFunc();
}
