#include <msp430.h> 
#include <stdint.h>

void debounce(uint16_t input){

    volatile uint16_t dt;
    dt = input;
    while(dt--);

}

/**
 * main.c
 */

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~(LOCKLPM5);

    P4DIR &= ~(BIT1);           // habilita entrada no P4.1 (bot�o S1)
    P4REN |= BIT1;              // habilita resistor
    P4OUT |= BIT1;              // escolhe resistor de pull up

    P2DIR &= ~(BIT3);           // habilita entrada no P2.3 (bot�o S2)
    P2REN |= BIT3;              // habilita resistor
    P2OUT |= BIT3;              // escolhe resistor de pull up

    P1DIR |= BIT0;              // habilita saida no P1.0 (LED VERMELHO)
    P1REN &= ~(BIT0);           // habilita resistor de pull up
    P1OUT &= ~(BIT0);           // zera saida

    P6DIR |= BIT6;              // habilita saida no P6.6 (LED VERDE)
    P6REN &= ~(BIT6);           // habilita resistor de pull up
    P6OUT &= ~(BIT6);           // zera saida


    volatile unsigned int tempo;
    volatile unsigned int tempo2;
    volatile unsigned int tempo_final;


    while(1){

        tempo = 0;
        while(P4IN & BIT1);  // n�o faz nada se n�o apertamos S1

        //----------------------------------------------------------
        // Come�o do Clock: Modo Cont�nuo, ACLK
        TB0CTL = TBSSEL__ACLK | ID__4 | MC__CONTINUOUS;

        // CAP: Seleciona entre captura e compara��o
        // CM: Configura o modo de captura,
        // SCS: define a sincronia do clock com o sinal de captura
        TB0CCTL1 = CAP | SCS | CM_1;
        CCIS1 |= BIT0;
        CCIS0 &= ~BIT0;

        // aperta s2, espera
        while(P2IN & BIT3);    //n�o faz nada enquanto n�o se aperta s2
        CCIS0 |= BIT0;

        TB0CCTL1 &= ~CCIFG;
        tempo = TB0CCR1;

        tempo_final = (tempo / 8192);      //8192 = ACLK / 4

        while(1);

    }


    return 0;

}
