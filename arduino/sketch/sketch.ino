#include "ScrapController.h"


// define all encoder pins
#define LEFT_ENCODER_INTERRUPT 3
#define LEFT_ENCODER_DIGITAL 4
#define RIGHT_ENCODER_INTERRUPT 2
#define RIGHT_ENCODER_DIGITAL 5

// define all motor pins
#define LEFT_MOTOR_PIN1 41
#define LEFT_MOTOR_PIN2 43
#define LEFT_MOTOR_PWM 45
#define RIGHT_MOTOR_PIN1 40
#define RIGHT_MOTOR_PIN2 42
#define RIGHT_MOTOR_PWM 44

#define FORWARD 2500
#define TURN 1250

// create encoders
ScrapEncoder leftEncoder(LEFT_ENCODER_INTERRUPT,LEFT_ENCODER_DIGITAL);
ScrapEncoder rightEncoder(RIGHT_ENCODER_INTERRUPT,RIGHT_ENCODER_DIGITAL);
// create motors
ScrapMotor leftMotor(LEFT_MOTOR_PIN1,LEFT_MOTOR_PIN2,LEFT_MOTOR_PWM);
ScrapMotor rightMotor(RIGHT_MOTOR_PIN1,RIGHT_MOTOR_PIN2,RIGHT_MOTOR_PWM);
// create dual controller
ScrapDualController dualControl(leftMotor,rightMotor,leftEncoder,rightEncoder);


// delay time
const int delayTime = 2;
// input parsing
const int maxValues = 2;
String command; // general command
String values[maxValues]; // stores values for command
String response; // response returned to main program


void setup() {
	// initialize encoders
	initEncoders();
	Serial.begin(115200);
	Serial.write(1);
	performSet(TURN,-TURN);
	/*leftMotor.setMotor(255);
	rightMotor.setMotor(255);
	delay(1000);
	leftMotor.stop();
	rightMotor.stop();*/
}

void loop () {
	// perform movement - moves arm to some goal coordinate
	performActions();

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
			else if (addTo <= maxValues) {
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
		for (int i = 0; i < maxValues; i++) {
			values[i] = "";
		}
	}
	// small delay
	delay(delayTime);
}


String interpretCommand() {
	String responseString = "n";  // string to be sent to main program
	String returnString = "";     // string received from a subfunction

	// determine what to do:
	
	// check if movement command - make sure length is okay
	if (command == "c") {
		//if (values[0].length() != 4 || values[1].length() != 4)
		//	return responseString;
		responseString = "1";
		returnString += String(leftEncoder.getCount());
		returnString += '|';
		returnString += String(rightEncoder.getCount());
	}/*
	else if (command == "sp") {
		if (values[0].length() != 4 || values[1].length() != 4)
			return responseString;
		responseString = "1";
		returnString = performSetPassive(values[0].toInt(),values[1].toInt());
	}
	else if (command == "r") {
		responseString = "1";
		returnString = performReset();
	}
	// check if mode-setting command
	// TODO: add functionality to STREAMOUT
	else if (command == "SYNCOUT") {
		responseString = "1";
	}
	else if (command == "STREAMOUT") {
		responseString = "1";
	}*/

	responseString += returnString;
	return responseString;
}

bool performSet(int left, int right) {
	dualControl.set(left,right);
	while(!dualControl.performMovement())
		delay(delayTime);
	return true;
}


bool performActions() {
	return dualControl.performMovement();
}













// initialize encoders
void initEncoders() {
	attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_INTERRUPT),leftEncoderFunc,CHANGE);
	attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_INTERRUPT),rightEncoderFunc,CHANGE);
}

void leftEncoderFunc() {
	if (digitalRead(LEFT_ENCODER_INTERRUPT) == digitalRead(LEFT_ENCODER_DIGITAL))
		leftEncoder.decrementCount();
	else
		leftEncoder.incrementCount();
}

void rightEncoderFunc() {
	if (digitalRead(RIGHT_ENCODER_INTERRUPT) == digitalRead(RIGHT_ENCODER_DIGITAL))
		rightEncoder.decrementCount();
	else
		rightEncoder.incrementCount();
}
