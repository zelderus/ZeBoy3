/*
 * lcd.h
 *
 * Created: 15.04.2016 10:45:46
 *  Author: kotenko_kg
 */ 


#ifndef LCD_H_
#define LCD_H_



void LCDinit(BOOL fromProt);
void LCDclear();
void LCDdraw(BYTE video[][122]);
void LCDdrawLeftOnly(BYTE video[][122]);


void LCD_A0(int b);
void LCD_CS(int b);
void LCD_SetD(int b);
void WriteByte(int b, int cd, int lr);
void WriteCodeL(int b);
void WriteCodeR(int b);
void WriteDataL(int b);
void WriteDataR(int b);






#endif /* LCD_H_ */