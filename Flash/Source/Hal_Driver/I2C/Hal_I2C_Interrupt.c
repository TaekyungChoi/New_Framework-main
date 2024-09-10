#include "HW.h"
#include "Hal_I2C.h"
#include "Hal_I2C_Interrupt.h"

extern volatile uint8_t * gp_uart0_tx_address;         /* uart0 send buffer address */
extern volatile uint16_t  g_uart0_tx_count;            /* uart0 send data number */
extern volatile uint8_t * gp_uart0_rx_address;         /* uart0 receive buffer address */
extern volatile uint16_t  g_uart0_rx_count;            /* uart0 receive data number */
extern volatile uint16_t  g_uart0_rx_length;           /* uart0 receive data length */
extern volatile uint8_t * gp_uart1_tx_address;         /* uart1 send buffer address */
extern volatile uint16_t  g_uart1_tx_count;            /* uart1 send data number */
extern volatile uint8_t * gp_uart1_rx_address;         /* uart1 receive buffer address */
extern volatile uint16_t  g_uart1_rx_count;            /* uart1 receive data number */
extern volatile uint16_t  g_uart1_rx_length;           /* uart1 receive data length */
extern volatile uint8_t * gp_uart2_tx_address;         /* uart2 send buffer address */
extern volatile uint16_t  g_uart2_tx_count;            /* uart2 send data number */
extern volatile uint8_t * gp_uart2_rx_address;         /* uart2 receive buffer address */
extern volatile uint16_t  g_uart2_rx_count;            /* uart2 receive data number */
extern volatile uint16_t  g_uart2_rx_length;           /* uart2 receive data length */
extern volatile uint8_t * gp_uart3_tx_address;         /* uart3 send buffer address */
extern volatile uint16_t  g_uart3_tx_count;            /* uart3 send data number */
extern volatile uint8_t * gp_uart3_rx_address;         /* uart3 receive buffer address */
extern volatile uint16_t  g_uart3_rx_count;            /* uart3 receive data number */
extern volatile uint16_t  g_uart3_rx_length;           /* uart3 receive data length */
extern volatile uint8_t   g_iica0_master_status_flag;  /* iica0 master flag */ 
extern volatile uint8_t   g_iica0_slave_status_flag;   /* iica0 slave flag */
extern volatile uint8_t * gp_iica0_rx_address;         /* iica0 receive buffer address */
extern volatile uint16_t  g_iica0_rx_cnt;              /* iica0 receive data length */
extern volatile uint16_t  g_iica0_rx_len;              /* iica0 receive data count */
extern volatile uint8_t * gp_iica0_tx_address;         /* iica0 send buffer address */
extern volatile uint16_t  g_iica0_tx_cnt;              /* iica0 send data count */

U8 I2C_ReceiveCommand_F = 0;
U8 TxData[50] = {0,};



MD_STATUS HAL_I2C_INT_ByteWrite_16bitAddrToData(U16 Addr, U8 Data)
{
    MD_STATUS status = MD_OK;
    U8  mu8Wait = 15;
    U16 mu16Temp = 0;

    if(Addr <= 0xFF)
    {
        TxData[0] = 0x00;
        TxData[1] = (U8)Addr;
    }
    else
    {
        mu16Temp = 0x00FF;
        mu16Temp = (Addr & mu16Temp);
        TxData[1] = (U8)mu16Temp;

        mu16Temp = 0xFF00;
        mu16Temp = (Addr & mu16Temp);
        TxData[0] = (U8)(mu16Temp >> 8);
    }

    TxData[2] = Data;

    IICAMK0 = 1U;  /* disable INTIICA0 interrupt */
    
    if (1U == IICBSY0)
    {
        /* Check bus busy */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        status = MD_ERROR1;
    }
    else
    {
        STT0 = 1U; /* send IICA0 start condition */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        
        /* Wait */
        while (mu8Wait--)
        {
            ;
        }
        
        if (0U == STD0)
        {
            status = MD_ERROR2;
        }
		    
        /* Set parameter */
        g_iica0_tx_cnt = 3;
        gp_iica0_tx_address = &TxData[0];
        g_iica0_master_status_flag = _00_IICA_MASTER_FLAG_CLEAR;
        IICA0 = DEVICE_ID | WRITE_COMMAND; /* send address */
    }

    return (status);    
}


MD_STATUS HAL_I2C_INT_ByteWrite_8bitAddrToData(U8 Addr, U8 Data)
{
    MD_STATUS status = MD_OK;
    U8  mu8Wait = 15;
    U16 mu16Temp = 0;

    // if(Addr <= 0xFF)
    // {
    //     TxData[0] = 0x00;
    //     TxData[1] = (U8)Addr;
    // }
    // else
    // {
    //     mu16Temp = 0x00FF;
    //     mu16Temp = (Addr & mu16Temp);
    //     TxData[1] = (U8)mu16Temp;

    //     mu16Temp = 0xFF00;
    //     mu16Temp = (Addr & mu16Temp);
    //     TxData[0] = (U8)(mu16Temp >> 8);
    // }

    TxData[0] = Addr;
    TxData[1] = Data;

    IICAMK0 = 1U;  /* disable INTIICA0 interrupt */
    
    if (1U == IICBSY0)
    {
        /* Check bus busy */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        status = MD_ERROR1;
    }
    else
    {
        STT0 = 1U; /* send IICA0 start condition */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        
        /* Wait */
        while (mu8Wait--)
        {
            ;
        }
        
        if (0U == STD0)
        {
            status = MD_ERROR2;
        }
		    
        /* Set parameter */
        g_iica0_tx_cnt = 2;
        gp_iica0_tx_address = &TxData[0];
        g_iica0_master_status_flag = _00_IICA_MASTER_FLAG_CLEAR;
        IICA0 = DEVICE_ID | WRITE_COMMAND; /* send address */
    }

    return (status);    
}


MD_STATUS HAL_I2C_INT_ByteRead_16bitAddrToData(U16 Addr, U8* RxBuffer)
{
    MD_STATUS status = MD_OK;
    U8  mu8Wait = 15;
    U16 mu16Temp = 0;

    if(Addr <= 0xFF)
    {
        TxData[0] = 0x00;
        TxData[1] = (U8)Addr;
    }
    else
    {
        mu16Temp = 0x00FF;
        mu16Temp = (Addr & mu16Temp);
        TxData[1] = (U8)mu16Temp;

        mu16Temp = 0xFF00;
        mu16Temp = (Addr & mu16Temp);
        TxData[0] = (U8)(mu16Temp >> 8);
    }

    IICAMK0 = 1U;  /* disable INTIICA0 interrupt */
    if (1U == IICBSY0)
    {
        /* Check bus busy */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        status = MD_ERROR1;
    } 
    else if ((1U == SPT0) || (1U == STT0)) 
    {
        /* Check trigger */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */  
        status = MD_ERROR2;
    }
    else
    {
        STT0 = 1U; /* send IICA0 start condition */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        
        /* Wait */
        while (mu8Wait--)
        {
            ;
        }
        
        /* Set parameter */
      	g_iica0_rx_len = 1;
      	gp_iica0_rx_address = RxBuffer;
      	
      	I2C_ReceiveCommand_F = SET;
        g_iica0_tx_cnt = 2;
        gp_iica0_tx_address = &TxData[0];
        g_iica0_master_status_flag = _00_IICA_MASTER_FLAG_CLEAR;
        //adr &= (uint8_t)~0x01U; /* set send mode */
        IICA0 = DEVICE_ID | WRITE_COMMAND; /* send address */
    }

    return (status);
}


MD_STATUS HAL_I2C_INT_ByteRead_8bitAddrToData(U8 Addr, U8* RxBuffer)
{
    MD_STATUS status = MD_OK;
    U8  mu8Wait = 15;
    U16 mu16Temp = 0;

    TxData[0] = Addr;

    IICAMK0 = 1U;  /* disable INTIICA0 interrupt */
    if (1U == IICBSY0)
    {
        /* Check bus busy */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        status = MD_ERROR1;
    } 
    else if ((1U == SPT0) || (1U == STT0)) 
    {
        /* Check trigger */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */  
        status = MD_ERROR2;
    }
    else
    {
        STT0 = 1U; /* send IICA0 start condition */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        
        /* Wait */
        while (mu8Wait--)
        {
            ;
        }
        
        /* Set parameter */
      	g_iica0_rx_len = 1;
      	gp_iica0_rx_address = RxBuffer;
      	
      	I2C_ReceiveCommand_F = SET;
        g_iica0_tx_cnt = 1;
        gp_iica0_tx_address = &TxData[0];
        g_iica0_master_status_flag = _00_IICA_MASTER_FLAG_CLEAR;
        //adr &= (uint8_t)~0x01U; /* set send mode */
        IICA0 = DEVICE_ID | WRITE_COMMAND; /* send address */
    }

    return (status);
}



MD_STATUS HAL_I2C_INT_PageWrite_16bitAddrToData(U16 Addr, U8* TxBuffer, U16 TxNum)
{
    MD_STATUS status = MD_OK;
    U8  mu8Wait = 15;
    U16 mu16Temp = 0;

    if(TxNum > 32)
    {
        status = MD_ERROR1;
        return status;
    }

    if(Addr <= 0xFF)
    {
        TxData[0] = 0x00;
        TxData[1] = (U8)Addr;
    }
    else
    {
        mu16Temp = 0x00FF;
        mu16Temp = (Addr & mu16Temp);
        TxData[1] = (U8)mu16Temp;

        mu16Temp = 0xFF00;
        mu16Temp = (Addr & mu16Temp);
        TxData[0] = (U8)(mu16Temp >> 8);
    }
    
    for(mu16Temp = 0; mu16Temp < TxNum ; mu16Temp++)
    {
        TxData[mu16Temp + 2] = TxBuffer[mu16Temp];
    }

    IICAMK0 = 1U;  /* disable INTIICA0 interrupt */
    
    if (1U == IICBSY0)
    {
        /* Check bus busy */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        status = MD_ERROR1;
    }
    else
    {
        STT0 = 1U; /* send IICA0 start condition */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        
        /* Wait */
        while (mu8Wait--)
        {
            ;
        }
        
        if (0U == STD0)
        {
            status = MD_ERROR2;
        }
		    
        /* Set parameter */
        g_iica0_tx_cnt = TxNum + 2;
        gp_iica0_tx_address = &TxData[0];
        g_iica0_master_status_flag = _00_IICA_MASTER_FLAG_CLEAR;
        IICA0 = DEVICE_ID | WRITE_COMMAND; /* send address */
    }

    return (status);        
}


MD_STATUS HAL_I2C_INT_PageWrite_8bitAddrToData(U8 Addr, U8* TxBuffer, U16 TxNum)
{
    MD_STATUS status = MD_OK;
    U8  mu8Wait = 15;
    U16 mu16Temp = 0;

    if(TxNum > 8)
    {
        status = MD_ERROR1;
        return status;
    }

    TxData[0] = Addr;

    for(mu16Temp = 0; mu16Temp < TxNum ; mu16Temp++)
    {
        TxData[mu16Temp + 1] = TxBuffer[mu16Temp];
    }

    IICAMK0 = 1U;  /* disable INTIICA0 interrupt */
    
    if (1U == IICBSY0)
    {
        /* Check bus busy */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        status = MD_ERROR1;
    }
    else
    {
        STT0 = 1U; /* send IICA0 start condition */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        
        /* Wait */
        while (mu8Wait--)
        {
            ;
        }
        
        if (0U == STD0)
        {
            status = MD_ERROR2;
        }
		    
        /* Set parameter */
        g_iica0_tx_cnt = TxNum + 1;
        gp_iica0_tx_address = &TxData[0];
        g_iica0_master_status_flag = _00_IICA_MASTER_FLAG_CLEAR;
        IICA0 = DEVICE_ID | WRITE_COMMAND; /* send address */
    }

    return (status);
}


MD_STATUS HAL_I2C_INT_PageRead_16bitAddrToData(U16 Addr, U8* RxBuffer, U16 RxNum)
{
    MD_STATUS status = MD_OK;
    U8  mu8Wait = 15;
    U16 mu16Temp = 0;

    if(Addr <= 0xFF)
    {
        TxData[0] = 0x00;
        TxData[1] = (U8)Addr;
    }
    else
    {
        mu16Temp = 0x00FF;
        mu16Temp = (Addr & mu16Temp);
        TxData[1] = (U8)mu16Temp;

        mu16Temp = 0xFF00;
        mu16Temp = (Addr & mu16Temp);
        TxData[0] = (U8)(mu16Temp >> 8);
    }

    IICAMK0 = 1U;  /* disable INTIICA0 interrupt */
    if (1U == IICBSY0)
    {
        /* Check bus busy */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        status = MD_ERROR1;
    } 
    else if ((1U == SPT0) || (1U == STT0)) 
    {
        /* Check trigger */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */  
        status = MD_ERROR2;
    }
    else
    {
        STT0 = 1U; /* send IICA0 start condition */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        
        /* Wait */
        while (mu8Wait--)
        {
            ;
        }
        
        /* Set parameter */
      	g_iica0_rx_len = RxNum;
      	gp_iica0_rx_address = RxBuffer;
      	
      	I2C_ReceiveCommand_F = SET;
        g_iica0_tx_cnt = 2;
        gp_iica0_tx_address = &TxData[0];
        g_iica0_master_status_flag = _00_IICA_MASTER_FLAG_CLEAR;
        //adr &= (uint8_t)~0x01U; /* set send mode */
        IICA0 = DEVICE_ID | WRITE_COMMAND; /* send address */
    }

    return (status);
}


MD_STATUS HAL_I2C_INT_PageRead_8bitAddrToData(U8 Addr, U8* RxBuffer, U16 RxNum)
{
    MD_STATUS status = MD_OK;
    U8  mu8Wait = 15;
    U16 mu16Temp = 0;

    TxData[0] = Addr;

    IICAMK0 = 1U;  /* disable INTIICA0 interrupt */
    if (1U == IICBSY0)
    {
        /* Check bus busy */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        status = MD_ERROR1;
    } 
    else if ((1U == SPT0) || (1U == STT0)) 
    {
        /* Check trigger */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */  
        status = MD_ERROR2;
    }
    else
    {
        STT0 = 1U; /* send IICA0 start condition */
        IICAMK0 = 0U;  /* enable INTIICA0 interrupt */
        
        /* Wait */
        while (mu8Wait--)
        {
            ;
        }
        
        /* Set parameter */
      	g_iica0_rx_len = RxNum;
      	gp_iica0_rx_address = RxBuffer;
      	
      	I2C_ReceiveCommand_F = SET;
        g_iica0_tx_cnt = 1;
        gp_iica0_tx_address = &TxData[0];
        g_iica0_master_status_flag = _00_IICA_MASTER_FLAG_CLEAR;
        //adr &= (uint8_t)~0x01U; /* set send mode */
        IICA0 = DEVICE_ID | WRITE_COMMAND; /* send address */
    }

    return (status);
}