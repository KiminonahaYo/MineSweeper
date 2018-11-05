#ifndef RUNSWEPPER_H_DEFINED

#include "RunSwepper_Set.h"

//フィールド作成（爆弾作成）
void MakeBomb(int mx, int my, int num)
{
	int rx,ry;
	int xi,yi;
	int rot;
	int rotx, roty;
	int aroundflag;

	//初期化
	for(xi=0; xi<SCREEN_X_SIZE; xi++)
	{
		for(yi=0; yi<SCREEN_Y_SIZE; yi++)
		{
			MineField[xi][yi].AroundBomb=0;
			MineField[xi][yi].CheckedFlag=0;
			MineField[xi][yi].MarkedFlag=0;
		}
	}

	//爆弾作成
	while(num>0)
	{
		rx = RangeRand(0,SCREEN_X_SIZE-1);
		ry = RangeRand(0,SCREEN_Y_SIZE-1);

		for(rot=0; rot<9; rot++)
		{
			switch(rot)
			{
				case 0: rotx=+0; roty=-1; break;
				case 1: rotx=+1; roty=-1; break;
				case 2: rotx=+1; roty=+0; break;
				case 3: rotx=+1; roty=+1; break;
				case 4: rotx=+0; roty=+1; break;
				case 5: rotx=-1; roty=+1; break;
				case 6: rotx=-1; roty=+0; break;
				case 7: rotx=-1; roty=-1; break;
				case 8: rotx=+0; roty=+0; break;
			}
			if(rx+rotx==mx || ry+roty==my)break;
		}
		if(rot==9)	aroundflag=0;
		else		aroundflag=1;


		if(MineField[rx][ry].AroundBomb==0 && aroundflag==0)
		{
			MineField[rx][ry].AroundBomb=-1;
			num--;
		}
	}

	//周りの爆弾を数える
	for(xi=0; xi<SCREEN_X_SIZE; xi++)
	{
		for(yi=0; yi<SCREEN_Y_SIZE; yi++)
		{
			if(MineField[xi][yi].AroundBomb!=-1)
			{
				for(rot=0; rot<8; rot++)
				{
					switch(rot)
					{
						case 0: rotx=+0; roty=-1; break;
						case 1: rotx=+1; roty=-1; break;
						case 2: rotx=+1; roty=+0; break;
						case 3: rotx=+1; roty=+1; break;
						case 4: rotx=+0; roty=+1; break;
						case 5: rotx=-1; roty=+1; break;
						case 6: rotx=-1; roty=+0; break;
						case 7: rotx=-1; roty=-1; break;
					}
					if(
						xi+rotx>=0 && xi+rotx<SCREEN_X_SIZE &&
						yi+roty>=0 && yi+roty<SCREEN_X_SIZE &&
						MineField[xi+rotx][yi+roty].AroundBomb==-1
					)
					MineField[xi][yi].AroundBomb++;
				}
			}
		}
	}

	return;
}

//左クリック処理
int LClickMineField(int MouseX, int MouseY)
{
	if(MineField[MouseX][MouseY].MarkedFlag==0)
	{
		OpenMineField(MouseX, MouseY);
		return MineField[MouseX][MouseY].AroundBomb;
	}
	else
	{
		return -2;
	}
}

//右クリック処理
void RClickMineField(int MouseX, int MouseY)
{
	if(MineField[MouseX][MouseY].CheckedFlag==0)
		MineField[MouseX][MouseY].MarkedFlag = !MineField[MouseX][MouseY].MarkedFlag;

	return;
}

//再帰呼び出しでブロックを開く
void OpenMineField(int px, int py)
{
	if(px<0 || px>=SCREEN_X_SIZE || py<0 || py>=SCREEN_Y_SIZE)
		return;
	if(MineField[px][py].CheckedFlag==1)
		return;
	if(MineField[px][py].MarkedFlag==1)
		return;
	MineField[px][py].CheckedFlag=1;

	if(MineField[px][py].AroundBomb==0)
	{
		OpenMineField(px-1,py  );
		OpenMineField(px+1,py  );
		OpenMineField(px  ,py-1);
		OpenMineField(px  ,py+1);
		OpenMineField(px-1,py-1);
		OpenMineField(px-1,py+1);
		OpenMineField(px+1,py-1);
		OpenMineField(px+1,py+1);
	}

	return;
}

//フラグをオフにする
void OffFlag(void)
{
	int xi,yi;

	for(xi=0; xi<SCREEN_X_SIZE; xi++)
	{
		for(yi=0; yi<SCREEN_X_SIZE; yi++)
		{
			MineField[xi][yi].CheckedFlag=0;
			MineField[xi][yi].MarkedFlag=0;
		}
	}

	return;
}

//開いていないブロックを数える
int CheckUnOpen(void)
{
	int xi,yi, cnt=0;

	for(xi=0; xi<SCREEN_X_SIZE; xi++)
		for(yi=0; yi<SCREEN_X_SIZE; yi++)
			if(MineField[xi][yi].CheckedFlag==0)
				cnt++;

	return cnt;
}

//配列に描画対象を格納する
void SetDrawField(void)
{
	int xi,yi;
	int col;
	int cflag;
	int mflag;

	for(xi=0; xi<SCREEN_X_SIZE; xi++)
	{
		for(yi=0; yi<SCREEN_Y_SIZE; yi++)
		{
			col = MineField[xi][yi].AroundBomb;
			cflag = MineField[xi][yi].CheckedFlag;
			mflag = MineField[xi][yi].MarkedFlag;

			if(mflag==1)
			{
				Field[xi][yi].Color=5;
			}
			else if(cflag==0)
			{
				Field[xi][yi].Color=7;
			}
			else if(col==-1)
			{
				Field[xi][yi].Color=ColorCode[4];
			}
			else if (col > 0)
			{
				Field[xi][yi].Color = ColorCode[2];
			}
			else
			{
				Field[xi][yi].Color = ColorCode[0];
			}
		}
	}
}

#define RUNSWEPPER_H_DEFINED
#endif