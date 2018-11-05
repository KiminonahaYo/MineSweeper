#ifndef EASYCOLOR_DEFINED
#define EASYCOLOR_DEFINED

int GetEasyColor(int);

int GetEasyColor(int Colnum)
{
	int clr;

	switch (Colnum)
	{
		case 0:
			clr = GetColor(0, 0, 0);
			break;
		case 1:
			clr = GetColor(255, 0, 0);
			break;
		case 2:
			clr = GetColor(0, 255, 0);
			break;
		case 3:
			clr = GetColor(0, 0, 255);
			break;
		case 4:
			clr = GetColor(255, 255, 0);
			break;
		case 5:
			clr = GetColor(255, 0, 255);
			break;
		case 6:
			clr = GetColor(0, 255, 255);
			break;
		case 7:
			clr = GetColor(255, 255, 255);
			break;
		default:
			clr = GetColor(0, 0, 0);
	}

	return clr;
}

#endif