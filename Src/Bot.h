#ifndef Bot_FSM_H_
#define Bot_FSM_H_

#include "ARM_inits.h"
#include "globais.h"
#include "NOKIA5110_fb.h"
#define updateRate 120

void Sm_OFFLINE(void);
void Sm_APPROACH(void);
void Sm_RETREAT(void);
void Sm_MOVETOPUNISH(void);
void Sm_ATTACK(void);
void Sm_RETREAT(void);
void Sm_COMBO(void);
void Sm_BAIT(void);
void Sm_DEFEND(void);
void Sm_OBSERVE(void);
char  lerDoInput2(uint8_t index);
void AdicionarNaLista1(char *add);
void Rodar_Maquina_Bot1(void);
// Mexe no Interpretador2 e InputBuffer 2
#endif
