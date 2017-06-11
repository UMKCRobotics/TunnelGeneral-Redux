#ifndef TUNNELBUTTONS_H
#define TUNNELBUTTONS_H
#include "Arduino.h"
#include "Definitions.h"

// class for robot's buttons
class TunnelButtons {
	private:
		volatile bool goButtonPressed = false;
		volatile bool stopButtonPressed = false;
	public:
		TunnelButtons() { resetButtons(); };
		String hasGoBeenPressed() { return (goButtonPressed ? "1" : "0"); };
		String hasStopBeenPressed() { return (stopButtonPressed ? "1": "0"); };
		void resetGoButton() { goButtonPressed = false; };
		void resetStopButton() { stopButtonPressed = false; };
		void resetButtons() { resetGoButton(); resetStopButton(); };
		void pressGoButton() { goButtonPressed = true; };
		void pressStopButton() { stopButtonPressed = true; };

};

#endif