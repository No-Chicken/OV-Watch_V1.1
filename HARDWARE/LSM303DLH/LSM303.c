#include "LSM303.h"
#include <math.h>
#include "i2c_hal.h"

#define PI 3.1415926
#define Delayms(X) HAL_Delay(X)

#define LSM303_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
iic_bus_t LSM303_bus = 
{
	.IIC_SDA_PORT = GPIOA,
	.IIC_SCL_PORT = GPIOA,
	.IIC_SDA_PIN  = GPIO_PIN_11,
	.IIC_SCL_PIN  = GPIO_PIN_12,
};

/************************************************************************************************************************
NOTICE:	the LSM303 can not use mutiple read!

*************************************************************************************************************************/


/*************************************************************************************************************************
*function  	:	LSM303_ReadOneReg()
*paraments	: RegAddr
*return     :	data readed
*detail     :	
*************************************************************************************************************************/
unsigned char LSM303_ReadOneReg(unsigned char RegAddr)
{
	unsigned char dat;
	unsigned char SlaveAddr = (RegAddr>0x19)?LSM303_SlaveAddr_A:LSM303_SlaveAddr_M;
	dat = IIC_Read_One_Byte(&LSM303_bus, SlaveAddr,RegAddr);
	return dat;
}

/*************************************************************************************************************************
*function  	:	LSM303_ReadMultiReg()
*paraments	: RegAddr, Regnumber, Databuff
*return     :	multiple datas readed
*detail     :	can't use real continue read, we tested the LSM303 is not allowed, so we have to use multiple ReadOneReg
*************************************************************************************************************************/
void LSM303_ReadMultiReg(unsigned char RegAddr, unsigned char RegNum, unsigned char DataBuff[])
{
	unsigned char i;
	unsigned char SlaveAddr = (RegAddr>0x19)?LSM303_SlaveAddr_A:LSM303_SlaveAddr_M;
	//IIC_Read_Multi_Byte(SlaveAddr,RegAddr,RegNum,DataBuff);
	for(i=0;i<RegNum;i++)
	{
		DataBuff[i] = IIC_Read_One_Byte(&LSM303_bus, SlaveAddr,RegAddr+i);
	}
}

/*************************************************************************************************************************
*function  	:	LSM303_Temp_ReadOneReg()
*paraments	: RegAddr
*return     : data readed
*detail     :	it's for temperature data read
*************************************************************************************************************************/
unsigned char LSM303_Temp_ReadOneReg(unsigned char RegAddr)
{
	unsigned char dat;
	dat = IIC_Read_One_Byte(&LSM303_bus, LSM303_SlaveAddr_M,RegAddr);
	return dat;
}

/*************************************************************************************************************************
*function  	:	LSM303_WriteOneReg()
*paraments	: RegAddr, data
*return     : None
*detail     :	
*************************************************************************************************************************/
void LSM303_WriteOneReg(unsigned char RegAddr, unsigned char dat)
{
	unsigned char SlaveAddr = (RegAddr>0x19)?LSM303_SlaveAddr_A:LSM303_SlaveAddr_M;
	IIC_Write_One_Byte(&LSM303_bus, SlaveAddr,RegAddr,dat);
}

/*************************************************************************************************************************
*function  	:	LSM303DLH_Init()
*paraments	: None
*return     : succeed or not
*detail     :	the defalt CTRL_REG4 value is 0x00. FS[5:4], 00: ??2 g, 01: ??4 g, 10: ??8 g, 11: ??16 g
*************************************************************************************************************************/
unsigned char LSM303DLH_Init()
{
	unsigned char temp;
	unsigned char retry = 0;
	
	LSM303_CLK_ENABLE;
	I2CInit(&LSM303_bus);
	
	for(retry = 0;retry < 3;retry ++)
	{
		LSM303_WriteOneReg(LSM303_CTRL_REG4_A, 0x10);		//full scale: +-4g
		Delayms(1);
		LSM303_WriteOneReg(LSM303_CTRL_REG1_A, 0x27);		//???????????????10Hz??????
		Delayms(1);															
		temp = LSM303_ReadOneReg(LSM303_CTRL_REG1_A);		//??????0x20????????????????????????0x07
		if(temp != 0x27)	
		{
			Delayms(10);	
		}
		else break;
	}
	if(temp != 0x27)
	{
		return 1;
	}
	Delayms(1);									
	for(retry = 0;retry < 3;retry ++)
	{
		LSM303_WriteOneReg(LSM303_CRA_REG_M, 0x90);		//???????????????15Hz,????????????;???????????????
		Delayms(1);		
		LSM303_WriteOneReg(LSM303_CRB_REG_M, 0x80);		//???????????????gain?????????0x80: +-4.0Gauss, 450LBS/Gauss for XY, 400LBS/Gauss for Z
		Delayms(1);	
		LSM303_WriteOneReg(LSM303_MR_REG_M, 0x00);		//?????????????????????????????????
		Delayms(1);										
		temp = LSM303_ReadOneReg(LSM303_MR_REG_M);		
		if(temp != 0)	
		{
			Delayms(10);	
		}
		else break;
	}
	if(temp != 0)	
	{
		return 1;	
	}
	return 0;
}

/*************************************************************************************************************************
*function  	:	LSM303_ReadAcceleration()
*paraments	: int16_t *Xa, int16_t *Ya, int16_t *Z
*return     : None
*detail     :	to read the Acceleration data, but the real Acceleration should be divided by the unit(n LSB/A) 
*************************************************************************************************************************/
void LSM303_ReadAcceleration(int16_t *Xa, int16_t *Ya, int16_t *Za)
{
	uint8_t buff[6];
	int16_t temp;
	LSM303_ReadMultiReg(LSM303_OUT_X_L_A,6,buff);
	
	temp = buff[1];
	temp <<= 8;
	temp |= buff[0];
	*Xa = temp;
	
	temp = buff[3];
	temp <<= 8;
	temp |= buff[2];
	*Ya = temp;
	
	temp = buff[5];
	temp <<= 8;
	temp |= buff[4];
	*Za = temp;
}

/*************************************************************************************************************************
*function  	:	LSM303_ReadMagnetic()
*paraments	: int16_t *Xm, int16_t *Ym, int16_t *Zm
*return     : None
*detail     :	to read the Magnetic data, but the real Magnetic should be divided by the unit(n LSB/M) 
*************************************************************************************************************************/
void LSM303_ReadMagnetic(int16_t *Xm, int16_t *Ym, int16_t *Zm)
{
	uint8_t buff[6];
	int16_t temp;
	LSM303_ReadMultiReg(LSM303_OUT_X_H_M,6, buff);
	
	temp = buff[0];
	temp <<= 8;
	temp |= buff[1];
	*Xm = temp;
	
	temp = buff[2];
	temp <<= 8;
	temp |= buff[3];
	*Zm = temp;
	
	temp = buff[4];
	temp <<= 8;
	temp |= buff[5];
	*Ym = temp;
}

/*************************************************************************************************************************
*function  	:	LSM303_ReadTemperature()
*paraments	: int16_t *Temp
*return     : None
*detail     :	to read the Temperature data, 
							the real Temperature already be divided by 8(8 LSB/deg)(not guaranteed, as the datasheet said) 
*************************************************************************************************************************/
void LSM303_ReadTemperature(int16_t *Temp)
{
	uint8_t buff[2];
	int16_t temp;
	IIC_Read_Multi_Byte(&LSM303_bus, LSM303_SlaveAddr_M, TEMP_OUT_H_M, 2, buff);
	temp = buff[0];
	temp <<= 8;
	temp |= buff[1];
	temp >>= 4;
	*Temp = temp / 3 + 0.5;//8 LSB/deg
}

/*************************************************************************************************************************
*function  	:	LSM303DLH_CalculationZAxisAngle()
*paraments	: int16_t Xa, int16_t Ya, int16_t Za
*return     : ZAxisAngle
*detail     :	
*************************************************************************************************************************/
int LSM303DLH_CalculationZAxisAngle(int16_t Xa, int16_t Ya, int16_t Za)
{
	double A;
	float fx,fy,fz;
	
	A = sqrt((int)Xa*Xa + (int)Ya*Ya + (int)Za*Za);	//????????????????????????????????? |A|=?????????(X*X+Y*Y+Z*Z)
	fx = Xa/A;
	fy = Ya/A;
	fz = Za/A;
	
	
	//Z??????
	A = fx*fx+fy*fy;
	A = sqrt(A);
	A = (double)A/fz;
	A = atan(A); 
	A = A*180/PI;
	if(A < 0)
	{
		A += 90;
		A = 0-A;
	}
	else
	{
		A = 90-A;
	}
	return A*100;
}
 
 
/*************************************************************************************************************************
*function  	:	LSM303DLH_CalculationZAxisAngle()
*paraments	: int16_t Xa, int16_t Ya, int16_t Za
*return     : XAxisAngle
*detail     :	
*************************************************************************************************************************/
int LSM303DLH_CalculationXAxisAngle(int16_t Xa, int16_t Ya, int16_t Za)
{
	double A;
	float fx,fy,fz;
	
	A = sqrt((int)Xa*Xa + (int)Ya*Ya + (int)Za*Za);	//????????????????????????????????? |A|=?????????(X*X+Y*Y+Z*Z)
	fx = Xa/A;
	fy = Ya/A;
	fz = Za/A;
	
	
	//X??????
	A = fz*fz+fy*fy;
	A = sqrt(A);
	
	A = (double)A/fx;
	A = atan(A); 
	A = A*180/PI;
	if(A < 0)
	{
		A += 90; //????????????
	}
	else
	{
		A = 90-A;
		A = 0-A; //????????????
	}
	return A*100;
}

/*************************************************************************************************************************
*function  	:	Azimuth_Calculate()
*paraments	: int16_t Xa, int16_t Ya, int16_t Za, int16_t Xm, int16_t Ym, int16_t Zm
*return     : Azimuth
*detail     :	to Calculate the Azimuth to find the direction
*************************************************************************************************************************/
float Azimuth_Calculate(int16_t Xa, int16_t Ya, int16_t Za, int16_t Xm, int16_t Ym, int16_t Zm)
{
	float pitch, roll, Hy, Hx, Azimuth; 
	pitch   = atan2f(Xa, sqrtf(Ya * Ya + Za * Za));
	roll    = atan2f(Ya, sqrtf(Xa * Xa + Za * Za));
	Hy      = Ym * cosf(roll) + Xm * sinf(roll) * sinf(pitch) - Zm * cosf(pitch) * sinf(roll);	//?????????
	Hx      = Xm * cosf(pitch) + Zm * sinf(pitch);																					//?????????
	Azimuth = atan2f(Ym,Xm)*180/PI;
	return Azimuth;
}
