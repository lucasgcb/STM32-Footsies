#include "MenuFSM.h"


uint8_t round_count = 0;
uint8_t round_countP1 = 0;
uint8_t round_countP2 = 0;
typedef struct
{
	StateType_Menu State;
	void (*func)(void);
}StateMachineType_Menu;

StateMachineType_Menu StateMachine_Menu[] =
{
		{ STATE_PowerOn, Sm_PowerOn },
		{ STATE_Menu, Sm_Menu },
		{ STATE_Menu1P, Sm_Menu1P },
		{ STATE_Menu2P, Sm_Menu2P },
		{ STATE_Arena1P_RoundStart, Sm_Arena1P_RoundStart },
		{ STATE_Arena1P_ONGOING, Sm_Arena1P_ONGOING },
		{ STATE_Arena2P_RoundStart, Sm_Arena2P_RoundStart },
		{ STATE_Arena2P_ONGOING, Sm_Arena2P_ONGOING },
		{ STATE_GameOver, Sm_GameOver },
};

StateType_Menu SmState_Menu = STATE_PowerOn;

void Sm_PowerOn(void)
{

	pontos_t p = {10,0,0,0,0,0};
	print_figura_seguro(&p, &xablauSoft);
	//pontos_t p = {5,5,10,10,15,15};
	//print_figura_seguro(&p, &fig1);
	osDelay(100);
	deleta_figura_seguro(&p, &xablauSoft);
	SmState_Menu = STATE_Menu;
}
void Sm_Menu(void)
{
	pontos_t p = {0,0,0,0,0,0};
	print_figura_seguro(&p, &mainMenu);
	SmState_Menu=STATE_Menu1P;
}

void Sm_Menu1P(void)
{
	pontos_t pmenu = {0,0,0,0,0,0};
	pontos_t p = {8,38,0,0,0,0};
	print_figura_seguro(&p, &cursor);
	if(SmState_Int1==STATE_ATKPressed_Int1)
	{
		round_count = 0;
		round_countP1 = 0;
		round_countP2 = 0;
		deleta_figura_seguro(&pmenu, &mainMenu);
		deleta_figura_seguro(&p, &cursor);
		SmState_Menu = STATE_Arena1P_RoundStart;
		SmState_Bot1 = STATE_OBSERVE;
	}
	if(SmState_Int1==STATE_RightPressed_Int1)
	{
		deleta_figura_seguro(&p, &cursor);
		SmState_Menu = STATE_Menu2P;
	}
}

void Sm_Menu2P(void)
{

	pontos_t pmenu = {0,0,0,0,0,0};
	pontos_t p = {60,38,0,0,0,0};
	print_figura_seguro(&p, &cursor);
	if(SmState_Int1==STATE_ATKPressed_Int1)
	{
		round_count = 0;
		round_countP1 = 0;
		round_countP2 = 0;
		deleta_figura_seguro(&p, &cursor);
		deleta_figura_seguro(&pmenu, &mainMenu);
		SmState_Bot1 = STATE_OBSERVE;
		SmState_Menu = STATE_Arena2P_RoundStart;
	}
	if(SmState_Int1==STATE_LeftPressed_Int1)
	{
		deleta_figura_seguro(&p, &cursor);
		SmState_Menu = STATE_Menu1P;

	}
}

void print_rounds(void)
{
	pontos_t W1 = {0,0,0,0,0,0};
	pontos_t W2 = {9,0,0,0,0,0};
	pontos_t W3 = {18,0,0,0,0,0};
	switch(round_countP1)
	{
		case 0:
				print_figura_seguro(&W1, &round_empty);
				print_figura_seguro(&W2, &round_empty);
				print_figura_seguro(&W3, &round_empty);
				break;
		case 1:
				print_figura_seguro(&W1, &round_win);
				break;
		case 2:
				print_figura_seguro(&W2, &round_win);
				break;
		case 3:
				print_figura_seguro(&W3, &round_win);
				break;
		default:
				deleta_figura_seguro(&W1, &round_empty);
				deleta_figura_seguro(&W2, &round_empty);
				deleta_figura_seguro(&W3, &round_empty);
	}
	W1.x1 = W1.x1 + 50;
	W2.x1 = W2.x1 + 50;
	W3.x1 = W3.x1 + 50;
	switch(round_countP2)
	{
		case 0:
				print_figura_seguro(&W1, &round_empty);
				print_figura_seguro(&W2, &round_empty);
				print_figura_seguro(&W3, &round_empty);
				break;
		case 1:
				print_figura_seguro(&W1, &round_win);
				break;
		case 2:
				print_figura_seguro(&W2, &round_win);
				break;
		case 3:
				print_figura_seguro(&W3, &round_win);
				break;
		default:
				deleta_figura_seguro(&W1, &round_empty);
				deleta_figura_seguro(&W2, &round_empty);
				deleta_figura_seguro(&W3, &round_empty);
	}
}

void print_roundstart(void)
{
	print_rounds();
	pontos_t pr = {20,10,0,0,0,0};
	pontos_t pb = {20,20,0,0,0,0};
	print_figura_seguro(&pr, &ROUND);
	pontos_t p = {65,5,0,0,0,0};
	switch(round_count + 1)
	{
		case 1:
					print_figura_seguro(&p, &um);
					osDelay(500);
					print_figura_seguro(&pb, &BRIGUE);
					osDelay(1000);
					deleta_figura_seguro(&p, &um);
					break;
		case 2:
					print_figura_seguro(&p, &dois);
					osDelay(500);
					print_figura_seguro(&pb, &BRIGUE);
					osDelay(1000);
					deleta_figura_seguro(&p, &dois);
					break;
		case 3:
					print_figura_seguro(&p, &tres);
					osDelay(500);
					print_figura_seguro(&pb, &BRIGUE);
					osDelay(1000);
					deleta_figura_seguro(&p, &tres);
					break;
		case 4:
					print_figura_seguro(&p, &quatro);
					osDelay(500);
					print_figura_seguro(&pb, &BRIGUE);
					osDelay(1000);
					deleta_figura_seguro(&p, &quatro);
					break;
		default:
					break;
	}
	deleta_figura_seguro(&pb, &BRIGUE);
	deleta_figura_seguro(&pr, &ROUND);

	print_rounds();
}
void Sm_Arena1P_RoundStart(void)
{
	SmState_P1 = STATE_PLAYER_RoundStart;
	SmState_P2 = STATE_PLAYER_RoundStart;
	print_roundstart();
	SmState_Menu = STATE_Arena1P_ONGOING;
}

void Sm_Arena1P_ONGOING(void)
{

	SmState_Menu = STATE_Arena1P_ONGOING;
	osDelay(1);
	if(SmState_P2 == STATE_PLAYER_Dead)
	{
		osDelay(300);
		round_count++;
		round_countP1++;
		print_rounds();
		if(round_countP1<3)
			SmState_Menu = STATE_Arena1P_RoundStart;
		else
			SmState_Menu = STATE_GameOver;
	}

	if(SmState_P1 == STATE_PLAYER_Dead)
	{
		osDelay(300);
		round_count++;
		round_countP2++;
		print_rounds();
		if(round_countP2<3)
			SmState_Menu = STATE_Arena1P_RoundStart;
		else
			SmState_Menu = STATE_GameOver;
	}
	/*if(SmState_Int1==STATE_LeftPressed_Int1)
			SmState_Menu = STATE_GameOver;*/
}

void Sm_Arena2P_RoundStart(void)
{
	SmState_P1 = STATE_PLAYER_RoundStart;
	SmState_P2 = STATE_PLAYER_RoundStart;
	print_roundstart();
	SmState_Menu = STATE_Arena2P_ONGOING;
}

void Sm_Arena2P_ONGOING(void)
{
	if(SmState_P1 == STATE_PLAYER_Dead)
	{
		osDelay(300);
		round_count++;
		round_countP1++;
		SmState_Menu = STATE_Arena2P_RoundStart;
	}
	/*print_seguro(10,3,"             ");
	print_seguro(6,3,"2P GAME ON");*/
	/*if(SmState_Int1==STATE_RightPressed_Int1)
			SmState_Menu = STATE_GameOver;*/
}



void Sm_GameOver(void)
{
	SmState_P1 = STATE_PLAYER_CLEAN;
	SmState_P2 = STATE_PLAYER_CLEAN;
	print_seguro(10,3,"             ");
	print_seguro(10,3,"gg ai man");

	osDelay(1000);
	SmState_Menu = STATE_Menu;
}

void Rodar_Maquina_Menu(void)
{
	osDelay(10);
	if(SmState_Menu < NUM_STATES_Menu)
	{
		(*StateMachine_Menu[SmState_Menu].func)();
	}
	else
	{
		return;
	}
}
