#ifndef MYMATH_DEFINED

#include <math.h>
#include <stdlib.h>
#include "GetTimeForStd.h"

//�v���g�^�C�v�錾
double Degsin(double);
double Degcos(double);
double round(double);
int RangeRand(int, int);
void InitRand(void);

//�W��rand()�֐��̏�����
void InitRand(void)
{
	DateAndTime Date;
	GetTime(&Date);
	srand( 
		Date.Hour*3600+
		Date.Min *60+
		Date.Sec
	);
	return;
}

//�͈͂��w�肵�ė����𔭐�
int RangeRand(int min, int max)
{
	if(min<=max)	return rand()%(max-min+1) + min;
	else			return -1;
}

//�f�O���[�Ŏw�肷��sin
double Degsin(double num)
{
	double RAD1=3.14159/180.0;
	return sin(RAD1*num);
}

//�f�O���[�Ŏw�肷��cos
double Degcos(double num)
{
	double RAD1=3.14159/180.0;
	return cos(RAD1*num);
}

//�l�̌ܓ�
double round(double num)
{
	if(num>=0)
	{
		if(num-int(num)>=0.5)	return double(int(num)+1);
		else					return double(int(num));
	}
	else
	{
		if(num-int(num)>=-0.5)	return double(int(num)-1);
		else					return double(int(num));
	}
}

#define MYMATH_DEFINED
#endif
