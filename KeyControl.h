//DxLib専用

#ifndef KEYCONTROL_DEFINED

bool Stick(int, bool);
bool MouseStick(int);

//キー入力関数
//一度受け入れて、しばらくしてまた受け入れるようにした
bool Stick(int KeyCode, bool ForSelectStickFlag=0)
{
	//キー入力情報を静的確保
	static char PushedKey[256];
	static char PushCount[256];

	if(CheckHitKey(KeyCode))
	{
		PushCount[KeyCode]++;
		if(PushedKey[KeyCode]==0 
			|| ( ForSelectStickFlag && (PushCount[KeyCode]==1 || PushCount[KeyCode]>=30)) )
		{
			PushedKey[KeyCode]=1;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		PushCount[KeyCode]=0;
		PushedKey[KeyCode]=0;
		return FALSE;
	}
}
bool MouseStick(int KeyCode)
{
	static char PushedKey[8];
	int InputState = GetMouseInput();
	int Key=(int)( log( (double)KeyCode )/log(2.0) );
	int KeyFlag = InputState & KeyCode;

	if(KeyFlag)
	{
		if(PushedKey[Key]==0)
		{
			PushedKey[Key]=1;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		PushedKey[Key]=0;
		return FALSE;
	}
}

#define KEYCONTROL_DEFINED
#endif
