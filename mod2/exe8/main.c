#include <msp430.h> 
//#include <stdint.h>


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;

	P1OUT &= ~BIT0;
	P1DIR |= BIT0;

	TB0CTL = (TBSSEL__ACLK | MC__UP | TBCLR);


	TB0CCR0 = 0x8000 - 1;

	while(1){
	    while(!(TB0CCTL0 & CCIFG));
	    TB0CCTL0 &= ~CCIFG;

	    P1OUT ^= BIT0;
	}

	
	return 0;
}
