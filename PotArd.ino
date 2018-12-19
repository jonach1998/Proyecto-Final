//Configuracion para Arduino Mega
//Leer valor de un POT y enviarlo por el puerto Serial1 del Arduino hacia el ESP
int potPin= A0; 
int readValue;  
String str;

void setup(){
 pinMode(potPin, INPUT);
 //Iniciar comunicación serial
 Serial.begin(115200);
 Serial1.begin(115200);
 Serial.println("Iniciar");
}
void loop()
{
 //Leer el valor del potenciometro
 readValue = analogRead(potPin); 
 //Imprimir valor en monitor
 Serial.print("Valor: ");
 Serial.println(readValue);
 str =String(readValue);
 //Imprimir valor en el canal de comunicación con el ESP
 Serial1.println(str);
 delay(1000);
}
