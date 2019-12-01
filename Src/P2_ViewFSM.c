#include "P2_ViewFSM.h"
typedef struct
{
	StateType_PLAYER State;
	void (*func)(void);
}StateMachineType_P2;

StateMachineType_P2 StateMachine_P2View[] =
{
		{STATE_PLAYER_MENU, Sm_P2View_MENU},
		{STATE_PLAYER_RoundStart, Sm_P2View_RoundStart},
		{STATE_PLAYER_Idle, Sm_P2View_Idle},
		{STATE_PLAYER_Idle_Recover, Sm_P2View_Idle_Recover},
		{STATE_PLAYER_Forward, Sm_P2View_Forward},
		{STATE_PLAYER_DashForward, Sm_P2View_DashForward},
		{STATE_PLAYER_Back, Sm_P2View_Back},
		{STATE_PLAYER_DashBack, Sm_P2View_DashBack},
		{STATE_PLAYER_ATK1, Sm_P2View_ATK1},
		{STATE_PLAYER_ATK1_Recover, Sm_P2View_ATK1_Recover},
		{STATE_PLAYER_ATK2,Sm_P2View_ATK2},
		{STATE_PLAYER_ATK2_Recover, Sm_P2View_ATK2_Recover},
		{STATE_PLAYER_Block,Sm_P2View_Block},
		{STATE_PLAYER_Hit,Sm_P2View_Hit},
		{STATE_PLAYER_Dying,Sm_P2View_Dying},
		{STATE_PLAYER_Dead,Sm_P2View_Dead},
		{STATE_PLAYER_CLEAN,Sm_P2View_CLEAN},
};

pontos_t  posP2 = {50 + 16,30};
pontos_t  rstartP2 = {50 + 16,30};

void Sm_P2View_CLEAN(void)
{
	deleta_figura_invertido_seguro(&posP2, &p1_idle);
	osDelay(1);
	SmState_P2 = STATE_PLAYER_MENU;
}

void Sm_P2View_MENU(void)
{
	osDelay(1);
}
void Sm_P2View_RoundStart(void)
{
	deleta_figura_invertido_seguro(&posP2, &p1_idle);
	posP2.x1 = rstartP2.x1;
	print_figura_invertido_seguro(&posP2, &p1_idle);
}
void Sm_P2View_Idle(void)
{
	print_figura_invertido_seguro(&posP2, &p1_idle);
	osDelay(updateRate);
}
void Sm_P2View_Idle_Recover(void)
{
	print_figura_invertido_seguro(&posP2, &p1_idle);
	osDelay(updateRate);
}
void Sm_P2View_Forward(void)
{
	deleta_figura_invertido_seguro(&posP2, &p1_idle);
	if(posP2.x1 > 0 && nivelDeColisao<2)
			posP2.x1=posP2.x1 - 1;
	print_figura_invertido_seguro(&posP2, &p1_idle);
	osDelay(updateRate);
}

void Sm_P2View_DashForward(void)
{
	deleta_figura_invertido_seguro(&posP2, &p1_idle);
	if(posP2.x1 > 15)
	{
			if(nivelDeColisao<2 )
				posP2.x1=posP2.x1 - 10;
	}
	else
	{
		posP2.x1=5;
	}
	print_figura_invertido_seguro(&posP2, &dashfwd);
	osDelay(updateRate);
}

void Sm_P2View_DashBack(void)
{
	deleta_figura_invertido_seguro(&posP2, &p1_idle);

	if(posP2.x1 < 50)
	{
		posP2.x1=posP2.x1 + 10;
	}
	else
	{
		posP2.x1=60;
	}
	print_figura_invertido_seguro(&posP2, &dashbck);
	osDelay(updateRate);
}
void Sm_P2View_Back(void)
{
	deleta_figura_invertido_seguro(&posP2, &p1_idle);
	if(posP2.x1 < 60)
		posP2.x1=posP2.x1 + 1;
	print_figura_invertido_seguro(&posP2, &p1_idle);
	osDelay(updateRate);
}
void Sm_P2View_ATK1(void)
{
	if(nivelDeColisao>0)
	{
		if(SmState_P1 == STATE_PLAYER_Back || SmState_P1 == STATE_PLAYER_Block)
		{
			SmState_P1 = STATE_PLAYER_Block;
		}
		else
		{
			if(SmState_P1 != STATE_PLAYER_Dead && SmState_P1 != STATE_PLAYER_Dying )
				SmState_P1 = STATE_PLAYER_Hit;
		}
	}
	deleta_figura_invertido_seguro(&posP2, &p1_idle);
	print_figura_invertido_seguro(&posP2, &ATK1);
	osDelay(updateRate);
}
void Sm_P2View_ATK2(void)
{
	if(nivelDeColisao>0)
	{
		if(SmState_P1 == STATE_PLAYER_Back ||  SmState_P1 ==STATE_PLAYER_Block )
		{
			SmState_P1 = STATE_PLAYER_Block;
		}
		else
		{
			SmState_P1 = STATE_PLAYER_Dying;
		}
	}
	deleta_figura_invertido_seguro(&posP2, &ATK1);
	print_figura_invertido_seguro(&posP2, &ATK2);
	osDelay(updateRate);
}

void Sm_P2View_ATK2_Recover(void)
{
	deleta_figura_invertido_seguro(&posP2, &ATK2);
	print_figura_invertido_seguro(&posP2, &recover);
	osDelay(updateRate);
}

void Sm_P2View_ATK1_Recover(void)
{
	deleta_figura_invertido_seguro(&posP2, &ATK1);
	print_figura_invertido_seguro(&posP2, &recover);
	osDelay(updateRate);
}

void Sm_P2View_Hit(void)
{
	deleta_figura_invertido_seguro(&posP2, &hit);
	print_figura_invertido_seguro(&posP2, &hit);
	osDelay(updateRate);
}

void Sm_P2View_Block(void)
{
	deleta_figura_invertido_seguro(&posP2, &block);
	print_figura_invertido_seguro(&posP2, &block);
	osDelay(updateRate);
}
void Sm_P2View_Dying(void)
{
	deleta_figura_invertido_seguro(&posP2, &block);
	print_figura_invertido_seguro(&posP2, &dying);
	osDelay(updateRate);
}
void Sm_P2View_Dead(void)
{
	deleta_figura_invertido_seguro(&posP2, &dead);
	print_figura_invertido_seguro(&posP2, &dead);
	osDelay(updateRate);
}


void Rodar_Maquina_P2View(void)
{
	if(SmState_P2 < NUM_STATES_PLAYER)
	{
		(*StateMachine_P2View[SmState_P2].func)();
	}
	else
	{
		return;
	}
}
