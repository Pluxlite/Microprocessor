#include <msp430.h>

void main()
{
 WDTCTL = WDTPW|WDTHOLD;

 float arr[] = {2.56,4.88,6.93,0.0,0.0};
 float *ptr = arr,sum = 0;
 short i;

 for(i=0; i<3; i++)
 {
 sum += *ptr++;	
 }
 *ptr++ = sum;		
 *ptr = sum/3;		

 while(1);
}

