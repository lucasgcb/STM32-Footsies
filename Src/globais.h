#ifndef globais_H_
#define globais_H_
#define DEBUG_P2

typedef struct pontos{
	uint32_t x1;
	uint32_t y1;
	uint32_t x2;
	uint32_t y2;
	uint32_t x3;
	uint32_t y3;
} pontos_t;

typedef struct figura
{
	unsigned char largura;
	unsigned char altura;
	unsigned char pixels[];
} figura_t;


typedef enum
{
	STATE_BotaoON,
	STATE_DEBOUNCE,
	STATE_BotaoOFF,
	NUM_STATES
}StateType_Botao1;

typedef enum
{
	STATE_Right_Int1,
	STATE_RightPressed_Int1,
	STATE_Left_Int1,
	STATE_LeftPressed_Int1,
	STATE_NeutralPressed_Int1,
	STATE_Neutral_Int1,
	STATE_DEBOUNCE_Int1,
	STATE_ATK_Int1,
	STATE_ATKPressed_Int1,
	STATE_Edge_Int1,
	NUM_STATES_Int1
}StateType_Int1;

typedef enum
{
	STATE_Right_Int2,
	STATE_RightPressed_Int2,
	STATE_Left_Int2,
	STATE_LeftPressed_Int2,
	STATE_NeutralPressed_Int2,
	STATE_Neutral_Int2,
	STATE_DEBOUNCE_Int2,
	STATE_ATK_Int2,
	STATE_ATKPressed_Int2,
	STATE_Edge_Int2,
	NUM_STATES_Int2
}StateType_Int2;
typedef enum
{
	STATE_PLAYER_MENU,
	STATE_PLAYER_RoundStart,
	STATE_PLAYER_Idle,
	STATE_PLAYER_Idle_Recover,
	STATE_PLAYER_Forward,
	STATE_PLAYER_DashForward,
	STATE_PLAYER_Back,
	STATE_PLAYER_DashBack,
	STATE_PLAYER_ATK1,
	STATE_PLAYER_ATK1_Recover,
	STATE_PLAYER_ATK2,
	STATE_PLAYER_ATK2_Recover,
	STATE_PLAYER_Block,
	STATE_PLAYER_Hit,
	STATE_PLAYER_Dying,
	STATE_PLAYER_Dead,
	NUM_STATES_PLAYER
}StateType_PLAYER;

typedef enum
{
	STATE_PowerOn,
	STATE_Menu,
	STATE_Menu1P,
	STATE_Menu2P,
	STATE_Arena1P_RoundStart,
	STATE_Arena1P_ONGOING,
	STATE_Arena2P_RoundStart,
	STATE_Arena2P_ONGOING,
	STATE_GameOver,
	NUM_STATES_Menu
}StateType_Menu;


extern StateType_Botao1 SmState_Botao1;
extern StateType_Menu SmState_Menu;
extern StateType_Int1 SmState_Int1;
extern StateType_PLAYER SmState_P1;
extern char  input_buffer1[12];
extern char  input_buffer2[12];
extern const figura_t fig1;
extern uint8_t round_count;
void AdicionarNaLista1(char *add);
char  lerDoInput1(uint8_t index);
#endif
