#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include<EEPROM.h>


//LCD initilization
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
const byte keypadRowPins[4] = {4, 5, 6, 7};
// Column pins
const byte keypadColPins[4] = {8, 9, 10, 11};


// GLOBALS
// Create a keypad input class from definitions above
Keypad customKeypad = Keypad( makeKeymap(keys), keypadRowPins, keypadColPins, 4, 3 );
// Record the code which the user has entered
char data[] = "    ";
// What position through the code is being entered?
int sequenceNum = 0;
int lock;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(0, 0); //we start writing from the first row first column
  lcd.print("Welcome"); //16 characters per line
  delay(300);
  // Get the keypad input this frame
  char key = customKeypad.getKey();

  // Has a key been pressed?
  if (key) {
    // Log it to the serial output
    Serial.println(key);
    // Set the current position of the code sequence to the key pressed
    data[sequenceNum] = key;
    sequenceNum++;
  }
  if (sequenceNum == 4) {
    checkFunction(data);
    if (lock == 1) {
      delay(100);
      lcd.setCursor(0, 1);
      lcd.print("Door Unlocked");
      delay(3000);
      lcd.clear();
    }
    else if(lock==2) {
      lcd.setCursor(0, 0);
      lcd.print("Access Denied,");
      lcd.setCursor(0, 1);
      lcd.print("Door locked");
      delay(3000);
      lcd.clear();
    }
  }
}














void checkFunction() {
  delay(100);

  // Take action based on the code entered
  if (strcmp(data, "3333") == 0) {
    delay(2000);
    return lock = 1;
  }
  else {
  }
  sequenceNum = 0;
  return lock = 2;
}
