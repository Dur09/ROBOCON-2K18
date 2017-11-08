#!/usr/bin/env python
import rospy
from robocon18.srv import general

def ball_check_():
    # Move arm to the required postion
    # Activate sensors
    # decide the presence of ball
    # return 1 if found 0 otherwise

def Go(resp):
    present=ball_check_algo()
    return generalResponse(present)
 
if __name__ == '__main__':
    rospy.init_node('Ball_Check')
    rospy.Service('ball_present', general, Go)