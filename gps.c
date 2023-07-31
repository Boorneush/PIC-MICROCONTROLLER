#include<pic.h>
#include <stdio.h>
#include <string.h>

__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_OFF & CP_OFF & BOREN_ON & LVP_OFF & CPD_OFF & WRT_OFF & DEBUG_OFF);

#define lcd_dat PORTD
#define rs RC0
#define rw RC1
#define en RC2
#define delay for(i=0;i<1000;i++)

/*GPS Variables And Functions*/
char namegps[7], name1gps[7] = "GPRMC,",gpsdat[63];
char msggps , checkgps;
int h;
unsigned char f;

void interrupt ser();

/*LCD Variables and Functions*/
int i;

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);

/*Serial Functions*/
void serial_init();
void tx(unsigned char dat);
unsigned char rx();
void tx_string(unsigned char *s);


void main()
{
  TRISD=0;
  INTCON|=0b11000000;
  PIE1=0b00100000;
  lcd_init();
  serial_init();

  cmd(0x80);
  show("LON:                ");
  cmd(0xc0);
  show("LAT:                ");
  while(1);
}

void interrupt ser()
{
  if(RCIF) {
    msggps=RCREG;
    
    if(msggps=='$') {
      RCIE=0;
      RCIF=0;
 
      for(f=0;f<=5;f++) {
        while(!RCIF);
        namegps[f]=RCREG;
      }
        checkgps=strcmp(namegps,name1gps);
         if(checkgps==0) {
           for(f=0;f<=62;f++) {
            while(!RCIF);
            gpsdat[f]=RCREG;      
        }
 
        cmd(0x84);
        for(h=12;h<14;h++) {
          dat(gpsdat[h]);
        }
        dat('.');
        for(h=14;h<16;h++) {
          dat(gpsdat[h]);
        }
        for(h=17;h<19;h++) {
          dat(gpsdat[h]);
        }
        dat(223);
        dat(' ');
        dat('N');
 
        cmd(0xc4);
        for(h=26;h<28;h++) {
          dat(gpsdat[h]);
        }
        dat('.');
        for(h=28;h<30;h++) {
          dat(gpsdat[h]);
        }
        for(h=31;h<33;h++) {
          dat(gpsdat[h]);
        }
        dat(223);
        dat(' ');
        dat('E');
      }
      TXIF=RCIF=0;
    }  
  }
  
}  

void lcd_init()
{
  TRISC0=TRISC1=TRISC2=TRISD=0;
  cmd(0x38);
  cmd(0x0e);
  cmd(0x06);
  cmd(0x80);
}

void cmd(unsigned char a)
{
  lcd_dat=a;
  rs=0;
  rw=0;
  en=1;
  delay;
  en=0;
}

void dat(unsigned char b)
{
  lcd_dat=b;
  rs=1;
  rw=0;
  en=1;
  delay;
  en=0;
}

void show(unsigned char *s)
{
  while(*s)
  {
    dat(*s++);
  }
}

void serial_init()
{
  TRISC6=TRISC7=1;
  TXSTA=0b00100010;
  RCSTA=0b10010000;
  SPBRG=17;
  TXIF=RCIF=0;
}
  
void tx(unsigned char dat)
{
  TXREG=dat;
  while(!TXIF);
}

unsigned char rx()
{
  while(!RCIF);
  return RCREG;
}

void tx_string(unsigned char *s)
{
  while(*s)
  {
    tx(*s++);
  }
}