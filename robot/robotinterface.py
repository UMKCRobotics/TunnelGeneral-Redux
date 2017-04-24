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
		return self.arduino.doCommand('c')

	def stop(self):
		self.arduino.stop()
