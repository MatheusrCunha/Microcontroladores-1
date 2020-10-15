#include "delay_wdt.h"
#include <msp430.h>
#include "bits.h"
#include "gpio.h"


volatile uint16_t contador;


#define LED BIT0

void config_wd_as_timer(void)
{

    //fonte de clock
    WDTCTL =  WDT_MDLY_8;

    IE1 |= WDTIE;  //Habilita irq


}

void delay_wdt(uint16_t time)
{

    contador = time;
    //economia de energia
    __bis_SR_register(LPM0_bits + GIE);

   // P3DIR = 0xff;

}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(test))) test (void)
#else
#error Compiler not supported!
#endif
{
    P3OUT ^= BIT0;

    static uint16_t cont_irq = 0;


    if(++cont_irq == contador){

       __bis_SR_register(LPM0_bits); //acorda CPU


    }

}
