#include<pic.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x3F72);

int data=0;

void interrupt isr()
{
if(RCIF==1)
{
data=RCREG;
RCIF=0;
}
}

void main()
{
GIE=1;
PEIE=1;
RCIE=1;

TRISB=0x00;
PORTB=0x00;
TRISC=0x00;

TXSTA=0x26;
RCSTA=0x90;
SPBRG=129;

while(1)
{
if(data=='a')
{
RB7=1;
}
else if(data=='b')
{
RB7=0;
}
}
}