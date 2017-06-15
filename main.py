import time
from robot.util import read_config, wait_till_done, RobotException, UserInput
from robot.robotinterface import RobotInterface
from simulation import AI_REDUX
from simulation.Robot import RobotMap

conf_dict = read_config("conf.txt")

# initialize our robot
direction = 1
robot_map = RobotMap(None, 50, (0,0), direction, shouldPlaySound=False)

# create interface for tracking faces
robot = RobotInterface(conf_dict, robot_map)

while not robot.checkIfConnected():
	time.sleep(0.1)

# start algorithm
robotAlgorithm = AI_REDUX(robot_impl, robot_impl)
robotAlgorithm.doStuff()
