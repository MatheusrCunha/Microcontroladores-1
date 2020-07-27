/*
 * main_tarefa1.c
 *
 *  Created on: 15 de abr de 2020
 *      Author: Matheus Cunha
 */

#include <msp430.h>
#include <stdio.h>
#include "teclado.h"
#include "lcd.h"

void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;  //Desabilita o whatchdog timer

    unsigned char ler; //Para ler o teclado

    /* Inicializa hardare: veja lcd.h para
    * configurar pinos */
    lcd_init_4bits();

    lcd_send_data(LCD_LINE_0, LCD_CMD);

    _delay_cycles(100000);


     //teclado

     hardware_init();


     _delay_cycles(100000);

     while (1){

        ler = ler_teclado(); //leitura do teclado

        if(ler!=0xFF){  //se alguma tecla foi pressionada mostra seu valor
            if(ler == '0'){
               lcd_clear();
               _delay_cycles(10000);
            }
            else
               lcd_send_data(ler,LCD_DATA);
               _delay_cycles(10000);
        }

     }

}
