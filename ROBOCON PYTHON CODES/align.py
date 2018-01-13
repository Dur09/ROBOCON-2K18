def align(face):
    while True:
        biCalculate()
        if( bi[(face+1)%4][0]==1 or bi[(face+1)%4][1]==1 or bi[(face+1)%4][2]==1):
            backright()
        elif( bi[(face+1)%4][5]==1 or bi[(face+1)%4][6]==1 or bi[(face+1)%4][7]==1):
            backleft()
        elif( bi[face][0]==1 or bi[face][1]==1 or bi[(face+1)%4][2]==1) :
            left()
        elif( bi[face][5]==1 or bi[face][6]==1 or bi[face][7]==1) :
            right()
        elif( bi[(face+1)%4][3]==1 and bi[(face+1)%4][4]==1 and bi[face][4]==1 and bi[face][3]==1):
            stop()
            print ("stop align")
        if ((bi[face][3]==1 or bi[face][4]==1) and (bi[(face+2)%4][3]==1 or bi[(face+2)%4][4]==1) and (bi[(face+1)%4][3]==1  or bi[(face+1)%4][3]==1)):
              break
