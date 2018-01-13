import RPi.GPIO as io
import Adafruit_MCP3008
import time
import cPickle as pickle

cf = 25

CLK  = 18
MISO = 23
MOSI = 24

node = 0
CS =[25, 22, 27, 10]
mcp = [Adafruit_MCP3008.MCP3008(clk = CLK, cs = CS[0], miso = MISO, mosi = MOSI)] * 4

for i in range(4):
	mcp[i] = Adafruit_MCP3008.MCP3008(clk=CLK, cs=CS[i], miso=MISO, mosi=MOSI)
avg = [[0 for i in range(8)] for j in range(4)]
bi = [[0 for i in range(8)] for j in range(4)]
values = [[0 for i in range(8)] for j in range(4)]

motordir = [6,4,2,19]
motorpwm = [13,17,8,26]
motorin =[0,0,0,0]
sp =[30,30,30,40]
flag=0
def motor():
    io.setmode(io.BCM)
    io.setwarnings(False)
    for i in range(4):
	io.setup(motordir[i],io.OUT)
	io.setup(motorpwm[i],io.OUT)
	motorin[i] = io.PWM(motorpwm[i],90)
	motorin[i].start(0)
	motorin[i].ChangeDutyCycle(0)
                
def setmotor(number,pwmvalue,d):
    io.output(motordir[number],d)
    motorin[number].ChangeDutyCycle(pwmvalue)
def forward():
	print "forward"
	if face==0:
		for i in range(4):
			setmotor(i,sp[i],0)
	elif face==1:
		setmotor(0,sp[0],0)
		setmotor(1,sp[1],1)
		setmotor(2,sp[2],0)
		setmotor(3,sp[3],1)
	elif face==2:
		setmotor(0,sp[0],1)
		setmotor(1,sp[1],1)
		setmotor(2,sp[2],1)
		setmotor(3,sp[3],1)
	elif face==3:
		setmotor(0,sp[0],1)
		setmotor(1,sp[1],0)
		setmotor(2,sp[2],1)
		setmotor(3,sp[3],0)
def left():
	print "left"
	if face==0:
		setmotor(0,sp[0],1)
		setmotor(1,sp[1],0)
		setmotor(2,sp[2],1)
		setmotor(3,sp[3],0)
	elif face==1:
		for i in range(4):
			setmotor(i,sp[i],0)
	elif face==2:
		setmotor(0,sp[0],0)
		setmotor(1,sp[1],1)
		setmotor(2,sp[2],0)
		setmotor(3,sp[3],1)
	elif face==3:
		for i in range(4):
			setmotor(i,sp[i],1)
		
def right():
	print "right"
	if face==0:
		setmotor(0,sp[0],0)
		setmotor(1,sp[1],1)
		setmotor(2,sp[2],0)
		setmotor(3,sp[3],1)
	elif face==1:
		for i in range(4):
			setmotor(i,sp[i],1)
	elif face==2:
		setmotor(0,sp[0],1)
		setmotor(1,sp[1],0)
		setmotor(2,sp[2],1)
		setmotor(3,sp[3],0)
	elif face==3:
		for i in range(4):
			setmotor(i,sp[i],0)
	
		
def backright():
	if face==0:
		setmotor(0,sp[0],0)
		setmotor(1,sp[1],0)
		setmotor(2,sp[2]+cf,1)
		setmotor(3,sp[3]+cf,0)
	elif face==1:
		setmotor(0,sp[0]+cf,0)
		setmotor(1,sp[1],1)
		setmotor(2,sp[2],0)
		setmotor(3,sp[3]+cf,0)
	elif face==2:
		setmotor(0,sp[0]+cf,0)
		setmotor(1,sp[1]+cf,1)
		setmotor(2,sp[2],1)
		setmotor(3,sp[3],1)
	elif face==3:
		setmotor(0,sp[0],1)
		setmotor(1,sp[1]+cf,1)
		setmotor(2,sp[2]+cf,1)
		setmotor(3,sp[3],0)		
def backleft():
	if face==0:
		setmotor(0,sp[0],0)
		setmotor(1,sp[1],0)
		setmotor(2,sp[2]+cf,0)
		setmotor(3,sp[3]+cf,1)
	elif face==1:
		setmotor(0,sp[0]+cf,1)
		setmotor(1,sp[1],1)
		setmotor(2,sp[2],0)
		setmotor(3,sp[3]+cf,0)
	elif face==2:
		setmotor(0,sp[0]+cf,1)
		setmotor(1,sp[1]+cf,0)
		setmotor(2,sp[2],1)
		setmotor(3,sp[3],1)
	elif face==3:
		setmotor(0,sp[0],1)
		setmotor(1,sp[1]+cf,0)
		setmotor(2,sp[2]+cf,0)
		setmotor(3,sp[3],0)		
def stop():
    for i in range(4):
        setmotor(i,0,0)
def read_sensor(i):
	index = 0
	for j in range(8):
		if i == 2:
			index = 7 - j
		else:
			index = j
		values[i][index] = mcp[i].read_adc(index)

def biCalculate():
	for k in range(4):
		read_sensor(k)
		print values[k]
		print avg[k]
		print "while averaging:.."
		for i in range(8):
			#print values[k][i], avg[k][i]
			if values[k][i]<=avg[k][i]:
				bi[k][i]=0
			else:
				bi[k][i]=1
	print "nikal gaya"
def conditioncheck() :
	print "checking condition..."
	biCalculate()
	global node
	for i in range(4):
		print(bi[i])
	print face
	if bi[face][0]==1 and bi[face][1]==1 and bi[face][2]==1 and bi[face][3]==1 and bi[face][4]==1 and bi[face][5]==1 and bi[face][6]==1 and bi[face][7]==1:
		forward()
		flag=1
	elif bi[face][3]==1 or bi[face][4]==1 :
		biCalculate()
		if (bi[(face + 2) % 4][3]==1 or bi[(face + 2) % 4][4]==1) :
			forward()
		elif bi[(face + 2) % 4][0]==1 or bi[(face + 2) % 4][1]==1 or bi[(face + 2) % 4][2]==1:
			backleft()
		elif bi[(face + 2) % 4][5]==1 or bi[(face + 2) % 4][6]==1 or bi[(face + 2) % 4][7]==1:
			backright()
		else:
			forward()

	elif bi[face][0]==1 or bi[face][1]==1 or bi[face][2]==1 :
		left()
	elif bi[face][5]==1 or bi[face][6]==1 or bi[face][7]==1 :
		right()
	else:
		print "stop case"
		stop()
	global flag
	
	if flag==1:
		print "check"
		if (bi[(face+3)%4][0]==1 or bi[(face+3)%4][1]==1 or bi[(face+3)%4][2]==1 or bi[(face+3)%4][3]==1 or bi[(face+3)%4][4]==1 or bi[(face+3)%4][5]==1 or bi[(face+3)%4][6]==1 or bi[(face+3)%4][7]==1) and ( bi[(face+1)%4][0]==1 or bi[(face+1)%4][1]==1 or bi[(face+1)%4][2]==1 or bi[(face+1)%4][3]==1 or bi[(face+1)%4][4]==1 or bi[(face+1)%4][5]==1 or bi[(face+1)%4][6]==1 or bi[(face+1)%4][7]==1 ) :
			node = node + 1
			flag=0
		
	return node
def specialconditioncheck() :
	print "checking condition..."
	biCalculate()
	global node
	for i in range(4):
		print(bi[i])
	print face
	if bi[face][3]==1 or bi[face][4]==1 :
		biCalculate()
		if (bi[(face + 2) % 4][3]==1 or bi[(face + 2) % 4][4]==1) :
			forward()
		elif bi[(face + 2) % 4][0]==1 or bi[(face + 2) % 4][1]==1 or bi[(face + 2) % 4][2]==1:
			backleft()
		elif bi[(face + 2) % 4][5]==1 or bi[(face + 2) % 4][6]==1 or bi[(face + 2) % 4][7]==1:
			backright()

	elif bi[face][0]==1 or bi[face][1]==1 or bi[face][2]==1 :
		left()
	elif bi[face][5]==1 or bi[face][6]==1 or bi[face][7]==1 :
		right()
	else:
		while True:
			forward()
			print ("SPECIAL")
			print (face)
			biCalculate()
			if (bi[(face+1)%4][2]==1 or bi[(face+1)%4][3]==1 or bi[(face+1)%4][4]==1 or bi[(face+1)%4][5]==1 ):
				print("IFK ANDR")
				node=node+1
				break
		
	return node
	
def initialfunc():
    motor()
    global avg
    filer = open('avgline', "rb")
    avg = pickle.load(filer)
    for i in range(4):
            print avg[i]
    filer.close()
def mainfunc(f,special=0):
    global node,face
    node=0
    face=f
    if special==0:
        while conditioncheck() == 0:
            pass
    else:
        while specialconditioncheck() == 0:
            pass    
        
"""
initialfunc()
while True:
	conditioncheck()
	#time.sleep(0.1)
"""
