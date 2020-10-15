/*
 * 03_main_ext_irq_encoder.c
 *
 *  Created on: Mar 12, 2020
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 */

#include <msp430.h>
#include <stdint.h>
#include "simple_display_mux.h"

#define ENCODER_INPUT  BIT0

volatile uint16_t pulses;
volatile uint8_t i;

void config_ext_irq()
{

    P2DIR &= ~(ENCODER_INPUT);

    /* Pull up/down */
    P2REN = ENCODER_INPUT;

    /* Pull up */
    P2OUT = ENCODER_INPUT;

    /* Habilitação da IRQ apenas botão */
    P2IE =  ENCODER_INPUT;

    /* Transição de nível alto para baixo */
    P2IES = ENCODER_INPUT;

    /* Limpa alguma IRQ pendente */
    P2IFG &= ~ENCODER_INPUT;


}

void main(void)
{
    /* Configuração de hardware */
    WDTCTL = WDTPW | WDTHOLD;

#if defined (__MSP430FR2355__)
    /* Disable the GPIO power-on default high-impedance mode */
    PM5CTL0 &= ~LOCKLPM5;
#endif

    /* Inicializa displays */
    display_mux_init();

    /* Configura interupções */
    config_ext_irq();

    __bis_SR_register(GIE);
    pulses = 0;

    while(1){

         // __bis_SR_register(LPM4_bits);   //Desligar a CPU

          display_mux_write(pulses);
           _delay_cycles(10);
    }
}



/* Port 1 ISR (interrupt service routine) */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void ext_irq(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(test))) test (void)
#else
#error Compiler not supported!
#endif
{
     /* Conta o número de pulsos */
    pulses++;

    /* Limpa sinal de IRQ do botão 0 */
    P2IFG &= ~ENCODER_INPUT;

    //__bic_SR_register_on_exit(LPM4_bits + GIE); //usado para acordar a main

}
