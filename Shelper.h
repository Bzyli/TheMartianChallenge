#ifndef Shelper_h
#define Shelper_h

#include "Arduino.h"

class Shelper
{
  public:
    Shelper(int feed);              // Constructor of the Stepper helper class, it takes a speed (feed) as a parameter
    void setFeedrate(int feed);     // Set the speed of our stepper motor by setting the dealy between steps to the value of feed
    int getpos();                   // Returns the positions of the stepper motor
    int getstep();                  // Returns the step that we are currently making. It returns a number from 0 to 3 which corresponds to our step 1 to 4
    int getNextStepf(int step);     // Returns the next step when going foward
    int getNextStepb(int step);     // Returns the next step when going backward       
    void doStep(int step);          // Makes the stepper motor "play" the step that we give as a parameter
    void movexstepforward(int x);   // Makes the stepper motot do X step forward
    void movexstepbackward(int x);  // Makes the stepper motor do X step backward
    void gotopos(int pos);          // This method is the most complete one, it uses a lot of the above ones to move the stepper to the desired position
  private:    //Variables of the class
    int _pos = 0; 
    int _step = 0;
    int _feed;
};

#endif