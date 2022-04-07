from asyncio.windows_events import NULL
from audioop import add
from re import L
import serial
import time


# function for sending various strings
def sendstring(string):
    for i in range (len(string)):
        ser.write(bytes(string[i], 'utf-8'))
        time.sleep(0.06)

# functions for starting update
def startUpdate():
    sendstring('U')
    time.sleep(1)

# function dealing with various responses
def recieveresponse(recieved):
    global linepos, lines, checkgoing


    print(recieved)

    # # debug to check if it matches the expected return
    # expectedCharArray = [x for x in lines[linepos]]
    # address = "0x" + expectedCharArray[3] + expectedCharArray[4] + expectedCharArray[5] + expectedCharArray[6]
    # intAddress = hex(int(address,16)/2)
    # print('Expected: Address: ' + intAddress )


    #if R start update
    if b'R' in recieved:
        sendstring(lines[linepos])
        time.sleep(1)
    #if X send next line and increase linepos, if at the last line send O
    elif b'X' in recieved:
        linepos = linepos + 1
        if linepos < len(lines):
            sendstring(lines[linepos])
        else:
            sendstring('O')
            checkgoing = False
        time.sleep(1)
    #if W then resend the last line
    elif b'W' in recieved:
        sendstring(lines[linepos])
        time.sleep(1)
    #if T timeout error, restart update by sending U
    elif b'T' in recieved:
        startUpdate()
        time.sleep(1)
    #if G completely unexpected error, restart program
    elif b'G' in recieved:
        time.sleep(1)
    # #this should never be reached but if it is restart
    # else:
    #     print(recieved)

# Open the serial port on COM6 (can be changed for a different port if needed)
ser = serial.Serial('COM6')
ser.baudrate = 9600

# Open the file and store its contents in an array, then close it
lines = []
# file = open('uploadtest.hex', 'r', encoding='utf-8' )
file = open('blinkingtest.hex', 'r', encoding='utf-8' )
lines = file.readlines()
file.close()
linepos = 0
checkgoing = True

startUpdate()
while checkgoing:
    # result = ser.read_all()
    # for i in range(len(result)):
    #     print(result)
    #     recieveresponse(result)
    # # print(result)
    recieveresponse(ser.read_all())
    time.sleep(3)
time.sleep(10)
# result = ser.read_all()
# compare = []
# for i in range (len(result)):
#     compare.append(result[i])
# print(compare)
# print(result)
print('Done')
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

