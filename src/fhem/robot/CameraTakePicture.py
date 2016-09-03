#!/usr/bin/env python
# Taken from http://picamera.readthedocs.io/en/release-1.12/recipes1.html
from picamera import PiCamera
from time import sleep

camera = PiCamera()
camera.resolution = (1024, 768)
# camera.start_preview()

# Camera warm-up time
sleep(3)
camera.capture('/opt/fhem/www/tablet/image.jpg')
# camera.capture('image.jpg')
camera.close()
