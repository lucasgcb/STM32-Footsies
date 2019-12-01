#ifndef P2_FSM_H_
#define P2_FSM_H_

#include "ARM_inits.h"
#include "globais.h"
#include "NOKIA5110_fb.h"

// Machine State Prototypes
void Sm_P2_MENU(void);
void Sm_P2_RoundStart(void);
void Sm_P2_Idle(void);
void Sm_P2_Idle_Recover(void);
void Sm_P2_Forward(void);
void Sm_P2_DashForward(void);
void Sm_P2_Back(void);
void Sm_P2_DashBack(void);
void Sm_P2_ATK1(void);
void Sm_P2_ATK2(void);
void Sm_P2_ATK1_Recover(void);
void Sm_P2_ATK2_Recover(void);
void Sm_P2_Hit(void);
void Sm_P2_Block(void);
void Sm_P2_Dying(void);
void Sm_P2_Dead(void);
void Sm_P2_CLEAN(void);
void Rodar_Maquina_P2(void);

// and end with:
#endif
