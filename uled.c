#include<pic.h>
#define _XTAL_FREQ 20000000
#define led RD0
int dummy;

void uart_init()
{
TXSTA=0x24;
RCSTA=0x90;
SPBRG=129;
}


void rx()
{
while(RCIF==0);
RCIF=0;
dummy=RCREG;
}

void main()
{
TRISD0=0;
uart_init();
while(1)
{
rx();
if (dummy=='A')
{
led=1;
}
else if(dummy=='B')
{
led=0;
}
}
}