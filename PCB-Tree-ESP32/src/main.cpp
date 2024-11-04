#include <Arduino.h>

//   PINOUT:          2   9   3   8   4   7   6   5
//   ledPin of PCB:   1   1   2   2   3   3   4   5
// const int ledPin[] = {15, 23,  2, 22, 26, 32, 33, 25}; // ESP32 30pins
const int ledPin[] = {16, 23, 17, 22,  5, 21, 19, 18}; // ESP32 38pins

// change effect pin
const int changeEffectPin = 35;

const int effectTime = 60000; // 60 seconds

int lastEffect = 0; // last effect        {0: sequential, 1: random, 2: blink_all, 3: blink_random, 4: blink_sequential}
int currentEffect = 0; // current effect

bool currentButton = false;

int effectVariable = 1;

long unsigned int lastChangeEffect, endChangeEffect;

// function declaration
void change_effect();
void change_button();
void sequential();
void random_effect();
void blink_all();
void blink_random();
void blink_sequential();

// setup function
void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 8; i++) {
    pinMode(ledPin[i], OUTPUT);
  }

  pinMode(changeEffectPin, INPUT);

  lastChangeEffect = millis();
  endChangeEffect = lastChangeEffect + effectTime;
}

void loop() {
  change_button();

  if (lastEffect != currentEffect) {
    change_effect();

    lastChangeEffect = millis();
    endChangeEffect = lastChangeEffect + effectTime;
  } else {
    if (millis() > endChangeEffect) {
      currentEffect++;
      change_effect();

      lastChangeEffect = millis();
      endChangeEffect = lastChangeEffect + 60000;
    }
  }

  Serial.println(currentEffect);

  switch (currentEffect) {
    case 0:
      sequential();
      break;
    case 1:
      random_effect();
      break;
    case 2:
      blink_all();
      break;
    case 3:
      blink_random();
      break;
    case 4:
      blink_sequential();
      break;
  }
}

// check if effect is changed and set effectVariable to 1, if effect is higher than 5 set to 0
void change_effect() {
  if (currentEffect == 5) currentEffect = 0;

  if (currentEffect != lastEffect) {
    lastEffect = currentEffect;
    effectVariable = 1;
  }
}

// check if button is pressed and change effect
void change_button() {
  if (digitalRead(changeEffectPin) == HIGH) {
    currentButton = true;
    // Serial.println("Button pressed");
  }
  if (currentButton == true && digitalRead(changeEffectPin) == LOW) {
    currentButton = false;
    currentEffect++;
    // Serial.println("Change effect");
  }
}

// led turn on with 200/300ms delay
void sequential() {
  if (effectVariable ==6) effectVariable = 1;
  switch (effectVariable) {
    case 1:
      digitalWrite(ledPin[0], HIGH);
      digitalWrite(ledPin[1], HIGH);
      break;
    case 2:
      digitalWrite(ledPin[2], HIGH);
      digitalWrite(ledPin[3], HIGH);
      break;
    case 3:
      digitalWrite(ledPin[4], HIGH);
      digitalWrite(ledPin[5], HIGH);
      break;
    case 4:
      digitalWrite(ledPin[6], HIGH);
      break;
    case 5:
      digitalWrite(ledPin[7], HIGH);
      break;
  }

  delay(random(200, 300)); // Random time between 200ms and 300ms

  switch (effectVariable) {
    case 1:
      digitalWrite(ledPin[0], LOW);
      digitalWrite(ledPin[1], LOW);
      break;
    case 2:
      digitalWrite(ledPin[2], LOW);
      digitalWrite(ledPin[3], LOW);
      break;
    case 3:
      digitalWrite(ledPin[4], LOW);
      digitalWrite(ledPin[5], LOW);
      break;
    case 4:
      digitalWrite(ledPin[6], LOW);
      break;
    case 5:
      digitalWrite(ledPin[7], LOW);
      break;
  }

  effectVariable++;
}

// random led turn on with 100/300ms delay
void random_effect() {
  effectVariable = random(1, 6);
  switch (effectVariable) {
    case 1:
      digitalWrite(ledPin[0], HIGH);
      digitalWrite(ledPin[1], HIGH);
      break;
    case 2:
      digitalWrite(ledPin[2], HIGH);
      digitalWrite(ledPin[3], HIGH);
      break;
    case 3:
      digitalWrite(ledPin[4], HIGH);
      digitalWrite(ledPin[5], HIGH);
      break;
    case 4:
      digitalWrite(ledPin[6], HIGH);
      break;
    case 5:
      digitalWrite(ledPin[7], HIGH);
      break;
  }

  delay(random(100, 300)); // Random time between 100ms and 300ms

  switch (effectVariable) {
    case 1:
      digitalWrite(ledPin[0], LOW);
      digitalWrite(ledPin[1], LOW);
      break;
    case 2:
      digitalWrite(ledPin[2], LOW);
      digitalWrite(ledPin[3], LOW);
      break;
    case 3:
      digitalWrite(ledPin[4], LOW);
      digitalWrite(ledPin[5], LOW);
      break;
    case 4:
      digitalWrite(ledPin[6], LOW);
      break;
    case 5:
      digitalWrite(ledPin[7], LOW);
      break;
  }
}

// blink all led with 200ms delay
void blink_all() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPin[i], HIGH);
  }

  delay(100);

  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPin[i], LOW);
  }

  delay(200);
}

// blink random segment line of led with 100ms delay
void blink_random() {
  int randomLed = random(0, 8);
  digitalWrite(ledPin[randomLed], HIGH);

  delay(100);

  digitalWrite(ledPin[randomLed], LOW);
}

// effects line [1, 2, 3, 4, 5] blink in sequence with 100ms delay
void blink_sequential() {
  if (effectVariable ==6) effectVariable = 1;
  switch (effectVariable) {
    case 1:
      digitalWrite(ledPin[0], HIGH);
      digitalWrite(ledPin[1], HIGH);
      break;
    case 2:
      digitalWrite(ledPin[2], HIGH);
      digitalWrite(ledPin[3], HIGH);
      break;
    case 3:
      digitalWrite(ledPin[4], HIGH);
      digitalWrite(ledPin[5], HIGH);
      break;
    case 4:
      digitalWrite(ledPin[6], HIGH);
      break;
    case 5:
      digitalWrite(ledPin[7], HIGH);
      break;
  }

  delay(100);

  switch (effectVariable) {
    case 1:
      digitalWrite(ledPin[0], LOW);
      digitalWrite(ledPin[1], LOW);
      break;
    case 2:
      digitalWrite(ledPin[2], LOW);
      digitalWrite(ledPin[3], LOW);
      break;
    case 3:
      digitalWrite(ledPin[4], LOW);
      digitalWrite(ledPin[5], LOW);
      break;
    case 4:
      digitalWrite(ledPin[6], LOW);
      break;
    case 5:
      digitalWrite(ledPin[7], LOW);
      break;
  }

  effectVariable++;
}