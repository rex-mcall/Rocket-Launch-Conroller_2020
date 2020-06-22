//FUNCTION PROTOTYPES
#ifndef prototypes
#define prototypes
/** 
 * Sets an int to be displayed on the hand controller 7-seg display
 * 
 * PARAM: num int to be written to the display
 */
void displayNum(int num);

/**
 * Returns which rocket should be fired based on the 
 * value of the potentiometer
 * 
 * PARAM: potVal value of the potentiometer from 0 to 1023
 * RETURNS: the number of the rocket to be fired, from 1 to 6 inclusive
 */
int getRocketNum(int potVal);

/**
 * Beeps the piezoelectric buzzer twice
 */
void beep();

/**
 * Fires a single rocket -1 for human counts
 * PARAM: int of rocket number to fire +1
 */
void fireSingle(int rocketNum);

/**
 * Fires a single rocket
 * PARAM: int of rocket number to fire
 */
void fireSingleBT(int rocketNum);

/**
 * Fires rockets from pad 0 to input number, inclusive
 * PARAM: int of maximum rocket number
 */
void fireSequence(int rocketNum);

void DEBOUNCE();

void countDownAndLaunch(int rocketNum);
#endif