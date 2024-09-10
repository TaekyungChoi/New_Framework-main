#include "HW.h"
#include "Hal.h"


void HAL_WDT_Resume(void)
{
    R_WDT_Restart();
}


void HAL_Delay(U32 us_time)  // us단위
{
    static U32 Time = 0;	
    Time = us_time;

    R_TAU0_Channel6_Start();

    while(Time > 0)
    {
        if(TMIF06 == 1)  // 1us Interval Timer
        {	
            HAL_WDT_Resume();
            TMIF06 = 0;
            Time--;
        }
    }

    R_TAU0_Channel6_Stop();
}


U8 HexToAscii_Nibble(U8 Data)
{
	if(Data <= 9)
	{
		return (Data + 0x30);
	}
	else
	{
		return (Data + 0x37);
	}
}


U8 HexToAscii_Byte(U8 HighLow, U8 Value)
{
	U8 Digit10;
	U8 Digit1;

	Digit1 = (Value & 0x0F) + 0x30;
	Digit10 = ((Value >> 4) & 0x0F) + 0x30;

	if(Digit1 >= 0x3A) Digit1 += 0x07;
	if(Digit10 >= 0x3A) Digit10 += 0x07;

	if(HighLow == 1) return( Digit10 );
	if(HighLow == 0) return( Digit1 );
	return(0);
}


U8 AsciiToHex_2Byte(U8 Upper, U8 Lower)
{
    if(Upper >= 'a') Upper = Upper - 0x27;
    else if (Upper >= 'A') Upper = Upper - 0x07;

	if (Lower >= 'a') Lower = Lower - 0x27;
	else if (Lower >= 'A') Lower = Lower - 0x07;

	return ( ((Upper-0x30)<<4) | (Lower-0x30) );
}


U8 AsciiToHex_Byte(U8 AsciiData)
{
	U8 hex;

    if(AsciiData >= '0' && AsciiData <= '9')
    {
        hex = AsciiData - 0x30;
    }
    else if(AsciiData >= 'A' && AsciiData <= 'Z')
    {
        hex = AsciiData - 0x37;
    }
    else 
    {
        hex = AsciiData - 0x57;
    }

    return hex;
}

U8 CalDataChecksum(U8 *ptr, U16 Len)
{
	U16 i = 0;
	U32 Buff = 0;

	for(i=0; i<Len; i++)
	{
		Buff  += ptr[i];
	}

	return (U8)(Buff & 0x000000FF);
}