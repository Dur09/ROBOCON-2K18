#!/usr/bin/env python
import rospy
from subprocess import call


################################################################
#Message and services types used


from robocon18.srv import general

#import all necessary message and service types, create user defined 
################################################################



#################################################################
#Function definitions
#################################################################

def terminate():
    call(["kill", "--all"])

def Normal_throw(x):
    rospy.wait_for_service('throw_from')
    attempt_algo = rospy.ServiceProxy('throw_from', general)
    success = attempt_algo(x)
    return success.y
     ######## Receive completion details

def Throw_RB():
    rospy.wait_for_service('rb_time')
    attempt_algo = rospy.ServiceProxy('rb_time', general)
    success = attempt_algo(1)
    return success.y
	
def reach(x):
    rospy.wait_for_service('destination')
    attempt_algo = rospy.ServiceProxy('destination', general)
    success = attempt_algo(x)
    return success.y
	      
def Read_state():
    rospy.wait_for_service('know')
    attempt_algo = rospy.ServiceProxy('know', general)
    success = attempt_algo(1)
    return success.y

def Write(x):
    rospy.wait_for_service('update')
    attempt_algo = rospy.ServiceProxy('update', general)
    success = attempt_algo(x)
    return success.y

#################################################################
#Main Program
#################################################################

if __name__ == '__main__':
    try:
        rospy.init_node('Brain')
        s=Read_state()
	
        if (s==3 or s==5): terminate()

        elif(s==0 or s==1): Normal_throw(s+1)#From Throw position TZs+1

        else:
            reach(2)#Reach load position TZ2
            if(s==2):
                Throw_RB()
            if(s==4):
                s=1
                Write(1)
	
		
    except rospy.ROSInterruptException:
        pass

