#!/usr/bin/env python
import RPi.GPIO as GPIO
import requests
import time

print 'Starting 05_Fsr.py'

# define constants
TRIGGER_INTERVAL = 1

# define pins
pinResponse = 36 # pin 36 = GPIO 16

# access numbers by physical location
GPIO.setmode(GPIO.BOARD)

# define GPIOs for trigger and echo
GPIO.setup(pinResponse, GPIO.IN)

try:
	while True:
		if GPIO.input(pinResponse):
			print 'Taste gedrueckt'
		time.sleep(TRIGGER_INTERVAL)

except KeyboardInterrupt:
	print '...Programm beendet.'
	GPIO.cleanup()
