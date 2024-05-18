#!/usr/bin/env python3
import serial
import time

def main():
    try:
        # Open serial port
        ser = serial.Serial('/dev/ttyAMA0', 57600, timeout=1)
        ser.reset_input_buffer()
    except serial.SerialException as e:
        print(f"Error opening serial port: {e}")
        return

    while True:
        try:
            userInput = input("Enter data to send to Arduino: ")
            if userInput.lower() == 'exit':
                break
            ser.write((userInput + '\n').encode())
            time.sleep(1)  # Allow some time for Arduino to process and respond
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').rstrip()
                print(f"Received from Arduino: {line}")
            else:
                print("No response received from Arduino.")
        except KeyboardInterrupt:
            print("Exiting...")
            break
        except Exception as e:
            print(f"An error occurred: {e}")

    ser.close()

if __name__ == '__main__':
    main()
