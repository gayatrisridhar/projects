#include<pic.h>
__CONFIG(0x20f2);
#define _XTAL_FREQ 20000000
#define MWS RD0
#define Buz RC1
#define BUTTON RD7
#define Latch RD2

void delay(unsigned int x)
{
    while(x--);
}

void transmit(unsigned vhar byte)
{
    TXSTA=0x24;//Transmit Status And Control Register
    RCSTA=0x90;
    BRG16=0
    SPBRG=10   ;//USART Baud Rate Generator
    TXREG=byte;
    while(TXIF==0);
    TXIF=0;
 }

void SIM900_print (unsigned char *p)
{
    while(*p)
    {
        transmit(*p++);
        delay(1000);
    }
}

void main()
{
    TRISC=0x80;
    TRISD=0x81;
    int flag=1;
    while(1)
    {
        if(MWS==1)
        {
            Latch=1;
            Buz=1;
            SIM900_print("AT\r\n");
            __delay_ms(1000);
            SIM900_print("AT+CMGF=1\r\n");//sets gsm in sms mode
            __delay_ms(1000);
            
            SIM900_print("AT+CMGS=\"+919818909609"\r\n"); //sends sms to this number
            __delay_print(1000);
            SIM900_print("Security Alert!!Burglar has entered.");
            __delay_ms(1000);
            transmit((char)26);//ascii of control+z;to send the message
            __delay_ms(1000);
            Buz=0;
            for (int i-0;i<6;i++)
            {
                __delay_ms(1000);
            }
        }
        Buz=Latch=0;
        if(Button==1)
        {
            while(1);
        }
    
    }
}