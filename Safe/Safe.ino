#include <Keypad.h>
#include <Stepper.h>
int buzzer = 12;
#define BLUE 4
#define GREEN 5
#define RED 6

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
const int stepsPerRevoluton = 1500;
int combo = 1234;
int value = 0;
int wrong = 0;
int redValue = 0;
int greenValue = 0;
int blueValue = 250;
bool locked = true;
bool changingCombo = false;
Stepper myStepper (stepsPerRevoluton, 8, 10, 9, 11);

byte rowPins[ROWS] = {A0, A1, A2, A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A4, A5, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  myStepper.setSpeed(20);
  Serial.begin(9600);
  pinMode (buzzer, OUTPUT);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  digitalWrite(BLUE,HIGH);
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
  digitalWrite(buzzer,LOW);
 
  
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
      myStepper.step(stepsPerRevoluton);
      wrong = 0;
      locked = false;
      value = 0;
      digitalWrite(RED,LOW);
      digitalWrite(BLUE,LOW);
      digitalWrite(GREEN,HIGH);
      }
      else {value = 0;
      wrong ++;
    
      if (wrong < 3){
        digitalWrite(RED,HIGH);
      digitalWrite(BLUE,LOW);
      digitalWrite(GREEN,LOW);
      delay(1000);
      digitalWrite(RED,LOW);
      digitalWrite(BLUE,HIGH);
      digitalWrite(GREEN,LOW);}
      } 
     }
     if (customKey == '*'){
      if(locked == false){
        myStepper.step(-stepsPerRevoluton);
        value = 0;
        digitalWrite(BLUE,HIGH);
        digitalWrite(RED,LOW);
        digitalWrite(GREEN,LOW);
        locked = true;}
        else{value = 0;}
        
        
      }
      if (wrong >= 3)
      {digitalWrite(buzzer,HIGH);
      digitalWrite(RED,HIGH);
      digitalWrite(BLUE,LOW);
      digitalWrite(GREEN,LOW);}
      else {digitalWrite(buzzer,LOW);}

      if (customKey == 'A'){
        if(changingCombo == false && value == combo){
        digitalWrite(RED,HIGH);
        digitalWrite(GREEN,HIGH);
        digitalWrite(BLUE,LOW);
        changingCombo = true;
        Serial.print("Changing Combo");
        value = 0;}}
        if (changingCombo == true && customKey == 'C')
        {changingCombo = false;
        Serial.print ("Cancled");
        digitalWrite(BLUE,HIGH);
        digitalWrite(RED,LOW);
        digitalWrite(GREEN,LOW);}
        if (changingCombo == true)
        {
        if(customKey == 'B'){
          if(value > 0){
          combo = value;
          value = 0;
          changingCombo = false;
          digitalWrite(BLUE,HIGH);
        digitalWrite(RED,LOW);
        digitalWrite(GREEN,LOW);}
        }
          }
}
