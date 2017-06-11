#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/*
DEFINITIONS BEGIN
*/

// define some constants
#define DELAYTIME 2
#define MAXVALUES 2
#define EMF_SAMPLE_COUNT 500
#define IR_AVERAGE_COUNT 20
#define IR_TOLERANCE 5
#define IS_IN_BOUND_COUNT 6

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

// define IR pin(s)
#define FRONT_IR A8
#define LEFT_IR_L A13
#define LEFT_IR_R A14
#define RIGHT_IR_L A9
#define RIGHT_IR_R A10
#define BACK_IR_L A12
#define BACK_IR_R A11

// defube button pins
#define GO_BUTTON_PIN 19
#define STOP_BUTTON_PIN 18

// define EMF pin
#define EMF_PIN A0

// define encoder distances
#define FORWARD 2500
#define TURN 1275
#define FAR 7000

// define IR distances
#define CLOSE_TO_WALL 200
#define OBSTACLE_NEARBY 200 // TODO

// define calibration IR differences
#define LEFT_CALIBRATION_DIFF 10
#define RIGHT_CALIBRATION_DIFF -15
#define BACK_CALIBRATION_DIFF -21

/*
DEFINITIONS END
*/

#endif
