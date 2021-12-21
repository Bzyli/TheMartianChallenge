#ifndef Shelper_h
#define Shelper_h

#include "Arduino.h"

class Shelper
{
  public:
    //      CONSTRUCTOR    //
    Shelper(int feed);
    // SETTERS AND GETTERS //             
    void setFeedrate(int feed);     
    int getpos();                   
    int getstep();                  
    int getNextStepf(int step);     
    int getNextStepb(int step);
    //        MOTION       // 
    void doStep(int step);          
    void movexstepforward(int x);   
    void movexstepbackward(int x);
    //  MOST USEFUL METHOD //  
    void gotopos(int pos);          
  private:
    int _pos = 0; 
    int _step = 0;
    int _feed;
};

#endif