#ifndef P1_FSM_H_
#define P1_FSM_H_

#include "ARM_inits.h"
#include "globais.h"
#include "NOKIA5110_fb.h"

// Machine State Prototypes
void Sm_P1_MENU(void);
void Sm_P1_RoundStart(void);
void Sm_P1_Idle(void);
void Sm_P1_Idle_Recover(void);
void Sm_P1_Forward(void);
void Sm_P1_DashForward(void);
void Sm_P1_Back(void);
void Sm_P1_DashBack(void);
void Sm_P1_ATK1(void);
void Sm_P1_ATK2(void);
void Sm_P1_ATK1_Recover(void);
void Sm_P1_ATK2_Recover(void);
void Sm_P1_Hit(void);
void Sm_P1_Block(void);
void Sm_P1_Dying(void);
void Sm_P1_Dead(void);
void Rodar_Maquina_P1(void);

// and end with:
#endif
