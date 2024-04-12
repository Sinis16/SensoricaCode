##Librerias
#!/usr/bin/env python3
import serial
import time

##Variables Actuadores
# Considerar guardar las variables de posicion

## Coreografias

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 56000, timeout=1)
    ser.reset_input_buffer()

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
        else:
            ser.write(str("Hello from Raspberry Pi!\n").encode('utf-8'))
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            time.sleep(1000)
