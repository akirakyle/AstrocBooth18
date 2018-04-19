#!/usr/bin/python

import RPi.GPIO as GPIO
from subprocess import Popen
from datetime import datetime
import time

url = 'file:///root/AstrocBooth18/QuickLoadTestBuild/index.html'

shutdownPin = 5 # unique pin will wake Raspberry Pi when button is pressed
shutdownMinSeconds = 1

reloadPin = 13
reloadMinSeconds = 0.2

GPIO.setmode(GPIO.BOARD)
GPIO.setup(shutdownPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(reloadPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

shutdownButtonPressedTime = None
reloadButtonPressedTime = None

def shutdownButtonChanged(pin):
    global shutdownButtonPressedTime

    if not (GPIO.input(pin)):
        if shutdownButtonPressedTime is None:
            shutdownButtonPressedTime = datetime.now()
    else:
        if shutdownButtonPressedTime is not None:
            elapsed = (datetime.now() - buttonPressedTime).total_seconds()
            shutdownButtonPressedTime = None
            if elapsed >= shutdownMinSeconds:
                print("shutting down...")
                Popen(['poweroff'])

wpeProc = None
def reloadButtonChanged(pin):
    global reloadButtonPressedTime
    global wpeProc

    if not (GPIO.input(pin)):
        if reloadButtonPressedTime is None:
            reloadButtonPressedTime = datetime.now()
    else:
        if reloadButtonPressedTime is not None:
            elapsed = (datetime.now() - buttonPressedTime).total_seconds()
            reloadButtonPressedTime = None
            if elapsed >= reloadMinSeconds:
                print("reloading wpe...")
                if wpeProc is not None:
                    wpeProc.terminate()
                Popen(['wpe', url])


GPIO.add_event_detect(shutdownPin, GPIO.BOTH, callback=shutdownButtonChanged)
GPIO.add_event_detect(reloadPin, GPIO.BOTH, callback=reloadButtonChanged)

while True:
    time.sleep(5)
