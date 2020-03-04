#include <msp430.h>

/* Tipos uint16_t, uint8_t, ... */
#include <stdint.h>

#include "led_display.h"

void main(void)
{
    /* Para o watchdog timer
     * Necessário para código em depuração */
    WDTCTL = WDTPW | WDTHOLD;

    volatile uint16_t i;  //
    uint8_t x = 0;

    /* Inicializa displays */
    display_init();

    while(1)
    {
        display_write(x);

        /* Delay */
        for(i=1000; i>0; i--);

        /* Incrementa e limita valor de x até 0x0f */
        x++;
        x = x & 0xf; //faz lógica & bit a bit
    }
}
