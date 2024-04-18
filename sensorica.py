#!/usr/bin/env python3
import serial
import time
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 57600, timeout=1)
    ser.reset_input_buffer()
    while True:
        userInput = input("Enter data to send to Arduino: ")
        ser.write(userInput + "\n")
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        time.sleep(1)




