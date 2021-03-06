//TRANSMITTER(2)----------------------------TRANSMITTER-2-(SLAVE)
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#include <SPI.h>

//transmitter final

RF24 radio(9, 10); // CE, CSN         

const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
int button_pin = 7;
int button_state = 0;

void setup() 
{
  pinMode(button_pin, INPUT);
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}
void loop()
{
  button_state = digitalRead(button_pin);
  if(button_state == 1)
  {
    const char text[] = "Your Button State is HIGH";
    radio.write(&text, sizeof(text));                  //Sending the message to receiver
  }
  else
    if(button_state == 0 )
  {
    const char text[] = "Your Button State is LOW";
    radio.write(&text, sizeof(text));                  //Sending the message to receiver 
  }
  //radio.write(&button_state, sizeof(button_state));  //Sending the message to receiver 
  delay(1000);
}
