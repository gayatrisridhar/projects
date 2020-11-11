//reciver(SLAVE)--------------------------(RECIEVER 2 )
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
int button_state = 0;
int red1=2;  
int yellow1=3;
int green1=4;

int red2=7;  
int yellow2=6;
int green2=5;

int x=1;
void setup() {
  
  Wire.begin(5);
pinMode(red1, OUTPUT);      
pinMode(yellow1, OUTPUT);   
pinMode(green1, OUTPUT);

pinMode(red2, OUTPUT);      
pinMode(yellow2, OUTPUT);   
pinMode(green2, OUTPUT);

Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();              //This sets the module as receiver
}
void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the sender arduino 
}
void loop()
{
if (radio.available())              //Looking for the data.
  {
    char text[32] = "";                 //Saving the incoming data
    radio.read(&text, sizeof(text));    //Reading the data
    radio.read(&button_state, sizeof(button_state));    //Reading the data
  
     Serial.println(button_state);
     
     
if (button_state == 1 && x==0)
    {

      
      digitalWrite(green1, HIGH);
      digitalWrite(red2, HIGH); 
      int i=0;
      while(i<10)
      {
       digitalWrite(yellow1,HIGH);
       delay(500);
       digitalWrite(yellow1,LOW);
       delay(500); 
       i++;
       }
    
      
      Serial.println(text);

    }    
    
 else if (button_state==0 && x==0)
   {
   
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
   else if (button_state==0 && x==1)
   {
    digitalWrite(red1, HIGH);
      digitalWrite(red2, HIGH); 
      
   }
   else if (button_state==1 && x==1)
   {
    digitalWrite(red1, HIGH);
      digitalWrite(red2, HIGH); 
      
   }
   }
  delay(5); 
  }
