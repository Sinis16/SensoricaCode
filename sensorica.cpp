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
HX711 balanza(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

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

//ServoDistribucion
Servo servoDistribucion;

//Limpieza L293D

const int limpieza1  = 37;
const int limpieza2  = 39; 

//Nema17
#define dirPin17 45
#define stepPin17 47

//luz
#define luzPin 41

//vibracionCajas
#define vibracionCajas 43


//RAMSES

//ServoNivelacion
Servo servoNivelacion;

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

//Peso
float peso;
int promMedicion;
int pesoConocido;

//Servos
int posCaja1 = 0;
int posCaja2 = 0;
int posCaja3 = 0;
int posDistribucion= 0;

//StateDeRelays
int luzState = 0;
int vibracionCajasState = 0;
int tamizState = 0;
int extraccionState = 0;

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

  Serial.print("Peso: ");
  Serial.print(peso, 1);
  Serial.println(" g");
  delay(100);

    Serial.print("Methane Conentration: ");
  Serial.println(AO_Out4); // Print out the methane value - the analog output - beteewn 0 and 1023
  Serial.print("Monoxide Conentration: ");
  Serial.println(AO_Out7);
  Serial.print("Hydrogen Conentration: ");
  Serial.println(AO_Out8);
  //delay(1000);
}

void calibrarPeso() {
  int escala = promMedicion/pesoConocido; // Relación entre el promedio de las mediciones analogas con el peso conocido en gramos 
  balanza.set_scale(escala);
}

void sensorPeso() {
  //Sensor de peso
  float peso = balanza.get_units(10); // Entrega el peso actualment medido en gramos
  if(peso<0) peso = peso*-1;
  if(peso*0.9882 - 0.1129);
  if(peso<0.5) peso = 0;
  delay(1000);
  Serial.println(peso);

}

void activarServo (int numServo, int posDestino) {
  if (numServo == 1) {
    posCaja1 = moverServo(servoCaja1, posCaja1, posDestino);
  }
  else if (numServo == 2) {
    posCaja2 = moverServo(servoCaja2, posCaja2, posDestino);
  }
  else if (numServo == 3) {
    posCaja3 = moverServo(servoCaja3, posCaja3, posDestino);
  }
  else if (numServo == 4) {
    posDistribucion = moverServo(servoDistribucion, posDistribucion, posDestino);
  }
  else if (numServo == 5) {
    posNivelacion = moverServo(servoNivelacion, posNivelacion, posDestino);
  }

}

//Escoge un servo, se toma su posicion actual y se lleva a la destino
int moverServo (Servo servo, int posActual, int posDestino) {
  int inc = 0;
  int pos;
  //Serial.println("ServoComienza");
  //Serial.print(posActual);
  //Serial.print(posDestino);

  if ((posActual - posDestino) > 0) {
    int inc = -1;
  }
  else {
    inc = 1;
  }

  for (pos = posActual; pos <= posDestino; pos += inc) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);
                           // waits 15ms for the servo to reach the position
  }
  return posDestino;
}

void limpiar(int dir) {
  if(dir == 0) {
    digitalWrite(limpieza1, LOW);
    digitalWrite(limpieza2, LOW);
  }
  else if(dir == 1) {
    digitalWrite(limpieza1, LOW);
    digitalWrite(limpieza2, HIGH);
  }
  else if(dir == 2) {
    digitalWrite(limpieza1, HIGH);
    digitalWrite(limpieza2, LOW);
  }
}

//Prende o apaga los motores de vibracion
void motoresVibracion() {
  int vibracionState = 1;
  if (vibracionState == 1) {
    vibracionState = 0;
  }
  else if (vibracionState == 0) {
    vibracionState = 1;
  }

  digitalWrite(vibracionCajas,vibracionState);

}

//Prende o apaga la luz que apunta a las cajas
void luz() {
  if (luzState == 1) {
    luzState = 0;
  }
  else if (luzState == 0) {
    luzState = 1;
  }
  digitalWrite(luzPin,luzState);
}

//Desplazar un nema hacia la derecha, izquiera o parar 
//(Considerar que se fijen distancias para que se pueda solo parar en la mitad de las cajas, esto en una posible segunda funcion de prueba)
void desplazarNema(int dirPin, int stepPin, int dir, int steps, int speed) {
  //Default: NEMA, 1, 2, 1
  //dir: 1 clockwise, 0 anticlockwise
  //speed: 0 a 3, NO MAS
  //Steps: Determinar largo TODO
  int vel = 2000 - speed*500;
  if (vel < 500) vel = 500;

  digitalWrite(dirPin17, dir);

  for (int i = 0; i < steps * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin17, HIGH);
    delayMicroseconds(vel);
    digitalWrite(stepPin17, LOW);
    delayMicroseconds(vel);
  }
}

void devolverNema17() {
  //Default: NEMA, 1, 2, 1
  //dir: 1 clockwise, 0 anticlockwise
  //speed: 0 a 3, NO MAS
  //Steps: Determinar largo TODO

  int dir = 1;
  
  digitalWrite(dirPin17, dir);

  while (!finDeCarrera) {
    // These four lines result in 1 step:
    digitalWrite(stepPin17, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin17, LOW);
    delayMicroseconds(2000);
  }
}

void moverNema(int nema, int dir, int steps, int speed) {
  if (nema == 0) {
    desplazarNema(dirPin17, stepPin17, dir, steps, speed);
  }
  else if (nema == 1) {
    desplazarNema(dirPin23, stepPin23, dir, steps, speed);
  }
  else if (nema == 2) {
    devolverNema17();
  }
}

//Prende o apaga el motorreductor que excava
void excavar() {
  if (extraccionState == 1) {
    extraccionState = 0;
  }
  else if (extraccionState == 0) {
    extraccionState = 1;
  }
  digitalWrite(extraccion,extraccionState); 
}


//Prende o apaga el motor que tamiza
void tamizar() {
  if (tamizState == 1) {
    tamizState = 0;
  }
  else if (tamizState == 0) {
    tamizState = 1;
  }
  digitalWrite(tamiz,tamizState);
}


void setup() {

  Serial.begin(57600);

  //Sensor Peso
  calibrarPeso();

  //Sensor Temp
  sensors.begin();

  //Servos EVA
  servoCaja1.attach(33);   
  servoCaja2.attach(31);   
  servoCaja3.attach(29);   
  servoDistribucion.attach(35);

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
  servoNivelacion.attach(10);  

  //Relays RAMSES
  pinMode(luz, OUTPUT);
  pinMode(vibracionCajas, OUTPUT);

  //Nema 23
  pinMode(stepPin23, OUTPUT);
  pinMode(dirPin23, OUTPUT);

  

}

void coreografiaNoCoordinada() {
  activarServo(1, 180);
  delay(500);
  activarServo(1, 0);
  delay(500);

  activarServo(2, 180);
  delay(500);
  activarServo(2, 0);
  delay(500);

  activarServo(3, 180);
  delay(500);
  activarServo(3, 0);
  delay(500);

  activarServo(4, 180);
  delay(500);
  activarServo(4, 0);
  delay(500);

  //Prueba Limpieza
  limpiar(2);
  delay(1500);
  limpiar(1);
  delay(1500);
  limpiar(0);

  //MotoresVibracion
  motoresVibracion();
  delay(1500);
  motoresVibracion();

  //Luz
  luz();
  delay(1500);
  luz();

  //Nema17
  moverNema(0, 1, 2, 1); 

  //Nema23
  moverNema(1, 1, 3, 1); 

  //ServoNivelador
  activarServo(5, 180);
  delay(500);
  activarServo(5, 0);
  delay(500);

  //MotoresVibracion
  excavar();
  delay(1500);
  excavar();

  //MotoresVibracion
  tamizar();
  delay(1500);
  tamizar();

  //TODO Balancear excavacion y nivelacion, revisar que sentido de nema va al fin de carrera, revisar Sensor de peso
  delay(1000);
}

void loop() {

  coreografiaNoCoordinada();

  //sensoresRamses();
  //sensoresEVA();

  ///Prueba Servo
  

}