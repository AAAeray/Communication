/*
 * clk_config.c
 *
 *  Created on: 2017年4月23日
 *      Author: Array
 */
#include"clk_config.h"
void DcoClkSet(unsigned char x,unsigned char y)  // msp430g2553datasheet P30
{
    DCOCTL &=~( 0xFF);
    BCSCTL1 &=~( 0xFF);
    unsigned char temp=(x<<4)+y;
    switch(temp){
       case 0x00: {
           DCOCTL  &=~( DCO0 + DCO1 + DCO2);
           BCSCTL1 &=~( RSEL0 + RSEL1 + RSEL2 + RSEL3);
           break;
       }
       case 0x03: {
           DCOCTL  |= ( DCO0 + DCO1 );
           BCSCTL1 &=~( RSEL0 + RSEL1 + RSEL2 + RSEL3);
           break;
       }
       case 0x13: {
           DCOCTL  |= ( DCO0 + DCO1 );
           BCSCTL1 |= ( RSEL0 );
           break;
       }
       case 0x23: {
           DCOCTL  |= ( DCO0 + DCO1 );
           BCSCTL1 |= ( RSEL1 );
           break;
       }
       case 0x33: {
           DCOCTL  |=  ( DCO0 + DCO1  );
           BCSCTL1 |= ( RSEL0 + RSEL1 );
           break;
       }
       case 0x43: {
           DCOCTL  |= ( DCO0 + DCO1  );
           BCSCTL1 |= ( RSEL2);
           break;
       }
       case 0x53: {
           DCOCTL  |= ( DCO0 + DCO1  );
           BCSCTL1 |= ( RSEL0 + RSEL2 );
           break;
       }
       case 0x63: {
           DCOCTL  |= ( DCO0 + DCO1  );
           BCSCTL1 |= ( RSEL1 + RSEL2 );
           break;
       }
       case 0x73: {
           DCOCTL  |= ( DCO0 + DCO1  );
           BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 );
           break;
       }
       case 0x83: {
           DCOCTL  |= ( DCO0 + DCO1  );
           BCSCTL1 |= ( RSEL3);
           break;
       }
       case 0x93: {
           DCOCTL  |= ( DCO0 + DCO1  );
           BCSCTL1 |= ( RSEL0+ RSEL3);
           break;
       }
       case 0xA3: {
           DCOCTL  |= ( DCO0 + DCO1  );
           BCSCTL1 |= ( RSEL1 + RSEL3);
           break;
       }
       case 0xB3: {
           DCOCTL  |= ( DCO0 + DCO1 );
           BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL3);
           break;
       }
       case 0xC3: {
           DCOCTL  |= ( DCO0 + DCO1 );
           BCSCTL1 |= ( RSEL2 + RSEL3);
           break;
       }
       case 0xD3: {
           DCOCTL  |= ( DCO0 + DCO1 );
           DCOCTL  |= ( MOD4 + MOD3 + MOD2 + MOD1 + MOD0 );//微调DCOCLK
           BCSCTL1 |= ( RSEL0 + RSEL2 + RSEL3);
           break;
       }
       case 0xE3: {
           DCOCTL  |= ( DCO0 + DCO1  );
           BCSCTL1 |= ( RSEL1 + RSEL2 + RSEL3);
           break;
       }
       case 0xF3: {
           DCOCTL  |= ( DCO0 + DCO1  );
           BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 + RSEL3);
           break;
       }
       case 0xF7: {
           DCOCTL  |= ( DCO0 + DCO1 + DCO2 );
           BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 + RSEL3);
           break;
       }
       default:   {
           DCOCTL  |= ( DCO0 + DCO1 + DCO2 );
           BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 + RSEL3);
       }
    }
}
/********************************************************************
* 函数名    :  MClkSet
* 函数功能  :  对时钟MCLK进行配置
* 函数形参  :  传入的形参为Div，对时钟源DCOCLK进行Div分频
* 函数返回值 :  无
********************************************************************/
void MClkSet(unsigned char Div)
{
    BCSCTL2 &= ~(SELM1+SELM0);         //select DCOCLK for MCLK
    switch(Div){                           //1分频
       case 0x01:{
           BCSCTL2 &=~(DIVM1 + DIVM0);
           break;
       }
       case 0x02:{                        //2分频
           BCSCTL2 &=~(DIVM1 + DIVM0);
           BCSCTL2 |=DIVM0;
           break;
       }
       case 0x04:{                        //4分频
           BCSCTL2 &=~(DIVM1 + DIVM0);
           BCSCTL2 |=DIVM1;
           break;
       }
       case 0x08:{                        //8分频
           BCSCTL2 |=(DIVM1 + DIVM0);
           break;
       }
       default :{                          //默认不分频
           BCSCTL2 &=~(DIVM1 + DIVM0);
       }
    }
}
/********************************************************************
* 函数名    :  SMClkSet
* 函数功能  :  对时钟MCLK进行配置
* 函数形参  :  传入的形参为Div，对时钟源DCOCLK进行Div分频
* 函数返回值 :  无
********************************************************************/
void SMClkSet(unsigned char Div)
{
    BCSCTL2 &= ~(SELM1+SELM0);             //select DCOCLK for SMCLK
    switch(Div){
       case 0x01:{                        //1分频
           BCSCTL2 &=~(DIVS_3);
           break;
       }
       case 0x02:{                        //2分频
           BCSCTL2 &=~(DIVS_3);
           BCSCTL2 |=(DIVS_1);
           break;
       }
       case 0x04:{                        //4分频
           BCSCTL2 &=~(DIVS_3);
           BCSCTL2 |=(DIVS_2);
           break;
       }
       case 0x08:{                        //8分频
           BCSCTL2 |=(DIVS_3);
           break;
       }
       default :{                          //默认不分频
           BCSCTL2 &=~(DIVS_3);
       }
    }
}

/*******************************************************************
* 函数名    :  AClkSet
* 函数功能  :  对时钟MCLK进行配置
* 函数形参  :  传入的形参为Div，对时钟源LFXT1CLK进行Div分频
* 函数返回值 :  无
********************************************************************/
void AClkSet(unsigned char Div)
{
    BCSCTL1 &=~(XTS);                      //low-frequency mode
    switch(Div){
       case 0x01:{                        //1分频
           BCSCTL1 &=~(DIVA_3);
           break;
       }
       case 0x02:{                        //2分频
           BCSCTL1 &=~(DIVA_3);
           BCSCTL1 |=(DIVA_1);
           break;
       }
       case 0x04:{                        //4分频
           BCSCTL1 &=~(DIVA_3);
           BCSCTL1 |=(DIVA_2);
           break;
       }
       case 0x08:{                        //8分频
           BCSCTL1 |=(DIVA_3);
           break;
       }
       default :{                          //默认不分频
           BCSCTL1 &=~(DIVA_3);
       }
    }
    BCSCTL3 |= XT2S0 + LFXT1S0 + XCAP_3;   //配置ACLK匹配电容
   // BCSCTL3 = XT2S_0 + LFXT1S_2 + XCAP_1;
}
/*******************************************************************
* 名称  :   Init_Clk()
* 功能  :   MSP430时钟系统初始化程序
* 输入  :   无
* 返回值 :   无
********************************************************************/
void Init_Clk()                //时钟系统设置
{
    DcoClkSet(13,3);             //7.84MHz     2553datasheet 第28页
    //AClkSet(0x08);              //8分频LFXT1CLK
    BCSCTL3 = XT2S_0 + LFXT1S_2 + XCAP_1;
    SMClkSet(0x04);             //4分频DCOCLK
    MClkSet(0x01);              //1分频DCOCLK
}


