#ifndef MYTIMEFORSTD_DEFINED

#include <time.h>
#include <stdio.h>
#include <string.h>

//時間取得のための構造体
typedef struct
{
	int Year, Mon, Day;
	int Hour, Min, Sec;
	int Week;
}
DateAndTime;

//プロトタイプ宣言
void GetTime(DateAndTime *);
char *GetWeek(int, char *);

int  Get12Hour(int);
char *GetAMorPM(int);

char *GetJapaneseYear(int,char *);

//時間取得をしやすくする関数
void GetTime(DateAndTime *Date)
{
	time_t timer;
	struct tm local;

	timer = time(NULL);
	localtime_s(&local,&timer);

	Date->Year   = local.tm_year+1900;
	Date->Mon    = local.tm_mon+1;
	Date->Day    = local.tm_mday;
	Date->Hour   = local.tm_hour;
	Date->Min    = local.tm_min;
	Date->Sec    = local.tm_sec;
	Date->Week   = local.tm_wday;

	return;
}

//GetTime()関数で得た曜日のフラグを与えて文字列で返す関数
//JS_S:日本語ショート、	JS:日本語
//US_S:英語ショート、	US:英語
char *GetWeek(int WeekDayFlag, char *Mode)
{
	if(strcmp(Mode,"JS_S")==0)
	{
		switch(WeekDayFlag)
		{
			case 0: return "日"; break;
			case 1: return "月"; break;
			case 2: return "火"; break;
			case 3: return "水"; break;
			case 4: return "木"; break;
			case 5: return "金"; break;
			case 6: return "土"; break;
			default: return ""; break;
		}
	}
	else if(strcmp(Mode,"JS")==0)
	{
		switch(WeekDayFlag)
		{
			case 0: return "日曜日"; break;
			case 1: return "月曜日"; break;
			case 2: return "火曜日"; break;
			case 3: return "水曜日"; break;
			case 4: return "木曜日"; break;
			case 5: return "金曜日"; break;
			case 6: return "土曜日"; break;
			default: return ""; break;
		}
	}
	else if(strcmp(Mode,"US_S")==0)
	{
		switch(WeekDayFlag)
		{
			case 0: return "Sun"; break;
			case 1: return "Mon"; break;
			case 2: return "Tue"; break;
			case 3: return "Wed"; break;
			case 4: return "Thu"; break;
			case 5: return "Fri"; break;
			case 6: return "Sat"; break;
			default: return ""; break;
		}
	}
	else if(strcmp(Mode,"US")==0)
	{
		switch(WeekDayFlag)
		{
			case 0: return "Sunday"; break;
			case 1: return "Monday"; break;
			case 2: return "Tuesday"; break;
			case 3: return "Wednesday"; break;
			case 4: return "Thursday"; break;
			case 5: return "Friday"; break;
			case 6: return "Saturday"; break;
			default: return ""; break;
		}
	}
	else
	{
		return "";
	}
}

//12時間表示にする
int Get12Hour(int Hour)
{
	return Hour%12;
}

//AM-PMを取得する
char *GetAMorPM(int Hour)
{
	return (Hour/12==0 ? "AM" : (Hour/12==1 ? "PM" : ""));
}

//年号を取得する
char *GetJapaneseYear(int Year,char *Mode)
{
	static char Ret[64];
	char *Nengo;
	int JYear;

	if(Year>=1900)
	{
		if(strcmp(Mode,"A")==0)
		{
			if(Year<1912)		Nengo="M";
			else if(Year<1926)	Nengo="T";
			else if(Year<1989)	Nengo="S";
			else				Nengo="H";
		}
		else if(strcmp(Mode,"K")==0)
		{
			if(Year<1912)		Nengo="明治";
			else if(Year<1926)	Nengo="大正";
			else if(Year<1989)	Nengo="昭和";
			else				Nengo="平成";
		}
		else return "";

		if(Year<1912)		JYear=Year-1868+1;
		else if(Year<1926)	JYear=Year-1912+1;
		else if(Year<1989)	JYear=Year-1926+1;
		else				JYear=Year-1989+1;

		sprintf_s(Ret,64, "%s%d",Nengo,JYear);

		return Ret;
	}
	else
	{
		return "";
	}
}

#define MYTIMEFORSTD_DEFINED
#endif
