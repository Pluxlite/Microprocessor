#include <msp430.h>

#define MotorStart (P1SEL |= 0x04)
#define MotorStop (P1SEL &= ~0x04)

 int Count = 0;
 int Control = 0;

void PinConfig(void);
void TimerConfig(void);
void ADCConfig(void);

void main(void)
{
 PinConfig();
 TimerConfig();
 ADCConfig();
 
 _enable_interrupts();

 while(1){
 ADC10CTL0 |= ADC10SC;
 
 while((ADC10CTL1&ADC10BUSY)==ADC10BUSY);

 if(Control == 0){
 if(ADC10MEM < 0x0300){
 MotorStart;
 TACTL = MC_1|ID_2|TASSEL_2|TACLR;
 Control = 1;
 }}}
}

void PinConfig(void){
 P1DIR = 0xFE;
 P1OUT = 0x10;
}

void TimerConfig(void){
 WDTCTL = WDTPW|WDTHOLD;
 
 TACCTL0 = CCIE;
 TACCTL1 = OUTMOD_7;
 TACTL = MC_0;
 TACCR0 = 49;
 TACCR1 = 25;
}

void ADCConfig(void){
 ADC10CTL0 = ADC10ON|SREF_0|ADC10SHT_3;
 ADC10CTL1 = INCH_0|ADC10SSEL_0|ADC10DIV_0\
 |SHS_0|CONSEQ_0;
 ADC10AE0 = BIT0;
 ADC10CTL0 |= ENC;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void isr_name (void){
 Count++;
 if(Count == 20000){
 MotorStop;
 TACTL = MC_0;
 Control = 0;
 Count = 0;
 }
}
