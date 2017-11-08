#!/usr/bin/env python
import rospy
from robocon18.srv import general

def reach(x):
    rospy.wait_for_service('destination')
    attempt_algo = rospy.ServiceProxy('destination', general)
    success = attempt_algo(x)
    return success.y
	
def Write(x):
    rospy.wait_for_service('update')
    attempt_algo = rospy.ServiceProxy('update', general)
    success = attempt_algo(x)
    return success.y
 
def checkball():
    rospy.wait_for_service('ball_present')
    attempt_algo = rospy.ServiceProxy('ball_present', general)
    success = attempt_algo(1)
    return success.y
    ##### send message to arm
    ##### get info
    
def Throw_Arm_Activate():
    rospy.wait_for_service('throw_action')
    attempt_algo = rospy.ServiceProxy('throw_action', general)
    success = attempt_algo(1)
    return success.y
    ###### Send activation
    ###### Receive update
    
def Update_ball():
    rospy.wait_for_service('update_ball')
    attempt_algo = rospy.ServiceProxy('update_ball', general)
    success = attempt_algo(1)
    return success.y
    ###### read ball info
    ###### overwrite ball--
    
def ball():
    rospy.wait_for_service('count_ball')
    attempt_algo = rospy.ServiceProxy('count_ball', general)
    success = attempt_algo(1)
    return success.y
    ###### read ball info
    ###### return number of balls
    
def manual():
    rospy.wait_for_service('manual_present')
    attempt_algo = rospy.ServiceProxy('manual_present', general)
    success = attempt_algo(1)
    return success.y
    ###### signal detecting node to check for manual
    ###### get info
    
def loadball():
    rospy.wait_for_service('load_ball_action')
    attempt_algo = rospy.ServiceProxy('load_ball_action', general)
    success = attempt_algo(1)
    return success.y
    ###### signal loading mechanism
    ###### get notified if task is complete
    
def totalball():
    rospy.wait_for_service('read_total_ball')
    attempt_algo = rospy.ServiceProxy('read_total_ball', general)
    success = attempt_algo(1)
    return success.y
    ###### read global variable file
    ###### return total normal balls
 
 
#########################################################################
#Callback function
########################################################################
 
def Go(x):
    reach(x.data) #Load position
    if(checkball()):
        reach(x.data) #Throw position
        
        Throw_Arm_Activate() #Attempts to throw the ball untill successfull
        Update_ball() 
            
        if(not ball()):
            Write(5)
    else:
        if(not ball()):
            Write(5)
        else:
            if(manual()):
                loadball()
            else:
                if(not ball()==totalball()):
                    Write(x.data)
                    
            

if __name__ == '__main__':
    rospy.init_node('Normal_Throw_Algo')
    rospy.Service('throw_from', general, Go)
    return generalResponse(1)