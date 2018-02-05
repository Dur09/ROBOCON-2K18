import RPi.GPIO as io
import Adafruit_MCP3008
import time
CLK  = 5
MISO = 6
MOSI = 13
CS =17
ir =0
sp = 20
value = Adafruit_MCP3008.MCP3008(clk=CLK, cs=CS, miso=MISO, mosi=MOSI)
motordir=19
motorpwm=26
motorin=0
lsp =10
def ini():
    global motorin
    io.setmode(io.BCM)
    io.setwarnings(False)
    io.setup(motordir,io.OUT)
    io.setup(motorpwm,io.OUT)
    motorin= io.PWM(motorpwm,500)
    motorin.start(0)
    motorin.ChangeDutyCycle(0)

                
def setmotor1(pwmvalue,d):
    io.output(motordir,d)
    motorin.ChangeDutyCycle(pwmvalue)

def motoron():
    setmotor1(sp,0)

def motoralign():
    x=sp
    d=0
    while(x>lsp):
        setmotor1(x,0)
        x=x-1
        time.sleep(0.1)

    received = True
    while x>0:
        print "ALIGNING"
        ir = value.read_adc(0)
        print (ir)
        if ir > 350 and not received:
            received = True
            x=x-1
            setmotor1(x,d)
        elif ir < 200 and received:
            d=1-d
            received = False
            x=x-1
            setmotor1(x,d)
    
def motorstop():
    print "stop"
    setmotor1(0,0)
ini()
motoron()
time.sleep(3)
#motoralign()
motorstop()
