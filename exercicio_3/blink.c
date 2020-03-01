
#include <msp430.h>

#define LED_2 BIT6 //Habilita led_2 do msp430fr2355 P6.6
#define SW_2 BIT3  //Habilita SW2 do msp430fr2355   P2.3
//#define LED_1 BIT0
#define SW_1 BIT1
#define DELAY 20000
//Anodo Comum

void hardware_init()
{

    P6DIR |= LED_2;         // Set P6.6 to output direction
    P2DIR &= ~SW_2;        // //P2.3 SW_2 INPUT

    /*Habilita resistor de pull up ou pull down*/
    P2REN |= SW_2;    //P2.3

    /*Habilita resitor como pull up*/
    P2OUT |= SW_1;    //P2.3
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    hardware_init();

    while(1){
        if(!(P2IN & SW_2))   //If SW is Pressed
        {
            //for(i=DELAY; i--; i>0);
            __delay_cycles(50000);      // Wait 20ms to debounce

            while(!(P2IN & SW_2));    // Wait till SW Released
            P6OUT ^= LED_2;           // Toggle LED
        }
    }

}
