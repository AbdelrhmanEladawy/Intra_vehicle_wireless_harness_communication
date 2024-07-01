import Adafruit_BBIO.GPIO as GPIO
from time import sleep

out_pin = "P9_12"
GPIO.setup(out_pin, GPIO.OUT)

for i in range(0,5) :
    GPIO.output(out_pin , GPIO.HIGH)
    sleep(3)
    GPIO.output(out_pin , GPIO.LOW)
    sleep(3)
GPIO.cleanup()
