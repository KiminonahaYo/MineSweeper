#ifndef DOTASCII_H_DEFINED

#include "DotAscii_Set.h"

//�����P���̃}�b�v��z��Ɋi�[
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

	//������
	for(xi=0; xi<SCREEN_X_SIZE; xi++)
	{
		for(yi=0; yi<SCREEN_Y_SIZE; yi++)
		{
			AscField[xi][yi]=0;
		}
	}

	//�`��p�z��ɐ����f�[�^���i�[
	for(i=0; Str[i]!='\0'; i++)
	{
		if(Str[i]>='a' && Str[i]<='z')	c = Str[i]-('a'-'A');
		else							c = Str[i];

		for(j=0; j<ASCNUM; j++)//���`�T��
		{
			if(AscData[j].FieldChr==c) SetDotAsc(x,y, j);
		}

		if(Str[i]!='\n'){
			x+=ASCFIELD_X_SIZE+1;
		}else{
			x=0; y+=ASCFIELD_Y_SIZE+1;
		}
	}

	//�z��Ɋi�[
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

//���t�A�������h�b�g�G�ɕ`��
void SetDotDate(int px,int py, int col, char StrMode)
{
	DateAndTime Date;
	char DateS[256];

	GetTime(&Date);

	//���[�h�ʏ���
	switch(StrMode)
	{
		case 'D':
		{
			//�j��
			//�h�b�g�G�̓��e ���s�����ł����Ɖ��s����
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

	//�`��
	SetDotString(px,py,col, DateS);
	//SetDotString("MYNAME\nYOSHI");

	return;
}

#define DOTASCII_H_DEFINED
#endif
