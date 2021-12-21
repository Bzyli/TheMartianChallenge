#include "Arduino.h"
#include "Shelper.h"

// Here is a link to the article that I followed to learn how to move a stepper :
// https://electrotoile.eu/commande-moteur-avec-shield-motor-l298P-sur-arduino.php

Shelper::Shelper(int feed) {
  pinMode(3, OUTPUT);  // ###################################  //
  pinMode(11, OUTPUT); //       Tell the Arduino wich          //
  pinMode(12, OUTPUT); //           pins it should use         //
  pinMode(13, OUTPUT); // ###################################  //
  _feed = feed;
}


/////////////   SETTERS AND GETTERS   /////////////

void Shelper::setFeedrate(int feed) {
  _feed = feed;
}

int Shelper::getpos(){ return _pos;}

int Shelper::getstep(){ return _step;}

int Shelper::getNextStepf(int step) {   // Returns the next step when going forward
  return (step++) >= 4 ? 0 : (step++); 
}

int Shelper::getNextStepb(int step) {   // Returns the next step when going backward
  return (step--) < 0 ? 3 : (step--); 
}

///////////////////////////////////////////////////


/////////////     MOTION  METHODS     /////////////
void Shelper::doStep(int step) {
  switch (step) {
  case 0:                         //STEP NUMBER 1
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);  
    analogWrite(3, 0);
    analogWrite(11, 255);
    break;
  case 1:                         //STEP NUMBER 2
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);   
    analogWrite(3, 255);
    analogWrite(11, 0);
    break;
  case 2:                         //STEP NUMBER 3
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);  
    analogWrite(3, 0);
    analogWrite(11, 255);
    break;
  case 3:                         //STEP NUMBER 4
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);   
    analogWrite(3, 255);
    analogWrite(11, 0);
    break;
  }
}

void Shelper::movexstepforward(int x) {
  for(int i = 0; i < x; i++) {
    doStep(_step);
    _step = getNextStepf(_step);
    delay(_feed);
  }
}

void Shelper::movexstepbackward(int x) {
  for(int i = 0; i < x; i++) {
    doStep(_step);
    _step = getNextStepb(_step);
    delay(_feed);
  }
}

///////////////////////////////////////////////////


/////////////       GOTO METHOD       /////////////
void Shelper::gotopos(int pos) {    // Most complete method, allows you to move the stepper to a desired position
     if (pos > _pos) {
      movexstepforward(pos - _pos);
     } else if (pos <= _pos) {
       movexstepbackward(_pos - pos);
     }
     _pos = pos;
}