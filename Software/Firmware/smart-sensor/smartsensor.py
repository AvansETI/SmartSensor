import serial
import logging
import threading
import time

def thread_function(ser):
    while (1):
        print(ser.readline())

if __name__ == "__main__":
    ser = serial.Serial('COM9')
    format = "%(asctime)s: %(message)s"
    logging.basicConfig(format=format, level=logging.INFO,
                        datefmt="%H:%M:%S")

    logging.info("Main    : before creating thread")
    x = threading.Thread(target=thread_function, args=(ser,))
    logging.info("Main    : before running thread")
    x.start()
    logging.info("Main    : wait for the thread to finish")
    # x.join()
    logging.info("Main    : all done")

    while (1):
        print("write")
        #ser.write(b"0123456789012345678901234567890123456789\n")
        ser.write(b"ab:test\n")
        time.sleep(60)





