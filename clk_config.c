/*
 * clk_config.c
 *
 *  Created on: 2017��4��23��
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
           DCOCTL  |= ( MOD4 + MOD3 + MOD2 + MOD1 + MOD0 );//΢��DCOCLK
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
* ������    :  MClkSet
* ��������  :  ��ʱ��MCLK��������
* �����β�  :  ������β�ΪDiv����ʱ��ԴDCOCLK����Div��Ƶ
* ��������ֵ :  ��
********************************************************************/
void MClkSet(unsigned char Div)
{
    BCSCTL2 &= ~(SELM1+SELM0);         //select DCOCLK for MCLK
    switch(Div){                           //1��Ƶ
       case 0x01:{
           BCSCTL2 &=~(DIVM1 + DIVM0);
           break;
       }
       case 0x02:{                        //2��Ƶ
           BCSCTL2 &=~(DIVM1 + DIVM0);
           BCSCTL2 |=DIVM0;
           break;
       }
       case 0x04:{                        //4��Ƶ
           BCSCTL2 &=~(DIVM1 + DIVM0);
           BCSCTL2 |=DIVM1;
           break;
       }
       case 0x08:{                        //8��Ƶ
           BCSCTL2 |=(DIVM1 + DIVM0);
           break;
       }
       default :{                          //Ĭ�ϲ���Ƶ
           BCSCTL2 &=~(DIVM1 + DIVM0);
       }
    }
}
/********************************************************************
* ������    :  SMClkSet
* ��������  :  ��ʱ��MCLK��������
* �����β�  :  ������β�ΪDiv����ʱ��ԴDCOCLK����Div��Ƶ
* ��������ֵ :  ��
********************************************************************/
void SMClkSet(unsigned char Div)
{
    BCSCTL2 &= ~(SELM1+SELM0);             //select DCOCLK for SMCLK
    switch(Div){
       case 0x01:{                        //1��Ƶ
           BCSCTL2 &=~(DIVS_3);
           break;
       }
       case 0x02:{                        //2��Ƶ
           BCSCTL2 &=~(DIVS_3);
           BCSCTL2 |=(DIVS_1);
           break;
       }
       case 0x04:{                        //4��Ƶ
           BCSCTL2 &=~(DIVS_3);
           BCSCTL2 |=(DIVS_2);
           break;
       }
       case 0x08:{                        //8��Ƶ
           BCSCTL2 |=(DIVS_3);
           break;
       }
       default :{                          //Ĭ�ϲ���Ƶ
           BCSCTL2 &=~(DIVS_3);
       }
    }
}

/*******************************************************************
* ������    :  AClkSet
* ��������  :  ��ʱ��MCLK��������
* �����β�  :  ������β�ΪDiv����ʱ��ԴLFXT1CLK����Div��Ƶ
* ��������ֵ :  ��
********************************************************************/
void AClkSet(unsigned char Div)
{
    BCSCTL1 &=~(XTS);                      //low-frequency mode
    switch(Div){
       case 0x01:{                        //1��Ƶ
           BCSCTL1 &=~(DIVA_3);
           break;
       }
       case 0x02:{                        //2��Ƶ
           BCSCTL1 &=~(DIVA_3);
           BCSCTL1 |=(DIVA_1);
           break;
       }
       case 0x04:{                        //4��Ƶ
           BCSCTL1 &=~(DIVA_3);
           BCSCTL1 |=(DIVA_2);
           break;
       }
       case 0x08:{                        //8��Ƶ
           BCSCTL1 |=(DIVA_3);
           break;
       }
       default :{                          //Ĭ�ϲ���Ƶ
           BCSCTL1 &=~(DIVA_3);
       }
    }
    BCSCTL3 |= XT2S0 + LFXT1S0 + XCAP_3;   //����ACLKƥ�����
   // BCSCTL3 = XT2S_0 + LFXT1S_2 + XCAP_1;
}
/*******************************************************************
* ����  :   Init_Clk()
* ����  :   MSP430ʱ��ϵͳ��ʼ������
* ����  :   ��
* ����ֵ :   ��
********************************************************************/
void Init_Clk()                //ʱ��ϵͳ����
{
    DcoClkSet(13,3);             //7.84MHz     2553datasheet ��28ҳ
    //AClkSet(0x08);              //8��ƵLFXT1CLK
    BCSCTL3 = XT2S_0 + LFXT1S_2 + XCAP_1;
    SMClkSet(0x04);             //4��ƵDCOCLK
    MClkSet(0x01);              //1��ƵDCOCLK
}


