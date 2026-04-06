#ifndef PRIZE_H
#define PRIZE_H
#include "src/screens/head.h"

#define MAX_PRIZES 27

typedef struct {
    float x, y;
    int radius;
    Color color;
    int isCaught;
    int isWon;
    int type; 
} Prize;

void DrawPrize(Prize p);

#endif