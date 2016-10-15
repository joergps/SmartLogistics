#!/usr/bin/env python
# Taken from http://picamera.readthedocs.io/en/release-1.12/recipes1.html
from picamera import PiCamera
from time import sleep
from time import time
import os

sleep(1)

camera = PiCamera()
camera.resolution = (1024, 768)
# camera.start_preview()

# Camera warm-up time
sleep(2)
# camera.capture('/opt/fhem/www/tablet/images/image.jpg')
camera.capture('image.jpg')
url='curl http://localhost:8083/fhem?cmd=setreading%20picture%20current_file%20image.jpg'
currentTime=time()
os.system(url + '?' + str(currentTime))
# camera.capture('image.jpg')
camera.close()
