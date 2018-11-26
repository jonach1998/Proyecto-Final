//Configuracion para Arduino Mega
//Leer valor de un POT y enviarlo por el puerto Serial1 del Arduino hacia el ESP
int potPin= A0; 
int readValue;  
String str;

void setup(){
 pinMode(potPin, INPUT);
 Serial.begin(115200);
 Serial1.begin(115200);
 Serial.println("Iniciar");
}
void loop()
{
 readValue = analogRead(potPin); 
 Serial.print("Valor: ");
 Serial.println(readValue);
 str =String(readValue);
 Serial1.println(str);
 delay(1000);
}
