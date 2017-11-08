#!/usr/bin/env python
import rospy
from robocon18.srv import general

def manual():
    rospy.wait_for_service('manual_present')
    attempt_algo = rospy.ServiceProxy('manual_present', general)
    success = attempt_algo(1)
    return success.y
    ###### signal detecting node to check for manual
    ###### get info
    
def gball():
    rospy.wait_for_service('count_gball')
    attempt_algo = rospy.ServiceProxy('count_gball', general)
    success = attempt_algo(1)
    return success.y
    ###### read golden ball info
    ###### return number of golden balls
    
def totalgball():
    rospy.wait_for_service('read_total_gball')
    attempt_algo = rospy.ServiceProxy('read_total_gball', general)
    success = attempt_algo(1)
    return success.y
    ###### read global variable.txt
    ###### return number of total golden balls
    
def loadrack():
    rospy.wait_for_service('load_rack')
    attempt_algo = rospy.ServiceProxy('load_rack', general)
    success = attempt_algo(1)
    return success.y
    ###### activate load rack
    ###### get success info
    
def goldenthrow():
    rospy.wait_for_service('gthrow')
    attempt_algo = rospy.ServiceProxy('gthrow', general)
    success = attempt_algo(1)
    return success.y
    ###### activate golden throw
    ###### report success
    
def rack():
    rospy.wait_for_service('rack_present')
    attempt_algo = rospy.ServiceProxy('rack_present', general)
    success = attempt_algo(1)
    return success.y
    ###### ask node to give rack status
    ###### return rack status
    
def Write(x):
    rospy.wait_for_service('update')
    attempt_algo = rospy.ServiceProxy('update', general)
    success = attempt_algo(x)
    return success.y


#########################################################################
#Callback function
########################################################################
def Go(x):
    if manual():
        if gball()==0:
            Write(4)
        elif gball()==totalgball():
            loadrack()
            goldenthrow()
        else:
            if(not rack()):
                loadrack()
            goldenthrow()
            
    else:
        if gball()==0:
            Write(3)
        if (gball()>0 and gball()<totalgball()):
            if rack():
                goldenthrow()
                    
            

if __name__ == '__main__':
    rospy.init_node('RB_Throw_Algo')
    rospy.Service('rb_time', general, Go)
    return generalResponse(1)