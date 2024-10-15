#include <math.h>
#define LIGHT_SENSOR 13
const int ledpin = 12;
const int thvalue = 50;
float Rsensor;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, INPUT);
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(LIGHT_SENSOR);
  Rsensor = (float)(4095-sensorValue)*10/sensorValue;

  Serial.println(Rsensor);

  if(Rsensor>=thvalue){
    digitalWrite(ledpin, HIGH);
    Serial.println("HIGH");

  }
  else{
    digitalWrite(ledpin, LOW);
    Serial.println("LOW");

  }
  delay(500);
} 
