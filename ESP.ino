//Comunicacion Serial hacia el Arduino. Imprime los valores recibidos por el Arduino.
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; 
  }
}

void loop() {
  if (Serial.available()) {
    Serial.write(Serial.read());
  }
}
