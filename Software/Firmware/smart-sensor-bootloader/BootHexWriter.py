import serial
import time

ser = serial.Serial('COM6')
ser.baudrate = 9600

lines = []
file = open('uploadtest.hex', 'r', encoding='utf-8' )
lines = file.readlines()
file.close()

ser.write(b'HEX')
time.sleep(10)
for line in lines:
    ser.write(bytes(line, 'utf-8'))
    time.sleep(1)
    result = ser.read_all()
    for i in range(len(result)):
        print(result[i])
    print(result)
time.sleep(10)
ser.write(b'O')
time.sleep(10)
hexresultfromarray = ser.read_all()
for val in hexresultfromarray:
    for i in range(len(result)):
        print(result[i])
        time.sleep(1)
ser.close()