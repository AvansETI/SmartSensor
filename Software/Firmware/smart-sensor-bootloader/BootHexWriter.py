from asyncio.windows_events import NULL
from re import L
import serial
import time

# function for sending various strings
def sendstring(string):
    ser.write(bytes(string, 'utf-8'))
    time.sleep(1)

# functions for starting update
def startUpdate():
    sendstring('U')
    time.sleep(1)

# function dealing with various responses
def recieveresponse(recieved):

    print(recieved)
    #if R start update
    if recieved == 'R':
        sendstring(lines[linepos])
        time.sleep(1)
    #if X send next line and increase linepos, if at the last line send O
    elif recieved == 'X':
        linepos = linepos + 1
        if lines[linepos] != NULL:
            sendstring(lines[linepos])
        else:
            sendstring('O')
            checkgoing = False
        time.sleep(1)
    #if W then resend the last line
    elif recieved == 'W':
        sendstring(lines[linepos])
        time.sleep(1)
    #if T timeout error, restart update by sending U
    elif recieved == 'T':
        startUpdate()
        time.sleep(1)
    #if G completely unexpected error, restart program
    elif recieved == 'G':
        time.sleep(1)
    #this should never be reached but if it is restart
    else:
        print(recieved)

# Open the serial port on COM6 (can be changed for a different port if needed)
ser = serial.Serial('COM6')
ser.baudrate = 9600

# Open the file and store its contents in an array, then close it
lines = []
file = open('uploadtest.hex', 'r', encoding='utf-8' )
lines = file.readlines()
file.close()
linepos = 0
checkgoing = True

startUpdate()
while checkgoing:
    recieveresponse(ser.read())
ser.close()

# ser.write(b'HEX')
# time.sleep(10)
# for line in lines:
#     ser.write(bytes(line, 'utf-8'))
#     time.sleep(1)
#     result = ser.read_all()
#     for i in range(len(result)):
#         print(result[i])
#     print(result)
# time.sleep(10)
# ser.write(b'O')
# time.sleep(10)
# hexresultfromarray = ser.read_all()
# for val in hexresultfromarray:
#     for i in range(len(result)):
#         print(result[i])
#         time.sleep(1)
# ser.close()

