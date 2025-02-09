//ヘッダーファイル読み込み
#include "DxLib.h"
#include <math.h>

#include "MineSwepper_Set.h"

#define MineNum 70

//コンパイル時の警告表示抑制
#pragma warning( disable:4305 4244 4305 )

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	//■■■ここから(出力はbox関数以外使用禁止）
	//初期設定
	Init();

	//ゲーム用変数
	int MouseX, MouseY;
	int AroundBomb = 0;
	bool MakeFlag  = FALSE;
	bool GameOver  = FALSE;
	bool ClearFlag = FALSE;
	bool OpenFlag  = FALSE;
	bool StartFlag = TRUE;
	char Mes[256];

	//結果ファイル出力用変数
	FILE *fp;
	DATEDATA Date;
	int Round=0;
	int Win=0;

	//ハンドラ（int型）
	HANDLER Open_H		=LoadSoundMem("Open.wav");
	HANDLER GameOver_H	=LoadSoundMem("GameOver.wav");
	HANDLER Clear_H		=LoadSoundMem("Clear.wav");

	//メインループ
	while(ProcessMessage()==0 && CheckHitKey(KEY_INPUT_ESCAPE)==0)
	{
		ClsDrawScreen();		//描画する画面（裏）を黒クリア

		//マウス座標取得
		GetMousePoint(&MouseX, &MouseY);
		if(MouseX<0)		MouseX=0;
		if(MouseX>=1024)	MouseX=1023;
		if(MouseY<0)		MouseY=0;
		if(MouseY>=1024)	MouseY=1023;
		MouseX=MouseX/SQUARE_X_SIZE;
		MouseY=MouseY/SQUARE_Y_SIZE;

		//左クリック
		if(MouseStick(MOUSE_INPUT_LEFT))
		{
			if(MakeFlag)
			{
				MakeBomb(MouseX,MouseY, MineNum);
				MakeFlag=FALSE;
				OpenFlag=TRUE;
			}
			if(OpenFlag)
			{
				AroundBomb = LClickMineField(MouseX, MouseY);
				PlaySoundMem(Open_H, DX_PLAYTYPE_BACK);
			}
			if(GameOver)
			{
				OffFlag();
				MakeFlag=TRUE;
				GameOver=FALSE;
			}
			if(ClearFlag)
			{
				OffFlag();
				MakeFlag=TRUE;
				ClearFlag=FALSE;
			}
			if(StartFlag)
			{
				OffFlag();
				MakeFlag=TRUE;
				StartFlag=FALSE;
			}
			if(AroundBomb==-1)
			{
				GameOver=TRUE;
				OpenFlag=FALSE;
				PlaySoundMem(GameOver_H, DX_PLAYTYPE_BACK);
				AroundBomb=0;
				Round++;
			}
			if(CheckUnOpen()==MineNum)
			{
				ClearFlag=TRUE;
				OpenFlag=FALSE;
				PlaySoundMem(Clear_H, DX_PLAYTYPE_BACK);
				Win++;
				Round++;
			}
		}

		//右クリック
		if(MouseStick(MOUSE_INPUT_RIGHT))
		{
			if(OpenFlag)
			{
				RClickMineField(MouseX, MouseY);
				PlaySoundMem(Open_H, DX_PLAYTYPE_BACK);
			}
		}

		//表示文字列の処理
		if(StartFlag)										sprintf_s(Mes,256,"Mine\nSweeper");
		else if(GameOver)									sprintf_s(Mes,256,"GameOver");
		else if(ClearFlag)									sprintf_s(Mes,256,"Clear");
		else if(MineField[MouseX][MouseY].CheckedFlag==0)	sprintf_s(Mes,256,"? Bl:%d\n",CheckUnOpen()-MineNum);
		else												sprintf_s(Mes,256,"%d Bl:%d\n", MineField[MouseX][MouseY].AroundBomb, CheckUnOpen()-MineNum);

		//表示
		SetDrawField();
		if(StartFlag)					SetDotString(3, SCREEN_Y_SIZE/2-5, 0, Mes);
		else if(GameOver)				SetDotString(0, SCREEN_Y_SIZE/2-3, 0, Mes);
		else if(ClearFlag)				SetDotString(6, SCREEN_Y_SIZE/2-3, 0, Mes);
		else if(MouseY<SCREEN_X_SIZE/2)	SetDotString(0, SCREEN_Y_SIZE-5-1, 0, Mes);
		else							SetDotString(0, 1, 0, Mes);

		Draw();

		//表と裏（描画画面）の入れ換え
		ScreenFlip();
	}
	//メインループ終了

	//結果ファイル出力
	GetDateTime(&Date);
	fopen_s(&fp,"Result.txt", "a");
	fprintf(fp,"%d/%d/%d %d:%02d:%02d 爆弾の数：%d個、結果：%d戦中%d勝 勝率%.1f%%\n",
		Date.Year,
		Date.Mon,
		Date.Day,
		Date.Hour,
		Date.Min,
		Date.Sec,
		MineNum,
		Round,
		Win,
		(Round!=0) ? (((float)Win/Round)*100) : 0.0f
		);
	fclose(fp);

	//■■■ここまで

	DxLib_End();
	return 0;
}

//初期設定
void Init(void)
{
	//変更不可
	SetGraphMode( 1024,1024, 32 );
	ChangeWindowMode(TRUE);
	if( DxLib_Init()==-1) exit(-1);			//DXライブラリ初期化
	SetBackgroundColor(0,0,0);				//背景色
	SetDrawScreen(DX_SCREEN_BACK );			//裏画面に描画

	InitRand();
	Flag_AllChange(TRUE);

	SetFontSize(30);

	return;
}

//描画フラグをすべて変更する
void Flag_AllChange(bool Swt)
{
	int xi,yi;
	for(xi=0; xi<SCREEN_X_SIZE; xi++)
	{
		for(yi=0; yi<SCREEN_Y_SIZE; yi++)
		{
			Field[xi][yi].flag=Swt;
		}
	}

	return;
}

//描画
void Draw(void)
{
	int xi,yi, c;

	for(xi=0; xi<SCREEN_X_SIZE; xi++)
	{
		for(yi=0; yi<SCREEN_Y_SIZE; yi++)
		{
			if (Field[xi][yi].flag)
			{
				box(xi, yi, Field[xi][yi].Color);
				if (MineField[xi][yi].MarkedFlag == 1)
					DrawFormatString(xi * 32, yi * 32, GetColor(255, 255, 100), "！");
				if (MineField[xi][yi].AroundBomb > 0 && MineField[xi][yi].CheckedFlag == 1)
					DrawFormatString(xi * 32, yi * 32, GetColor(0, 0, 0), "%d", MineField[xi][yi].AroundBomb);
			}
		}
	}

	return;
}
