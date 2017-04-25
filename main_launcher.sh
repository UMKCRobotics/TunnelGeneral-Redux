#!/bin/sh
# main_launcher.sh
# runs main.py

sudo python "/home/pi/TunnelGeneral-Redux/main.py" 2>&1 | tee "/home/pi/robotlogs/$(date +"%FT%H%M%S").log"
