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

//#define LED_1 BIT0; //BIT0 define o pino do led
#define LED_2 BIT6; //BIT6 define o pino do led 2


void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    //P1DIR |= LED_1;                         // Set P1.0 to output direction
    P6DIR |= LED_2

    for(;;) {
        volatile unsigned int i;            // volatile to prevent optimization

        //P1OUT ^= LED_1;                     // Toggle P1.0 using exclusive-OR
        P6OUT ^= LED_2;                       // Led GREEN

        i = 50000;                          // SW Delay para 1 segundo
        do i--;
        while(i != 0);
    }
}
