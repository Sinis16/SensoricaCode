##Librerias
#!/usr/bin/env python3
import serial
import time

##Variables Actuadores
# Considerar guardar las variables de posicion

##Variables Sensores

##Variables Maquina De Estados


##Funciones

#Escoge un servo, se toma su posicion actual y se lleva a la destino 
#( La otra seria dos funciones diferentes de mover a un lado o al otro). O funciones separadas dependiendo del tipo de servo, que creo que es mejor que se divida en caja, distribucion y nivelacion)
def moverServo(servo, posActual, posDestino) {

}

#Prende o apaga los motores de vibracion
def motoresVibracion() {

}

#Prende o apaga la luz que apunta a las cajas
def luz() {
    
}

#Desplazar un nema hacia la derecha, izquiera o parar 
#(Considerar que se fijen distancias para que se pueda solo parar en la mitad de las cajas, esto en una posible segunda funcion de prueba)
def desplazarNema(int nemaVar1, int nemaVar2, int desplazamiento) {

}

#Prende o apaga el motorreductor que excava
def excavar() {
    
}


#Prende o apaga el motor que tamiza
def tamizar() {

}

## Coreografias


if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.reset_input_buffer()

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
        else:
            ser.write(b"Hello from Raspberry Pi!\n")
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            time.sleep(1)


        