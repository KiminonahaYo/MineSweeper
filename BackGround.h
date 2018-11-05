#ifndef BACKGROUND_H_DEFINED

#include "BackGround_Set.h"

void GetBackGround(void)
{
	int xi,yi;
	static int FrameCnt=0;

	//ドットの初期設定
	if(FrameCnt==0)
	{
		for(xi=0; xi<SCREEN_X_SIZE; xi++)
		{
			for(yi=0; yi<SCREEN_Y_SIZE; yi++)
			{
				int xt=xi-CENTER_X;
				int yt=yi-CENTER_Y;
				int r1=CENTER_X-4;
				int r2=CENTER_X-2;
				if(xt*xt+yt*yt<r1*r1)		BgColFlag[xi][yi]=0;//小さい円
				else if(xt*xt+yt*yt<r2*r2)	BgColFlag[xi][yi]=1;//大きい円
				else						BgColFlag[xi][yi]=2;//外
			}
		}
	}
	//ドットの移動
	else
	{
		if(FrameCnt%10==0)
		{
			int TempX[SCREEN_X_SIZE-1];
			int TempY[SCREEN_Y_SIZE-1];
			int Temp;

			Temp = BgColFlag[SCREEN_X_SIZE-1][SCREEN_Y_SIZE-1];
			for(xi=0; xi<SCREEN_X_SIZE-1; xi++)
			{
				TempY[xi] = BgColFlag[xi][SCREEN_Y_SIZE-1];
			}
			for(yi=0; yi<SCREEN_Y_SIZE-1; yi++)
			{
				TempX[yi] = BgColFlag[SCREEN_X_SIZE-1][yi];
			}

			for(xi=SCREEN_X_SIZE-2; xi>=0; xi--)
			{
				for(yi=SCREEN_Y_SIZE-2; yi>=0; yi--)
				{
					BgColFlag[xi+1][yi+1]	=BgColFlag[xi][yi];
				}
			}

			for(xi=0; xi<SCREEN_X_SIZE-1; xi++)
			{
				BgColFlag[xi+1][0]	= TempY[xi];
			}
			for(yi=0; yi<SCREEN_Y_SIZE-1; yi++)
			{
				BgColFlag[0][yi+1]	= TempX[yi];
			}
			BgColFlag[0][0] = Temp;
		}
	}

	FrameCnt++;

	return;
}

void SetBackGround(void)
{
	int xi,yi,col[3];

	GetTimeColor(col,'b');
	for(xi=0;xi<SCREEN_X_SIZE;xi++)
	{
		for(yi=0;yi<SCREEN_Y_SIZE;yi++)
		{
			Field[xi][yi].Color=col[ BgColFlag[xi][yi] ];
		}
	}
}

#define BACKGROUND_H_DEFINED
#endif