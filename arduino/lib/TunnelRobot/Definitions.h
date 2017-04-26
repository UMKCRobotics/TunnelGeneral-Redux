#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/*
DEFINITIONS BEGIN
*/

// define some constants
#define DELAYTIME 2
#define MAXVALUES 2

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

// define encoder distances
#define FORWARD 2500
#define TURN 1275
#define FAR 7000
// define IR distances
#define CLOSE_TO_WALL 200

/*
DEFINITIONS END
*/

#endif