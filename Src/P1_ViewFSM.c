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
};
pontos_t  posP1 = {4,20};

const figura_t p1_idle =
{
	16,
	16,
 	{0x0, 0x0, 0x0, 0x84, 0x44, 0x3f, 0x25, 0x25, 0x25, 0x3f, 0x40, 0x80, 0x80, 0x40, 0x80, 0x0, 0x0, 0x0, 0xe1, 0x9a, 0x44, 0xa4, 0x25, 0x26, 0x20, 0x20, 0x48, 0x54, 0xa4, 0x42, 0x81, 0x0}
};

const figura_t ATK1=
{
	16,
	16,
 	{0x20, 0x40, 0xe0, 0xa0, 0xa0, 0xa0, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x78, 0x84, 0x27, 0xdc, 0x4, 0x14, 0x2f, 0x2a, 0x54, 0x74, 0x58, 0x40, 0x40, 0x78, 0x88, 0x70}
};

const figura_t ATK2=
{
	16,
	16,
 	{0x88, 0xc8, 0xfe, 0x6a, 0xea, 0xaa, 0x3e, 0x60, 0xc0, 0x60, 0x20, 0x30, 0x98, 0x88, 0x68, 0x38, 0x3, 0x6, 0xff, 0x18, 0x0, 0x81, 0xe1, 0x3d, 0x5, 0x6, 0x2, 0x3, 0x1, 0x0, 0x0, 0x0}
};

const figura_t dashbck=
{
	16,
	16,
 	{0x80, 0x44, 0x24, 0x3f, 0xe5, 0x25, 0x25, 0xff, 0x60, 0xe4, 0x0, 0x24, 0x24, 0x24, 0x24, 0x24, 0xcf, 0xb0, 0x84, 0xe5, 0x14, 0x23, 0xe1, 0xcd, 0x93, 0xa1, 0xe0, 0x0, 0x0, 0x0, 0x1, 0x1}
};

const figura_t dashfwd=
{
	16,
	16,
 	{0x44, 0x44, 0x4, 0x4, 0x0, 0x80, 0x44, 0x24, 0x3f, 0xe5, 0x25, 0x25, 0xff, 0x60, 0xe0, 0x0, 0x4, 0x0, 0xe0, 0xa0, 0x90, 0xcf, 0xe0, 0x24, 0x15, 0xe4, 0x83, 0xb1, 0xcd, 0x3, 0x1, 0x0}
};

const figura_t recover=
{
	16,
	16,
 	{0x0, 0x0, 0x0, 0x84, 0x44, 0x3f, 0x25, 0x25, 0x25, 0x3f, 0x40, 0x80, 0x97, 0x40, 0x97, 0x0, 0x0, 0x0, 0xe1, 0x9a, 0x44, 0xa4, 0x25, 0x26, 0x20, 0x20, 0x48, 0x54, 0xa4, 0x42, 0x81, 0x0}
};

void Sm_P1View_MENU(void)
{
	osDelay(1);
}
void Sm_P1View_RoundStart(void)
{
	print_figura_seguro(&posP1, &p1_idle);
}
void Sm_P1View_Idle(void)
{
	print_figura_seguro(&posP1, &p1_idle);
}
void Sm_P1View_Idle_Recover(void)
{
	print_figura_seguro(&posP1, &p1_idle);
}
void Sm_P1View_Forward(void)
{
	deleta_figura_seguro(&posP1, &p1_idle);
	if(posP1.x1 < 70)
		posP1.x1=posP1.x1 + 1;
	print_figura_seguro(&posP1, &p1_idle);
	osDelay(updateRate);
}

void Sm_P1View_DashForward(void)
{
	deleta_figura_seguro(&posP1, &p1_idle);
	if(posP1.x1 < 60)
	{
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
	if(posP1.x1 > 0)
		posP1.x1=posP1.x1 - 1;
	print_figura_seguro(&posP1, &p1_idle);
	osDelay(updateRate);
}
void Sm_P1View_ATK1(void)
{
	deleta_figura_seguro(&posP1, &p1_idle);
	print_figura_seguro(&posP1, &ATK1);
	osDelay(updateRate);
}
void Sm_P1View_ATK2(void)
{
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
	osDelay(1);
}

void Sm_P1View_Block(void)
{
	osDelay(1);
}
void Sm_P1View_Dying(void)
{
	osDelay(1);
}
void Sm_P1View_Dead(void)
{
	osDelay(1);
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
