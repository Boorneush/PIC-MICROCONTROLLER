#include<pic.h>
__CONFIG(0x3F76pr);
#define _XTAL_FREQ 20000000
#define led RB0
void main()
{
TRISB0=0;
while(1)
{
led=1;
__delay_ms(1000);
led=0;
__delay_ms(1000);
}
}