
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
def getscore(a):
    counter=0
    sum1=0
    for i in a:
        sum1=sum1+(i*2**counter)
        counter=counter+1
    return sum1
def check(a,b):
    if a or b:
        return 1
    else:
        return 0
#def myprint(d,s):
 #   for k in d[s]:
        
global current
current='a'
global meta_front,meta_back,meta_left,meta_right
global sensorf,sensorb,sensorl,sensorr
while True:
    
    front=map(int,raw_input().split())
    back=map(int,raw_input().split())
    left=map(int,raw_input().split())
    right=map(int,raw_input().split())
    if len(current)==1:
        scoref=getscore(front)
        scoreb=getscore(back)
        scorel=getscore(left)
        scorer=getscore(right)
        if (scoref):
            if scoref==24:
                meta_front="middle"
            elif scoref<24:
                meta_front="right"
            elif scoref>24:
                meta_front=="left"
        if (scoreb):
            if scoreb==24:
                meta_back="middle"
            elif scoreb<24:
                meta_back="right"
            elif scoreb>24:
                meta_back=="left"
        if (scorel):
            if scorel==24:
                meta_left="middle"
            elif scorel<24:
                meta_left="front"
            elif scorel>24:
                meta_left=="back"
        if (scorer):
            if scorer==24:
                meta_right="middle"
            elif scorer<24:
                meta_right="front"
            elif scorer>24:
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
        if(scorel==scorer==0 and check(scoref,scoreb) and mch!="error"):
            tmp = item[current][mch]
            if tmp==0:
                continue
            current = tmp
        if(scoref==scoreb==0 and check(scorel,scorer) and mcv!="error"):
            tmp = item[current][mcv]
            if tmp==0:
                continue
            current = tmp
        print current
