/*
 * Communication.h
 *
 *  Created on: 2017��4��23��
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
unsigned char bit_count;//�������ֽڵڼ�λ
unsigned char send_char;//��ǰ��������
unsigned char char_num;
unsigned char Status;
unsigned char into_ask_num;//���뿪ʼ״̬���������ڲ�����ʼ�ź�
unsigned char receive_char;//��ǰ�����ֽ�
unsigned char sent_num;//�ѷ��͵��ֽ���
unsigned char total_num;//��Ҫ�������ֽ���



void SendOneChar(unsigned char msg);
void SendChars(unsigned char* msg,unsigned short length);

#endif /* COMMUNICATION_H_ */
