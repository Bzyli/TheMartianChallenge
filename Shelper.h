#ifndef Shelper_h
#define Shelper_h

#include "Arduino.h"

class Shelper
{
  public:
    Shelper(int feed); //Constructor of the Stepper helper class (Shelper), it takes a speed(feed) as a parameter
    void setFeedrate(int feed);
    int getpos();
    int getstep();
    int getNextStepf(int step);
    int getNextStepb(int step);
    void gotopos(int pos);
    void doStep(int step);
    void movexstepforward(int x);
    void movexstepbackward(int x);
  private:
    int _pos = 0;
    int _step = 0;
    int _feed;
};

#endif