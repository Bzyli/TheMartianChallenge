#include "Shelper.h"
#define DELAY 300
#define STEPBTWPOS 15

Shelper shelper(7); // Initialize the stepper class so we can use it's methods later

String key;
int pos = 0;
char positions[17] = "0123456789abcdef";

void setup() {
    Serial.begin(9600);
    shelper.gotopos(0);
}

// This function convert the byte that we have with the Serial connection to a two char string
String decToHex(byte decValue, byte desiredStringLength) {
  
    String hexString = String(decValue, HEX);
    while (hexString.length() < desiredStringLength) hexString = "0" + hexString;
  
  return hexString;
}

// Returns a position between 0 and 200 corresponding to the position of the first Hex char on our circle
int getfirstpos(String order) {
        for(int i = 0; i < 16; i++) {
          if(order.substring(0, 1) == String(positions[i]) ) return (i*STEPBTWPOS + STEPBTWPOS);
        }
}

// Returns a position between 0 and 200 corresponding to the position of the second Hex char on our circle
int getsecondpos(String order) {
        for(int i = 0; i < 16; i++) {
          if(order.substring(1) == String(positions[i])) return (i*STEPBTWPOS + STEPBTWPOS);
        }
}

void loop() {
    if (Serial.available() > 0) {
        key = decToHex(Serial.read(), 2);
        if( key == "0a" ) return;
        log(key);
        shelper.gotopos(getfirstpos(key));     // Point to first Hex Char 
        delay(DELAY);                          // Wait a bit so we can read it
        shelper.gotopos(getsecondpos(key));    // Point to second Hex Char
        delay(DELAY);                     
        shelper.gotopos(0);                    // Goes back to origin
        key = "";                              // Reset our string
    } 

}


void log(String key) {
  Serial.println("****** NEW KEY PRESSED ******");
  Serial.print("First Hex : ");
  Serial.println(key.substring(0,1));
  Serial.print("First pos : ");
  Serial.println(getfirstpos(key));
  Serial.print("Second Hex: ");
  Serial.println(key.substring(1,2));
  Serial.print("Second pos : ");
  Serial.println(getsecondpos(key));
}
