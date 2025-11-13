/*
  Password-Protected Door Lock (v1.0)
  -----------------------------------
  Arduino-based security system using a 4x4 keypad and servo motor.
  Correct password unlocks the door; incorrect attempts are rejected.
  Clean, structured code for academic and professional presentation.
*/

#include <Keypad.h>
#include <Servo.h>

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
String inputPassword = "";
String correctPassword = "1234";   // change as needed
const int maxLength = 4;

void setup() {
  Serial.begin(9600);
  lockServo.attach(servoPin);

  lockDoor();  // start locked

  Serial.println("Password Door Lock System Ready");
  Serial.println("Enter 4-digit password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Key Pressed: ");
    Serial.println(key);

    if (key == '#') {
      // Clear input
      inputPassword = "";
      Serial.println("Input cleared.");
    }
    else if (key == '*') {
      // Submit password
      checkPassword();
    }
    else {
      // Add digits
      if (inputPassword.length() < maxLength) {
        inputPassword += key;
        Serial.print("Current Input: ");
        Serial.println(inputPassword);
      }
    }
  }
}

// ----- Functions -----

void checkPassword() {
  if (inputPassword == correctPassword) {
    Serial.println("Password Correct → Door Unlocked.");
    unlockDoor();
    delay(3000); // keep unlocked for 3 seconds
    lockDoor();
  } else {
    Serial.println("Incorrect Password → Try Again.");
  }

  inputPassword = ""; // clear for next attempt
}

void unlockDoor() {
  lockServo.write(90);  // adjust depending on your servo orientation
  Serial.println("Door Unlocked.");
}

void lockDoor() {
  lockServo.write(0);
  Serial.println("Door Locked.");
}
