#include "includes.h"
#include "NorFlash.h"

#define FNT_BASIC_ADDR                    0X00020000
/*********************************************************************/
void Font_Read_16x16_CN( uint8_t  *pString, uint8_t  *pdat )
{
    uint16_t MSB;
	uint16_t LSB;
	uint32_t addr = 0X000000 + FNT_BASIC_ADDR;

	MSB = pString[0];
	LSB = pString[1];

	if(MSB >= 0xA4 && MSB <= 0XA8 && LSB >= 0XA1)
	{
        addr += 0;
	}
	else if(MSB >= 0XA1 && MSB <= 0XA9 && LSB >= 0XA1)
	{
        addr += ((MSB - 0XA1) * 94 + (LSB - 0XA1)) << 5;
	}
	else if(MSB >= 0XB0 && MSB <= 0XF7 && LSB >= 0XA1)
	{
        addr += ((MSB - 0XB0) * 94 + (LSB - 0XA1) + 846) << 5;
	}

	SpiFlash_ReadBytes( addr, pdat , 32);
}

void Font_Read_12x12_CN( uint8_t  *pString, uint8_t  *pdat )
{
    uint16_t MSB;
	uint16_t LSB;
	uint32_t addr = 0X03CF80 + FNT_BASIC_ADDR;

	MSB = pString[0];
	LSB = pString[1];

	if(MSB >= 0xA1 && MSB <= 0XA3 && LSB >= 0XA1)
	{
        addr = ( (MSB - 0XA1) * 94 + (LSB - 0XA1)) * 24 + addr;
	}
	else if(MSB == 0XA9 && LSB >= 0XA1)
	{
        addr = (282 + (LSB - 0XA1)) * 24 + addr;
	}
	else if(MSB >= 0XB0 && MSB <= 0XF7 && LSB >= 0XA1)
	{
        addr = ((MSB - 0XB0) * 94 + (LSB - 0XA1) + 376) * 24 + addr;
	}

	SpiFlash_ReadBytes( addr, pdat, 24 );
}


void Font_Read_8x16_ASCII( uint8_t  *pString, uint8_t  *pdat )
{
    uint16_t ASCIICode;
	uint32_t addr = 0x03B7C0 + FNT_BASIC_ADDR;

	ASCIICode = pString[0];
	if( ASCIICode >= 0x20 && ASCIICode <= 0x7E )
	{
        addr = addr + ((ASCIICode - 0x20) << 4);
	}

	SpiFlash_ReadBytes( addr, pdat, 16);
}

void Font_Read_6x12_ASCII( uint8_t  *pString, uint8_t  *pdat )
{
    uint16_t ASCIICode;
	uint32_t addr = 0x066d40 + FNT_BASIC_ADDR;

	ASCIICode = pString[0];

	if( ASCIICode >= 0x20 && ASCIICode <= 0x7E )
	{
        addr = addr + ((ASCIICode - 0x20) * 12);
	}

	SpiFlash_ReadBytes( addr, pdat, 12 );
}


void Font_Read_5x7_ASCII( uint8_t  *pString, uint8_t  *pdat )
{
    uint16_t ASCIICode;
	uint32_t addr = 0x03bfc0 + FNT_BASIC_ADDR;

	ASCIICode = pString[0];

	if( ASCIICode >= 0x20 && ASCIICode <= 0x7E )
	{
        addr = addr + ((ASCIICode - 0x20) << 3);
	}

	SpiFlash_ReadBytes( addr, pdat, 5 );
}

uint8_t Font_Read_6x9_Number( uint8_t  *pString, uint8_t  *pdat, uint8_t isGradient)
{
    uint16_t ASCIICode;
	uint32_t addr = 0X0730F0 + FNT_BASIC_ADDR;

	if(isGradient)
	{
		addr += 1080;
	}

	ASCIICode = pString[0];
	if( ASCIICode >= 0x30 && ASCIICode <= 0x39 )
	{
        addr = addr + ((ASCIICode -0x30) * 108);
		SpiFlash_ReadBytes(addr, pdat, 108);
	}
	else if(ASCIICode == '-')
	{
        addr = addr + 1080;
        SpiFlash_ReadBytes(addr, pdat, 108);
	}
	else
	{
		return 0;
	}

	return 1;
}

uint8_t Font_Read_12x17_Number( uint8_t  *pString, uint8_t  *pdat, uint08_t isGradient)
{
    uint16_t ASCIICode;
	uint32_t addr = 0x070000 + FNT_BASIC_ADDR;

    if(isGradient == 0)
	{
		addr += 5406;
	}

	ASCIICode = pString[0];
	if( ASCIICode >= 0x30 && ASCIICode <= 0x39 )
	{
        addr = addr + ((ASCIICode -0x30) * 408);
		SpiFlash_ReadBytes(addr, pdat, 408);
	}
	else if(ASCIICode == 'C')
	{
		addr = addr + 4080;
        SpiFlash_ReadBytes(addr, pdat, 408);
	}
    else if(ASCIICode == 'H')
	{
		addr = addr + 4488;
        SpiFlash_ReadBytes(addr, pdat, 408);
	}
	else if(ASCIICode == '-')
	{
        addr = addr + 4896;
        SpiFlash_ReadBytes(addr, pdat, 408);
	}
	else if(ASCIICode == '.')
	{
        addr = addr + 5304;
        SpiFlash_ReadBytes(addr, pdat, 102);
        return 2;
	}
	else
	{
		return 0;
	}

	return 1;
}