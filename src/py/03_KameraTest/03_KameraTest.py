#!/usr/bin/env python
import RPi.GPIO as GPIO
from picamera import PiCamera
from time import sleep


print '3_KameraTest started...'

camera = PiCamera()
camera.start_preview()
sleep(10)
camera.stop_preview()


print '... done.'
