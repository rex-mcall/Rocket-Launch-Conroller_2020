#ifndef global
#define global
//GLOBAL VARIABLES
int RELAYS[8] = {22, 23, 24, 25, 26, 27, 28, 29}; //relay pin numbers on Arduino Mega
int NUM_RELAYS = sizeof(RELAYS);

//7 segment display on handheld controller
const int BIT_ONE = 51;  //bcd for 7seg
const int BIT_TWO = 49;  //bcd for 7seg
const int BIT_FOUR = 47; //bcd for 7seg

//inputs from hand controller
const int POT_PIN = 10;  //potentiometer
const int ARM_PIN = 33;  //arm switch
const int FIRE_PIN = 31; //key switch or fire

const int BUZZER_PIN = 36;        //piezoelectric buzzer
const int BLT_OR_MANUAL_PIN = 35; //mode switch - bluetooth or handheld

const int ERROR = -1;
const int INTERVAL = 170;

bool hasBeeped = false;

int isArmed = 0;
int shouldFire = 0;
int potVal = 0;
int bluetoothOrManual = 0;
#endif