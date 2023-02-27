#include "i2c_hal.h"

#define DELAY_TIME	20

/**
  * @brief SDA线输入模式配置
  * @param None
  * @retval None
  */
void SDA_Input_Mode(iic_bus_t *bus)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.Pin = bus->IIC_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(bus->IIC_SDA_PORT, &GPIO_InitStructure);
}

/**
  * @brief SDA线输出模式配置
  * @param None
  * @retval None
  */
void SDA_Output_Mode(iic_bus_t *bus)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.Pin = bus->IIC_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(bus->IIC_SDA_PORT, &GPIO_InitStructure);
}

/**
  * @brief SDA线输出一个位
  * @param val 输出的数据
  * @retval None
  */
void SDA_Output(iic_bus_t *bus, uint16_t val)
{
    if ( val )
    {
        bus->IIC_SDA_PORT->BSRR |= bus->IIC_SDA_PIN;
    }
    else
    {
        bus->IIC_SDA_PORT->BSRR = (uint32_t)bus->IIC_SDA_PIN << 16U;
    }
}

/**
  * @brief SCL线输出一个位
  * @param val 输出的数据
  * @retval None
  */
void SCL_Output(iic_bus_t *bus, uint16_t val)
{
    if ( val )
    {
        bus->IIC_SCL_PORT->BSRR |= bus->IIC_SCL_PIN;
    }
    else
    {
         bus->IIC_SCL_PORT->BSRR = (uint32_t)bus->IIC_SCL_PIN << 16U;
    }
}

/**
  * @brief SDA输入一位
  * @param None
  * @retval GPIO读入一位
  */
uint8_t SDA_Input(iic_bus_t *bus)
{
	if(HAL_GPIO_ReadPin(bus->IIC_SDA_PORT, bus->IIC_SDA_PIN) == GPIO_PIN_SET){
		return 1;
	}else{
		return 0;
	}
}


/**
  * @brief I2C的短暂延时
  * @param None
  * @retval None
  */
static void delay1(unsigned int n)
{
    uint32_t i;
    for ( i = 0; i < n; ++i);
}

/**
  * @brief I2C起始信号
  * @param None
  * @retval None
  */
void I2CStart(iic_bus_t *bus)
{
    SDA_Output(bus,1);
    delay1(DELAY_TIME);
    SCL_Output(bus,1);
    delay1(DELAY_TIME);
    SDA_Output(bus,0);
    delay1(DELAY_TIME);
    SCL_Output(bus,0);
    delay1(DELAY_TIME);
}

/**
  * @brief I2C结束信号
  * @param None
  * @retval None
  */
void I2CStop(iic_bus_t *bus)
{
    SCL_Output(bus,0);
    delay1(DELAY_TIME);
    SDA_Output(bus,0);
    delay1(DELAY_TIME);
    SCL_Output(bus,1);
    delay1(DELAY_TIME);
    SDA_Output(bus,1);
    delay1(DELAY_TIME);

}

/**
  * @brief I2C等待确认信号
  * @param None
  * @retval None
  */
unsigned char I2CWaitAck(iic_bus_t *bus)
{
    unsigned short cErrTime = 5;
    SDA_Input_Mode(bus);
    SCL_Output(bus,1);
    while(SDA_Input(bus))
    {
        cErrTime--;
        delay1(DELAY_TIME);
        if (0 == cErrTime)
        {
            SDA_Output_Mode(bus);
            I2CStop(bus);
            return ERROR;
        }
    }
    SDA_Output_Mode(bus);
    SCL_Output(bus,0);
    delay1(DELAY_TIME);
    return SUCCESS;
}

/**
  * @brief I2C发送确认信号
  * @param None
  * @retval None
  */
void I2CSendAck(iic_bus_t *bus)
{
    SDA_Output(bus,0);
    delay1(DELAY_TIME);
    delay1(DELAY_TIME);
    SCL_Output(bus,1);
    delay1(DELAY_TIME);
    SCL_Output(bus,0);
    delay1(DELAY_TIME);
	
}

/**
  * @brief I2C发送非确认信号
  * @param None
  * @retval None
  */
void I2CSendNotAck(iic_bus_t *bus)
{
    SDA_Output(bus,1);
    delay1(DELAY_TIME);
    SCL_Output(bus,1);
    delay1(DELAY_TIME);
    SCL_Output(bus,0);
    delay1(DELAY_TIME);

}

/**
  * @brief I2C发送一个字节
  * @param cSendByte 需要发送的字节
  * @retval None
  */
void I2CSendByte(iic_bus_t *bus,unsigned char cSendByte)
{
    unsigned char  i = 8;
    while (i--)
    {
        SCL_Output(bus,0);
        delay1(1);//1
        SDA_Output(bus, cSendByte & 0x80);
        delay1(DELAY_TIME);
        cSendByte += cSendByte;
        delay1(DELAY_TIME);
        SCL_Output(bus,1);
        delay1(DELAY_TIME);
    }
    SCL_Output(bus,0);
    //delay1(DELAY_TIME);//
}

/**
  * @brief I2C接收一个字节
  * @param None
  * @retval 接收到的字节
  */
unsigned char I2CReceiveByte(iic_bus_t *bus)
{
    unsigned char i = 8;
    unsigned char cR_Byte = 0;
    SDA_Input_Mode(bus);
    while (i--)
    {
        cR_Byte += cR_Byte;
        SCL_Output(bus,0);
        delay1(DELAY_TIME);
        SCL_Output(bus,1);
        delay1(DELAY_TIME);
        cR_Byte |=  SDA_Input(bus);
    }
    SCL_Output(bus,0);
    delay1(DELAY_TIME);
    SDA_Output_Mode(bus);
    return cR_Byte;
}

uint8_t IIC_Write_One_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t addr,uint8_t data)
{				   	  	    																 
  I2CStart(bus);  
	
	I2CSendByte(bus,daddr);	    
	if(I2CWaitAck(bus))	//等待应答
	{
		I2CStop(bus);		 
		return 1;		
	}
	I2CSendByte(bus,addr);
	I2CWaitAck(bus);	   	 										  		   
	I2CSendByte(bus,data);     						   
	I2CWaitAck(bus);  		    	   
  I2CStop(bus);
	delay1(DELAY_TIME);
	return 0;
}

uint8_t IIC_Write_Multi_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t addr,uint8_t length,uint8_t buff[])
{			
	unsigned char i;	
  I2CStart(bus);  
	
	I2CSendByte(bus,daddr);	    
	if(I2CWaitAck(bus))
	{
		I2CStop(bus);
		return 1;
	}
	I2CSendByte(bus,addr);
	I2CWaitAck(bus);	
	for(i=0;i<length;i++)
	{
		I2CSendByte(bus,buff[i]);     						   
		I2CWaitAck(bus); 
	}		    	   
  I2CStop(bus);
	delay1(DELAY_TIME);
	return 0;
} 

unsigned char IIC_Read_One_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t addr)
{
	unsigned char dat;
	I2CStart(bus);
	I2CSendByte(bus,daddr);
	I2CWaitAck(bus);
	I2CSendByte(bus,addr);
	I2CWaitAck(bus);
	
	I2CStart(bus);
	I2CSendByte(bus,daddr+1);
	I2CWaitAck(bus);
	dat = I2CReceiveByte(bus);
	I2CSendNotAck(bus);
	I2CStop(bus);
	return dat;
}

uint8_t IIC_Read_Multi_Byte(iic_bus_t *bus, uint8_t daddr, uint8_t addr, uint8_t length, uint8_t buff[])
{
	unsigned char i;
	I2CStart(bus);
	I2CSendByte(bus,daddr);
	if(I2CWaitAck(bus))
	{
		I2CStop(bus);		 
		return 1;		
	}
	I2CSendByte(bus,addr);
	I2CWaitAck(bus);
	
	I2CStart(bus);
	I2CSendByte(bus,daddr+1);
	I2CWaitAck(bus);
	for(i=0;i<length;i++)
	{
		buff[i] = I2CReceiveByte(bus);
		if(i<length-1)
		{I2CSendAck(bus);}
	}
	I2CSendNotAck(bus);
	I2CStop(bus);
	return 0;
}

//
void I2CInit(iic_bus_t *bus)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

		//bus->CLK_ENABLE();
		
    GPIO_InitStructure.Pin = bus->IIC_SDA_PIN ;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(bus->IIC_SDA_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.Pin = bus->IIC_SCL_PIN ;
    HAL_GPIO_Init(bus->IIC_SCL_PORT, &GPIO_InitStructure);
}
