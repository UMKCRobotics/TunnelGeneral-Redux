#ifndef TUNNELSENSORS_H
#define TUNNELSENSORS_H
#include "Arduino.h"
#include "Definitions.h"

class TunnelSensors {
	private:
	public:
		TunnelSensors() {};
		long getReadingEMF();
		long getAverageIR(int IRpin);

};

#endif