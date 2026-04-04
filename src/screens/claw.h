#ifndef CLAW_H
#define CLAW_H
#include "src/screens/head.h"
#include "src/ui/prize.h"
#include "src/ui/drawClaw.h"
#include "src/ui/tombolCapit.h"
#include "src/ui/bodyMesin.h"
#include "src/ui/joystick.h"
#include "src/ui/tombolOut.h"
#include "src/ui/indikatorSkor.h"
#include "src/screens/sound.h"
#include "src/effect/stonePrizeVfx.h"

// Definisi State Machine
typedef enum {
    STATE_IDLE,
    STATE_DROPPING,
    STATE_GRABBING,
    STATE_RETURNING,
    STATE_MOVING_HOME, 
    STATE_RELEASING    
} ClawState;

void InitClaw(void);
int DrawProgramClaw(void);

#endif