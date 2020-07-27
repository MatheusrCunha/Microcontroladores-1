/*
 * teclado.h
 *
 *  Created on: 14 de abr de 2020
 *      Author: Matheus Cunha
 */

#ifndef TECLADO_H_
#define TECLADO_H_

#include <stdint.h>
#include <msp430.h>

#include "gpio.h"


#define PORT P3

// Protótipo de funções

void hardware_init();

unsigned char ler_teclado();


#endif /* TECLADO_H_ */
