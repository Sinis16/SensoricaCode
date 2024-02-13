////Librerias
#include Servo

////Pines (Estan solo los que se necesitan, no cuantos pines requieren)

///ACTUADORES

/* 
//EVA
ServoCaja1
ServoCaja2
ServoCaja3
ServoDispensador

MotorLimpieza (manejado conL293D)

MotoresVibracion (Manejado con un solo pin de rele)

Luz (Manejado con un solo pin de rele)

Nema17
*/

/*
//RAMSES
ServoNivelacion

Motorreductor (Manejado con un solo pin de rele)

MotorTamiz (Manejado con un solo pin de rele)

Nema23
*/

///Sensores

/* 
//EVA
MQ4
MQ7
MQ8
FinDeCarrera (Es un switch y ya)
Peso (Hx711 y load cell)
*/

/*
//RAMSES
Temperatura Ds18b20
Humedad :)
*/

////Variables (Poner las necesarias por coso)

//ServoCaja1 (Ejemplo)

//ServoCaja2


///Funciones

//Escoge un servo, se toma su posicion actual y se lleva a la destino
void moverServo (int servo, int posActual, int posDestino) {

}

//Prende o apaga los motores de vibracion
void motoresVibracion() {

}

//Prende o apaga la luz que apunta a las cajas
void luz() {
    
}

//Desplazar un nema hacia la derecha, izquiera o parar 
//(Considerar que se fijen distancias para que se pueda solo parar en la mitad de las cajas, esto en una posible segunda funcion de prueba)
void desplazarNema(int nemaVar1, int nemaVar2, int desplazamiento) {

}

//Prende o apaga el motorreductor que excava
void excavar() {
    
}


//Prende o apaga el motor que tamiza
void tamizar() {

}


void setup() {
  Serial.begin(9600);
}
void loop() {

}