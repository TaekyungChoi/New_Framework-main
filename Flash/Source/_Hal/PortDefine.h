#ifndef _PORT_DEFINE_H_
#define _PORT_DEFINE_H_


// KEY
#define P_KEY_LIGHT         P2.4
#define P_KEY_SPEED         P2.5
#define P_KEY_AIRQUALITY    P2.6
#define P_KEY_MODE          P2.7
#define P_KEY_POWER         P15.0
#define P_KEY_DIRECTION     P15.1


// Display
#define P_HOLTEKDRIVER_IC_SCL    P11.1
#define P_HOLTEKDRIVER_IC_SDA    P11.0         


// Front RGB
#define P_FRONTRGB_SET_1    P0.5
#define P_FRONTRGB_SET_2    P0.6
#define P_FRONTRGB_SET_3    P7.0
#define P_FRONTRGB_SET_4    P7.1
#define P_FRONTRGB_SET_5    P7.2
#define P_FRONTRGB_SET_6    P7.3
#define P_FRONTRGB_SET_7    P7.4
#define P_FRONTRGB_SET_8    P7.5

#define P_FRONTRGB_RED        P7.6
#define P_FRONTRGB_GREEN      P7.7
#define P_FRONTRGB_BLUE       P6.7


// REED
#define P_REED_FRONTCOVER     P12.0
#define P_REED_SLIDE          P14.0


// STEPMOTOR
#define P_STEPMOTOR_11      P5.3
#define P_STEPMOTOR_12      P5.2
#define P_STEPMOTOR_13      P5.1
#define P_STEPMOTOR_14      P5.0

#define P_STEPMOTOR_21          
#define P_STEPMOTOR_22          
#define P_STEPMOTOR_23          
#define P_STEPMOTOR_24


// EEPROM
#define	P_EEPROM_SCL	    P6.0
#define	P_EEPROM_SDA	    P6.1
#define	PM_EEPROM_SCL_SDA	PM6



//---------------------------------------------------------------------------------------------------------


// Buzzer
#define P_BUZZER_POWER  P1.7


// BLDC MOTOR
#define P_MOTOR_POWER_1     P6.6
#define P_MOTOR_FEEDBACK_1  P3.1

#define P_MOTOR_POWER_2
#define P_MOTOR_FEEDBACK_2


// DUST SENSOR
#define P_DUST_POWER        P14.2


#endif