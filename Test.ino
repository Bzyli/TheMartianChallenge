#include "Shelper.h"
#define DELAY 400

Shelper shelper(7);

String key;
int pos = 0;
char positions[17] = "0123456789ABCDEF";

void setup() {
    Serial.begin(9600);
    shelper.gotopos(0);
}

String decToHex(byte decValue, byte desiredStringLength) {
  
    String hexString = String(decValue, HEX);
    while (hexString.length() < desiredStringLength) hexString = "0" + hexString;
  
  return hexString;
}

int getfirstpos(String order) {
        for(int i = 0; i < 16; i++) {
          if(order.substring(0, 1) == String(positions[i]) ) return (i*12 + 12);
        }
}

int getsecondpos(String order) {
        for(int i = 0; i < 16; i++) {
          if(order.substring(1) == String(positions[i])) return (i*12 + 12);
        }
}

// TODO : FIX the issue with the two above functions, they should iterate trhough our 

void loop() {
     if (Serial.available() > 0) {
        key = decToHex(Serial.read(), 2);
        Serial.println(key.substring(0,1));
        Serial.println(key.substring(1));
        Serial.println(getfirstpos(key));
        Serial.println(getsecondpos(key));
        shelper.gotopos(getfirstpos(key));     // Point to first Hex Char 
        delay(DELAY);                          // Wait a bit so we can read it
        shelper.gotopos(getsecondpos(key));    // Point to second Hex Char
        delay(DELAY);                          // Wait again
        shelper.gotopos(0);                    // Goes back to origin
  }
}