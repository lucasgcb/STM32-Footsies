#ifndef MenuFSM_H_
#define MenuFSM_H_

#include "ARM_inits.h"
#include "NOKIA5110_fb.h"
#include "globais.h"


// Machine State Prototypes
void Sm_PowerOn(void);
void Sm_Menu(void);
void Sm_Menu1P(void);
void Sm_Menu2P(void);
void Sm_Arena1P_RoundStart(void);
void Sm_Arena1P_ONGOING(void);
void Sm_Arena2P_RoundStart(void);
void Sm_Arena2P_ONGOING(void);
void print_roundstart(void);
void Sm_GameOver(void);
void Rodar_Maquina_Menu(void);

// and end with:
#endif
