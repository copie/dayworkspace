#!/usr/bin/python
#coding=utf-8
import cv2
import numpy as np
import sys
import random
cap =  cv2.VideoCapture(0)
i=-200
print "你就是一个sb"
while(True):

    ret,frame = cap.read()
    #gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    gray = cv2.cvtColor(frame, cv2.IMREAD_COLOR)
    font = cv2.FONT_HERSHEY_SIMPLEX
    str=' SB'
    cv2.putText(gray, str, (i, 300), font, i/100+1, (random.randint(1,255), random.randint(1,255), random.randint(1,255)), 4)
    cv2.putText(gray, str, (i-800, 300), font, i/100+1, (255, 200, 155), 4)
    i = i + 10
    if i > 1100 :
        i=-200

    cv2.imshow('fram',gray)
    if cv2.waitKey(1)&0xff == ord('q'):
        break;

cap.release()
cv2.destroyAllWindows()