/*
 * lcd.c
 *
 * Created: 15.04.2016 10:45:37
 *  Author: kotenko_kg
 */ 


//# warning "LCD c"

#include <avr/io.h>
#include "../common.h"
#include "lcd.h"



#ifndef DBG_PROTEUS
# warning "DBG_PROTEUS is setted"
#define _LCD_INPROT 1
#else
//#define _LCD_INPROT 0
#endif





#define __PORTDATADIR	DDRA
#define __PORTDATA		PORTA

#define __PORTCMDDIR	DDRC
#define __PORTCMD		PORTC


 

#define LCD_E_on 			__PORTCMD|=(1<<0)
#define LCD_RES_on 		__PORTCMD|=(1<<4)
#define LCD_CS_on 		__PORTCMD|=(1<<3)
#define LCD_RW_on 		__PORTCMD|=(1<<1)
#define LCD_E_off 		__PORTCMD&=~(1<<0)
#define LCD_RES_off 		__PORTCMD&=~(1<<4)
#define LCD_CS_off 		__PORTCMD&=~(1<<3)
#define LCD_RW_off 		__PORTCMD&=~(1<<1)

void LCD_A0(int b)
{
	if(b>=1)(__PORTCMD|=(1<<5));
	else (__PORTCMD&=~(1<<5));
}
void LCD_CS(int b)
{
	if(b>=1)(__PORTCMD|=(1<<3));
	else (__PORTCMD&=~(1<<3));
}
void LCD_SetD(int b)
{
	__PORTDATA = b;
}
//#define LCD_GetD() 				GetByte(__PORTA)








 //Процедура программной инициализации индикатора
 void LCDinit()
 {
	__PORTDATADIR = 0xFF; // out
	__PORTCMDDIR = 0xFF; // out


	 LCD_E_on;//Начальное значение сигнала индикатору
	 LCD_RES_off;//Выдать сигнал RES=0 индикатору
	 delayUs(10);//Задержка на время больше 10 мкс
	 LCD_RES_on;//Снять сигнал RES
	 delayMs(1);//Задержка на время больше 1 мс
	 WriteCodeL(0xE2);//Reset
	 WriteCodeR(0xE2);//Reset
	 WriteCodeL(0xEE);//ReadModifyWrite off
	 WriteCodeR(0xEE);//ReadModifyWrite off
	 WriteCodeL(0xA4);//Включить обычный режим
	 WriteCodeR(0xA4);//Включить обычный режим
	 WriteCodeL(0xA9);//Мультиплекс 1/32
	 WriteCodeR(0xA9);//Мультиплекс 1/32
	 WriteCodeL(0xC0);//Верхнюю строку на 0
	 WriteCodeR(0xC0);//Верхнюю строку на 0

	 WriteCodeL(0xA1);//Invert scan RAM
	 //NonInvert scan RAM
	 //if (fromProt == FALSE)
	 //WriteCodeR(0xA0);
	 //else
	 //WriteCodeR(0xA1);
	 #ifdef _LCD_INPROT
	 WriteCodeR(0xA1);
	 #else
	 WriteCodeR(0xA0);
	 #endif
	 
	 
	 //Display on
	 WriteCodeL(0xAF);//Display on
	 WriteCodeR(0xAF);//Display on
 }


 void WriteCodeL(int b) { WriteByte(b,0,1); }//Команду в левый кристалл индикатора
 void WriteCodeR(int b) { WriteByte(b,0,0); }//Команду в правый кристалл индикатора

 void WriteDataL(int b) { WriteByte(b,1,1); }//Данные в левую половину индикатора
 void WriteDataR(int b) { WriteByte(b,1,0); }//Данные в правую половину индикатора

 //Процедура выдачи байта в индикатор
 void WriteByte(int b, int cd, int lr) {
	 //При необходимости настроить здесь шину данных на вывод
	 LCD_RW_off;
	 LCD_A0(cd);
	 LCD_CS(lr);
	 LCD_SetD(b);
	 delayNs(40);		//Это время предустановки адреса (tAW)
	 LCD_E_off;
	 delayNs(160);	//Длительность сигнала E=0 (время предустановки данных попало сюда (tDS))
	 LCD_E_on;		//Сбросить сигнал E индикатору
	 //Delay(>(2000ns-40ns-160ns));	//Минимально допустимый интервал между сигналами E=0
 }


 void LCDclear() {
	 int	p = 0;//Номер текущей страницы индикатора
	 int	c = 0;//Позиция по горизонтали выводимого байта
	 int clearSymb = 0x00;
	 
	 // reset LCD addr
	 WriteCodeL(0xE2);
	 WriteCodeR(0xE2);
	 
	 for(p=0; p<4; p++) {//Цикл по всем 4-м страницам индикатора
		 WriteCodeL(p|0xB8);//Установка текущей страницы для левого кристалла индикатора
		 WriteCodeL(0x13);//Установка текущего адреса для записи данных в левую отображаемую позицию левой половины индикатора
		 for(c=0; c<61; c++) {//Цикл вывода данных в левую половину индикатора
			 WriteDataL(clearSymb);
		 }
		 WriteCodeR(p|0xB8);//Установка текущей страницы для правого кристалла индикатора
		 WriteCodeR(0x00);//Установка текущего адреса для записи данных в левую отображаемую позицию правой половины индикатора
		 for(c=61; c<122; c++) {//Цикл вывода данных в правую половину индикатора
			 WriteDataR(clearSymb);
		 }
	 }
 }




 void LCDdraw(BYTE video[][122]){
	 
	 int	p = 0;
	 int	c = 0;

	 // reset LCD addr
	 WriteCodeL(0xE2);
	 WriteCodeR(0xE2);
	 
	 for(p=0; p<4; p++) {//Цикл по всем 4-м страницам индикатора
		 //WriteCodeL(0xE2); // reset
		 WriteCodeL(p|0xB8);//Установка текущей страницы для левого кристалла индикатора
		 WriteCodeL(0x13);//Установка текущего адреса для записи данных в левую отображаемую позицию левой половины индикатора
		 for(c=0; c<61; c++) {//Цикл вывода данных в левую половину индикатора
			 WriteDataL(video[p][c]);//Вывод очередного байта в индикатор
		 }
		 //WriteCodeR(0xE2); // reset
		 WriteCodeR(p|0xB8);//Установка текущей страницы для правого кристалла индикатора
		 WriteCodeR(0x00);//Установка текущего адреса для записи данных в левую отображаемую позицию правой половины индикатора
		 for(c=61; c<122; c++) {//Цикл вывода данных в правую половину индикатора
			 #ifndef _LCD_INPROT
			 WriteDataR(video[p][c]);
			 #endif
		 }
	 }
	 
 }


 void LCDdrawLeftOnly(BYTE video[][122])
 {
	 
	 int	p = 0;
	 int	c = 0;
	 
	 // reset LCD addr
	 WriteCodeL(0xE2);
	 WriteCodeR(0xE2);
	 
	 for(p=0; p<4; p++) {//Цикл по всем 4-м страницам индикатора
		 WriteCodeL(0xE2); // reset
		 
		 WriteCodeL(p|0xB8);//Установка текущей страницы для левого кристалла индикатора
		 WriteCodeL(0x13);//Установка текущего адреса для записи данных в левую отображаемую позицию левой половины индикатора
		 for(c=0; c<61; c++) {//Цикл вывода данных в левую половину индикатора
			 WriteDataL(video[p][c]);//Вывод очередного байта в индикатор
		 }
		 
		 //WriteCodeR(0xE2); // reset
		 //WriteCodeR(p|0xB8);//Установка текущей страницы для правого кристалла индикатора
		 //WriteCodeR(0x00);//Установка текущего адреса для записи данных в левую отображаемую позицию правой половины индикатора
		 //for(c=61; c<122; c++) {//Цикл вывода данных в правую половину индикатора
		 //	WriteDataR(video[p][c]);
		 //}
	 }
	 
 }
