#include <SoftwareSerial.h>
#include "Servo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//////// Ids for identifying bluetooth data stream //////
#define ledID 'a'
#define servoID 's'
#define irID 'i'


//////// LED Varibles //////
//int led1Pin = 9;
//int led2Pin = 10;
//int led3Pin = 11;
//int led4Pin = 12;

//////// Servo Varibles //////
Servo servoUnit;
int servoAngle = 0;
int servoIncrement = 1;

//////// IR Varibles //////
int irAnalogPin = A0;
int irDigitalPin = 8;

//////// Bluetooth Varibles //////
String inputString ="";
char deLim = '-';
SoftwareSerial ble(2,3);

void setup()                    
{
 Serial.begin(9600);            
// pinMode(led1Pin, OUTPUT);
// pinMode(led2Pin,OUTPUT);
// pinMode(led3Pin, OUTPUT);
 ble.begin(9600);

  servoUnit.attach(9);
  pinMode(irDigitalPin, OUTPUT);
  pinMode(irAnalogPin, INPUT);  
}

void loop()
{
  if(ble.available()){
  while(ble.available())
    {
      Serial.println("serial is still available");
      char letter = (char)ble.read(); //read the input
      delay(50);
      inputString += letter;
    }
     Serial.println(inputString);
     if(inputString[0] == ledID){
      turnOnLed();
    }
    else if(inputString[0] == servoID){
      activateServo();
    }
    else if(inputString[0] == irID){
      activateIR();
    }
  }
}

void turnOnLed(){

     //will need the second char to id which LED to turn on
     if(inputString[1] == ledID){     
      digitalWrite(9, HIGH); 
      delay(500);
      digitalWrite(9,LOW); 
    }else if(inputString[1] == 'b'){   
      digitalWrite(10, HIGH); 
      delay(500);
      digitalWrite(10,LOW);
    }else if(inputString[1] == 'c'){   
      digitalWrite(11, HIGH); 
      delay(500);
      digitalWrite(11,LOW);
    }
    inputString = "";
}

void activateServo(){
  Serial.println("inside servo function");
  String inputCopy = inputString;
  String param = getValue(inputCopy,'-', 1);
  char paramCh[256];
  param.toCharArray(paramCh, sizeof(paramCh));

  //converting the servo param to int
  int paramNum = atoi(paramCh);
  Serial.println(paramNum);
  inputString = "";
}


void activateIR(){
  int val = analogRead(irAnalogPin);
  Serial.println("printing ir value");
  Serial.println(val);

  inputString = "";
}

//string splitter function
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
