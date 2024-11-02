#include <Arduino.h>

//   ledPin of PCB:   1   1   2   2   3   3   4   5
const int ledPin[] = {53, 39, 51, 41, 49, 43, 45, 47};

// change effect pin
const int changeEffectPin = 35;

int lastEffect = 0; // last effect        {0: sequential, 1: random, 2: blink_all, 3: blink_random, 4: blink_sequential}
int currentEffect = 0; // current effect

int effectVariable = 1;

long unsigned int lastChangeEffect, endChangeEffect;

void changeEffect();
void sequential();
void random_effect();
void blink_all();
void blink_random();
void blink_sequential();

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(ledPin[i], OUTPUT);
  }

  lastChangeEffect = millis();
  endChangeEffect = lastChangeEffect + 60000;
}

void loop() {
  if (lastEffect != currentEffect) {
    changeEffect();

    lastChangeEffect = millis();
    endChangeEffect = lastChangeEffect + 60000;
  } else {
    if (millis() > endChangeEffect) {
      currentEffect++;
      changeEffect();

      lastChangeEffect = millis();
      endChangeEffect = lastChangeEffect + 60000;
    }
  }

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

void changeEffect() {
  if (currentEffect == 5) currentEffect = 0;

  if (currentEffect != lastEffect) {
    lastEffect = currentEffect;
    effectVariable = 1;
  }
}

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

  delay(random(300, 800)); // Random time between 300ms and 800ms

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

  delay(random(100, 500)); // Random time between 100ms and 500ms

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

void blink_all() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPin[i], HIGH);
  }

  delay(100);

  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPin[i], LOW);
  }
}

void blink_random() {
  int randomLed = random(0, 8);
  digitalWrite(ledPin[randomLed], HIGH);

  delay(100);

  digitalWrite(ledPin[randomLed], LOW);
}

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