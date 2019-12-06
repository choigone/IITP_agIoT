import RPi.GPIO as GPIO
import time

pin = 5

GPIO.setmode(GPIO.BCM);
GPIO.setup(pin, GPIO.OUT);

while 1:
	print("HIGH")
	GPIO.output(pin,GPIO.HIGH)
	time.sleep(0.5)
	print("LOW")
	GPIO.output(pin,GPIO.LOW)
	time.sleep(0.5)
