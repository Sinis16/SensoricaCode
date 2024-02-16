////Librerias
#include <Servo.h>
#include <Arduino.h>
#include "HX711.h"
#include <OneWire.h>                
#include <DallasTemperature.h>

////Pines (Estan solo los que se necesitan, no cuantos pines requieren)

///SENSORES

//EVA

//FinDeCarrera
const int finDeCarrera = 53; 

//Peso
const int LOADCELL_DOUT_PIN = 51;
const int LOADCELL_SCK_PIN = 49;

//MQ4
const int MQ4_AOPin=0;

//MQ7
const int MQ7_AOPin=1;

//MQ8
const int MQ8_AOPin=2;


//RAMSES

//Temperatura
OneWire ourWire(13);  
DallasTemperature sensors(&ourWire);

//Humedad
const int HM_Pin=3;

///ACTUADORES

//EVA

//ServoCaja1
Servo servoCaja1; 

//ServoCaja2
Servo servoCaja2; 

//ServoCaja3
Servo servoCaja3;

//ServoDistribuidor
Servo servoDistribuidor;

//Limpieza L293D

const int limpieza1  = 37;
const int limpieza2  = 39; 

//Nema17
#define dirPin17 45
#define stepPin17 47

//luz
#define luzPin 41

//vibracionCajas
#define VibracionCajas 43


//RAMSES

//ServoNivelacion
Servo servoNivelador;

//Tamiz
#define tamiz 11

//Extraccion
#define extraccion 12

//Nema23
#define dirPin23 8
#define stepPin23 9

////Variables

//MQ4 Output
int AO_Out4;

//MQ7 Output
int AO_Out7;

//MQ8 Output
int AO_Out8;

//temp
float temp;


//Servos
int posCaja1 = 0;
int posCaja2 = 0;
int posCaja3 = 0;
int posDistruibor = 0;

//Nema 17
#define stepsPerRevolution 200

//Servo RAMSES
int posNivelacion = 0;

//Nema23
#define stepsPerRevolution 200




///Funciones

void sensoresRamses() {
  
  Serial.println("Humedad");
  Serial.println(analogRead(HM_Pin));
  delay(100);

  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);
  Serial.println("Temperatura");
  Serial.print(temp);
  Serial.println(" C");
  delay(100);
}

void sensoresEVA() {
  AO_Out4 = analogRead(MQ4_AOPin); // Read the analog output measurement sample from the MQ4 sensor's AO pin
  AO_Out7 = analogRead(MQ7_AOPin);
  AO_Out8 = analogRead(MQ8_AOPin);

  Serial.print("Methane Conentration: ");
  Serial.println(AO_Out4); // Print out the methane value - the analog output - beteewn 0 and 1023
  Serial.print("Monoxide Conentration: ");
  Serial.println(AO_Out7);
  Serial.print("Hydrogen Conentration: ");
  Serial.println(AO_Out8);
  //delay(1000);
}


//Escoge un servo, se toma su posicion actual y se lleva a la destino
void moverServo (int servo, int posActual, int posDestino) {
  for (pos = posActual; pos <= posDestino; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoCaja1.write(pos);              // tell servo to go to position in variable 'pos'
    servoCaja2.write(pos);   
    servoCaja3.write(pos);              // tell servo to go to position in variable 'pos'
    servoRamses.write(pos);              // tell servo to go to position in variable 'pos'
    servoServidor.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);
                           // waits 15ms for the servo to reach the position
  }
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

  Serial.begin(57600);

  //Sensor Temp
  sensors.begin();

  //Servos EVA
  servoCaja1.attach(33);   
  servoCaja2.attach(31);   
  servoCaja3.attach(29);   
  servoDistribuidor.attach(35);

  //Relays EVA
  pinMode(tamiz, OUTPUT);
  pinMode(extraccion, OUTPUT);

  //Limpieza
  pinMode(limpieza1, OUTPUT);
  pinMode(limpieza2, OUTPUT);

  //Nema 17
  pinMode(stepPin17, OUTPUT);
  pinMode(dirPin17, OUTPUT);

  //FinDeCarrera
  pinMode(finDeCarrera, INPUT);




  //Servo RAMSES
  servoNivelador.attach(10);  

  //Relays RAMSES
  pinMode(luz, OUTPUT);
  pinMode(VibracionCajas, OUTPUT);

  //Nema 23
  pinMode(stepPin23, OUTPUT);
  pinMode(dirPin23, OUTPUT);

  

}
void loop() {

  sensoresRamses();
  sensoresEVA();
  delay(1000);

}