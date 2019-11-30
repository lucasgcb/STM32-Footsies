#ifndef Botao1FSM_H_
#define Botao1FSM_H_
#define BOTAO_DEBOUNCE 10
#include "ARM_inits.h"
#include "NOKIA5110_fb.h"
#include "globais.h"

// Machine State Prototypes
void Sm_BotaoON(void);
void Sm_DEBOUNCE(void);
void Sm_BotaoOFF(void);
void ObservaBotao(void const * argument);
void Rodar_Maquina_Botao1(void);

// and end with:
#endif
