/*
 * simple_display_mux.c
 *
 *  Created on: April 9, 2020
 *      Author: Carolina de Farias
 *      Instituto Federal de Santa Catarina
 */

#include <msp430.h>
#include <stdint.h>
#include "simple_display_mux.h"
#include "bits.h"
#include "gpio.h"

/* Tabela de conversão em flash: Anodo comum */
#ifdef COM_ANODO
const uint8_t convTable[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02,
        0x78, 0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};
#endif

/**
  * @brief  Configura hardware.
  * @param  Nenhum
  *
  * @retval Nenhum.
  */
void display_mux_init() {


   PORT_DIR(DISPLAYS_DATA_PORT) = 0xff;
   PORT_OUT(DISPLAYS_DATA_PORT) = 0;


   PORT_DIR(DISPLAYS_MUX_PORT) = 0b00000111;
   PORT_OUT(DISPLAYS_MUX_PORT)= 0;
}

/**
  * @brief  Escrevre nos displays de 7 segmentos e faz a multiplexação.
  * @param  data: valor sem decimal sem conversão. Dados
  *             são convertidos internamente. data
  *             deve ser maior caso mais de dois displays.
  *
  * @retval Nenhum.
  */
void display_mux_write(uint16_t data){

    int8_t n = NUMBER_DISPLAYS;

    for (n=NUMBER_DISPLAYS-1; n >= 0; n--)
    {

        /*desliga display*/
        //PORT_OUT(DISPLAYS_MUX_PORT)= 0;
        //PORT_OUT(DISPLAYS_DATA_PORT)= 0xff;


        SET_BIT(PORT_OUT(DISPLAYS_MUX_PORT),1<<n);
        /*Escreve no display */
        PORT_OUT(DISPLAYS_DATA_PORT)= display_write(data);


        data = data >> 4;  //atualiza dados
        /* Mantém um tempo ligado:  */
        _delay_cycles(10);

        CLR_BIT(PORT_OUT(DISPLAYS_MUX_PORT),1<<n);


    }

}
/**
  * @brief  Escrevre nos displays de 7 segmentos.
  * @param  data: valor sem decimal sem conversão. Dados
  *             são convertidos internamente. data
  *             deve ser maior caso mais de dois displays.
  *
  * @retval Nenhum.
  */
uint8_t display_write(uint8_t data){

    uint8_t conv;

    /* Data nao pode ser maior que 0x0f */
    conv = data & 0x0f ;

    return convTable[conv];
}

