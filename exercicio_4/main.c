#include <msp430.h> 

//#define LED_1 BIT0    // RED LED -> P1.0
#define LED_2 BIT6    // GREEN LED -> P6.6
#define SW_1 BIT1     // SW1 -> P4.1
#define SW_2 BIT3     // SW2 -> P2.3
#define delay_1 30000
#define delay_2 10000
/**
 * main.c
 */

void hardware_init()
{
    P6DIR |= LED_2;
}
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode

	int i;
	int count1;
	int count2;

	hardware_init();
	while(1){

	    //Pisca rapidamente
	   for(count1=0; count1<5; count1++){


	   P6OUT = P6OUT ^ LED_2;  //->LED ON

	   for(i=0;i<delay_1;i++);

	   }
	   for(count2=0;count2<5;count2++){

	   //Liga/Desliga LED
	   P6OUT = P6OUT ^ LED_2;

	   /* Atraso */
	   for (i=0;i<delay_2; i ++);

	   }
   }
}
