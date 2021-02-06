#include <Arduino.h>
#include "BleConnection.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(33, OUTPUT);
  digitalWrite(33,HIGH);
  delay(1000);
  digitalWrite(33,LOW);
  BleConnection.initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
}