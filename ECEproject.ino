#include<SoftwareSerial.h>
#include <MQ2.h>

//change this with the pin that you use
int pin = A5;
int lpg, co, smoke;
MQ2 mq2(pin);
int sensorPin = A0; // select the input pin for the LDR
int sensorValue = 0; // variable to store the value coming from the sensor
int yellow = 11,blue=10,white=9,green=8; // Output pin for LED
int buzzer = 12; // Output pin for Buzzer

void setup() {
// declare the ledPin and buzzer as an OUTPUT:
pinMode(yellow, OUTPUT);
pinMode(green, OUTPUT);
pinMode(white, OUTPUT);
pinMode(blue, OUTPUT);
pinMode(pin,INPUT);
pinMode(sensorPin,INPUT);
pinMode(buzzer,OUTPUT);
mq2.begin();
Serial.begin(9600);
delay(20000);
}

void loop()

{
sensorValue = analogRead(sensorPin);
Serial.println(sensorValue);
 float* values= mq2.read(true); //set it false if you don't want to print the values in the Serial
  //lpg = values[0];
  lpg = mq2.readLPG();
  //co = values[1];
  co = mq2.readCO();
  //smoke = values[2];
  smoke = mq2.readSmoke();
  
if (sensorValue < 100)
{
Serial.println("Fire Detected");
digitalWrite(yellow,HIGH);
digitalWrite(buzzer,HIGH);
delay(1000);

}
else
{digitalWrite(yellow,LOW);
noTone(buzzer);
  }
if(lpg>=10000)
{Serial.println("leakage detected");
digitalWrite(blue,HIGH);
delay(1000);
}
else
{digitalWrite(blue,LOW);
  }
if(co>=100)
{Serial.println("CO Detected");
digitalWrite(white,HIGH);
delay(1000);}
else
{digitalWrite(white,LOW);
  }

 if(smoke>=500)
{Serial.println("smoke Detected");
digitalWrite(green,HIGH);
delay(1000);
  }
else 
{
digitalWrite(green,LOW);
  }
}
