/*!
 * @file IP5385.c
 * @author conandllu
 * @version V0.1
 * @note This file is IP5385 communication with software I2C
 **/

#include "IP5385.h"
#include "debug.h"

void IP5385_init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    
    GPIO_PinRemapConfig(GPIO_Remap_PD01,ENABLE); //Change PD0 to GPIO function
    
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = IP5383_SDA_PIN; // SDA
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(IP5383_SDA_GROUP, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = IP5383_SCL_PIN; // SCL
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(IP5383_SCL_GROUP, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = IP5383_INT_PIN; // INT
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(IP5383_INT_GROUP, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = IP5383_KEY_PIN; // KEY
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(IP5383_KEY_GROUP, &GPIO_InitStructure);
}

void __SWI2C_Start() {
    SWI2CSETSDA();
    SWI2CSETSCL();
    SWI2CDELAY();
    SWI2CCLRSDA();
    SWI2CDELAY();
    SWI2CCLRSCL();
    SWI2CDELAY();
}

void __SWI2C_Transmit(uint8_t data) {
    uint8_t bit_sel;
    bit_sel = 0x80;
    while (bit_sel) {
        if (bit_sel & data)
            SWI2CSETSDA();
        else
            SWI2CCLRSDA();
        SWI2CDELAY();
        SWI2CSETSCL();
        SWI2CDELAY();
        SWI2CCLRSCL();
        bit_sel >>= 1;
    }
    SWI2CDELAY();
}

uint8_t __SWI2C_Reveice() {
    uint8_t cnt = 0;
    uint8_t data = 0xFF;

    SWI2CCLRSCL();
    SWI2CDELAY();

    for(cnt = 0;cnt < 8;cnt++) {
        SWI2CSETSCL();
        SWI2CDELAY();
        data <<= 1;
        if(SWI2CCHECKSDA() == 0x01) {
            data = data + 0x01;
        }
        SWI2CCLRSCL();
        SWI2CDELAY();
    }
    return data;
}

uint8_t __SWI2C_Ack() {
    uint8_t ack = 0;

    SWI2CSETSDA();
    SWI2CSETSCL();
    SWI2CDELAY();

    ack = SWI2CCHECKSDA();

    SWI2CCLRSCL();

    return ack;
}

void __SWI2C_Stop() {
    SWI2CCLRSDA();
    SWI2CDELAY();
    SWI2CSETSCL();
    SWI2CDELAY();
    SWI2CSETSDA();
    SWI2CDELAY();
}

void SWI2C_Send_One_Byte(uint8_t address, uint8_t data){
    uint8_t ack = 0;

    __SWI2C_Start();
    __SWI2C_Transmit(address);
    ack = __SWI2C_Ack();
    Delay_Us(50);
    __SWI2C_Transmit(data);
    ack = __SWI2C_Ack();
    Delay_Us(50);
    //SWI2C_Stop();
}

uint8_t SWI2C_Read_One_Byte(uint8_t address) {
    uint8_t ack = 0;
    uint8_t data = 0x00;

    __SWI2C_Start();
    __SWI2C_Transmit(address + 1);
    ack = __SWI2C_Ack();
    Delay_Us(50);
    data = __SWI2C_Reveice();
    ack = __SWI2C_Ack();
    __SWI2C_Stop();
    return data;
}
