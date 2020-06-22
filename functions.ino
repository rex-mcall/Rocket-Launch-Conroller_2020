#include "global.h"
//FUNCTIONS
void DEBOUNCE()
{
  delay(50); //halts the program for 50ms
}

void displayNum(int num)
{ //binary coded decimal values for each number on the 7 segment display
  digitalWrite(BIT_ONE, ((num &       0x1) == 0x1) ? HIGH : LOW);
  digitalWrite(BIT_TWO, ((num >>  1 & 0x1) == 0x1) ? HIGH : LOW);
  digitalWrite(BIT_FOUR, ((num >> 2 & 0x1) == 0x1) ? HIGH : LOW);
}

int getRocketNum(int potVal)
{
  int localRocket = 6;

  if (potVal >= 1024)
    return ERROR;

  //sets values based on potentiometer
  int temp = INTERVAL;
  while (temp < potVal)
  {
    temp += INTERVAL;
    localRocket--;
  }

  return localRocket;
}

void beep()
{
  DEBOUNCE();
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);

  hasBeeped = true;
}

void fireSingleBT(int rocketNum)
{
  digitalWrite(RELAYS[rocketNum], LOW);
  delay(750);
  digitalWrite(RELAYS[rocketNum], HIGH);
}

void fireSingle(int rocketNum)
{
  digitalWrite(RELAYS[rocketNum -1], LOW);
  delay(750);
  digitalWrite(RELAYS[rocketNum -1], HIGH);
}

void fireSequence(int rocketNum)
{
  for (int b = 0; b <= rocketNum; b++)
  {
    displayNum(b); //this code counts up on 7seg while it is launching
    digitalWrite(RELAYS[b], LOW); //active low relay board
    delay(750);
    digitalWrite(RELAYS[b], HIGH);
  }
}

void countDownAndLaunch(int rocketNum) {
  int count = 3;
  while (shouldFire == 0  && count > 0) {
    displayNum(count);
    count--;
    delay(750);
    shouldFire = digitalRead(FIRE_PIN);
    if (shouldFire == 1) {
      displayNum(rocketNum);
    }
  }
  if (shouldFire == 0) {
    displayNum(0);
    fireSingle(rocketNum);
    delay(750);
    displayNum(rocketNum);
  }
}
