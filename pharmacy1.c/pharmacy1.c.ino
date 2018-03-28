#include <SoftwareSerial.h>

char junk;
String inputString="";
SoftwareSerial ble(2,3);
void setup()                    // run once, when the sketch starts
{
 Serial.begin(9600);            // set the baud rate to 9600, same should be of your Serial Monitor
 pinMode(9, OUTPUT);
 pinMode(10,OUTPUT);
 pinMode(11, OUTPUT);
 ble.begin(9600);
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
    if(inputString[0] == 'a'){         //in case of 'a' turn the LED on
      digitalWrite(9, HIGH); 
      delay(500);
      digitalWrite(9,LOW); 
    }else if(inputString[0] == 'b'){   //incase of 'b' turn the LED off
      digitalWrite(10, HIGH); 
      delay(500);
      digitalWrite(10,LOW);
    }else if((char)inputString[0] == 'c'){   //incase of 'b' turn the LED off
      digitalWrite(11, HIGH); 
      delay(500);
      digitalWrite(11,LOW);
    }
    inputString = "";
  }
}
