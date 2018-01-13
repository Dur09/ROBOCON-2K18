import RPi.GPIO as io
import time
from valuesnpins import *
def motor():
        io.setmode(io.BCM)
        io.setwarnings(False)
        for i in range(4):
                io.setup(motordir[i],io.OUT)
                io.setup(motorpwm[i],io.OUT)
                motorin[i] = io.PWM(motorpwm[i],90)
                motorin[i].start(0)
                motorin[i].ChangeDutyCycle(0)
                io.output(motordir[i],0)
                motorin[i].ChangeDutyCycle(40)
                time.sleep(0.8)
                motorin[i].ChangeDutyCycle(0)
                io.output(motordir[i],1)
                motorin[i].ChangeDutyCycle(40)
                time.sleep(0.8)
motor()
