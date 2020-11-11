//reciver (MASTER)--------------RECIEVER(1)
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00002";
int button_state = 0;   //for the tx and rx of master
int red1=2;  
int yellow1=3;
int green1=4;


int red2=7;  
int yellow2=6;
int green2=5;

int x=1;

void yel()
{
  int j=0;
      while(j<10)
      {
        digitalWrite(yellow1,HIGH);
        delay(500);
        digitalWrite(yellow1,LOW);
        delay(500);
        j++;
        }
      
  }

void setup() {
pinMode(red1, OUTPUT);      
pinMode(yellow1, OUTPUT);   
pinMode(green1, OUTPUT);

pinMode(red2, OUTPUT);      
pinMode(yellow2, OUTPUT);   
pinMode(green2, OUTPUT);

Serial.begin(9600);
Wire.begin(00001);
radio.begin();
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();              //This sets the module as receiver
}
void loop()
{
if (radio.available())              //Looking for the data.
  {
    char text[32] = "";                 //Saving the incoming data
    radio.read(&text, sizeof(text));    //Reading the data
    radio.read(&button_state, sizeof(button_state));    //Reading the data
  
     Serial.println(button_state);
     
      
    if (button_state == 1)
    {

      x=1;
      Wire.beginTransmission(5);
      Wire.write(x);
      Wire.endTransmission();
      digitalWrite(green1, HIGH);
      digitalWrite(red2, HIGH); 
      yel();
      
      Serial.println(text);

    }    
    
   else if (button_state==0)
   {
       x=0;
       Wire.beginTransmission(5);
      Wire.write(x);
      Wire.endTransmission();
      digitalWrite(red1, HIGH); 
      digitalWrite(yellow1, LOW);
      digitalWrite(green1, LOW);

      digitalWrite(red2, LOW); 
      digitalWrite(yellow2, LOW);
      digitalWrite(green2, HIGH);
      delay(500);

      digitalWrite(red2, LOW); 
      digitalWrite(yellow2, HIGH);
      digitalWrite(green2, LOW);
      delay(100);

    
      digitalWrite(red2, HIGH); 
      digitalWrite(yellow2, LOW);
      digitalWrite(green2, LOW);
      
      digitalWrite(red1, LOW); 
      digitalWrite(yellow1, LOW);
      digitalWrite(green1, HIGH);
      delay(500);

      digitalWrite(red1, LOW); 
      digitalWrite(yellow1, HIGH);
      digitalWrite(green1, LOW);
      delay(100);
      Serial.println(text);

   }
  }
  delay(5);
  
}
