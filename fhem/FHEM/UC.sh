#!/usr/bin/python
#+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#|R|a|s|p|b|e|r|r|y|P|i|-|S|p|y|.|c|o|.|u|k|
#+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#
# Orginal-Script von Author : Matt Hawkins ultrasonic_2.py
# Measure distance using an ultrasonic module
#
# --------------------------------------------------------
#           Import required Python libraries
# --------------------------------------------------------
#
# Veraendert von Ollir (FHEM-Forum) fuer die Rueckgabe an 
# FHEM per Telnet: Port 7072
#

# run the script: script <FHEM UC ID> <TRIGGER GPIO> <ECHO GPIO>

import time
import RPi.GPIO as GPIO
import os
import sys

# --------------------------------------------------------
#                  Define some functions
# --------------------------------------------------------

def measure():
  time.sleep(0.2)
  GPIO.output(GPIO_TRIGGER, True)
  time.sleep(0.0001)
  GPIO.output(GPIO_TRIGGER, False)
  while GPIO.input(GPIO_ECHO)==0:
    start = time.time()
  while GPIO.input(GPIO_ECHO)==1:
    stop = time.time()
  elapsed = stop - start
  distance = elapsed * 17150
  if float(distance) >= 200:
    distance = measure()
  return distance

def measure_average():
  # This function takes 3 measurements and
  # returns the average.
  distance1 = measure()
  distance2 = measure()
  distance3 = measure()
  distance_sum = distance1 + distance2 + distance3
  distance = distance_sum / 3
  return distance

# --------------------------------------------------------
#                        Main Script
# --------------------------------------------------------
# Use BCM GPIO references
# instead of physical pin numbers
GPIO.setmode(GPIO.BCM)
GPIO_TRIGGER = int(sys.argv[2])   #### evtl. GPIO anpassen 
GPIO_ECHO    = int(sys.argv[3])   #### evtl. GPIO anpassen
GPIO.setup(GPIO_TRIGGER,GPIO.OUT)  # Trigger
GPIO.setup(GPIO_ECHO,GPIO.IN)      # Echo
GPIO.output(GPIO_TRIGGER, False)

# --------------------------------------------------------
#                Rueckgabe an FHEM
# --------------------------------------------------------

#distanceRet = "%.1f" % measure_average() # fuer Mittelwert Messung
distanceRet = "%.1f" % measure()        # fuer einmalige Messung
if float(distanceRet) <= 400:
  os.system('perl /opt/fhem/fhem.pl 7072 "setreading '+str(sys.argv[1])+' Abstand '+str(distanceRet)+'"')
  #os.system('perl /opt/fhem/fhem.pl 7072 "setreading UC1 Abstand '+str(distanceRet)+'"')
GPIO.cleanup()