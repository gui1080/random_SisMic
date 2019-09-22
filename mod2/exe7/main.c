#include <msp430.h> 
#include <stdint.h>

void debounce(uint16_t input){

    volatile uint16_t dt;
    dt = input;
    while(dt--);

}

unsigned char rand(){
    static unsigned char num = 5;
    num = (num * 17) % 7;
    return num;

}

int main(void)
{
    PM5CTL0 &= ~(LOCKLPM5);
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P4DIR &= ~(BIT1);           // habilita entrada no P4.1 (bot�o S1)
    P4REN |= BIT1;              // habilita resistor
    P4OUT |= BIT1;              // escolhe resistor de pull up

    P2DIR &= ~(BIT3);           // habilita entrada no P2.3 (bot�o S2)
    P2REN |= BIT3;              // habilita resistor
    P2OUT |= BIT3;              // escolhe resistor de pull up

    P1DIR |= BIT0;              // habilita saida no P1.0 (LED VERMELHO)
    P1REN &= ~(BIT0);           // habilita resistor de pull up
    P1OUT &= ~(BIT0);           // zera saida

    P6DIR |= BIT6;              // habilita saida no P1.0 (LED VERDE)
    P6REN &= ~(BIT6);           // habilita resistor de pull up
    P6OUT &= ~(BIT6);

    uint16_t conta_user;
    conta_user = 0;         // contador do usuario

    uint16_t num_rand;
    num_rand = rand();      // numero gerado aleatoriamente

    // o jogo come�a com as luzes apagadas
    // id�ia: aperte 7 vezes para terminar o jogo!

    while(1){

        while((P2IN & BIT3) && (P4IN & BIT1));  // n�o faz nada se n�o apertamos nada

        if(!(P4IN & BIT1)){
            debounce(25000);   // aperta s1, incrementa
            conta_user++;
        }

        if(!(P2IN & BIT3)){    // aperta s2, compara
            debounce(25000);
            if(num_rand == conta_user){   // se o numero � igual ao numero gerado
                P6OUT |= BIT6;          // setamos a luz verde
                P1OUT &= ~(BIT0);       // apagamos a vermelha
                num_rand = rand();      // geramos um numero novo
                conta_user = 0;         // zeramos a contagem e voltamos pro inicio
            }
            else{   // se o resultado � diferente do que foi gerado
                P1OUT |= BIT0;  // ligamos a luz vermelha
                P6OUT &= ~(BIT6);    // apagamos a luz verde
                num_rand = rand();  // geramos um numero novo
                conta_user = 0;   // zeramos a contagem e voltamos pro inicio
            }

        // entre as rodadas, haver� uma luz verde ou uma luz vermelha da rodada anterior.
        // o resultado da nova rodada ir� "dar overwrite" no resultado da rodada anterior

        }


    }


    return 0;
}
