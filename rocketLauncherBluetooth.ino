/*
* The relays on the board this code is designed for are active low. This means that when they are set high they are off, and when set low they are on.
* -Rex McAllister
*  CEO McAllister Aerospace, Inc.
*/

#include "prototypes.h"
#include <Arduino.h>

//VARIABLES
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

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(13, OUTPUT);
  pinMode(POT_PIN, INPUT);
  pinMode(ARM_PIN, INPUT_PULLUP); //INPUT_PULLUP uses the Arduino internal resistors
  pinMode(FIRE_PIN, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BLT_OR_MANUAL_PIN, INPUT_PULLUP);

  pinMode(BIT_ONE, OUTPUT);
  pinMode(BIT_TWO, OUTPUT);
  pinMode(BIT_FOUR, OUTPUT);

  for (int a = 0; a < NUM_RELAYS; a++)
  { //sets all the relays high because they are active low
    pinMode(RELAYS[a], OUTPUT);
    digitalWrite(RELAYS[a], HIGH);
  }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void loop()
{
  bluetoothOrManual = digitalRead(BLT_OR_MANUAL_PIN);

  if (! bluetoothOrManual)
  {

    if (Serial1.available())
    {
      int inByte = Serial1.read();
      Serial.print(inByte);
      Serial.write("\n");
      Serial1.print("Firing relay ");
      Serial1.print(inByte);
      fireSingleBT(inByte);
      Serial1.write("Done");
    }
  }

  else
  {
    shouldFire = digitalRead(FIRE_PIN);
    isArmed = digitalRead(ARM_PIN);
    if (isArmed == 0)
    {
      if (!hasBeeped)
      {
        beep();
      }
      if (shouldFire == 0)
      {
        countDownAndLaunch(getRocketNum(potVal));
      }
    }
    else
    {
      if (hasBeeped)
      {
        hasBeeped = false;
      }
      potVal = analogRead(POT_PIN);
      displayNum(getRocketNum(analogRead(POT_PIN)));
    }
  }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */