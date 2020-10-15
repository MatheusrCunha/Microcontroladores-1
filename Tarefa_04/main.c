/*
 * 02_simple_display_mux.c
 *
 *  Created on: Feb 27, 2020
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 *
 *
 *      Exemplo de aplica��o:
 *
 *      - Utiliza o WatchDog Timer
 *      para multiplexar 4 displays de 7 segmentos.
 *      - Utiliza IRQ externa para contar n�mero
 *      de pulsos exibindo-os no display.
 *
 *
 */

#include <msp430.h>

/* Tipos uint16_t, uint8_t, ... */
#include <stdint.h>

#include "gpio.h"
#include "timerA_display_mux.h"
#include "bits.h"

volatile uint16_t i = 0;

#define ENCODER_INPUT  BIT0

void config_ext_irq(){
    /* Pull up/down */
    P2REN = ENCODER_INPUT;

    /* Pull up */
    P2OUT = ENCODER_INPUT;

    /* Habilita��o da IRQ apenas bot�o */
    P2IE =  ENCODER_INPUT;

    /* Transi��o de n�vel alto para baixo */
    P2IES = ENCODER_INPUT;

    /* Limpa alguma IRQ pendente */
    P2IFG &= ~ENCODER_INPUT;
}


/**
  * @brief  Configura sistema de clock para usar o Digitally Controlled Oscillator (DCO).
  *         Utililiza-se as calibra��es internas gravadas na flash.
  *         Exemplo baseado na documenta��o da Texas: msp430g2xxx3_dco_calib.c
  *         Configura ACLK para utilizar VLO = ~10KHz
  * @param  none
  *
  * @retval none
  */
void init_clock_system(){

    /* Configura��o do MCLK em 8MHz */

    /* Se calibra��o foi apagada, para aplica��o */
    if (CALBC1_8MHZ==0xFF)
        while(1);

    DCOCTL = 0;
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ;

    /* Configura ACLK para usar VLO: ~10kHZ */
    BCSCTL3 |= LFXT1S_2;
}

void main(void)
{
    /* Para o watchdog timer
     * Necess�rio para c�digo em depura��o */
    WDTCTL = WDTPW | WDTHOLD;

#if defined (__MSP430FR2355__)
    /* Disable the GPIO power-on default high-impedance mode */
    PM5CTL0 &= ~LOCKLPM5;
#endif

    init_clock_system();
    config_ext_irq();

    /* Inicializa displays */
    timerA_display_mux_init();

    /* Entra em modo de economia de energia */
    __bis_SR_register(LPM4_bits);
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(test))) test (void)
#else
#error Compiler not supported!
#endif
{
    // Liga/desliga LED quando detectado borda no bot�o

    timerA_display_mux_write(i++);

    P2IFG &= ~ENCODER_INPUT;
}
