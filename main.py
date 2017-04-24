import time
from robot.util import read_config, wait_till_done, RobotException, UserInput
from comm.serialcomm import SerialComm
from robot.robotinterface import RobotInterface

conf_dict = read_config("conf.txt")

# create interface for tracking faces
robot = RobotInterface(conf_dict)

# start user input thread
userInput = UserInput()
userInput.start()

while True:
	# check if there is a user message
	user_inp = userInput.returnMessage()
	if user_inp is not None and user_inp.lower().startswith("exit"):
		break
	# now do normal tracking behavior
	elif user_inp == 's':
		print wait_till_done(robot.goForward())
	time.sleep(0.1)

robot.stop()
time.sleep(0.25)
