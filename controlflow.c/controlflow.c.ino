#include <SoftwareSerial.h>
#include "Servo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define pillSignal 't'

////////Button Variables
int buttonState = 0;  
const int buttonPin = 8;
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

//////// Servo Varibles //////
Servo servoUnit;
int servoAngle = 0;
int servoIncrement = 1;
int pos = 0;

//////// IR Varibles //////
int irDefault = 1023;
int dtect=7;
int sense=A0;

//////// Bluetooth Varibles //////

SoftwareSerial ble(2,3);

//////// LED Variables //////

int lightstatus = 0;

int dispensed = 0; 

int lastval = 0; 



void setup()                    
{
 Serial.begin(9600);      
       
  ble.begin(9600);

  servoUnit.attach(5);

  pinMode(buttonPin, INPUT);
 
  pinMode(dtect,OUTPUT);
  pinMode(sense,INPUT);
  digitalWrite(dtect,HIGH);
  setColor(255, 0, 0);  // red


}

void loop() {
    
  if (ble.available()) {
    
      //Serial.println("Is available");  
      char letter = (char)ble.read();
      if (letter == pillSignal) {
        Serial.println("Time to take pill");
        //Serial.println(lightstatus);
        changeLight(); 
        //Serial.println(lightstatus);
      }
      
    }

  buttonState = digitalRead(buttonPin);
  if (lightstatus == 1 && buttonState == HIGH) {
     dispensed = 1; 
     //Serial.println("dispensed value:"); 
     Serial.println("Dispensed pill");
     delay(10);
     servoTurn(); 
     delay(10);
     changeLightBack(); 
     delay(10); 
     ble.write("pill taken"); 
     Serial.println("Pill taken"); 
     dispensed = 0; 
     lightstatus = 0; 
      dispensed = 0; 
      delay(10); 
     setColor(255, 0, 0);  // red
  }
 
  //int val = analogRead(A0);
  //Serial.println(val); 

 
}


void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void changeLight() 
{
    if (lightstatus == 0) {
      setColor(0, 0, 255);  // green
      //Serial.println("light changed green"); 
      lightstatus = 1;
    }
}

void changeLightBack() 
{
    if (lightstatus == 1) {
      setColor(0, 0, 255);  // blue
      //Serial.println("light changed blue"); 
      lightstatus = 0;
    }
}



void servoTurn() {

        for (pos = 0; pos <= 30; pos += 5) { 
            servoUnit.write(pos);              
            delay(30);                       
        }
      delay(30);
      pos=90;
      servoUnit.write(pos);
  
}




