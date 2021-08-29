#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H
/*This file is containing the global APIs that are used for any standard project*/
/*********************************Global Symbols******************************/
/*
Symbol name: F_CPU
Symbol Description: MCU CPU Freq as defined by AVR/io.h
Symbol Range: for ATMega16 : 0 .. 16000000
*/
#define F_CPU 8000000UL

/*
Symbol name: OP_ON
Symbol Description: enable a specific feature
Symbol Range: 1U
*/
#define OP_ON 1U

/*
Symbol name: OP_OFF
Symbol Description: disable a specific feature
Symbol Range: 0U
*/
#define OP_OFF 0U
/*********************************Global Types********************************/

typedef unsigned char uint8_t;
/*
Type name: uint8_t
Type Description: unsigned char type
Type Range: 0 .. 255
*/
typedef char int8_t;
/*
Type name: int8_t
Type Description: char type
Type Range: -127 .. 127
*/

typedef signed short int int16_t;
/*
Type name: int16_t
Type Description: unsigned short int type
Type Range: -32,767 .. 32,767
*/

typedef unsigned short int uint16_t;
/*
Type name: uint16_t
Type Description: unsigned short int type
Type Range: 0 .. 65535
*/

typedef signed long int int32_t;
/*
Type name: int32_t
Type Description: unsigned long int type
Type Range: -2,147,483,647 .. 2,147,483,647
*/

typedef unsigned long int uint32_t;
/*
Type name: int32_t
Type Description: unsigned long int type
Type Range: 0 .. 4,294,967,295
*/
typedef enum { OK,NOK } BasicRet;
/*
Type name: BasicRet
Type Description: Basic Return type
Type Range: OK,NOK
*/

typedef enum { TRUE,FALSE } bool;
/*
Type name: bool
Type Description: boolean type
Type Range: TRUE,FALSE
*/
#endif

