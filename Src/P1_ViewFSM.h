#ifndef P1View_FSM_H_
#define P1View_FSM_H_

#include "ARM_inits.h"
#include "globais.h"
#include "NOKIA5110_fb.h"
#define updateRate 120
// Machine State Prototypes
void Sm_P1View_MENU(void);
void Sm_P1View_RoundStart(void);
void Sm_P1View_Idle(void);
void Sm_P1View_Idle_Recover(void);
void Sm_P1View_Forward(void);
void Sm_P1View_DashForward(void);
void Sm_P1View_Back(void);
void Sm_P1View_DashBack(void);
void Sm_P1View_ATK1(void);
void Sm_P1View_ATK2(void);
void Sm_P1View_ATK1_Recover(void);
void Sm_P1View_ATK2_Recover(void);
void Sm_P1View_Hit(void);
void Sm_P1View_Block(void);
void Sm_P1View_Dying(void);
void Sm_P1View_Dead(void);
void Rodar_Maquina_P1View(void);

// and end with:
#endif
