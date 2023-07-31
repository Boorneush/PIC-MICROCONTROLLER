#include<htc.h>

__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_OFF & CP_OFF & BOREN_ON & LVP_OFF & CPD_OFF & WRT_OFF & DEBUG_OFF);

#define NUMBER 9876543210          //Here insert your number where you want to send message
 
void ser_int();
void tx(unsigned char);
unsigned char rx();
void tx_str(unsigned char *);
 
void sms(unsigned char *num1,unsigned char *msg);
void gsm_delay();
 
unsigned int dell;
 
int main()
{
        TRISC6=TRISC7=1;
        ser_int();
        sms(NUMBER, "Welcome to the Embetronicx");
        while(1);
}
 
void sms(unsigned char *num1,unsigned char *msg)
{
  tx_str("AT");
  tx(0x0d);
  gsm_delay();
 
  tx_str("AT+CMGF=1");
  tx(0x0d);
  gsm_delay();
 
  tx_str("AT+CMGS=");
  tx('"');
  while(*num1)
    tx(*num1++);
  tx('"');
  tx(0x0d);
  gsm_delay();
 
  while(*msg)
    tx(*msg++);
  tx(0x1a);
  gsm_delay();
}
 
void gsm_delay()
{
  unsigned long int gsm_del;
  for(gsm_del=0;gsm_del<=50000;gsm_del++);
}
 
void ser_int()
{
  TXSTA=0x20;  //BRGH=0, TXEN = 1, Asynchronous Mode, 8-bit mode
  RCSTA=0b10010000; //Serial Port enabled,8-bit reception
  SPBRG=17;      //9600 baudrate for 11.0592Mhz
  TXIF=RCIF=0;
}
  
void tx(unsigned char a)
{
  TXREG=a;
  while(!TXIF);
  TXIF = 0;
}

unsigned char rx()
{
  while(!RCIF);
  RCIF=0;
  return RCREG;
}

void tx_str(unsigned char *s)
{
  while(*s) {
    tx(*s++);
  }
}