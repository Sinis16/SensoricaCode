void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    char c = Serial.read();
    if (c=='H'){
      Serial.println("H Pulsada");
    } else if (c=='L') {
      Serial.println("L Pulsada");
    } else {
      Serial.println("Caracter no reconocido");
    }
  }
}
