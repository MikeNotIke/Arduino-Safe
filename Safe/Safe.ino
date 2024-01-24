// include libaries
#include <Keypad.h>
#include <Servo.h>
#include "pitches.h"

// assaign a servo to a name
Servo myservo;

// variables
int combo = 1234;
int newCombo = 0;
int pos = 0;
int value = 0;
int wrong = 0;
bool changeCombo = false;



//set up key pad
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 11, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);

  myservo.attach(10);
}

void loop() {

 char customKey = customKeypad.getKey();


if (customKey)
{Serial.print(customKey);}

  if ((customKey >= '0') &&(customKey <= '9')) {
    value = value*10;
    value = value + customKey - '0';
  }

  if (customKey == '#'){
    Serial.print(value);
   if (value == combo){
      pos = 180;
      myservo.write(pos);
      value = 0;
      wrong = 0;
      
      }
      else {value = 0;
      wrong ++;
      Serial.print("wrong = ");
      Serial.print(wrong);
      } 
     }

     
     if (customKey == '*')
     {
      pos = -180;
      myservo.write(pos);
     value = 0;
     delay (100);
     }

     

     

    
  
}
