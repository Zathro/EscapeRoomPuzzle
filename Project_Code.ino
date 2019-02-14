#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
//#include<EEPROM.h>


//LCD initilization using pins A4 and a5
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //

// CONSTANTS
// Define the characters on the keypad layout
const char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// Row pins
const byte keypadRowPins[4] = {3, 4, 5, 6};
// Column pins
const byte keypadColPins[4] = {7, 8, 9, 10};
//Relay Pins
const byte relayPin = 11;
const byte buzzer = A1;


// GLOBALS
// Create a keypad input class from definitions above
Keypad customKeypad = Keypad( makeKeymap(keys), keypadRowPins, keypadColPins, 4, 4 );
// Record the code which the user has entered
char data[] = "    ";
// What position through the code is being entered?
byte sequenceNum = 0;
byte lock = 0;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  lcd.setCursor(0, 0); //we start writing from the first row first column
  lcd.print("Enter Code"); //16 characters per line
  delay(10);
  // Get the keypad input this frame
  char key = customKeypad.getKey();

  // Has a key been pressed?
  if (key) {
    // Log it to the serial output
    Serial.println(key);
    // Set the current position of the code sequence to the key pressed
    data[sequenceNum] = key;
    lcd.setCursor(sequenceNum, 1);
    lcd.print(data[sequenceNum]);
    sequenceNum++;
  }
  if (sequenceNum == 4) {
    checkFunction();
    lcd.clear();
    if (lock == 1) {
      accessGranted();
    }
    else if (lock == 2) {  //3 seconds
      accessDenied();
    }
  }
}


void accessGranted() {  //1.5 Seconds
  delay(10);
  lcd.setCursor(0, 0);
  lcd.print("Access Granted");
  lcd.setCursor(0, 1);
  lcd.print("Door Unlocked");
  digitalWrite(buzzer, HIGH);
  delay(1500);
  digitalWrite(buzzer, LOW);
  lcd.clear();
  Serial.println("Access Granted");
}


void accessDenied() { //1.5 seconds
  lcd.setCursor(0, 0);
  lcd.print("Access Denied,");
  lcd.setCursor(0, 1);
  lcd.print("Door locked");
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(100);

  digitalWrite(buzzer, LOW);
  delay(1000);
  lcd.clear();
  Serial.println("Access Denied");
}






void checkFunction() {
  delay(100);
  Serial.println(data);
  delay(100);
  // Take action based on the code entered
  if (strcmp(data, "1111") == 0) {
    delay(10);
    sequenceNum = 0;
    lock = 1;
  }
  else {
    sequenceNum = 0;
    lock = 2;
    // resetFunc();
  }
  delay(1000);
  Serial.println(lock);
  delay(1000);
}
