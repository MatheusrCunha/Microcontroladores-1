#include <msp430.h>

#define LED_2   BIT6
#define BUTTON_0  BIT1

void config_ext_irq(){
    /* Primeiramente configura porta: LEDS como saída.
     * Demais pinos como entraada  */
    P6DIR = LED_2;

    /* Pull up/down */
    P4REN = BUTTON_0;

    /* Pull up */
    P4OUT = BUTTON_0;

    /* Habilitação da IRQ apenas botão */
    P4IE =  BUTTON_0;

    /* Transição de nível alto para baixo */
    P4IES = BUTTON_0;

    /* Limpa alguma IRQ pendente */
    P4IFG &= ~BUTTON_0;
}



void main(){
    /* Configuração de hardware */
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0  &= ~LOCKLPM5;
    /* Configura interupções */
    config_ext_irq();

    /* Habilita IRQs e desliga CPU */
    __bis_SR_register(LPM4_bits | GIE);

}


/* Port 1 ISR (interrupt service routine) */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else
#error Compiler not supported!
#endif
{
    /* Liga/desliga LED quando detectado borda no botão */
    P6OUT ^= LED_2;

    /* Limpa sinal de IRQ do botão 0 */
    P4IFG &= ~BUTTON_0;
}
