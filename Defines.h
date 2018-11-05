//���ʂŎg�����ƂɂȂ�萔�A�ϐ�
#ifndef DEFINES_H_DEFINED

#include "MyMath.h"

#define SCREEN_X_SIZE 32
#define SCREEN_Y_SIZE 32
#define SQUARE_X_SIZE (1024/SCREEN_X_SIZE)
#define SQUARE_Y_SIZE (1024/SCREEN_Y_SIZE)

typedef int HANDLER;

typedef struct
{
	int Color;
	bool flag;
}
FIELD;

typedef struct
{
	int AroundBomb;		//���e�Ȃ�-1, �����łȂ���Ύ���̔��e�̐�
	int CheckedFlag;	//�J�����u���b�N���ǂ����̃t���O
	int MarkedFlag;		//���e�t���O�i�\�z�j
}
MINEFIELD;

FIELD Field[SCREEN_X_SIZE][SCREEN_Y_SIZE];
MINEFIELD MineField[SCREEN_X_SIZE][SCREEN_Y_SIZE] = { 0 };

int ColorCode[5] = { 6, 3, 2, 4, 1 };

#define DEFINES_H_DEFINED
#endif
