#!/usr/bin/env python
import rospy
from robocon18.srv import general

def checkball():
    rospy.wait_for_service('ball_present')
    attempt_algo = rospy.ServiceProxy('ball_present', general)
    success = attempt_algo(1)
    return success.y
    ##### send message to arm
    ##### get info
    
def throw(resp):
    #angle of release
    #position arm
    #rotate
    #release

def Go(resp):
    while True:
        throw(resp)
        if(not checkball()):
            break
    
    return generalResponse(found)
 
if __name__ == '__main__':
    rospy.init_node('Throw_Arm_Activate')
    rospy.Service('throw_action', general, Go)