#ifndef DOTASCII_H_DEFINED

#include "DotAscii_Set.h"

//数字１桁のマップを配列に格納
void SetDotAsc(int px, int py, int Code)
{
	int xi,yi;

	for(xi=0; xi<ASCFIELD_X_SIZE; xi++)
	{
		for(yi=0; yi<ASCFIELD_Y_SIZE; yi++)
		{
			if(px+xi<SCREEN_X_SIZE && py+yi<SCREEN_Y_SIZE)
				AscField[px+xi][py+yi] = AscData[Code].FieldCol[yi][xi];
		}
	}

	return;
}

void SetDotString(int px,int py, int col, char *Str)
{
	int x=0,y=0, xi,yi, i,j;
	char c;

	//初期化
	for(xi=0; xi<SCREEN_X_SIZE; xi++)
	{
		for(yi=0; yi<SCREEN_Y_SIZE; yi++)
		{
			AscField[xi][yi]=0;
		}
	}

	//描画用配列に数字データを格納
	for(i=0; Str[i]!='\0'; i++)
	{
		if(Str[i]>='a' && Str[i]<='z')	c = Str[i]-('a'-'A');
		else							c = Str[i];

		for(j=0; j<ASCNUM; j++)//線形探索
		{
			if(AscData[j].FieldChr==c) SetDotAsc(x,y, j);
		}

		if(Str[i]!='\n'){
			x+=ASCFIELD_X_SIZE+1;
		}else{
			x=0; y+=ASCFIELD_Y_SIZE+1;
		}
	}

	//配列に格納
	for(xi=0; xi<SCREEN_X_SIZE; xi++)
	{
		for(yi=0; yi<SCREEN_Y_SIZE; yi++)
		{
			if(AscField[xi][yi] && px+xi<SCREEN_X_SIZE && py+yi<SCREEN_Y_SIZE)
			{
				Field[px+xi][py+yi].Color=col;
			}
		}
	}

	return;
}

//日付、時刻をドット絵に描画
void SetDotDate(int px,int py, int col, char StrMode)
{
	DateAndTime Date;
	char DateS[256];

	GetTime(&Date);

	//モード別処理
	switch(StrMode)
	{
		case 'D':
		{
			//曜日
			//ドット絵の内容 改行文字でちゃんと改行する
			sprintf_s(DateS, 256, "%02d\n%02d/%02d\n%s\n%02d:%02d:%02d", 
				Date.Year,
				Date.Mon,
				Date.Day, GetWeek(Date.Week,"US"),
				Date.Hour,
				Date.Min,
				Date.Sec
				);
			break;
		}
		case 'J':
		{
			char *JNengo;
			JNengo = GetJapaneseYear(Date.Year, "A");
			sprintf_s(DateS, 256, "%s\n%02d/%02d\n%s\n%02d:%02d:%02d", 
				JNengo,
				Date.Mon,
				Date.Day, GetWeek(Date.Week,"US"),
				Date.Hour,
				Date.Min,
				Date.Sec
				);
			break;
		}
	}

	//描画
	SetDotString(px,py,col, DateS);
	//SetDotString("MYNAME\nYOSHI");

	return;
}

#define DOTASCII_H_DEFINED
#endif
