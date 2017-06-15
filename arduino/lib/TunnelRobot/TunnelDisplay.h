#ifndef TUNNELDISPLAY_H
#define TUNNELDISPLAY_H
#include "Arduino.h"
#include "Definitions.h"
#include "Adafruit_GFX.h"
#include "Adafruit_NeoMatrix.h"
#include "Adafruit_NeoPixel.h"

	// initialize matrix


// define class
class TunnelDisplay {
	private:
	public:
		Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8,8,MATRIX_PIN, 
			NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + 
			NEO_MATRIX_PROGRESSIVE, NEO_GRB + NEO_KHZ800);
		TunnelDisplay();
		void init();
		void turnOnReadyLight();
		void setToTunnel(int index);
		void setToDeadend(int index);
		void setToEmpty(int index);
};
#endif
