/*
 * uart_fr2355.h
 *
 *  Created on: 7 de out de 2020
 *      Author: Matheus Cunha
 */

#ifndef UART_FR2355_H_
#define UART_FR2355_H_


#include <stdint.h>

#define CLOCK_24MHz

void init_uart();
void uart_send_package(uint8_t *data, uint8_t size);
void uart_receive_package(uint8_t *data, uint8_t size);



#endif /* UART_FR2355_H_ */
