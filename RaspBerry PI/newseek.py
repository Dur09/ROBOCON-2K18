import RPi.GPIO as io
import Adafruit_MCP3008
import time
import cPickle as pickle
from valuesnpins import *
from numpy import interp

def motor():
    io.setmode(io.BCM)
    io.setwarnings(False)
    for i in range(4):
		io.setup(motordir[i],io.OUT)
		io.setup(motorpwm[i],io.OUT)
		motorin[i] = io.PWM(motorpwm[i],500)
		motorin[i].start(0)
		motorin[i].ChangeDutyCycle(0)
                
def setmotor(number,pwmvalue,d):
    io.output(motordir[number],d)
    motorin[number].ChangeDutyCycle(pwmvalue)
def slowforward():
        for i in range(4):
                setmotor(i,sp[i]-20,0)
def backward(m=0):
#	print "backward"
	if face==0:
		for i in range(4):
			setmotor(i,sp[i]-m,1)
	elif face==1:
		setmotor(0,sp[0]-m,1)
		setmotor(1,sp[1]-m,0)
		setmotor(2,sp[2]-m,1)
		setmotor(3,sp[3]-m,0)
	elif face==2:
		setmotor(0,sp[0]-m,0)
		setmotor(1,sp[1]-m,0)
		setmotor(2,sp[2]-m,0)
		setmotor(3,sp[3]-m,0)
	elif face==3:
		setmotor(0,sp[0]-m,0)
		setmotor(1,sp[1]-m,1)
		setmotor(2,sp[2]-m,0)
		setmotor(3,sp[3]-m,1)

def travel(x):
#	print "forward"
	x1=x[face]
	x2=x[(face+2)%4]
	if face==0:
		setmotor(0,sp[0]+x1,0)
		setmotor(1,sp[1]-x1,0)
		setmotor(2,sp[2]-x2,0)
		setmotor(3,sp[3]+x1,0)
	elif face==1:
		setmotor(0,sp[0]+x2,0)
		setmotor(1,sp[1]+x1,1)
		setmotor(2,sp[2]-x1,0)
		setmotor(3,sp[3]-x2,1)
	elif face==2:
		setmotor(0,sp[0]-x2,1)
		setmotor(1,sp[1]+x2,1)
		setmotor(2,sp[2]+x1,1)
		setmotor(3,sp[3]-x1,1)
	elif face==3:
		setmotor(0,sp[0]-x1,1)
		setmotor(1,sp[1]-x2,0)
		setmotor(2,sp[2]+x2,1)
		setmotor(3,sp[3]+x1,0)

def forward(m=0):	
	if face==0:
		for i in range(4):
			setmotor(i,sp[i]-m,0)
	elif face==1:
		setmotor(0,sp[0]-m,0)
		setmotor(1,sp[1]-m,1)
		setmotor(2,sp[2]-m,0)
		setmotor(3,sp[3]-m,1)
	elif face==2:
		setmotor(0,sp[0]-m,1)
		setmotor(1,sp[1]-m,1)
		setmotor(2,sp[2]-m,1)
		setmotor(3,sp[3]-m,1)
	elif face==3:
		setmotor(0,sp[0]-m,1)
		setmotor(1,sp[1]-m,0)
		setmotor(2,sp[2]-m,1)
		setmotor(3,sp[3]-m,0)
def left(m=0):
	print "left"
	if face==0:
		setmotor(0,sp[0]-sf-m,1)
		setmotor(1,sp[1]-sf-m,0)
		setmotor(2,sp[2]-sf-m,1)
		setmotor(3,sp[3]-sf-m,0)
	elif face==1:
		for i in range(4):
			setmotor(i,sp[i]-sf-m,0)
	elif face==2:
		setmotor(0,sp[0]-sf-m,0)
		setmotor(1,sp[1]-sf-m,1)
		setmotor(2,sp[2]-sf-m,0)
		setmotor(3,sp[3]-sf-m,1)
	elif face==3:
		for i in range(4):
			setmotor(i,sp[i]-sf-m,1)
		
def right(m=0):
	print "right"
	if face==0:
		setmotor(0,sp[0]-sf-m,0)
		setmotor(1,sp[1]-sf-m,1)
		setmotor(2,sp[2]-sf-m,0)
		setmotor(3,sp[3]-sf-m,1)
	elif face==1:
		for i in range(4):
			setmotor(i,sp[i]-sf-m,1)
	elif face==2:
		setmotor(0,sp[0]-sf-m,1)
		setmotor(1,sp[1]-sf-m,0)
		setmotor(2,sp[2]-sf-m,1)
		setmotor(3,sp[3]-sf-m,0)
	elif face==3:
		for i in range(4):
			setmotor(i,sp[i]-sf-m,0)
	
		
def backright(m=0):
	if face==0:
		setmotor(0,sp[0]-m,0)
		setmotor(1,sp[1]-m,0)
		setmotor(2,sp[2]+cf-m,1)
		setmotor(3,sp[3]+cf-m,0)
	elif face==1:
		setmotor(0,sp[0]+cf-m,0)
		setmotor(1,sp[1]-m,1)
		setmotor(2,sp[2]-m,0)
		setmotor(3,sp[3]+cf-m,0)
	elif face==2:
		setmotor(0,sp[0]+cf-m,0)
		setmotor(1,sp[1]+cf-m,1)
		setmotor(2,sp[2]-m,1)
		setmotor(3,sp[3]-m,1)
	elif face==3:
		setmotor(0,sp[0]-m,1)
		setmotor(1,sp[1]+cf-m,1)
		setmotor(2,sp[2]+cf-m,1)
		setmotor(3,sp[3]-m,0)		
def backleft(m=0):
	if face==0:
		setmotor(0,sp[0]-m,0)
		setmotor(1,sp[1]-m,0)
		setmotor(2,sp[2]+cf-m,0)
		setmotor(3,sp[3]+cf-m,1)
	elif face==1:
		setmotor(0,sp[0]+cf-m,1)
		setmotor(1,sp[1]-m,1)
		setmotor(2,sp[2]-m,0)
		setmotor(3,sp[3]+cf-m,1)
	elif face==2:
		setmotor(0,sp[0]+cf-m,1)
		setmotor(1,sp[1]+cf-m,0)
		setmotor(2,sp[2]-m,1)
		setmotor(3,sp[3]-m,1)
	elif face==3:
		setmotor(0,sp[0]-m,1)
		setmotor(1,sp[1]+cf-m,0)
		setmotor(2,sp[2]+cf-m,0)
		setmotor(3,sp[3]-m,0)		
def stop():
    for i in range(4):
        setmotor(i,0,0)
def read_sensor(i):
	index = 0
	for j in range(8):
		if i == 3:
			index = j
		else:
			index = j
		values[i][index] = mcp[i].read_adc(index)
		if values[i][index]>maxi[i][index]:
			values[i][index]=100
		elif values[i][index]<mini[i][index]:
			values[i][index]=0
		else:
			values[i][index]=interp(values[i][index],[mini[i][index],maxi[i][index]],[0,100])
#	print values[i],"\n"
#	print values
nodeDetected = False
def biCalculate():
	global nodeDetected
	nodeDetected = False
	for k in range(4):
		read_sensor(k)
#		print values[k]
		#print avg[k]		
		for i in range(8):
			#print values[k][i], avg[k][i]
			if values[k][i]<=50:
				bi[k][i]=0
			else:
				if k==(face+1)%4 or k==(face+3)%4:
					nodeDetected=True
				bi[k][i]=1
	

def poscalculate():
	global cfactor
	for k in range(4):
		read_sensor(k)
		v = values[k]
		ma = max(v)
		gmin = min(v)
		d = ma - gmin
		p = v.index(ma)
		if not p==0 and not p==7 and not d==0:
			if v[p-1] <= v[p+1]:
				mi = v[p-1]
			else:
				mi = v[p+1]
			d = ma - mi
			n = v[p+1] - v[p-1]
			r = (n*1.0)/(d*2.0)
			pos[k] = p + r -3.5
		elif p == 0 and not d==0:
			n = d - v[p] + v[p+1]
			r = (n*1.0)/(d*2.0)
			pos[k] = p + r -3.5
		elif p == 7 and not d==0:
			n = d + v[p-1] - v[p]
			r = (n*1.0)/(d*2.0)
			pos[k] = p - r -3.5	
	cfactor=interp(pos ,[-3.5,3.5],[-20,20])

def align():
	face = 0
	while pos[face] > 0.05 or pos[face] < -0.05 or pos[(face+2)%4] > 0.05 or pos[(face+2)%4] < -0.05 or pos[(face+1)%4] > 0.05 or pos[(face+1)%4] < -0.05 or pos[(face+3)%4] > 0.05 or pos[(face+3)%4] < -0.05:
		face = 0
		poscalculate()
		while pos[face] > 0.05 or pos[face] < -0.05 or pos[(face+2)%4] > 0.05 or pos[(face+2)%4] < -0.05:
			cfactor = 5*interp(pos ,[-3.5,3.5],[-10,10])
			x1 = cfactor[face]
			x2 = cfactor[(face+2)%4]
			if x1 < 0:
				setmotor(0,-x1,1)
				setmotor(1,-x1,0)
			else:
				setmotor(0,x1,0)
				setmotor(1,x1,1)
			if x2 < 0:
				setmotor(2,-x2,0)
				setmotor(3,-x2,1)
			else:
				setmotor(2,x2,1)
				setmotor(3,x2,0)
			poscalculate()

		face = 1
		poscalculate()
		while pos[face] > 0.05 or pos[face] < -0.05 or pos[(face+2)%4] > 0.05 or pos[(face+2)%4] < -0.05:
			cfactor = 5*interp(pos ,[-3.5,3.5],[-10,10])
			x1 = cfactor[face]
			x2 = cfactor[(face+2)%4]
			if x1 < 0:
				setmotor(1,-x1,0)
				setmotor(2,-x1,0)
			else:
				setmotor(1,x1,1)
				setmotor(2,x1,1)
			if x2 < 0:
				setmotor(0,-x2,1)
				setmotor(3,-x2,1)
			else:
				setmotor(0,x2,0)
				setmotor(3,x2,0)
			poscalculate()
	

def conditioncheck() :	
	global nodeDetected
	biCalculate()
	global node
	global snodes
#	for i in range(4):
		#print(bi[i])
	#print face
	'''if bi[face][0]==0 and bi[face][1]==0 and bi[face][2]==0 and bi[face][3]==0 and bi[face][4]==0 and bi[face][5]==0 and bi[face][6]==0 and bi[face][7]==0 : 
		backward(40)
		while bi[face][2]==0 and bi[face][3]==0 and bi[face][4]==0 and bi[face][5]==0:
			biCalculate()'''
	poscalculate()
	if  nodeDetected:
		#forward()
		if ( snodes==0):
			#while True:
				#stop()
			flag=1
			node+=1
			print "Big Node"
		else:
			snodes=snodes-1
			print "Small Node"
			while(nodeDetected) :
				biCalculate()
				poscalculate()
				travel(cfactor)
	else:
		travel(cfactor)
	"""	elif bi[face][3]==1 or bi[face][4]==1 :
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
		stop() """
	'''	global flag
	
	if flag==1:		
		if (bi[(face+3)%4][0]==1 or bi[(face+3)%4][1]==1 or bi[(face+3)%4][2]==1 or bi[(face+3)%4][3]==1 or bi[(face+3)%4][4]==1 or bi[(face+3)%4][5]==1 or bi[(face+3)%4][6]==1 or bi[(face+3)%4][7]==1) and ( bi[(face+1)%4][0]==1 or bi[(face+1)%4][1]==1 or bi[(face+1)%4][2]==1 or bi[(face+1)%4][3]==1 or bi[(face+1)%4][4]==1 or bi[(face+1)%4][5]==1 or bi[(face+1)%4][6]==1 or bi[(face+1)%4][7]==1 ) :
			node = node + 1
			flag=0
			print "Big Node"'''
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
			slowforward()
			print ("SPECIAL")
			print (face)
			biCalculate()
			if (bi[(face+1)%4][2]==1 or bi[(face+1)%4][3]==1 or bi[(face+1)%4][4]==1 or bi[(face+1)%4][5]==1 ):
				print("IF K ANDR")
				node=node+1
				break
		
	return node
	
def initialfunc():
        motor()
        global avg , maxi , mini
        filer = open('avgline', "rb")
        avg = pickle.load(filer)
        for i in range(4):
                print avg[i]
		filer.close()
		filer = open('maxi', "rb")
		maxi = pickle.load(filer)
		filer.close()
		filer = open('mini', "rb")
		mini = pickle.load(filer)
		filer.close()
def mainfunc(f,s,special=0):
	global node,face,snodes
	node=0
	snodes=s
	face=f
	if special==0:
		while conditioncheck() == 0:
			pass
	else:
		while specialconditioncheck() == 0:
			pass

def backslow():
	global face
	biCalculate()
	while(bi[(face+1)%4][3]==1 or bi[(face+1)%4][4]==1 or bi[(face+3)%4][3]==1 or bi[(face+3)%4][4]==1):
		biCalculate()
	backward(20)
	while(bi[(face+1)%4][3]==0 and bi[(face+1)%4][4]==0 and bi[(face+3)%4][3]==0 and bi[(face+3)%4][4]==0):
		biCalculate()
	stop()
        
"""
initialfunc()
while True:
	conditioncheck()
	#time.sleep(0.1)
"""

