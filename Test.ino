#include "Shelper.h"

Shelper shelper(7);

void setup() {
    Serial.begin(9600);
}

String decToHex(byte decValue, byte desiredStringLength) {
  
  String hexString = String(decValue, HEX);
  while (hexString.length() < desiredStringLength) hexString = "0" + hexString;
  
  return hexString;
}

void loop() {
    /*  if (Serial.available() > 0) {
        Serial.print("We got this as decimal : ");
        Serial.println(Serial.read(), DEC);
        Serial.print("Which means we have this as HEX: ");
        Serial.println(decToHex(Serial.read(), 2));
  }*/
 shelper.gotopos(100);
 delay(1000);
 shelper.gotopos(0);
 delay(1000);
}