/*
 * Communication.h
 *
 *  Created on: 2017年4月23日
 *      Author: Array
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include<msp430g2553.h>
#define COM_WAIT      0
#define COM_SEND      1
#define COM_RECEIVE   2
#define COM_START     4
#define COM_END       5
unsigned char send_flag;
unsigned char bit_count;//待发送字节第几位
unsigned char send_char;//当前待发送字
unsigned char char_num;
unsigned char Status;
unsigned char into_ask_num;//进入开始状态次数，用于产生开始信号
unsigned char receive_char;//当前接收字节
unsigned char sent_num;//已发送的字节数
unsigned char total_num;//需要发送总字节数



void SendOneChar(unsigned char msg);
void SendChars(unsigned char* msg,unsigned short length);

#endif /* COMMUNICATION_H_ */
