# http://www.netzmafia.de/skripten/hardware/RasPi/RasPi_SPI.html
# http://erik-bartmann.de/component/attachments/download/21.html

import time;
import RPi.GPIO as GPIO
import os

os.system('perl /opt/fhem/fhem.pl 7072 "setreading FSR PID '+str(os.getpid())+'"')


GPIO.setmode(GPIO.BCM)  # GPIO-Pin Bezeichnungen verwenden
GPIO.setwarnings(False) # Warnungen deaktivieren

def readAnalogData(adcChannel, SCLKPin, MOSIPin, MISOPin, CSPin, delay):
    """ Funktionsdefinition """
    # Negative Flanke des CS-Signals generieren
    GPIO.output(CSPin,   GPIO.HIGH)
    GPIO.output(CSPin,   GPIO.LOW)
    GPIO.output(SCLKPin, GPIO.LOW)   
    sendCMD = adcChannel
    sendCMD |= 0b00011000 # Entspricht 0x18 (1: Startbit, 1: Single/ended)
    # Senden der Bitkombination (Es finden nur 5 Bits Beruecksichtigung)
    for i in range(5):
        if(sendCMD & 0x10): # Bit an Position 4 pruefen.
            GPIO.output(MOSIPin, GPIO.HIGH)
        else:
            GPIO.output(MOSIPin, GPIO.LOW)
        # Negative Flanke des Clock-Signals generieren
        GPIO.output(SCLKPin, GPIO.HIGH)
        GPIO.output(SCLKPin, GPIO.LOW)
        sendCMD <<= 1 # Bitfolge eine Position nach links schieben
    # Empfangen der Daten des AD-Wandlers
    adcValue = 0 # Reset des gelesenen Wertes
    for i in range(11):
        # Negative Flanke des Clock-Signals generieren
        GPIO.output(SCLKPin, GPIO.HIGH)
        GPIO.output(SCLKPin, GPIO.LOW)
        adcValue <<= 1 # Bitfolge 1 Position nach links schieben
        if(GPIO.input(MISOPin)):
            adcValue |=0x01
    time.sleep(delay) # Kurze Pause
    return adcValue

def setupGPIO(SCLKPin, MOSIPin, MISOPin, CSPin):
    """ GPIO-Pin Setup """
    GPIO.setup(SCLKPin, GPIO.OUT)
    GPIO.setup(MOSIPin, GPIO.OUT)
    GPIO.setup(MISOPin, GPIO.IN)
    GPIO.setup(CSPin,   GPIO.OUT)

# Variablendefinition
ADCChannel = 0   # AD-Kanal
SCLK       = 11  # Serial-Clock
MOSI       = 10  # Master-Out-Slave-In
MISO       = 9  # Master-In-Slave-Out
CS         = 8   # Chip-Select
PAUSE      = 0.5 # Anzeigepause

setupGPIO(SCLK, MOSI, MISO, CS) # GPIO-Pin Setup

   
try:
    while True:
        os.system('perl /opt/fhem/fhem.pl 7072 "setreading FSR Druck '+str(readAnalogData(ADCChannel, SCLK, MOSI, MISO, CS, PAUSE))+'"')
finally:
    GPIO.cleanup()

#result = readAnalogData(ADCChannel, SCLK, MOSI, MISO, CS, PAUSE)
#os.system('perl /opt/fhem/fhem.pl 7072 "setreading FSR Druck '+str(result)+'"')
#GPIO.cleanup()
