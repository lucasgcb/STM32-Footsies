#include "P1_ViewFSM.h"
typedef struct
{
	StateType_PLAYER State;
	void (*func)(void);
}StateMachineType_P1;

StateMachineType_P1 StateMachine_P1View[] =
{
		{STATE_PLAYER_MENU, Sm_P1View_MENU},
		{STATE_PLAYER_RoundStart, Sm_P1View_RoundStart},
		{STATE_PLAYER_Idle, Sm_P1View_Idle},
		{STATE_PLAYER_Idle_Recover, Sm_P1View_Idle_Recover},
		{STATE_PLAYER_Forward, Sm_P1View_Forward},
		{STATE_PLAYER_DashForward, Sm_P1View_DashForward},
		{STATE_PLAYER_Back, Sm_P1View_Back},
		{STATE_PLAYER_DashBack, Sm_P1View_DashBack},
		{STATE_PLAYER_ATK1, Sm_P1View_ATK1},
		{STATE_PLAYER_ATK1_Recover, Sm_P1View_ATK1_Recover},
		{STATE_PLAYER_ATK2,Sm_P1View_ATK2},
		{STATE_PLAYER_ATK2_Recover, Sm_P1View_ATK2_Recover},
		{STATE_PLAYER_Block,Sm_P1View_Block},
		{STATE_PLAYER_Hit,Sm_P1View_Hit},
		{STATE_PLAYER_Dying,Sm_P1View_Dying},
		{STATE_PLAYER_Dead,Sm_P1View_Dead},
		{STATE_PLAYER_CLEAN,Sm_P1View_CLEAN},
};

pontos_t  rstartP1 = {8,30};
pontos_t  posP1 = {8,30};

void Sm_P1View_CLEAN(void)
{
	deleta_figura_seguro(&posP1, &p1_idle);

	osDelay(1);
	SmState_P1 = STATE_PLAYER_MENU;
}


void Sm_P1View_MENU(void)
{
	osDelay(1);
}
void Sm_P1View_RoundStart(void)
{
	deleta_figura_seguro(&posP1, &p1_idle);
	posP1.x1 = rstartP1.x1;
	print_figura_seguro(&posP1, &p1_idle);
	osDelay(updateRate);
}
void Sm_P1View_Idle(void)
{
	print_figura_seguro(&posP1, &p1_idle);
	osDelay(updateRate);
}
void Sm_P1View_Idle_Recover(void)
{
	print_figura_seguro(&posP1, &p1_idle);
	osDelay(updateRate);
}
void Sm_P1View_Forward(void)
{
	deleta_figura_seguro(&posP1, &p1_idle);
	if(posP1.x1 < 70 && nivelDeColisao<2)
		posP1.x1=posP1.x1 + 1;
	print_figura_seguro(&posP1, &p1_idle);
	osDelay(updateRate);
}

void Sm_P1View_DashForward(void)
{
	deleta_figura_seguro(&posP1, &p1_idle);

	if(posP1.x1 < 60)
	{
			if(nivelDeColisao<2)
					posP1.x1=posP1.x1 + 10;
	}
	else
	{
		posP1.x1=75;
	}
	print_figura_seguro(&posP1, &dashfwd);
	osDelay(updateRate);
}

void Sm_P1View_DashBack(void)
{
	deleta_figura_seguro(&posP1, &p1_idle);
	if(posP1.x1 > 15)
	{
			posP1.x1=posP1.x1 - 10;
	}
	print_figura_seguro(&posP1, &dashbck);
	osDelay(updateRate);
}
void Sm_P1View_Back(void)
{
	deleta_figura_seguro(&posP1, &p1_idle);
	if(posP1.x1 > 8)
		posP1.x1=posP1.x1 - 1;
	print_figura_seguro(&posP1, &p1_idle);
	osDelay(updateRate);
}
void Sm_P1View_ATK1(void)
{
	if(nivelDeColisao>0)
	{
		if(SmState_P2 == STATE_PLAYER_Back || SmState_P2 == STATE_PLAYER_Block)
		{
			SmState_P2 = STATE_PLAYER_Block;
		}
		else
		{
			if(SmState_P2 != STATE_PLAYER_Dead && SmState_P2 != STATE_PLAYER_Dying )
				SmState_P2 = STATE_PLAYER_Hit;
		}
	}
	deleta_figura_seguro(&posP1, &p1_idle);
	print_figura_seguro(&posP1, &ATK1);
	osDelay(updateRate);
}
void Sm_P1View_ATK2(void)
{
	if(nivelDeColisao>0)
	{
		if(SmState_P2 == STATE_PLAYER_Back ||  SmState_P2 ==STATE_PLAYER_Block )
		{
			SmState_P2 = STATE_PLAYER_Block;
		}
		else
		{
			SmState_P2 = STATE_PLAYER_Dying;
		}
	}
	deleta_figura_seguro(&posP1, &ATK1);
	print_figura_seguro(&posP1, &ATK2);
	osDelay(updateRate);
}

void Sm_P1View_ATK2_Recover(void)
{
	deleta_figura_seguro(&posP1, &ATK2);
	print_figura_seguro(&posP1, &recover);
	osDelay(updateRate);
}

void Sm_P1View_ATK1_Recover(void)
{
	deleta_figura_seguro(&posP1, &ATK1);
	print_figura_seguro(&posP1, &recover);
	osDelay(updateRate);
}

void Sm_P1View_Hit(void)
{
	deleta_figura_seguro(&posP1, &hit);
	print_figura_seguro(&posP1, &hit);
	osDelay(updateRate);
}

void Sm_P1View_Block(void)
{
	deleta_figura_seguro(&posP1, &block);
	print_figura_seguro(&posP1, &block);
	osDelay(updateRate);
}
void Sm_P1View_Dying(void)
{
	deleta_figura_seguro(&posP1, &block);
	print_figura_seguro(&posP1, &dying);
	osDelay(updateRate);
}
void Sm_P1View_Dead(void)
{
	deleta_figura_seguro(&posP1, &dead);
	print_figura_seguro(&posP1, &dead);
	osDelay(updateRate);
}

void Rodar_Maquina_P1View(void)
{
	if(SmState_P1 < NUM_STATES_PLAYER)
	{
		(*StateMachine_P1View[SmState_P1].func)();
	}
	else
	{
		return;
	}
}
