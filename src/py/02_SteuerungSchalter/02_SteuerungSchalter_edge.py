#!/usr/bin/env python
import RPi.GPIO as GPIO
import time
from picamera import PiCamera

inputPin = 32 # pin 32 = GPIO 12

print 'Starting 2_SteuerungSchalter.py'

# access numbers by physical location
GPIO.setmode(GPIO.BOARD)

# define GPIO for LED to be output
GPIO.setup(inputPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

inputPin = GPIO.wait_for_edge(inputPin, GPIO.RISING, timeout=5000)

camera = PiCamera()

if inputPin is None:
	print 'Timeout'
else:
	print 'Edge detected'
	camera.capture('image.jpg')
	print 'Image taken'

GPIO.cleanup()


print '... done.'
