/*
 * teclado.c
 *
 *  Created on: 14 de abr de 2020
 *      Author: Matheus Cunha
 */
#include <msp430.h>
#include "teclado.h"
#include "bits.h"
#include "gpio.h"

/*codificação do teclado */

const unsigned char teclado[4][3] = {{'1', '2', '3'},
                                    {'4', '5', '6'},
                                    {'7', '8', '9'},
                                    {'*', '0', '#'}};

//0x07  =  0000 0111

//macros utilização do  port

void hardware_init()
{
    PORT_DIR(PORT) = 0x07; // Definindo pino como saída

    PORT_OUT(PORT) = 0x07; // Definindo
}

unsigned char ler_teclado()
{

    // n é para a coluna
    // j é para linhas
    unsigned char col, j, tecla=0xFF, linha;

    for(col=0;col<3;col++){

        //Zera os bits da coluna
        CLR_BIT(PORT_OUT(PORT), 1 << col); //apaga o bit da coluna(varredura)

        _delay_cycles(1000); //atraso para uma varredura mais lenta, também elimina o ruído da tecla

        linha = 0; //verifica linha

        for(j=3; j<7; j++){

          if(!TST_BIT(PORT_IN(PORT), 1 << j)){ //Testa se foi pressionado?
            //PORT_IN Registrador de entrada

            tecla = teclado[linha][col];

          }
          linha++;
      }

      SET_BIT(PORT_OUT(PORT), 1 << col); //Ativa bit zarado anteriormente


    }
    return tecla;
}
