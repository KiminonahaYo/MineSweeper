#ifndef BACKGROUND_SET_H_DEFINED

#include "Defines.h"
#include "GetTimeArea.h"
#include "GetTimeForStd.h"

#define CENTER_X (SCREEN_X_SIZE/2)
#define CENTER_Y (SCREEN_Y_SIZE/2)

int BgColFlag[SCREEN_X_SIZE][SCREEN_Y_SIZE];

void GetBackGround(void);
void SetBackGround(void);

#define BACKGROUND_SET_H_DEFINED
#endif
