/*
 * common.h
 *
 * Created: 15.04.2016 10:47:10
 *  Author: kotenko_kg
 */ 


#ifndef COMMON_H_
#define COMMON_H_



//
// types
//
typedef unsigned char BYTE;
typedef unsigned int BOOL;
#define TRUE 1
#define FALSE 0

//
// bits
//
int SetBit(int x,int y);
int ClrBit(int x,int y);
int ToggleBit(int x,int y);

//
// times
//
void nop();
void delay(unsigned int p);
void delay1000(unsigned int p);
void delayMs(unsigned int p);
void delayUs(unsigned int p);
void delayNs(unsigned int p);




#endif /* COMMON_H_ */