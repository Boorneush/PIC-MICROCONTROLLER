#include<pic.h>

#define relay RB0
#define sw RB1

void main()
{
    TRISB0=0;
    TRISB1=1;
    while(1) {
        if(sw==1){
            relay=1;
        } else {
            relay=0;
        }
    }
}