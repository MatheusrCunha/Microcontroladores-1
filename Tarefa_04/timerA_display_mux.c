/*
 * simple_display_mux.c
 *
 *  Created on: Feb 27, 2020
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 */

#include <msp430.h>
#include <stdint.h>

#include "timerA_display_mux.h"
#include "gpio.h"
#include "bits.h"

#ifndef __MSP430F2132__
    #error "Example not tested with this device!"
#endif

/* Tabela de conversão em flash: Anodo comum */
#ifdef COM_ANODO
const uint8_t convTable[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02,
        0x78, 0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};
#endif


volatile struct display_status_t {  //se a struct é volatile todos os membros da struct serão volatile
    uint16_t current_data;   //inteiro sem sinal de 16bits
    uint8_t i; //inteiro sem sinal de 8bits

} my_displays;


void timerA_display_mux_init(){
    /* Estado inicial */
    my_displays.current_data = 0;
    my_displays.i = 0;

    /* Configuração de portas */
    PORT_DIR(DISPLAYS_DATA_PORT) |= 0x7f;
    PORT_DIR(DISPLAYS_MUX_PORT) |= 0xf;
    //registro de controle,

    TA0CTL = TASSEL_2 | MC_1 | ID_1;


//registro de controle,

    /* IRQ por comparação entre contagem e comparador 0 */
    TA0CCTL0 = CCIE;
     /* Valor de comparação é 50000 ciclos*/
    TA0CCR0 = 20000;


    P2DIR = BIT2;
}


void inline timerA_display_mux_write(uint16_t data){
    my_displays.current_data = data;
}

void inline timerA_display_multiplexacao()
{
    /* Separa os nibles dos dados em função de i */
    uint8_t data = my_displays.current_data >> (my_displays.i * 4);
         // 0001 = 001
     /* Converte dados */
    data = data & 0xf;
    data = convTable[data];

           /* Desliga todos os displays e coloca dado convertido em DISPLAYS_DATA_PORT */
    PORT_OUT(DISPLAYS_MUX_PORT) &= ~(0x0f);
    PORT_OUT(DISPLAYS_DATA_PORT) = data;

    /* Liga cada display independentemente */
    SET_BIT(PORT_OUT(DISPLAYS_MUX_PORT), (1 << my_displays.i));


    /* Faz a variável i circular entre 0 e 3 */
    my_displays.i++;
    my_displays.i &= 0x03;


}


/* ISR do watchdog: executado toda a vez que o temporizador estoura */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void) //tipo de timer, esse é 0
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) TIMER0_A0_VECTOR (void)
#else
#error Compiler not supported!
#endif
{
    P2OUT ^= BIT2;


    // display
    timerA_display_multiplexacao();
}
