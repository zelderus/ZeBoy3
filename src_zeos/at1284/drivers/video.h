/*
 * video.h
 *
 *	Работа с видео буфером
 *
 * Created: 15.04.2016 11:52:09
 *  Author: kotenko_kg
 */ 


#ifndef VIDEO_H_
#define VIDEO_H_

 //# warning "video H"


void VIDEO_Init(void);
void VIDEO_Clear(void);
void VIDEO_Draw(void);

// рисуем пиксель
void VIDEO_Pixel(int x, int y);


#endif /* VIDEO_H_ */