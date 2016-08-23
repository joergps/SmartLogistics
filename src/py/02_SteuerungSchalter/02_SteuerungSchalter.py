#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

inputPin = 32 # pin 32 = GPIO 12

print 'Starting 2_SteuerungSchalter.py'

# access numbers by physical location
GPIO.setmode(GPIO.BOARD)

# define GPIO for LED to be output
GPIO.setup(inputPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

try:
	while True:
		if GPIO.input(inputPin):
			print 'Taste gedrueckt'
		# else:
			print 'KEINE Taste'
except KeyboardInterrupt:
	GPIO.cleanup()


print '... done.'
