#!/usr/bin/env python
import rospy
from robocon18.srv import general

def manual_check_sensors():
    # Get current location
    # process dearination
    # get path using grid
    # control line seeking and motors module

def Go(resp):
    success=move_to(resp.x)
    return generalResponse(success)
 
if __name__ == '__main__':
    rospy.init_node('Navigate')
    rospy.Service('destination', general, Go)