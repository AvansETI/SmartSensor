import serial
import time

ser = serial.Serial('COM6')

lines = []
file = open('uploadtest.hex', 'r')
lines = file.readlines()
file.close()

ser.write(b'HEX')
time.sleep(10)
for line in lines:
    ser.write(bytes(line, 'utf-8'))
    time.sleep(1)
time.sleep(10)
ser.write(b'O')