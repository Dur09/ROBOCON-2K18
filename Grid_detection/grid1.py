import json
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
                        "back": 0,
                        "front": "b"
                        },
                    "b": {
                        "left": 0,
                        "right": "bc",
                        "back": 0,
                        "front": 0
                        },
                   "bc": {
                        "left": 0,
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

    
def myprint(d,s):
    #print s,d[s]
    #front,back,left,right=get_sensor()
    front,back,left,right=get_sensor()
    for k in d[s]:
        
        
        
        if d[s][k] !=0 and getscorel(left)==getscorer(right)==12 and getscoref(front)==getscoreb(back)==24 and k=='front':
            temp=d[s][k]
            print temp
            myprint(d,temp)
            
        elif d[s][k]!=0 and getscorel(left)==getscoref(front)==0 and getscorer(right)==getscoreb(back)==24 and k=='right':
            temp=d[s][k]
            print temp
            myprint(d,temp)
        elif d[s][k]!=0 and getscorel(left)==getscorer(right)==24 and getscoref(front)==getscoreb(back)==12 and k=='right':
            temp=d[s][k]
            print temp
            myprint(d,temp)
        elif d[s][k]!=0 and getscorel(left)==getscorer(right)==0 and getscoref(front)==getscoreb(back)==24 and k=='front':
            temp=d[s][k]
            print temp
            myprint(d,temp)
        

#aqq=raw_input()       
#myprint(item,aqq)

def get_sensor():
    front=map(int,raw_input('front sensor ').split())
    back=map(int,raw_input('back sensor ').split())
    left=map(int,raw_input('left sensor ').split())
    right=map(int,raw_input('right sensor ').split())
    return (front,back,left,right)

def getscorel(left):
    counter=0
    sum1=0
    for i in left:
        sum1=sum1+i*(2**counter)
        counter=counter+1
    return sum1
def getscorer(right):
    counter=0
    sum2=0
    for i in right:
        sum2=sum2+i*(2**counter)
        counter=counter+1
    return sum2
def getscoref(front):
    counter=0
    sum3=0
    for i in front:
        sum3=sum3+i*(2**counter)
        counter=counter+1
    return sum3
def getscoreb(back):
    counter=0
    sum4=0
    for i in back:
        sum4=sum4+i*(2**counter)
        counter=counter+1
    return sum4
#print left,right
myprint(item,'a')
