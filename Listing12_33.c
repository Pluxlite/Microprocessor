#include <msp430.h>

 unsigned int ReceivedDutyCycle = 0;

void PinConfig(void);
void TimerConfig(void);
void I2CConfig(void);

void main(void)
{
 PinConfig();
 TimerConfig();
 I2CConfig();

 _enable_interrupts();
 LPM0;
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void){
 ReceivedDutyCycle = UCB0RXBUF;
 TACCR1 = ReceivedDutyCycle*10;
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void){
 UCB0STAT &= ~(UCSTPIFG | UCSTTIFG);
}

void PinConfig(void){
 P1DIR = BIT2;
 P1SEL |= BIT6|BIT7|BIT2;
 P1SEL2 |= BIT6|BIT7;
}

void TimerConfig(void){
 WDTCTL = WDTPW|WDTHOLD;
 BCSCTL1 = CALBC1_1MHZ;
 DCOCTL = CALDCO_1MHZ;
 TACTL = TASSEL_2|MC_1|ID_3;	
 TACCR1 = 0;
 TACCR0 = 999;
 TACCTL1 = OUTMOD_7;
}

void I2CConfig(void){
 UCB0CTL1 |= UCSWRST;
 UCB0CTL0 = UCMODE_3 | UCSYNC;
 UCB0I2COA = 0x48;
 UCB0CTL1 &= ~UCSWRST;
 UCB0I2CIE |= UCSTPIE | UCSTTIE;
 IE2 |= UCB0RXIE;
}
