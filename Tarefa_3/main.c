#include <msp430.h>
#include <stdint.h>
#include <stdio.h>


#include "lcd.h"
#include "delay_wdt.h"
#include "bits.h"
#include "gpio.h"


/**
 * main.c
 */

#define LED BIT0

void init_clock_system(){

    /* Configuração do MCLK em 8MHz */

     /* Se calibração foi apagada, para aplicação */
     if (CALBC1_8MHZ==0xFF)
         while(1);

     DCOCTL = 0;
     BCSCTL1 = CALBC1_8MHZ;
     DCOCTL = CALDCO_8MHZ;

     /* Configura ACLK para usar VLO: ~10kHZ */
    // BCSCTL3 |= LFXT1S_2;
}


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    init_clock_system();

    config_wd_as_timer();

    P3DIR = 0xFF;

    while(1){

       //P3OUT ^= BIT0;

       delay_wdt(100);

    }

}
