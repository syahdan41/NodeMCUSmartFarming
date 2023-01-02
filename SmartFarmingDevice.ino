#include "DHT.h"

const int moistPin= A0;/* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
const int lightPin = D3;


#define triggerPin D7
#define echoPin D8
#define relay D4
#define tempPin D2
#define DHTTYPE DHT22

DHT dht(tempPin, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();/* Define baud rate for serial communication */
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(relay, OUTPUT);
  pinMode(moistPin, INPUT);
  pinMode(lightPin, INPUT);
}

void loop() {
  float moistVal;
  int nilaiADC = analogRead(moistPin);
  moistVal= ( 100 - ( (nilaiADC/1023.00) * 100 ) );

  if(moistVal <= 50){
    digitalWrite(relay,LOW);
    delay(1000);
  }
  else{
    digitalWrite(relay,HIGH);
    delay(1000);
  }
  

  long durasi, jarak;  //Varibel durasi dan jarak
  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  durasi = pulseIn(echoPin, HIGH);
  jarak = (durasi/2) / 29;  //Perhitungan untuk pembacaan jarak

  if(jarak == 45){
    Serial.println("Level Air Cukup");
    delay(1000);
  }

  else if(jarak <45 && jarak >=30){
    Serial.println("Level Air Sedang");
    delay(1000);
  }

  else if(jarak == 0){
    Serial.println("Air Habis");
    delay(1000);
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  delay(2000);
  
  int lightIntens = digitalRead(lightPin);

  Serial.print("\n");
  Serial.print("<------Soil Moisture------->");
  Serial.print("\nKelembaban tanah = ");
  Serial.print(moistVal);
  Serial.print("%\n");
  delay(1000);

  Serial.print("\n<------Water Level------->\n");
  Serial.print("Level Ketinggian Air = ");
  Serial.print(jarak);
  Serial.print("cm\n");
  Serial.print("\n");
  delay(1000);

  Serial.print("<------Sensor Cahaya------>\n");
  Serial.print("Intensitas Cahaya =  ");
  Serial.println(lightIntens);
  Serial.print("\n");
  delay(1000); 
  
  Serial.print("<------Sensor Suhu------>\n");
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print("\n");
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print("°C ");
  Serial.print("\n");

}
