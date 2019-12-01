#ifndef P2View_FSM_H_
#define P2View_FSM_H_

#include "ARM_inits.h"
#include "globais.h"
#include "NOKIA5110_fb.h"
#define updateRate 120
// Machine State Prototypes
void Sm_P2View_MENU(void);
void Sm_P2View_RoundStart(void);
void Sm_P2View_Idle(void);
void Sm_P2View_Idle_Recover(void);
void Sm_P2View_Forward(void);
void Sm_P2View_DashForward(void);
void Sm_P2View_Back(void);
void Sm_P2View_DashBack(void);
void Sm_P2View_ATK1(void);
void Sm_P2View_ATK2(void);
void Sm_P2View_ATK1_Recover(void);
void Sm_P2View_ATK2_Recover(void);
void Sm_P2View_Hit(void);
void Sm_P2View_Block(void);
void Sm_P2View_Dying(void);
void Sm_P2View_Dead(void);
void Sm_P2View_CLEAN(void);
void Rodar_Maquina_P2View(void);

// and end with:
#endif
