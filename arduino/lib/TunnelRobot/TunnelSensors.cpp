#include "TunnelSensors.h"


//get EMF reading
long TunnelSensors::getReadingEMF() {
	int count = 0; // non-zero samples taken
	long sum = 0; // sum of squares of samples
	long average = 0;
	int reading; // used to store a sample
	for (int i = 0; i < EMF_SAMPLE_COUNT; i++) {
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

//get average reading of single IR
long TunnelSensors::getAverageIR(int IRpin) {
	long sum = 0;
	for (int i = 0; i < IR_AVERAGE_COUNT; i++) {
		sum += analogRead(IRpin);
	}
	return sum/IR_AVERAGE_COUNT;
}

long TunnelSensors::getAverageIRdual(int IRpinLeft, int IRpinRight) {
	long sumLeft = 0;
	long sumRight = 0;
	for (int i = 0; i < IR_AVERAGE_COUNT; i++) {
		sumLeft += analogRead(IRpinLeft);
		sumRight += analogRead(IRpinRight);
	}
	return ((sumLeft/IR_AVERAGE_COUNT)+(sumRight/IR_AVERAGE_COUNT))/2;
}

long TunnelSensors::getDifferenceIR(int IRpinLeft,  int IRpinRight) {
	long sumLeft = 0;
	long sumRight = 0;
	for (int i = 0; i < IR_AVERAGE_COUNT; i++) {
		sumLeft += analogRead(IRpinLeft);
		sumRight += analogRead(IRpinRight);
	}
	return (sumLeft/IR_AVERAGE_COUNT)-(sumRight/IR_AVERAGE_COUNT);
}

String TunnelSensors::getObstacleReport() {
	String report = "";
	// right side
	report += ((getAverageIR(RIGHT_IR_L) > OBSTACLE_NEARBY || getAverageIR(RIGHT_IR_R) > OBSTACLE_NEARBY) ? "1" : "0");
	// front side
	report += ((getAverageIR(FRONT_IR) > OBSTACLE_NEARBY) ? "1" : "0");
	// left side
	report += ((getAverageIR(LEFT_IR_L) > OBSTACLE_NEARBY || getAverageIR(LEFT_IR_R) > OBSTACLE_NEARBY) ? "1" : "0");
	// back side
	report += ((getAverageIR(BACK_IR_L) > OBSTACLE_NEARBY || getAverageIR(BACK_IR_R) > OBSTACLE_NEARBY) ? "1" : "0");
	return report;
}
