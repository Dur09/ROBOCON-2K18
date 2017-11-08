#!/usr/bin/env python
import rospy
from robocon18.srv import general

def update_gball():
    rospy.wait_for_service('update_gball')
    attempt_algo = rospy.ServiceProxy('update_gball', general)
    success = attempt_algo(1)
    return success.y
    ###### read ball info
    ###### overwrite ball--

def Throw_Arm_Activate():
    rospy.wait_for_service('throw_action')
    attempt_algo = rospy.ServiceProxy('throw_action', general)
    success = attempt_algo(1)
    return success.y
    ###### Send activation
    ###### Receive update
    
def load_gball():
    rospy.wait_for_service('load_gball_action')
    attempt_algo = rospy.ServiceProxy('load_gball_action', general)
    success = attempt_algo(1)
    return success.y
    ###### signal loading mechanism
    ###### get notified if task is complete
    
def gball():
    rospy.wait_for_service('count_gball')
    attempt_algo = rospy.ServiceProxy('count_gball', general)
    success = attempt_algo(1)
    return success.y
    ###### read golden ball info
    ###### return number of golden balls

def Go(resp):
    while gball():
        load_gball()
        Throw_Arm_Activate()
        update_gball()
    return generalResponse(1)
 
if __name__ == '__main__':
    rospy.init_node('Golden_Ball_Throw')
    rospy.Service('gthrow', general, Go)