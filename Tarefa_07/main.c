
/*
 * 05_main_simple_pwm.c
 *
 *  Created on: Apr 22, 2020
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 *
 *      Exemplo de parcial de aplicação:
 *
 *      - Gera PWM com o temporizador A0.
 *
 *      - Use o MSP430F2132 para simular PWM no Proteus.
 *      -  http://e2e.ti.com/support/microcontrollers/msp430/f/166/p/702207/2588488
 */

#include <msp430.h>

/* Tipos uint16_t, uint8_t, ... */
#include <stdint.h>
#include "motor.h"
#include "bits.h"

/**
 * @brief  Configura sistema de clock para usar o Digitally Controlled Oscillator (DCO).
 *         Utililiza-se as calibrações internas gravadas na flash.
 *         Exemplo baseado na documentação da Texas: msp430g2xxx3_dco_calib.c
 *         Configura ACLK para utilizar VLO = ~10KHz
 * @param  none
 *
 * @retval none
 */
void init_clock_system(){

    /* Configuração do MCLK em 8MHz */

    /* Se calibração foi apagada, para aplicação */
    if (CALBC1_8MHZ==0xFF)
        while(1);

    DCOCTL = 0;
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ;

    /* Configura ACLK para usar VLO: ~10kHZ */
    BCSCTL3 |= LFXT1S_2;
}

/**
 * @brief  Configura temporizador A.
 *
 * @param  none
 *
 * @retval none
 */
void main(void)
{
    /* Para o watchdog timer
     * Necessário para código em depuração */
    WDTCTL = WDTPW | WDTHOLD;

#if defined (__MSP430FR2355__)
    /* Disable the GPIO power-on default high-impedance mode */
    PM5CTL0 &= ~LOCKLPM5;
#endif

    init_clock_system();

    motor_init();

    define_velocidade_pwm(100);


    while(1)
    {

         motor_direcao(frente);
         _delay_cycles(100000);

         motor_direcao(parado);
         _delay_cycles(100000);

          motor_direcao(re);
         _delay_cycles(100000);

         motor_direcao(esquerda);
         _delay_cycles(100000);

         motor_direcao(direita);
         _delay_cycles(100000);


    }
}
