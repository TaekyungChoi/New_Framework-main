//""FILE COMMENT""************************************************************
// System Name : Active Action ????u????
// File Name   : Type_Define.h
// Version     : Ver 0.0.1.2
// Contents    : 
// Cgu16tomer  : 
// Model       : AP-0818A
// Order       : 
// CPU         : R5F100PG
// Assembler   : 
// Linker      : 
// OS          : WINDOWS 10
// Programmer  : J.J.K // K.K.H
// Note        : 
//****************************************************************************
// Copyright, 2017 Coway Corporatiuon
//****************************************************************************

// History     : 2017.5.1     Ver 0.0.0.1 
//        
//""FILE COMMENT END""********************************************************


#ifndef _TYPE_DEFINE_H_
#define _TYPE_DEFINE_H_


//***************************************************
//*                    DATA TYPES                   *
//***************************************************
typedef unsigned char       U8;
typedef char                I8;
typedef unsigned int        U16;
typedef int                 I16;
typedef const char          CI8;
typedef const int           CI16;
typedef unsigned long int   U32;
typedef float               F32;
typedef double              D64;

typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef signed short        int16_t;
typedef unsigned short      uint16_t;
typedef signed long         int32_t;
typedef unsigned long       uint32_t;
typedef unsigned short      MD_STATUS;


//***************************************************
//*                  struct & union                 *
//***************************************************
typedef struct
{
    unsigned char   b7:1;
    unsigned char   b6:1;
    unsigned char   b5:1;
    unsigned char   b4:1;
    unsigned char   b3:1;
    unsigned char   b2:1;
    unsigned char   b1:1;
    unsigned char   b0:1;
} SBYTE_FIELD;

typedef struct
{
  unsigned char     high_nibble:4;
  unsigned char     low_nibble:4;
} SBYTE_FIELD1;

typedef struct
{
    unsigned char   b15:1;
    unsigned char   b14:1;
    unsigned char   b13:1;
    unsigned char   b12:1;
    unsigned char   b11:1;
    unsigned char   b10:1;
    unsigned char   b9:1;
    unsigned char   b8:1;
    unsigned char   b7:1;
    unsigned char   b6:1;
    unsigned char   b5:1;
    unsigned char   b4:1;
    unsigned char   b3:1;
    unsigned char   b2:1;
    unsigned char   b1:1;
    unsigned char   b0:1;
} SWORD_FIELD;

/////////////////////////////////////////////////////
//                 USER CODE             
/////////////////////////////////////////////////////
typedef struct
{
    unsigned char b0:1;
    unsigned char b1:1;
    unsigned char b2:1;
    unsigned char b3:1;
    unsigned char b4:1;
    unsigned char b5:1;
    unsigned char b6:1;
    unsigned char b7:1;
}
BYTE_FIELD;

typedef struct
{
    unsigned char high_nibble:4;
    unsigned char low_nibble:4;
}
BYTE_FIELD1;

typedef struct
{
    unsigned char b0:1;
    unsigned char b1:1;
    unsigned char b2:1;
    unsigned char b3:1;
    unsigned char b4:1;
    unsigned char b5:1;
    unsigned char b6:1;
    unsigned char b7:1;
    unsigned char b8:1;
    unsigned char b9:1;
    unsigned char b10:1;
    unsigned char b11:1;
    unsigned char b12:1;
    unsigned char b13:1;
    unsigned char b14:1;
    unsigned char b15:1;
}
WORD_FIELD;

typedef struct
{
    unsigned char data_l:8;
    unsigned char data_h:8;
    unsigned char data_id:8;
    unsigned char parity:1;
    unsigned char msg_type:3;
    unsigned char space:4;
}
OT_FIELD;

/*=======  BYTE IO ========*/
typedef union
{
    unsigned char     byte;
    BYTE_FIELD         Bit;
}
TYPE_BYTE;

typedef union
{
    unsigned char     byte;
    BYTE_FIELD1        Bit;
}
TYPE_BYTE1;

/*======= WORD IO ========*/
typedef union
{
    unsigned int    word;
    unsigned char    byte[2];
    WORD_FIELD         Bit;
}
TYPE_WORD;

/*====== DOUBLE IO =======*/
typedef union
{
    unsigned long     wword;
    unsigned int     word[2];
    unsigned char    byte[4];
    OT_FIELD         Bit;
}
TYPE_DWORD;

//***************************************************
//*    DEFINITION & constant data(Reference data)   *
//***************************************************
#define TRUE        1
#define FALSE       0
#define SET         1
#define CLEAR       0
#define HIGH        1
#define LOW         0
#define ON          1
#define OFF         0
#define _ON         0         // NEGATIVE ON
#define _OFF        1         // NEGATIVE OFF
#define PUSH        0
#define POP         1
#define OPEN        1
#define CLOSE       0

#define MAX(x,y) (x)>(y)?(x):(y)
#define MIN(x,y) (x)<(y)?(x):(y)
#define GET_MIN(x,y,z) (MIN(x, y))<(z)?(MIN(x, y)):(z)
#define GET_MAX(x,y,z) (MAX(x, y))>(z)?(MAX(x, y)):(z)

#define  Watchdog() WDTE = 0xAC

typedef void (*fp_void)(void);
typedef void (*fp_U32Ptr)(unsigned long *const ptr);
typedef MD_STATUS (*fp_Param_pU8_U16_pU8)(U8*, U16, U8*);
typedef MD_STATUS (*fp_Param_pU8_U16)(U8*, U16);


#endif
