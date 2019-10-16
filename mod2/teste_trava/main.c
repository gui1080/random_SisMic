#include <msp430.h> 


inline void trava_milissegundos(long long int milissegundos){

    // conta até 8 segundos
    // recebo um long int

    // 8192 = ACLK / 4
    // milisegundos = ((batidas de clock * 1000) / 8192)
    // batidas de clock = ((milissegundos * 8192) / 1000)
    // o nosso CCR0!

    volatile unsigned long int batidas_de_clock;
    batidas_de_clock = (milissegundos * 8.192);

    TB0CTL = (TBSSEL__ACLK | ID__4 | MC__CONTINOUS | TBCLR);
    TB0CCR0 = batidas_de_clock - 1;

    while(!(TB0CCTL0 & CCIFG));
    TB0CCTL0 &= ~CCIFG;

}

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	PM5CTL0 &= ~(LOCKLPM5);

    P1DIR |= BIT0;              // habilita saida no P1.0 (LED VERMELHO)
    P1REN &= ~(BIT0);           // habilita resistor de pull up
    P1OUT &= ~(BIT0);           // zera saida

    // area de testes

    trava_milissegundos(1000);
    P1OUT ^= BIT0;

    trava_milissegundos(1000);
    P1OUT ^= BIT0;

    trava_milissegundos(1000);
    P1OUT ^= BIT0;

    trava_milissegundos(1000);
    P1OUT ^= BIT0;

    trava_milissegundos(1000);
    P1OUT ^= BIT0;

	return 0;
}
