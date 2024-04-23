import serial
import time

arduino = serial.Serial('/dev/ttyACM0', baudrate=9600)

texto=''

while True:
    comando = input("Introduzca un comando: ")
    arduino.write(str.encode(comando))
    time.sleep(0.1)
    while arduino.inWaiting()>0:
        texto += arduino.read(1)
    print(texto)
    texto = ''

arduino.close()
