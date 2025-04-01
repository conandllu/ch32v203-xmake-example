/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

*/

#include "debug.h"
#include "tiny-macro-os.h"
/* Global typedef */

/* Global define */

/* Global Variable */
void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void SYSTICK_Init_Config(void)
{
    SysTick->SR = 0;
    SysTick->CNT = 0;
    SysTick->CMP = SystemCoreClock / 1000;
    SysTick->CTLR =0xF;

    NVIC_SetPriority(SysTicK_IRQn, 1);
    NVIC_EnableIRQ(SysTicK_IRQn);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    uint8_t data = 0;
    uint8_t int_state = 0;

    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("This is printf example\r\n");
    SYSTICK_Init_Config();
    //IP5385_init();
    //while((INTCHECK() == 0));
    //SWI2C_Send_One_Byte(0xEA,0x05);
    //data = SWI2C_Read_One_Byte(0xEA);
    //printf("IP5385 read data %X\r\n",data);
    tmos_test_main();
    while(1)
    {
        
    }
}

void SysTick_Handler(void)
{
    SysTick->SR = 0;
    OS_UPDATE_TIMERS();
}
