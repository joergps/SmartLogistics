#!/usr/bin/python


import time
import RPi.GPIO as GPIO
import os
import sys


GPIO.setmode(GPIO.BCM)
GPIO_INPUT = 26 
GPIO.setup(GPIO_INPUT,GPIO.IN)

result = GPIO.input(GPIO_INPUT)

print "result: "+ str(result)
#os.system('perl /opt/fhem/fhem.pl 7072 "set pressureSensor '+str(result)+'"')

GPIO.cleanup()