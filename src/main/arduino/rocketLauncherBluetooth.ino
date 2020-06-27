/*
* The relays on the board this code is designed for are active low. This means that when they are set high they are off, and when set low they are on.
* -Rex McAllister
*  CEO McAllister Aerospace, Inc.
*/

#include "functions/prototypes.h"
#include "variables/global.h"
#include <Arduino.h>

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
    /*
    We have to do a Serial1.read to acknowledge that the bluetooth
    device has bytes available so they don't linger until the mode is changed
    back from manual to bluetooth
    */
    if (Serial1.available())  {int inByte = Serial1.read(); }
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