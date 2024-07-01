import Adafruit_BBIO.UART as UART
import serial
import time

UART.setup("UART1")

ser = serial.Serial(port = "/dev/ttyS1", baudrate=115200 , timeout=1 )
ser.close()
ser.open()
if ser.isOpen():
	while True:
		print ("Serial is open!")
		ser.write("Hello World!".encode('utf-8'))
		received_data = ser.readline().decode('utf-8').strip()
		print("Received:", received_data)
		time.sleep(1)
ser.close()
