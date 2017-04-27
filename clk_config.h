/*
 * clk_config.h
 *
 *  Created on: 2017Äê4ÔÂ23ÈÕ
 *      Author: Array
 */

#ifndef CLK_CONFIG_H_
#define CLK_CONFIG_H_

#include<msp430g2553.h>

void DcoClkSet(unsigned char x,unsigned char y);
void MClkSet(unsigned char Div);
void SMClkSet(unsigned char Div);
void AClkSet(unsigned char Div);
void Init_Clk();

#endif /* CLK_CONFIG_H_ */
