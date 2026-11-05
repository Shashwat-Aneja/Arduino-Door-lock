/*
  Password-Protected Door Lock (v1.1)
  -----------------------------------
  Arduino-based security system using a 4x4 keypad and servo motor.
  Password input is kept in a fixed-size buffer and is never printed.
*/

#include <Keypad.h>
#include <Servo.h>
#include "PasswordInput.h"
#include "LockTiming.h"

// ----- Keypad Setup -----
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ----- Servo Setup -----
Servo lockServo;
const int servoPin = 10;

// ----- Security Setup -----
PasswordInput inputPassword;
const char correctPassword[] = "1234"; // Change before deploying the lock.
const uint32_t UNLOCK_DURATION_MS = 3000UL;

bool isUnlocked = false;
uint32_t unlockedAt = 0;

void setup() {
  Serial.begin(9600);
  lockServo.attach(servoPin);

  lockDoor();

  Serial.println("Password Door Lock System Ready");
  Serial.println("Enter 4-digit password:");
}

void loop() {
  updateLockTimeout();

  const char key = keypad.getKey();
  if (!key) {
    return;
  }

  if (key == '#') {
    inputPassword.clear();
    Serial.println("Input cleared.");
  } else if (key == '*') {
    checkPassword();
  } else if (!inputPassword.appendDigit(key)) {
    Serial.println("Enter up to four numeric digits.");
  }
}

void checkPassword() {
  if (inputPassword.matches(correctPassword)) {
    Serial.println("Password accepted.");
    unlockDoor();
  } else {
    Serial.println("Incorrect password.");
  }

  inputPassword.clear();
}

void updateLockTimeout() {
  if (isUnlocked
      && lockTimeoutElapsed(static_cast<uint32_t>(millis()), unlockedAt, UNLOCK_DURATION_MS)) {
    lockDoor();
  }
}

void unlockDoor() {
  lockServo.write(90);
  isUnlocked = true;
  unlockedAt = static_cast<uint32_t>(millis());
  Serial.println("Door unlocked.");
}

void lockDoor() {
  lockServo.write(0);
  isUnlocked = false;
  Serial.println("Door locked.");
}
