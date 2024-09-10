#ifndef _HAL_I2C_H_
#define _HAL_I2C_H_


// I2C
#define P_I2C_SCL	P_EEPROM_SCL //P6.0
#define	P_I2C_SDA	P_EEPROM_SDA //P6.1
#define	PM_I2C      PM_EEPROM_SCL_SDA
#define PM_I2C_SDA_OUTPUT   0xFC
#define PM_I2C_SDA_INPUT    0x02

#define DEVICE_ID      0xA0
#define WRITE_COMMAND  0x00
#define READ_COMMAND   0x01
#define ACK             0
#define NACK            1

#define START_ADDRESS_POINTER   0x00







#endif