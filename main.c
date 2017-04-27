#include <msp430.h> 
#include<msp430g2553.h>
#include<stdio.h>
#include"clk_config.h"
#include"Communication.h"
unsigned short i = 0;
/*
 * main.c
 */
void DelayMs(unsigned short ms)
{
	unsigned short t = 7912,i = 0;
	for(i = 0;i<ms;i++)
	{
		t = 7912;
		while(t--)
			asm("nop");
	}
}
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  Init_Clk();
  send_flag = 0;
  into_ask_num = 0;
  bit_count = 0;
  send_char = 0xd7;
  sent_num = 1;
  //char_num = 0;
  P1DIR |= 0x01;                            // P1.0 output
  P1OUT |= BIT0;
  P1DIR |=BIT4;
  P1SEL |=BIT4;
  ///p1.3 按键中断配置
  P1DIR &=~BIT3;                             // P1.3 input
  P1OUT |=BIT3;                              //p1.3set
  P1DIR |= BIT6;                             //p1.6 output
  P1OUT &= ~BIT6;
  P1REN |= BIT3;                            // P1.4 pullup
  P1IE |= BIT3;                             // P1.4 interrupt enabled
  P1IES |= BIT3;                            // P1.4 Hi/lo edge
  P1IFG &= ~BIT3;                           // P1.4 IFG cleared
  ///时钟中断配置，0.5ms进一次中断
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 936;
  TACTL = TASSEL_2 + MC_1 + ID_0;                  // SMCLK, contmode
  __bis_SR_register( GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)//发送一个字节
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
	if(Status == COM_START)//产生一个下降沿，表示传输开始，延时两个周期之后开始发送
	{
		into_ask_num++;
		if(into_ask_num == 1)
			P1OUT &= ~BIT0;
		if(into_ask_num == 3)
			P1OUT |= BIT0;
		if(into_ask_num == 5)
		{
			into_ask_num = 0;
			Status = COM_SEND;
		}
	}

	if(Status == COM_WAIT)
	{
		bit_count = 0;
		sent_num = 0;
		P1OUT |= BIT0;
	}

	if(Status == COM_SEND)
	{
		if(bit_count==0)
			P1OUT &= ~BIT0;
		else if(bit_count==9)
			P1OUT |= BIT0;
		else
		{
			if((send_char>>(bit_count-1))&0x01)
				P1OUT |= BIT0;
			else
				P1OUT &= ~BIT0;
		}
		bit_count++;
		if(bit_count==10)
		{
			bit_count = 0;
			sent_num++;
			if(sent_num == total_num)
				Status = COM_END;
		}
	}

	if(Status == COM_END)
	{
		/*****发送结束帧*****/
		Status = COM_WAIT;
	}

	if(Status == COM_RECEIVE)
	{

	}
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else
#error Compiler not supported!
#endif
{
	if(P1IFG & BIT3)
	{
		DelayMs(40);
		P1OUT ^= BIT6;                            // P1.0 = toggle
	    if(Status == COM_WAIT)
	    {
	    	TAR = 0;
	    	Status = COM_START;
	    }
	    else
	    {
	    	Status = COM_WAIT;
	    }
	    P1IFG &= ~BIT3;                           // P1.3 IFG cleared
	}
	P1IFG = 0;
}
