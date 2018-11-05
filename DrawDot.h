#ifndef DRAWDOT_H_DEFINED

#include "DrawDot_Set.h"

//box関数の使い方
//	box(ｘ座標,ｙ座標,色)
//	ｘ座標：０－３１
//	ｙ座標：０－３１
//	色：０－７

//以下変更禁止
void box(int x,int y,int c)
{
	int clr;
	if(c<0 || c>8 ||y<0 || y>=SCREEN_Y_SIZE || x<0 || x>=SCREEN_X_SIZE)
	{
		DxLib_End();
		exit(-1);
	}

	clr = GetEasyColor(c);

	DrawBox(x*SQUARE_X_SIZE,y*SQUARE_Y_SIZE,(x+1)*SQUARE_X_SIZE-2,(y+1)*SQUARE_Y_SIZE-2,clr,TRUE);
}

#define DRAWDOT_H_DEFINED
#endif
