#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

ledPin = 11 # pin 11 = GPIO 17

print 'Starting 1_SteuerungLed.py'

# access numbers by physical location
GPIO.setmode(GPIO.BOARD)

# define GPIO for LED to be output
GPIO.setup(ledPin, GPIO.OUT)

# define default for LED GPIO to be LOW
GPIO.output(ledPin, GPIO.LOW)

try:
	while True:
		print 'LED on'
		GPIO.output(ledPin, GPIO.HIGH)
		time.sleep(0.5)
		
		print 'LED off'
		GPIO.output(ledPin, GPIO.LOW)
		time.sleep(0.5)
except KeyboardInterrupt:
	GPIO.output(ledPin, GPIO.LOW)
	GPIO.cleanup()


print '... done.'
