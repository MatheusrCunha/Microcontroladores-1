#include <msp430.h>

/* Tipos uint16_t, uint8_t, ... */
#include <stdint.h>
#include "motor.h"
/**
 * @brief  Configura temporizador A.
 *
 * @param  none
 *
 * @retval none
 */
void motor_init(){


    /* Estamos usando TA0CCR0 para contagem m�xima
        * que permite controle preciso sobre o per�odo
        * � poss�vel usar o overflow */

       /* Configura��o dos comparadores como PWM:
        * TA0CCR0: Timer0_A Capture/Compare 0: per�odo do PWM
        * OUTMOD_7: PWM output mode: 7 - PWM reset/set - CCR1 reset/set
        * TA0CCR1 PWM duty cycle: TA0CCR1 / TA0CCR0 */

    TA0CCR0 = 1000; //1000us -1kHz //RESOLU��O PARA REGULAR A LARGURA

    TA0CCTL1 = OUTMOD_7;
    TA0CCTL2 = OUTMOD_7;

    //Duas sa�das PWM -> largura do pulso
    TA0CCR1 = 0;
    TA0CCR2 = 0;
       /*      .
       *      /|\                  +  Comparador 0: TA0CCR0 (m�ximo da contagem) -> per�odo do PWM
       *       |                 + |
       *       |               +   |
       *       |------------- +  <--  Comparador 1: TA0CCR1 raz�o c�clica
       *       |           +  |    |
       *       |         +    |    |
       *       |       +      |    |
       *       |     +        |    |      +
       *       |   +          |    |    +
       *       | +            |    |  +
       * Timer +--------------|----|+----------->
       *       |              |    |
       *       |
       *
       *       |--------------+    |---------
       * Sa�da |              |    |
       *       +---------------+++++------------->
       */

       /* TASSEL_2 ->  Timer A clock source select: 2 - SMCLK
        * MC_1     ->  Timer A mode control: 1 - Up to CCR0
        *
        * Configura��o da fonte do clock do timer 1 */
    TA0CTL = TASSEL_2 | MC_1| ID_3;  //1mhz

    MOTORPONTEH_VELOCIDADE_DIR = ( MOTORPONTEH_PWM1N | MOTORPONTEH_PWM2N);
    MOTORPONTEH_DIRECAO_DIR |= ( MOTORPONTEH_PWM1 | MOTORPONTEH_PWM2);

}

void define_velocidade_pwm(uint16_t velocidadepwm)
{

    TA0CCR1 = velocidadepwm;

    TA0CCR2 = velocidadepwm;


}
void direcao_motor(uint8_t direcao)
{

    switch(direcao)
    {
        case parado:

            MOTORPONTEH_VELOCIDADE_SEL &= ~(MOTORPONTEH_PWM1N | MOTORPONTEH_PWM2N);
            MOTORPONTEH_VELOCIDADE_OUT &= ~(MOTORPONTEH_PWM1N | MOTORPONTEH_PWM2N);

            //Desligar os sentidos de direcao
            MOTORPONTEH_DIRECAO_OUT = 0;

            break;

        case frente:
            MOTORPONTEH_VELOCIDADE_SEL |= (MOTORPONTEH_PWM1N | MOTORPONTEH_PWM2N);

           //Os dois eixos do motor tem q girar no mesmo sentido, ou gira todox mundo pra direita ou pra esquerda
            MOTORPONTEH_DIRECAO_OUT |= (MOTORPONTEH_PWM1 | MOTORPONTEH_PWM2);

            break;
        case re:
           //Os dois PWMS tem que ligar
           MOTORPONTEH_VELOCIDADE_SEL |= (MOTORPONTEH_PWM1N | MOTORPONTEH_PWM2N);

                    //Os dois eixos do motor tem q girar no mesmo sentido, ou gira todox mundo pra direita ou pra esquerda - Se pra frente � 1, pra tras esse povo � 0
           MOTORPONTEH_DIRECAO_OUT &= ~(MOTORPONTEH_PWM1 | MOTORPONTEH_PWM2);
           break;

       case esquerda:
                    //Os dois PWMS tem que ligar, nao tem problema pq s� um eixo vai funcionar dai ta de boas-
           MOTORPONTEH_VELOCIDADE_SEL |= (MOTORPONTEH_PWM1N | MOTORPONTEH_PWM2N);

                   //Vamos ligar s� o motor da esquerda e por o outro em 0v
           MOTORPONTEH_DIRECAO_OUT &= ~(MOTORPONTEH_PWM1);
           MOTORPONTEH_DIRECAO_OUT |= (MOTORPONTEH_PWM2);

           break;

       case direita:

           MOTORPONTEH_VELOCIDADE_SEL |= (MOTORPONTEH_PWM1N | MOTORPONTEH_PWM2N);

                    //Vamos ligar s� o motor da esquerda e por o outro em 0v
           MOTORPONTEH_DIRECAO_OUT |= (MOTORPONTEH_PWM1);
           MOTORPONTEH_DIRECAO_OUT &= ~(MOTORPONTEH_PWM2);

           break;

       default:

           break;

    }
}




