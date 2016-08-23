#!/usr/bin/env python
# Taken from http://www.einplatinencomputer.com/raspberry-pi-ultraschallsensor-hc-sr04-ansteuern-entfernung-messen/
import RPi.GPIO as GPIO
import requests
import time

print 'Starting 04_Ultraschall.py'

# define constants
NO_ELEMENT_DISTANCE = 210 # distance in cm that is returned if no element in front of sensor
SONIC_SPEED = 34300 # sonic speed in cm/s
TRIGGER_TIME = 0.0001 # length of ultra sound trigger in seconds

# define pins
pinTrigger = 11 # pin 11 = GPIO 17
pinEcho = 18 # pin 18 = GPIO 24

# define REST calls
restUri = 'http://localhost:8080'
restParamHasItem = { 'hasItem': 'true' }
restParamNoItem = { 'hasItem': 'false' }

# access numbers by physical location
GPIO.setmode(GPIO.BOARD)

# define GPIOs for trigger and echo
GPIO.setup(pinTrigger, GPIO.OUT)
GPIO.setup(pinEcho, GPIO.IN)

# method to stop distance
def getDistance():
	# fire GPIO for trigger
	GPIO.output(pinTrigger, True)

	# wait 0.01ms and release trigger
	time.sleep(TRIGGER_TIME)
	GPIO.output(pinTrigger, False)

	while GPIO.input(pinEcho) == 0:
		start = time.time()

	while GPIO.input(pinEcho) == 1:
		end = time.time()

	# measure time spent between trigger and echo
	timeDifference = end - start

	# calculate distance with light speed
	result = (timeDifference * SONIC_SPEED) / 2

	return result


if __name__ == '__main__':
	try:
		while True:
			distance = getDistance()
			if (distance < NO_ELEMENT_DISTANCE): 
				print 'Distanz = %.1f cm' % distance
				r = requests.get(restUri, params=restParamHasItem)
				# print r.text
			else:
				requests.get(restUri, params=restParamNoItem)
			time.sleep(1)

	except KeyboardInterrupt:
		print '...Programm beendet.'
		GPIO.cleanup()
