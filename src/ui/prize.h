#ifndef PRIZE_H
#define PRIZE_H
#include "src/screens/head.h"

#define MAX_PRIZES 25

typedef struct {
    float x, y;
    int radius;
    Color color;
    int isCaught;
    int isWon;
    int type; // 0 = hadiah biasa, 1 = batu, 2 = boneka
} Prize;

void DrawPrize(Prize p);

#endif