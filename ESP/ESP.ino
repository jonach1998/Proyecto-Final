//Comunicacion Serial hacia el Arduino. Imprime los valores recibidos por el Arduino.
void setup() {
  //Inicia comunicación serial
  Serial.begin(115200);
  while (!Serial) {
    ; 
  }
}

void loop() {
  //Leer los valores recibidos por la comunicación serial
  if (Serial.available()) {
    Serial.write(Serial.read());
  }
}
