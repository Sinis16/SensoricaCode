#!/usr/bin/env python3
import serial
import random
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 57600, timeout=1)
    ser.reset_input_buffer()
    
    while True:
        number = ser.read()
        print(number)
        if number != (b'0' or b'') :
            led_number = random.randint(1,4)
            print("Button has been pressed.")
            print("Sending number " + str(led_number) + " to Arduino.")
            ser.write(str(led_number).encode('utf-8'))