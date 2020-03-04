/*
 * bit_bit.h
 *
 *  Created on: 4 de mar de 2020
 *      Author: mcunha
 */

#ifndef BIT_BIT_H_
#define BIT_BIT_H_

#define set_bit(x,y)    (x |= y)
#define clr_bit(x,y)    (x &=~y)
#define cpl_bit(x,y)    (x ^= y)
#define tst_bit(x,y)    (x & y)



#endif /* BIT_BIT_H_ */
