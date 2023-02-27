#ifndef __I2C_HAL_H
#define __I2C_HAL_H

#include "stm32f4xx_hal.h"

typedef struct
{
	GPIO_TypeDef * IIC_SDA_PORT;
	GPIO_TypeDef * IIC_SCL_PORT;
	uint16_t IIC_SDA_PIN;
	uint16_t IIC_SCL_PIN;
	
}iic_bus_t;

void I2CStart(iic_bus_t *bus);
void I2CStop(iic_bus_t *bus);
unsigned char I2CWaitAck(iic_bus_t *bus);
void I2CSendAck(iic_bus_t *bus);
void I2CSendNotAck(iic_bus_t *bus);
void I2CSendByte(iic_bus_t *bus, unsigned char cSendByte);
unsigned char I2CReceiveByte(iic_bus_t *bus);
void I2CInit(iic_bus_t *bus);

uint8_t IIC_Write_One_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Write_Multi_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t addr,uint8_t length,uint8_t buff[]);
unsigned char IIC_Read_One_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t addr);
uint8_t IIC_Read_Multi_Byte(iic_bus_t *bus, uint8_t daddr, uint8_t addr, uint8_t length, uint8_t buff[]);
#endif
