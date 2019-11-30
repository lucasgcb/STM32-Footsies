#ifndef Int2FSM_H_
#define Int2FSM_H_

#include "ARM_inits.h"
#include "NOKIA5110_fb.h"
#include "globais.h"
#define DIREITA_FRENTE_2 6
#define ESQUER_ATRAS_2 4
#define NEUTRO_2 5
#define ATK_2 0

#define DELAY_INT2 5
// Machine State Prototype
void Sm_RightPressed_Int2(void);
void Sm_Right_Int2(void);
void Sm_NeutralPressed_Int2(void);
void Sm_Neutral_Int2(void);
void Sm_LeftPressed_Int2(void);
void Sm_Left_Int2(void);
void Sm_ATKPressed_Int2(void);
void Sm_Edge_Int2(void);
void Sm_ATK_Int2(void);
void Sm_DEBOUNCE_Int2(void);
void Sm_REBOUNCE_Int2(void);
void AdicionarNaLista2(char *add);
char  lerDoInput2(uint8_t index);
uint32_t P2_INTERPRETER(uint32_t value);
void Rodar_Maquina_Interpretador2(void);

// and end with:
#endif
