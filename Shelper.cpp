#include "Arduino.h"
#include "Shelper.h"

// https://electrotoile.eu/commande-moteur-avec-shield-motor-l298P-sur-arduino.php

Shelper::Shelper(int feed) {
  pinMode(3, OUTPUT);  // ###################################  //
  pinMode(11, OUTPUT); // Déclaration des différentes broches  //
  pinMode(12, OUTPUT); // du motor shield                      //
  pinMode(13, OUTPUT); // ###################################  //
  _feed = feed;
}

void Shelper::setFeedrate(int feed) {
  _feed = feed;
}

int Shelper::getpos(){ return _pos;}

int Shelper::getstep(){ return _step;}

int Shelper::getNextStepf(int step) {
  return (step++) >= 4 ? 0 : (step++); 
}

int Shelper::getNextStepb(int step) {
  return (step--) < 0 ? 3 : (step--); 
}

void Shelper::doStep(int step) {
  switch (step) {
  case 0:                         //PAS NUMERO 1
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);  
    analogWrite(3, 0);
    analogWrite(11, 255);
    Serial.println("Step 1");
    break;
  case 1:                         //PAS NUMERO 2
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);   
    analogWrite(3, 255);
    analogWrite(11, 0);
    Serial.println("Step 2");
    break;
  case 2:                         //PAS NUMERO 3
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);  
    analogWrite(3, 0);
    analogWrite(11, 255);
    Serial.println("Step 3");
    break;
  case 3:                         //PAS NUMERO 4
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);   
    analogWrite(3, 255);
    analogWrite(11, 0);
    Serial.println("Step 4");
    break;
  }
}

void Shelper::gotopos(int pos) {
     if (pos > _pos) {
      movexstepforward(pos - _pos);
     } else if (pos <= _pos) {
       movexstepbackward(_pos - pos);
     }
     _pos = pos;
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