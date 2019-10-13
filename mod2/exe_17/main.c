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
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~(LOCKLPM5);
	
    P4DIR &= ~(BIT1);           // habilita entrada no P4.1 (botão S1)
    P4REN |= BIT1;              // habilita resistor
    P4OUT |= BIT1;              // escolhe resistor de pull up

    P2DIR &= ~(BIT3);           // habilita entrada no P2.3 (botão S2)
    P2REN |= BIT3;              // habilita resistor
    P2OUT |= BIT3;              // escolhe resistor de pull up

    P1DIR |= BIT0;              // habilita saida no P1.0 (LED VERMELHO)
    P1REN &= ~(BIT0);           // habilita resistor de pull up
    P1OUT &= ~(BIT0);           // zera saida

    P6DIR |= BIT6;              // habilita saida no P6.6 (LED VERDE)
    P6REN &= ~(BIT6);           // habilita resistor de pull up
    P6OUT &= ~(BIT6);           // zera saida


    volatile unsigned int tempo;

    while(1){

        tempo = 0;
        while(P4IN & BIT1);  // não faz nada se não apertamos S1

        TB0CTL = (TBSSEL__SMCLK | ID__8| MC__CONTINOUS | TBCLR); // MC__UP faz teto de contagem

        // 45000 = 3 segundos

        // 37000 = 2 segundos

        // 28000 = 1 segundo

       // aperta s2, espera


        //debounce(15000);

       while(P2IN & BIT3);    //não faz nada enquanto não se aperta s2

       tempo = TB0R;

       if(tempo >= 45000){
           P1OUT &= ~(BIT0);
           P6OUT |= (BIT6);
       }
       if((tempo >= 28000) && (tempo < 45000)){
           P1OUT |= (BIT0);
           P6OUT |= (BIT6);
       }
       else{
           P1OUT |= (BIT0);
           P6OUT &= ~BIT6;
       }


       while(1);
       //TB0CCTL1 &= ~CCIFG;

    }


    return 0;

}
