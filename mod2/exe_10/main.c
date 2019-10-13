#include <msp430.h> 

/**
 * main.c
 */

/*
 *  N0 = Tempo/Tclk = (1 / X hz desejados) / (1 / x_CLK)
 *  CCR0 = N0 - 1
 *
 *  Duty Cicle de X %
 *  N1 = 0,X * N0
 *  CCR1 = N1 - 1
 *
 *  Divisor = Fo_clock / nossa Freq
 *
*/

int main(void)
{

    //P1OUT &= ~BIT0;
    P1DIR |= BIT0;
    PM5CTL0 &= ~LOCKLPM5;       // destrava pinos

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    TB0CTL = (TBSSEL__ACLK | MC__UP | TBCLR); // MC__UP faz teto de contagem
    TB0CCR0 = 0x8000 - 1;   //ACLK conta 2 segundos, pegamos metade

    TBCCTL0 = CCIE; // permite vermos a interrup��o (local)
    __enable_interrupt();  // cntrl + space, HABILITADOR GLOBAL DE INTERRUP��O EM SR
                            // SETA GIE no SR

    while(1){

    }

    return 0;
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void TB0_CCR0_ISR(){

    P1OUT ^= BIT0;                      // executado qnd led chega a 1 segundo

}
