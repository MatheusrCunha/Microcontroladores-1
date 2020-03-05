/*
 * LAUNCHPAD.h
 *
 *  Created on: 4 de mar de 2020
 *      Author: mcunha
 */

#ifndef LAUNCHPAD_H_
#define LAUNCHPAD_H_


#define SW_1 BIT1  //
#define SW_1_DIR P1DIR
#define SW_1_IN P1IN
#define SW_2_IN P2IN
#define SW_2_DIR P2DIR
#define SW_2  BIT3  //P2.3
#define LED_1 BIT0
#define LED_1_DIR P1DIR
#define LED_1_OUT P1OUT
#define LED_2 BIT6 //P6.6
#define LED_2_DIR P6DIR
#define LED_2_OUT P6OUT


#define set_led1()      (LED1_OUT |= LED1)
#define clr_led1()      (LED1_OUT &=~LED1)
#define cpl_led1()      (LED1_OUT |= LED1_OUT ^ LED1)
#define set_led2()      (LED2_OUT |= LED2)
#define clr_led2()      (LED2_OUT &=~LED2)
#define cpl_led2()      (LED2_OUT |= LED2_OUT ^ LED2)



#endif /* LAUNCHPAD_H_ */
