
item = {
                    "a": {
                        "left": 0,
                        "right": 0,
                        "back": 0,
                        "front":"ab"
                        },
                    "ab": {
                        "left": 0,
                        "right": 0,
                        "back": "a",
                        "front": "b"
                        },
                    "b": {
                        "left": 0,
                        "right": "bc",
                        "back": 0,
                        "front": 0
                        },
                   "bc": {
                        "left": "b",
                        "right": "c",
                        "back": 0,
                        "front": 0
                        },
                    "c": {
                        "left": "cb",
                        "right": "cg",
                        "back": 0,
                        "front": "cd"
                        },
                    "cd": {
                        "left": 0,
                        "right": 0,
                        "back": "c",
                        "front": "d"
                        },
                    "d": {
                        "left": 0,
                        "right": 0,
                        "back": "dc",
                        "front": "de"
                        },
                    "de": {
                        "left": 0,
                        "right": 0,
                        "back": "d",
                        "front": "e"
                        },
                    "e": {
                        "left": 0,
                        "right": 0,
                        "back": "ed",
                        "front": "ef"
                        },
                    "ef": {
                        "left": 0,
                        "right": 0,
                        "back": "e",
                        "front": "f"
                        },
                    "f": {
                        "left": 0,
                        "right": 0,
                        "back": "fe",
                        "front": 0
                        },
                    "cg": {
                        "left": "c",
                        "right": "g",
                        "back": 0,
                        "front": 0
                        },
                    "g": {
                        "left": "gc",
                        "right": 0,
                        "back": 0,
                        "front": "gh"
                        },
                    "gh": {
                        "left": 0,
                        "right": 0,
                        "back": "g",
                        "front": "h"
                        },
                    "h": {
                        "left": 0,
                        "right": 0,
                        "back": "hg",
                        "front": "hi"
                        },
                    "hi": {
                        "left": 0,
                        "right": 0,
                        "back": "h",
                        "front": "i"
                        },
                    "i": {
                        "left": 0,
                        "right": 0,
                        "back": "ih",
                        "front": "ij"
                        },
                    "ij": {
                        "left": 0,
                        "right": 0,
                        "back": "i",
                        "front": "j"
                        },
                    "j": {
                        "left": 0,
                        "right": 0,
                        "back": "ji",
                        "front": "jk"
                        },
                    "jk": {
                        "left": 0,
                        "right": 0,
                        "back": "j",
                        "front": "k"
                        },
                    "k": {
                        "left": 0,
                        "right": 0,
                        "back": "kj",
                        "front": "kl"
                        },
                    "kl": {
                        "left": 0,
                        "right": 0,
                        "back": "k",
                        "front": "l"
                        },
                    "l": {
                        "left": 0,
                        "right": 0,
                        "back": "lk",
                        "front": "lm"
                        },
                    "lm": {
                        "left": 0,
                        "right": 0,
                        "back": "l",
                        "front": "m"
                        },
                    "m": {
                        "left": 0,
                        "right": 0,
                        "back": "ml",
                        "front": 0
                        }
                        
                }
def getscore(a):
    counter=0
    sum1=0
    for i in range(len(a)):
        sum1=sum1+(a[i]*2**counter)
        counter=counter+1
    return sum1
def check(a,b):
    if a or b:
        return 1
    else:
        return 0
#def myprint(d,s):
 #   for k in d[s]:
def convert(a):
    for i in range(len(a)):
        a[i] = int(a[i])
    return a
    
        
global current
current='a'
global meta_front,meta_back,meta_left,meta_right
global meta2_front,meta2_back,meta2_left,meta2_right
meta2_front=""
meta2_back=""
meta2_left=""
meta2_right=""
f=open("sensor.txt","r")


global sensorf,sensorb,sensorl,sensorr

for i in range(0,10):
    flag=0
    
    front=f.readline().split()
    back=f.readline().split()
    left=f.readline().split()
    right=f.readline().split()

    front_int=convert(front)
    back_int=convert(back)
    left_int=convert(left)
    right_int=convert(right)

    scoref=getscore(front_int)
    scoreb=getscore(back_int)
    scorel=getscore(left_int)
    scorer=getscore(right_int)

    if current!=0 and len(current)==1:
        if (scoref):
            if scoref==48 or scoref==12 or scoref==24:
                meta_front="middle"
            elif scoref<12:
                meta_front="right"
            elif scoref>48:
                meta_front=="left"
        if (scoreb):
            if scoreb==48 or scoreb==12 or scoreb==24:
                meta_back="middle"
            elif scoreb<12:
                meta_back="right"
            elif scoreb>48:
                meta_back=="left"
        if (scorel):
            if scorel==48 or scorel==12 or scorel==24:
                meta_left="middle"
            elif scorel<12:
                meta_left="front"
            elif scorel>48:
                meta_left=="back"
        if (scorer):
            if scorer==48 or scorer==12 or scorer==24:
                meta_right="middle"
            elif scorer<12:
                meta_right="front"
            elif scorer>48:
                meta_right=="back"
        if meta_front==meta_back:
            mcv=meta_front
        elif scoref!=scoreb:
            mcv="error"
        if meta_left==meta_right:
            mch=meta_left
        elif scorel!=scorer:
            mch="error"
        print meta_front,meta_back,meta_left,meta_right
        if(scorel==scorer==0 and (scoref or scoreb) and mch!="error"):
            tmp = item[current][mch]
            if tmp==0:
                continue
            current = tmp
        if(scoref==scoreb==0 and (scorel or scorer) and mcv!="error"):
            tmp = item[current][mcv]
            if tmp==0:
                continue
            current = tmp
        print current
    elif (current!=0 and len(current)==2):
        print "edge"
        temp=current[0]
        for k in item[temp]:
           if item[temp][k]!=0 and item[temp][k]==current:
               dirr=k
        print dirr
        if dirr==("front" or "back"):
            print "front or back"
            if((scoref or scoreb)):
                if scorel>48:
                    meta2_left="front"
                elif scorel<12:
                    meta2_left="back"
                if scorer>48:
                    meta2_right="front"
                elif scorer<12:
                    meta2_right="back"
            flag=1
        elif dirr==("right" or "left"):
            print "left or right"
            if (scorer or scorel):
                if scoref>48:
                    meta2_front="right"
                elif scoref<12:
                    meta2_front="left"
                if scoreb>48:
                    meta2_back="right"
                elif scoreb<12:
                    meta2_back="left"
            flag=2
        print meta2_front,meta2_back,meta2_right,meta2_left
        if (scorel==(24 or 12 or 48) and scorer==(24 or 12 or 48) and scoref==(24 or 12 or 48) and scoreb==(24 or 12 or 48) ):
            if (meta2_left==meta2_right and flag==1):
                #print "mcv loop"
                print meta2_left
                mcv2=meta2_left
                current=item[current][mcv2]
                print current
            elif(meta2_front==meta2_back and flag==2):
                #print "mch loop"
                mch2=meta2_front
                current=item[current][mch2]
                print current
        else:
            print current
