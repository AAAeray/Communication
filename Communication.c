/*
 * Communication.c
 *
 *  Created on: 2017��4��23��
 *      Author: Array
 */
#include"Communication.h"

void SendOneChar(unsigned char msg)
{
	send_flag = 1;
	send_char = msg;
}

void SendChars(unsigned char* msg,unsigned short length)
{

}
