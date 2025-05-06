#include "includes.h"


#define I2C_SCK_H                                 GPIOF->BSRR = GPIO_Pin_1
#define I2C_SCK_L                                 GPIOF->BRR  = GPIO_Pin_1
	
#define I2C_SDA_IN                               GpioModeSwitch( GPIOB,GPIO_Pin_11,0)
#define I2C_SDA_OUT                              GpioModeSwitch( GPIOB,GPIO_Pin_11,1)
#define I2C_SDA_H                                GPIOB->BSRR = GPIO_Pin_11
#define I2C_SDA_L                                GPIOB->BRR  = GPIO_Pin_11
#define I2C_SDA_VAL                              (GPIOB->IDR & GPIO_Pin_11)

/******************************************************************************************/
void I2C_Start(void)
{
	I2C_SDA_H;
	DelayUs(10);
	I2C_SCK_H;
	DelayUs(10);
	I2C_SDA_L;
	DelayUs(10);
	I2C_SCK_L;
	DelayUs(10);
}

void I2C_Stop(void)
{
	I2C_SCK_L;
	DelayUs(10);
	I2C_SDA_L;
	DelayUs(10);
	I2C_SCK_H;
	DelayUs(10);
	I2C_SDA_H;
	DelayUs(10);
	I2C_SCK_L;
	I2C_SDA_L;
}

uint8_t I2C_Read(bool bFinal)
{
	uint8_t i, Data;

	I2C_SDA_IN;
    DelayUs(20);
	Data = 0;
	for (i = 0; i < 8; i++)
	{
		I2C_SCK_H;
		DelayUs(10);
		Data <<= 1;
		if (I2C_SDA_VAL)
		{
			Data |= 1U;
		}
		I2C_SCK_L;
		DelayUs(10);
	}

	I2C_SDA_OUT;
	DelayUs(20);
	if (bFinal)
	{
		I2C_SDA_H;
	}
	else
	{
		I2C_SDA_L;
	}
	DelayUs(10);
	I2C_SCK_H;
	DelayUs(10);
	I2C_SCK_L;
	DelayUs(10);

	return Data;
}

uint8_t I2C_Write(uint8_t Data)
{
	uint8_t i;
	uint8_t ret = 1;

	I2C_SCK_L;
	DelayUs(10);
	for (i = 0; i < 8; i++)
	{
		if ((Data & 0x80) == 0)
		{
			I2C_SDA_L;
		}
		else
		{
			I2C_SDA_H;
		}
		Data <<= 1;
		DelayUs(10);
		I2C_SCK_H;
		DelayUs(10);
		I2C_SCK_L;
		DelayUs(10);
	}
    I2C_SDA_L;
    DelayUs(10);
	I2C_SDA_IN;
	DelayUs(10);
	I2C_SCK_H;
	DelayUs(10);

	for (i = 0; i < 100; i++)
	{
		if (I2C_SDA_VAL == 0)
		{
			ret = 0;
			break;
		}
	}
	I2C_SCK_L;
	DelayUs(10);
	I2C_SDA_OUT;
	I2C_SDA_H;

	return ret;
}

uint8_t I2C_ReadBuffer(void *pBuffer, uint8_t Size)
{
	uint8_t *pData = (uint8_t*) pBuffer;
	uint8_t i;

	if (Size == 1)
	{
		*pData = I2C_Read(TRUE);
		return 1;
	}

	for (i = 0; i < Size - 1; i++)
	{
		DelayUs(10);
		pData[i] = I2C_Read(FALSE);
	}

	DelayUs(10);
	pData[i++] = I2C_Read(TRUE);

	return Size;
}

uint8_t I2C_WriteBuffer(const void *pBuffer, uint8_t Size)
{
	const uint8_t *pData = (const uint8_t*) pBuffer;
	uint8_t i;

	for (i = 0; i < Size; i++)
	{
		if (I2C_Write(*pData++) == 1)
		{
			return 1;
		}
	}

	return 0;
}

