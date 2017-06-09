import os, sys, time
from arduinointerface import ArduinoInterface

# add relevant dir to path
__location__ = os.path.realpath(
	os.path.join(os.getcwd(), os.path.dirname(__file__)))  # directory from which this script is ran
main_dir = os.path.realpath(os.path.join(__location__,'../..'))
sys.path.insert(0, main_dir)


class RobotInterface(object):


	def __init__(self, conf):
		self.conf = conf
		self.arduino = ArduinoInterface(conf["ard_port"], int(conf["ard_baud"]), int(conf["MAX_TRIES"]))

	# button-related commands
	def getGoButton(self):
		return self.arduino.doCommand('B', ['G'])

	def getStopButton(self):
		return self.arduino.doCommand('B', ['S'])

	# display-related commands
	def set8x8(self, index, gridType):
		return self.arduino.doCommand(gridType, [str(index)])

	def set7segment(self, number):
		return self.arduino.doCommand('N', [str(number)])

	# movement-related commands
	def goForward(self):
		return self.arduino.doCommand('f')
	
	def goForwardWithIR(self):
		return self.arduino.doCommand('F')
	
	def goBackward(self):
		return self.arduino.doCommand('b')
	
	def rotateCounterClockwise(self):
		return self.arduino.doCommand('l')
	
	def rotateClockwise(self):
		return self.arduino.doCommand('r')

	def goCalibrateIR(self, side):
		return self.arduino.doCommand('C', [side])
	
	# sensor-related commands
	def checkFrontIR(self):
		return self.arduino.doCommand('I')

	def getEMFreading(self):
		return self.arduino.doCommand('S', ['E'], returnType=[])

	def getObstacleReport(self):
		return self.arduino.doCommand('S', ['O'])

	# not related to robot movement, but config stuff
	def stop(self):
		self.arduino.stop()
