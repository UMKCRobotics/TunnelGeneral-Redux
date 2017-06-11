#include "TunnelSensors.h"


//get EMF reading
long TunnelSensors::getReadingEMF() {
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

//get average reading of single IR
long TunnelSensors::getAverageIR(int IRpin) {
	int max_count = 10;
	long sum = 0;
	for (int i = 0; i < max_count; i++) {
		sum += analogRead(IRpin);
	}
	return sum/max_count;
}
