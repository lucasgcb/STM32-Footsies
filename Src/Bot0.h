#ifndef Bot_FSM_H_
#define Bot_FSM_H_

#include "ARM_inits.h"
#include "globais.h"
#include "NOKIA5110_fb.h"
#define updateRate 100

void Sm_OFFLINE0(void);
void Sm_APPROACH0(void);
void Sm_RETREAT0(void);
void Sm_MOVETOPUNISH0(void);
void Sm_ATTACK0(void);
void Sm_RETREAT0(void);
void Sm_COMBO0(void);
void Sm_BAIT0(void);
void Sm_DEFEND0(void);
void Sm_OBSERVE0(void);
// Mexe no Interpretador2 e InputBuffer 2
#endif
