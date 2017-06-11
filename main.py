import time
from robot.util import read_config, wait_till_done, RobotException, UserInput
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
	elif user_inp == 'f':
		print wait_till_done(robot.goForward())
	elif user_inp == 'fi':
		print wait_till_done(robot.goForwardWithIR())
	elif user_inp == 'b':
		print wait_till_done(robot.goBackward())
	elif user_inp == 'l':
		print wait_till_done(robot.rotateCounterClockwise())
	elif user_inp == 'r':
		print wait_till_done(robot.rotateClockwise())
	elif user_inp == 'i':
		print wait_till_done(robot.checkFrontIR())
	elif user_inp == 'e':
		print wait_till_done(robot.getEMFreading())
	elif user_inp == 'cl':
		print wait_till_done(robot.goCalibrateIR("L"))
	elif user_inp == 'cr':
		print wait_till_done(robot.goCalibrateIR("R"))
	elif user_inp == 'cb':
		print wait_till_done(robot.goCalibrateIR("B"))
	elif user_inp == 'gg':
		print wait_till_done(robot.getGoButton())
	elif user_inp == 'gs':
		print wait_till_done(robot.getStopButton())	
	time.sleep(0.1)

robot.stop()
time.sleep(0.25)
