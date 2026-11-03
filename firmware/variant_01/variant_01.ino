#include <DHT.h>
#include <math.h>
const byte PIN_NTC=A0, PIN_SOIL=A1, PIN_DHT=2, PIN_RELAY=7, PIN_LED=8;
const unsigned long T_MS=1000, DHT_MS=2000;
const float SOIL_THRESHOLD=30.0;
// Реле Wokwi (transistor=npn) включается высоким уровнем на входе IN. Проверено в симуляции:
// при THRESHOLD (HIGH на D7) индикатор на модуле реле горит, при NORMAL (LOW) погашен.
const byte RELAY_ON=HIGH, RELAY_OFF=LOW;
DHT dht(PIN_DHT,DHT22);
unsigned long n=0, lastSample=0, lastDht=0;
float humidity=NAN;
bool alarm=false;
void outputs(bool on){
 digitalWrite(PIN_RELAY,on?RELAY_ON:RELAY_OFF);
 digitalWrite(PIN_LED,on?HIGH:LOW);
}
void valueOut(float v){
 if(isnan(v)||isinf(v)) Serial.print("ERROR");
 else Serial.print(v,2);
}
void setup(){
 Serial.begin(9600);
 digitalWrite(PIN_RELAY,RELAY_OFF);
 digitalWrite(PIN_LED,LOW);
 pinMode(PIN_RELAY,OUTPUT); pinMode(PIN_LED,OUTPUT);
 pinMode(PIN_NTC,INPUT); pinMode(PIN_SOIL,INPUT);
 dht.begin(); outputs(false);
 // Прогрев DHT22. Первая DATA — через 1 с после точки отсчёта.
 delay(2000);
 humidity=dht.readHumidity(); lastDht=millis(); lastSample=lastDht;
}
void loop(){
 unsigned long now=millis();
 if((unsigned long)(now-lastSample)<T_MS) return;
 // При задержке не генерируем фиктивные догоняющие замеры.
 lastSample=now;
 if((unsigned long)(now-lastDht)>=DHT_MS){
  humidity=dht.readHumidity(); lastDht=now;
 }
 ++n;
 float s1=50.0*analogRead(PIN_NTC)/1023.0;
 float s3=100.0*analogRead(PIN_SOIL)/1023.0;
 Serial.print("DATA n="); Serial.print(n);
 Serial.print(" s1="); valueOut(s1);
 Serial.print(" s2="); valueOut(humidity);
 Serial.print(" s3="); valueOut(s3); Serial.println();
 // Управление по исходному значению, а не округлённому Serial.
 bool dry=s3<SOIL_THRESHOLD;
 if(dry!=alarm){
  alarm=dry; outputs(alarm);
  Serial.print("EVENT n="); Serial.print(n);
  Serial.println(alarm?" type=THRESHOLD":" type=NORMAL");
 }
}
