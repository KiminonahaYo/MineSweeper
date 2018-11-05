#ifndef RUNSWEPPER_SET_H_DEFINED

#include "Defines.h"
#include "MyMath.h"

void MakeBomb(int,int, int);
void SetDrawField(void);
int LClickMineField(int,int);
void RClickMineField(int,int);
void OpenMineField(int,int);
void OffFlag(void);
int CheckUnOpen(void);

#define RUNSWEPPER_SET_H_DEFINED
#endif
