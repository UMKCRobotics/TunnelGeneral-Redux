import os, sys, time

# add relevant dir to path
__location__ = os.path.realpath(
	os.path.join(os.getcwd(), os.path.dirname(__file__)))  # directory from which this script is ran
main_dir = os.path.realpath(os.path.join(__location__,'../..'))
sys.path.insert(0, main_dir)

from arduinointerface import ArduinoInterface


class RobotInterface(object):


	def __init__(self, conf):
		self.conf = conf
		self.arduino = ArduinoInterface(conf["ard_port"],int(conf["ard_baud"]),int(conf["MAX_TRIES"]))

	def goForward(self):
		return self.arduino.doCommand('f')
	
	def goForwardWithIR(self):
		return self.arduino.doCommand('fi')
	
	def goBackward(self):
		return self.arduino.doCommand('b')
	
	def goLeft(self):
		return self.arduino.doCommand('l')
	
	def goRight(self):
		return self.arduino.doCommand('r')
	
	def checkFrontIR(self):
		return self.arduino.doCommand('I')

	def stop(self):
		self.arduino.stop()
