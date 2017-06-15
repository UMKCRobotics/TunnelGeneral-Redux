#include "TunnelDisplay.h"

TunnelDisplay::TunnelDisplay() {


}

void TunnelDisplay::init() {
	matrix.begin();
	matrix.setBrightness(20);
	matrix.show();  // set all to off
}

void TunnelDisplay::turnOnReadyLight() {
	matrix.setPixelColor(MATRIX_READY_LIGHT_INDEX, 255, 151, 0);  // yellow
	matrix.show();
}

void TunnelDisplay::setToTunnel(int index) {
	if (index != MATRIX_READY_LIGHT_INDEX)  // don't change the ready light
	{
		matrix.setPixelColor(index, 255, 0, 0);
		matrix.show();
	}	
}

void TunnelDisplay::setToDeadend(int index) {
	if (index != MATRIX_READY_LIGHT_INDEX)  // don't change the ready light
	{
		matrix.setPixelColor(index, 0, 255, 255);
		matrix.show();
	}
}

void TunnelDisplay::setToEmpty(int index) {
	if (index != MATRIX_READY_LIGHT_INDEX)  // don't change the ready light
	{
		matrix.setPixelColor(index, 0, 0, 0);
		matrix.show();
	}
}
