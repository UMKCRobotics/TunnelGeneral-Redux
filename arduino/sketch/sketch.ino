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
	// initialize serial
	Serial.begin(115200);
	Serial.write(1);
	robot.performSet(0,0);
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
	if (command == "CC") {
		//if (values[0].length() != 4 || values[1].length() != 4)
		//	return responseString;
		responseString = "1";
		returnString += robot.getEncoderValues();
	}
	else if (command == "f") {
		responseString = "1";
		returnString += robot.performForwardCommand();
	}
	else if (command == "fi") {
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

// initialize interrupt functions
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
