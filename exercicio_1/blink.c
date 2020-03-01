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

#define LED_1 BIT0 //Ativa led 1 do msp430fr2355
#define LED_2 BIT6 //Ativa led 2 do msp430fr2355
#define DELAY 50000

void main(void){

    int i;

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    P6DIR |= LED_2;                          // Set P6.6 to output direction

    while(1){

        P6OUT = P6OUT ^ LED_2;

       /* Atraso */
       for (i=DELAY;i--; i > 0);
   }
}
