#ifndef TUNNELROBOT_H
#define TUNNELROBOT_H
#include "Arduino.h"
#include "Definitions.h"
#include "ScrapController.h"
#include "TunnelButtons.h"
#include "TunnelSensors.h"

// class for main TunnelRobot functions
class TunnelRobot {
	private:
		// encoders
		ScrapEncoder leftEncoder = ScrapEncoder(LEFT_ENCODER_INTERRUPT,LEFT_ENCODER_DIGITAL);
		ScrapEncoder rightEncoder = ScrapEncoder(RIGHT_ENCODER_INTERRUPT,RIGHT_ENCODER_DIGITAL);
		// motors
		ScrapMotor leftMotor = ScrapMotor(LEFT_MOTOR_PIN1,LEFT_MOTOR_PIN2,LEFT_MOTOR_PWM);
		ScrapMotor rightMotor = ScrapMotor(RIGHT_MOTOR_PIN1,RIGHT_MOTOR_PIN2,RIGHT_MOTOR_PWM);
		// dual motor controller
		ScrapDualController dualControl = ScrapDualController(leftMotor,rightMotor,leftEncoder,rightEncoder);
	public:
		TunnelButtons buttons = TunnelButtons();
		TunnelSensors sensors = TunnelSensors();
		TunnelRobot();
		bool performActions();
		bool performSet(int left, int right); // set encoder goal
		// movement functions
		String performForwardCommand();
		String performForwardWithIRCommand();
		String performBackwardCommand();
		String performLeftTurnCommand();
		String performRightTurnCommand();
		// calibrate functions
		String calibrateOnLeft();
		String calibrateOnRight();
		String calibrateOnBack();
		// button functions
		void goButtonFunc();
		void stopButtonFunc();
		// display functions
		void markOnGrid(int index) {};
		void displayDigit(int digit) {};
		// IR functions
		long getAverageIR(int IRpin);
		// encoder functions
		String getEncoderValues();
		void leftEncoderFunc();
		void rightEncoderFunc();

};

#endif
