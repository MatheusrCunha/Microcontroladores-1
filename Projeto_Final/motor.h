/*
 * bit.h
 *
 *  Created on: Sep 09, 2016
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 *
 *      Bit manipulation macros
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTORPONTEH_VELOCIDADE_DIR P1DIR
#define MOTORPONTEH_VELOCIDADE_OUT P1OUT
#define MOTORPONTEH_VELOCIDADE_SEL P1SEL
#define MOTORPONTEH_PWM1N BIT2
#define MOTORPONTEH_PWM2N BIT3

#define MOTORPONTEH_DIRECAO_DIR P3DIR
#define MOTORPONTEH_DIRECAO_OUT P3OUT
#define MOTORPONTEH_PWM1 BIT0
#define MOTORPONTEH_PWM2 BIT1


typedef enum{
    frente,
    re,
    esquerda,
    direita,
    parado
}direcoes_motor;


void motor_init();

void define_velocidade_pwm(uint16_t velocidadepwm);

void direcao_motor(uint8_t direcao);

#endif /* BITS_H_ */
