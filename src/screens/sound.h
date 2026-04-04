#ifndef SOUND_H
#define SOUND_H
#include "src/screens/head.h"

void InitGameAudio(void);
void PlayMenuBGM(void);
void PlayClawBGM(void);
void UpdateGameAudio(Screen current);
void UnloadGameAudio(void);              
void PlaySfxDown(void);
void PlaySfxUp(void);
void PlaySfxPrize(void);
void UpdateSfxRail(int isMoving);
void PlaySfxSoundBatu(void);
void PlaySfxButton(void);

#endif