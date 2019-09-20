#include <msp430.h> 
#include <stdint.h>

void debounce(){

    volatile uint16_t dt;
    dt = 10000;
    while(dt--);

}


int main(void)
{
    PM5CTL0 &= ~(LOCKLPM5);
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P4DIR  &= ~(BIT1);          // bot�o 4.1
	P4REN  |= BIT1;
	P4OUT  |= BIT1;

	P1DIR  |= BIT0;             // led
	P1REN  &= ~(BIT0);
	P1OUT &= ~(BIT0);

	while(1){

	    if(!(P4IN & BIT1)){
	        P1OUT ^= BIT1;
	    }
	    else{
	        P1OUT ^= BIT0;
	    }

	}

	return 0;
}
