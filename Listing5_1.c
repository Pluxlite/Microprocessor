#include <msp430.h> 

int d = 0;

void main(void)
{
 WDTCTL = WDTPW|WDTHOLD;
 
 int a = 1;
 float b = -255.25;
 char c = 'c';
 d = d+1;

 while(1);
}
