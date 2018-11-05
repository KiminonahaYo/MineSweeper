#ifndef GETTIMEAREA_H_DEFINED

#include "GetTimeForStd.h"
#include "Defines.h"

typedef enum
{
	TIME_NULL,
	TIME_ASA,
	TIME_HIRU,
	TIME_YUU,
	TIME_YORU
}
TIMEAREA;

bool GetTimeColor(int*, char);
TIMEAREA GetTimeArea(void);

bool GetTimeColor(int *col, char Mode)
{
	TIMEAREA Area = GetTimeArea();

	switch(Mode)
	{
		case 'b':
			switch(Area)
			{
				case TIME_ASA:	col[0]=ColorCode[2]; col[1]=ColorCode[3]; col[2]=ColorCode[4]; break;
				case TIME_HIRU:	col[0]=ColorCode[2]; col[1]=ColorCode[4]; col[2]=ColorCode[3]; break;
				case TIME_YUU:	col[0]=ColorCode[1]; col[1]=ColorCode[1]; col[2]=ColorCode[0]; break;
				case TIME_YORU:	col[0]=ColorCode[1]; col[1]=ColorCode[1]; col[2]=ColorCode[5]; break;
			}
			break;
		case 's':
			switch(Area)
			{
				case TIME_ASA:	*col=7; break;
				case TIME_HIRU:	*col=ColorCode[1]; break;
				case TIME_YUU:	*col=ColorCode[4]; break;
				case TIME_YORU:	*col=ColorCode[4]; break;
			}
			break;
		default: return FALSE;
	}

	return TRUE;
}

TIMEAREA GetTimeArea(void)
{
	DateAndTime Date;

	GetTime(&Date);

	if(Date.Hour>=6 && Date.Hour<10)		return TIME_ASA;
	else if(Date.Hour>=10 && Date.Hour<15)	return TIME_HIRU;
	else if(Date.Hour>=15 && Date.Hour<18)	return TIME_YUU;
	else									return TIME_YORU;
}

#define GETTIMEAREA_H_DEFINED
#endif
