import serial
import time

ser = serial.Serial('/dev/ttyACM3', baudrate=9600)

texto=''

while True:
    comando = input("Introduzca un comando: ")
    ser.write(str.encode(comando))
    line = ser.readline().decode('utf-8').rstrip()
    print(line)
    time.sleep(1)
    """ while arduino.inWaiting()>0:
        texto += arduino.read(1)
    print(texto)
    texto = '' """

arduino.close()
