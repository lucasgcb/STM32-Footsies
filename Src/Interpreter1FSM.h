#ifndef Int1FSM_H_
#define Int1FSM_H_

#include "ARM_inits.h"
#include "NOKIA5110_fb.h"
#include "globais.h"
#define DIREITA_FRENTE_1 6
#define ESQUER_ATRAS_1 4
#define NEUTRO_1 5
#define ATK_1 0

#define DELAY_INT1 5
// Machine State Prototype
void Sm_RightPressed_Int1(void);
void Sm_Right_Int1(void);
void Sm_NeutralPressed_Int1(void);
void Sm_Neutral_Int1(void);
void Sm_LeftPressed_Int1(void);
void Sm_Left_Int1(void);
void Sm_ATKPressed_Int1(void);
void Sm_Edge_Int1(void);
void Sm_ATK_Int1(void);
void Sm_DEBOUNCE_Int1(void);
void Sm_REBOUNCE_Int1(void);
void AdicionarNaLista1(char *add);
char  lerDoInput1(uint8_t index);
uint32_t P1_INTERPRETER(uint32_t value);
void Rodar_Maquina_Interpretador(void);

// and end with:
#endif
