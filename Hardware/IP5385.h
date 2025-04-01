/*!
 * @file IP5385.h
 * @author conandllu
 * @version V0.1
 * @note This file is IP5385 communication with software I2C
 **/

#ifndef __IP5385_H
#define __IP5385_H

#define IP5383_SCL_PIN      GPIO_Pin_2
#define IP5383_SCL_GROUP    GPIOA

#define IP5383_SDA_PIN      GPIO_Pin_1
#define IP5383_SDA_GROUP    GPIOA

#define IP5383_INT_PIN      GPIO_Pin_0
#define IP5383_INT_GROUP    GPIOD

#define IP5383_KEY_PIN      GPIO_Pin_0
#define IP5383_KEY_GROUP    GPIOA

#define    SWI2CSETSCL()            GPIO_SetBits(IP5383_SCL_GROUP, IP5383_SCL_PIN)
#define    SWI2CCLRSCL()            GPIO_ResetBits(IP5383_SCL_GROUP, IP5383_SCL_PIN)
#define    SWI2CCHECKSCL()          GPIO_ReadInputDataBit(IP5383_SCL_GROUP, IP5383_SCL_PIN)

#define    SWI2CSETSDA()            GPIO_SetBits(IP5383_SDA_GROUP, IP5383_SDA_PIN)
#define    SWI2CCLRSDA()            GPIO_ResetBits(IP5383_SDA_GROUP, IP5383_SDA_PIN)
#define    SWI2CCHECKSDA()          GPIO_ReadInputDataBit(IP5383_SDA_GROUP, IP5383_SDA_PIN)

#define    SWI2CDELAY()             Delay_Us(2)

#define    INTCHECK()               GPIO_ReadInputDataBit(IP5383_INT_GROUP, IP5383_INT_PIN)


#define IP5385_IIC_ADDR             0xEA
#define IP5385_SYS_CTL0             0x00
#define IP5385_DCP_DIG_CTL1_VBUS    0x01
#define IP5385_DCP_DIG_CTL2_VBUS    0x02
#define IP5385_DCP_DIG_CTL3_VIN     0x03
#define IP5385_DCP_DIG_CTL4_VOUT1   0x04
#define IP5385_DCP_DIG_CTL5_VOUT2   0x05
#define IP5385_SYS_CTL7             0x07
#define IP5385_SYS_CTL8             0x08
#define IP5385_SYS_CTL9             0x09
#define IP5385_SYS_CTL10            0x0A
#define IP5385_SYS_CTL12            0x0C
#define IP5385_SYS_CTL13            0x0D
#define IP5385_SYS_CTL14            0x0E
#define IP5385_CHG_NTC_TEMP         0x0F
#define IP5385_BST_NTC_TEMP         0x10
#define IP5385_TYPEC_CTL15          0x11
#define IP5385_SYS_CTL32            0x20
#define IP5385_SYS_CTL33            0x21
#define IP5385_SYS_CTL34            0x22

//Read only regesistor 
#define IP5385_SOC_CAP_DATA         0x40
#define IP5385_STATE_CTL0           0x41
#define IP5385_STATE_CTL1           0x42
#define IP5385_MOS_STATE            0x45
#define IP5385_KEY_STATE            0x46
#define IP5385_STATE_CTL3           0x47
#define IP5385_NTC_STATE            0x48
#define IP5385_BATVADC_DAT0         0x49
#define IP5385_BATVADC_DAT1         0x4A
#define IP5385_VSYSVADC_DAT0        0x4B
#define IP5385_VSYSVADC_DAT1        0x4C
#define IP5385_IVBUS_IN_IADC_DAT0   0x4D
#define IP5385_IVBUS_IN_IADC_DAT1   0x4E
#define IP5385_IVOUT1_IADC_DAT0     0x4F
#define IP5385_IVOUT1_IADC_DAT1     0x50
#define IP5385_IVOUT2_IADC_DAT0     0x51
#define IP5385_IVOUT2_IADC_DAT1     0x52
#define IP5385_IVBUS_OUT_IADC_DAT0  0x53
#define IP5385_IVBUS_OUT_IADC_DAT1  0x54
#define IP5385_IBAT_IADC_DAT0       0x55
#define IP5385_IBAT_IADC_DAT1       0x56
#define IP5385_IVSYS_IADC_DAT0      0x57
#define IP5385_IVSYS_IADC_DAT1      0x58
#define IP5385_VSYS_POW_DAT0        0x59
#define IP5385_VSYS_POW_DAT1        0x5A
#define IP5385_FCAP_DAT0            0x5B
#define IP5385_FCAP_DAT1            0x5C

#endif /* __IP5385_H */
