#include "HW.h"
#include "Hal_GPIO.h"


static U8 HAL_PORT_Register_SET(U8 u8RegData, U8 u8Value);
static U8 HAL_PORT_Register_CLEAR(U8 u8RegData, U8 u8Value);


// Port Latch Register (0: Low Level , 1: High Level)
const uint16_t u16PnAddress[16]=
{
    0xFF00,     // P0
    0xFF01,     // P1 
    0xFF02,     // P2
    0xFF03,     // P3
    0xFF04,     // P4
    0xFF05,     // P5
    0xFF06,     // P6
    0xFF07,     // P7
    0xFF08,     // P8
    0xFF09,     // P9
    0xFF0A,     // P10
    0xFF0B,     // P11
    0xFF0C,     // P12
    0xFF0D,     // P13
    0xFF0E,     // P14
    0xFF0F      // P15
};


// Port Mode Regidter (0: Output Mode, 1:Input Mode)
const uint16_t u16PMnAddress[16]=
{
    0xFF20,  // PM0
    0xFF21,  // PM1  
    0xFF22,  // PM2
    0xFF23,  // PM3
    0xFF24,  // PM4
    0xFF25,  // PM5
    0xFF26,  // PM6
    0xFF27,  // PM7
    0xFF28,  // Unused
    0xFF29,  // Unused
    0xFF2A,  // PM10
    0xFF2B,  // PM11
    0xFF2C,  // PM12
    0xFF2D,  // Unused
    0xFF2E,  // PM14
    0xFF2F,  // PM15
};

// Pull-up resistor option registers (0: On-chip pull-up resistor not connected, 1:On-chip pull-up resistor connected)
const uint16_t u16PUnAddress[16]=
{
    0x0030,  // PU0
    0x0031,  // PU1  
    0x0032,  // PU2
    0x0033,  // PU3
    0x0034,  // PU4
    0x0035,  // PU5
    0x0036,  // PU6
    0x0037,  // PU7
    0x0038,  // PU8
    0x0039,  // PU9
    0x003A,  // PU10
    0x003B,  // PU11
    0x003C,  // PU12
    0x003D,  // Unused
    0x003E,  // PU14 
    0x003F,  // Unused
};

// Port output mode registers(0:Nomal output mode, 1:N-ch open-drain output)
const uint16_t u16POMnAddress[16]=
{
    0x0050,  // POM0
    0x0051,  // POM1  
    0x0052,  // Unused
    0x0053,  // Unused
    0x0054,  // POM4
    0x0055,  // POM5
    0x0056,  // Unused
    0x0057,  // POM7
    0x0058,  // POM8
    0x0059,  // POM9
    0x005A,  // Unused
    0x005B,  // Unused
    0x005C,  // Unused
    0x005D,  // Unused
    0x005E,  // POM14  
    0x005F   // Unused
};

// Port input mode registers(0:Normal input buffer, 1: TTL input buffer)
const uint16_t u16PIMnAddress[16]=
{
    0x0040, // PIM0
    0x0041, // PIM1
    0x0042, // Unused
    0x0043, // Unused
    0x0044, // PIM4
    0x0045, // PIM5
    0x0046, // Unused
    0x0047, // Unused
    0x0048, // PIM8
    0x0049, // Unused
    0x004A, // Unused
    0x004B, // Unused
    0x004C, // Unused
    0x004D, // Unused
    0x004E, // PIM14
    0x004F, // Unused    
};

// const uint8_t u8PMnInMaskData[16]=
// {
//     0x8C,  // PM0
//     0x5E,  // PM1  
//     0x1F,  // PM2
//     0xFE,  // PM3
//     0xC1,  // PM4
//     0xC0,  // PM5
//     0xA3,  // PM6
//     0x80,  // PM7
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFE,  // PM10
//     0xFC,  // PM11
//     0xE0,  // PM12
//     0xFF,  // Unused
//     0x38,  // PM14
//     0xF0,  // PM15
// };
// const uint8_t u8PMnOutMaskData[16]=
// {
//     0x8C,  // PM0
//     0x5E,  // PM1  
//     0x1F,  // PM2
//     0xFE,  // PM3
//     0xC1,  // PM4
//     0xC0,  // PM5
//     0xA3,  // PM6
//     0x80,  // PM7
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFE,  // PM10
//     0xFC,  // PM11
//     0xFE,  // PM12
//     0xFF,  // Unused
//     0x38,  // PM14
//     0xF0,  // PM15
// };

// const uint8_t u8PUnMaskData[16]=
// {
//     0x00,  // PU0
//     0x00,  // PU1  
//     0xFF,  // PU2
//     0x00,  // PU3
//     0xC0,  // PU4
//     0xC0,  // PU5
//     0x0F,  // PU6
//     0x00,  // PU7
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFE,  // PU10
//     0x00,  // PU11
//     0x1E,  // PU12
//     0xFF,  // Unused
//     0x20,  // PU14 
//     0xFF,  // Unused
// };

// const uint8_t u8POMnMaskData[16]=
// {
//     0xE2,  // POM0
//     0x40,  // POM1  
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xC7,  // POM4
//     0xC2,  // POM5
//     0xFF,  // Unused
//     0xED,  // POM7
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xE3,  // POM14  
//     0xFF   // Unused
// };

// const uint8_t u8PIMnMaskData[16]=
// {
//     0xE5,  // PIM0
//     0x04,  // PIM1  
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xE7,  // PIM4
//     0xC7,  // PIM5
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xFF,  // Unused
//     0xF3,  // PIM14  
//     0xFF   // Unused
// };


void HAL_PORT_Latch_SET(U8 u8PortNum, U8 u8Value, U8 P_HighLow)
{
    U8 *u8ptr = NULL;
    U8  i = 0;

    u8ptr = (volatile __near unsigned char *)u16PnAddress[u8PortNum];

    if(P_HighLow == SET)
    {
        *u8ptr = HAL_PORT_Register_SET(*u8ptr,u8Value);
    }
    else
    {
        *u8ptr = HAL_PORT_Register_CLEAR(*u8ptr,u8Value);
    }    
}

// Set Port to Input / Output Mode
void HAL_PORT_InOutMode_SET(U8 u8PortNum, U8 u8Value, U8 InOut)
{
    U8 *u8ptr = NULL;
    U8  i = 0;

    u8ptr = (volatile __near unsigned char *)u16PMnAddress[u8PortNum];

    if(InOut == IO_INPUT)
    {
        *u8ptr = HAL_PORT_Register_SET(*u8ptr,u8Value);
    }
    else if(InOut == IO_OUTPUT)
    {
        *u8ptr = HAL_PORT_Register_CLEAR(*u8ptr,u8Value);
    }

    // if(u8Value & u8PMnInMask[u8PortNum]) // If Set to Inhibited Bit 
    // {
    //         printf_f((const char* __far)"[Err]setPortIn:%d, 0x%02x\n\r", u8PortNum,u8Value);
    // }
    // else
    // {	
    //     u8ptr = (volatile __near unsigned char  *)u16PMn[u8PortNum];        
    //     *u8ptr = setRegister(*u8ptr,u8Value); 
    // }
}

// // Set Port to Output
// void HAL_PORT_OutputMode_SET(U8 u8PortNum, U8 u8Value)
// {
//     U8 *u8ptr;
//     U8  i = 0;

//     u8ptr=(volatile __near unsigned char *)u16PMn[u8PortNum]; 
//     *u8ptr = HAL_PORT_Register_CLEAR(*u8ptr,u8Value);

//     // if(u8Value & u8PMnOutMask[u8PortNum]) // If Set to Inhibited Bit 
//     // {
//     //         printf_f((const char* __far)"[Err]setPortOut:%d, 0x%02x\n\r", u8PortNum,u8Value);
//     // }
//     // else
//     // {	
//     //     u8ptr=(volatile __near unsigned char  *)u16PMn[u8PortNum]; 
// 	//     *u8ptr = clrRegister(*u8ptr,u8Value); 
//     // }
// } 


// Set Port to Pull Up
void HAL_PORT_PullUpMode_SET(U8 u8PortNum, U8 u8Value, U8 P_Set)
{
    U8 *u8ptr;
    U8  i = 0;

    if(P_Set == SET)
    {
        u8ptr=(volatile __near unsigned char *)u16PUnAddress[u8PortNum]; 
        *u8ptr = HAL_PORT_Register_SET(*u8ptr,u8Value);
    }
    else
    {
        u8ptr=(volatile __near unsigned char *)u16PUnAddress[u8PortNum]; 
        *u8ptr = HAL_PORT_Register_CLEAR(*u8ptr,u8Value);
    }

    // if(u8Value & u8PMnOutMask[u8PortNum]) // If Set to Inhibited Bit 
    // {
    //         printf_f((const char* __far)"[Err]setPortOut:%d, 0x%02x\n\r", u8PortNum,u8Value);
    // }
    // else
    // {	
    //     u8ptr=(volatile __near unsigned char  *)u16PMn[u8PortNum]; 
	//     *u8ptr = clrRegister(*u8ptr,u8Value); 
    // }
} 


// Set Port to N-CH Open Drain
void HAL_PORT_NChOpenDrainMode_SET(U8 u8PortNum, U8 u8Value, U8 P_Set)
{
    U8 *u8ptr;
    U8  i = 0;

    if(P_Set == SET)
    {
        u8ptr=(volatile __near unsigned char *)u16POMnAddress[u8PortNum]; 
        *u8ptr = HAL_PORT_Register_SET(*u8ptr,u8Value);
    }
    else
    {
        u8ptr=(volatile __near unsigned char *)u16POMnAddress[u8PortNum]; 
        *u8ptr = HAL_PORT_Register_CLEAR(*u8ptr,u8Value);
    }

    // if(u8Value & u8PMnOutMask[u8PortNum]) // If Set to Inhibited Bit 
    // {
    //         printf_f((const char* __far)"[Err]setPortOut:%d, 0x%02x\n\r", u8PortNum,u8Value);
    // }
    // else
    // {	
    //     u8ptr=(volatile __near unsigned char  *)u16PMn[u8PortNum]; 
	//     *u8ptr = clrRegister(*u8ptr,u8Value); 
    // }
} 



// Set Port to TTL Input Buffer
void HAL_PORT_TTLInputMode_SET(U8 u8PortNum, U8 u8Value, U8 P_Set)
{
    U8 *u8ptr;
    U8  i = 0;

    if(P_Set == SET)
    {
        u8ptr=(volatile __near unsigned char *)u16PIMnAddress[u8PortNum]; 
        *u8ptr = HAL_PORT_Register_SET(*u8ptr,u8Value);
    }
    else
    {
        u8ptr=(volatile __near unsigned char *)u16PIMnAddress[u8PortNum]; 
        *u8ptr = HAL_PORT_Register_CLEAR(*u8ptr,u8Value);
    }

    // if(u8Value & u8PMnOutMask[u8PortNum]) // If Set to Inhibited Bit 
    // {
    //         printf_f((const char* __far)"[Err]setPortOut:%d, 0x%02x\n\r", u8PortNum,u8Value);
    // }
    // else
    // {	
    //     u8ptr=(volatile __near unsigned char  *)u16PMn[u8PortNum]; 
	//     *u8ptr = clrRegister(*u8ptr,u8Value); 
    // }
} 


static U8 HAL_PORT_Register_SET(U8 u8RegData, U8 u8Value)
{
    U8 i=0;	
  
    for(i=0; i<8; i++)
    {
        if(u8Value & (0x01<<i))
        {
            u8RegData |= (U8)(0x01<<i); 
        }
    }

    return u8RegData;  
}

static U8 HAL_PORT_Register_CLEAR(U8 u8RegData, U8 u8Value)
{
    U8 i=0;	
  
    for(i=0; i<8; i++)
    {
        if(u8Value & (0x01<<i))
        {
            u8RegData &= (U8)(~(0x01<<i)); 
        }
    }
    return u8RegData;  
}