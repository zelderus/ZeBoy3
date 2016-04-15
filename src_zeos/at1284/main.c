/*
 * at1284.c
 *
 * Created: 15.04.2016 9:50:40
 * Author : kotenko_kg
 */ 

#define F_CPU 8000000
#define DBG_PROTEUS





#include <avr/io.h>
#include <util/delay.h>
#include "common.h"
#include "drivers/drivers.h"



void Loop(void);
void Update(void);


int main(void)
{

	// init
	VIDEO_Init();
	
	while(1)
	{
		Loop();
	}


}


 
 
 
 /*
 *		Основной цикл
 */
 void Loop(void) {
 	VIDEO_Clear();
 	Update();
 	VIDEO_Draw();
	//_delay_ms(100);
 }
 
 
 

 
 int _x = 0;
 int _maxX = 60;

 void Update(void){
 	
	int i = 0;

	_x++;
	if (_x >= _maxX) _x = 0;
	
	for(i = 0; i <= 7; i++)
	{
		int y = i * 4 + 0;
		

		VIDEO_Pixel(_x, y+0);
		VIDEO_Pixel(_x, y+1);
		VIDEO_Pixel(_x+1, y+0);
		VIDEO_Pixel(_x+1, y+1);

	}


	
	
 }
 
 
