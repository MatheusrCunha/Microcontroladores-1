//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  Texas Instruments, Inc
//  July 2013
//***************************************************************************************

#include <msp430.h>

#define LED_2 BIT6
#define SW_1 BIT1


void hardware_init()
{
    /* Acesso direto: P6.6 como saída. Demais como entrada */
    P6DIR |= LED_2;  //P6.6 (GREEN) OUTPUT

    P4DIR &= ~SW_1;   //P4.1 SW_1 INPUT

    /* Habilita resistor de pull up ou pull down */
    P4REN |= SW_1;

    /* Habilita resitor como pull up */
    P4OUT |= SW_1;
}
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    hardware_init();

    while(1){

        if(P4IN & BIT1)
            P6OUT &= ~BIT6;
        else
            P6OUT |= BIT6;

    }
}
