#!/usr/bin/env python

import RPi.GPIO as GPIO
from mfrc522 import SimpleMFRC522

reader = SimpleMFRC522()

import time
GPIO.setwarnings(False)

while True:
    id = 0
    text = ""
    time.sleep(2)
    GPIO.setmode(GPIO.BOARD)
    try:
        id, text = reader.read()
        print("succesfully read " + str(id) + " with code " + text)
    except:
        print("error reading code")


    if id == 7459773699:
        print("correct code\n\n")
        GPIO.setup(12,GPIO.OUT)
        GPIO.output(12,GPIO.LOW)
        time.sleep(3)
        GPIO.cleanup()
    else:
        print("incorrect code\n\n")
        GPIO.cleanup()
        
