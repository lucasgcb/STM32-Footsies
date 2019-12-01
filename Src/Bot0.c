#include "Bot0.h"

StateType_Bot SmState_Bot0 = STATE_OFFLINE;

typedef struct
{
	StateType_Bot State;
	void (*func)(void);
}StateMachineType_Bot0;


StateMachineType_Bot0 StateMachine_Bot0[] =
{
		{ STATE_OFFLINE, Sm_OFFLINE0 },
		{ STATE_APPROACH, Sm_APPROACH0 },
		{ STATE_RETREAT, Sm_RETREAT0},
		{ STATE_MOVETOPUNISH, Sm_MOVETOPUNISH0 },
		{ STATE_ATTACK, Sm_ATTACK0 },
		{ STATE_COMBO, Sm_COMBO0 },
		{ STATE_BAIT, Sm_BAIT0 },
		{ STATE_DEFEND, Sm_DEFEND0},
		{ STATE_OBSERVE, Sm_OBSERVE0}
};


void Sm_OFFLINE0(void)
{
	#ifdef DEBUG_BOT0
	print_seguro(0,0,"stat: off" );
	#endif
	osDelay(updateRate);
}
void Sm_APPROACH0(void)
{
	#ifdef DEBUG_BOT0
	print_seguro(0,0,"stat: app" );
	#endif
	SmState_Int1 = STATE_LeftPressed_Int1;
	osDelay(updateRate);
	SmState_Bot0 = STATE_OBSERVE;
}
void Sm_RETREAT0(void)
{
	#ifdef DEBUG_BOT0
	print_seguro(0,0,"stat: RET" );
	#endif
	SmState_Int1 = STATE_RightPressed_Int1;
	osDelay(updateRate);
	SmState_Bot0 = STATE_OBSERVE;
}
void Sm_MOVETOPUNISH0(void)
{
	#ifdef DEBUG_BOT0
	print_seguro(0,0,"stat: PUN" );
	#endif
	SmState_Int1 = STATE_RightPressed_Int1;
	while(nivelDeColisao<0)
	{
		AdicionarNaLista1("R");
		AdicionarNaLista1("R");
	}
	osDelay(updateRate);
	SmState_Bot0 = STATE_OBSERVE;
}
void Sm_ATTACK0(void)
{
	#ifdef DEBUG_BOT0
	print_seguro(0,0,"stat: ATK" );
	#endif
	SmState_Int1 = STATE_ATKPressed_Int1;
	AdicionarNaLista1("A");
	osDelay(updateRate);
	SmState_Bot0 = STATE_OBSERVE;
}
void Sm_COMBO0(void)
{
	#ifdef DEBUG_BOT0
	print_seguro(0,0,"stat: KILL" );
	#endif
	SmState_Int1 = STATE_ATKPressed_Int1;
	AdicionarNaLista1("A");
	AdicionarNaLista1("A");
	osDelay(updateRate);
	SmState_Bot0 = STATE_OBSERVE;
}
void Sm_BAIT0(void)
{
	osDelay(updateRate);
}
void Sm_DEFEND0(void)
{
	SmState_Int1 = STATE_LeftPressed_Int1;

	osDelay(updateRate);
	SmState_Bot0 = STATE_OBSERVE;

}
void Sm_OBSERVE0(void)
{
	#ifdef DEBUG_BOT0
	print_seguro(0,0,"stat: obs" );
	#endif
	AdicionarNaLista1("N");
	if(SmState_Botao1 == STATE_BotaoON && SmState_Menu == STATE_Arena2P_ONGOING)
	{
		SmState_Menu = STATE_GameOver;
		return;
	}
	if(SmState_Menu == STATE_Menu1P || SmState_Menu == STATE_Menu2P)
	{
		SmState_Bot0 = STATE_OFFLINE;
		return;
	}
	switch(SmState_P2)
	{
		case STATE_PLAYER_Forward:
			SmState_Bot0 = STATE_APPROACH;
			break;
		case STATE_PLAYER_Hit:
			SmState_Bot0 = STATE_COMBO;
			break;
		case STATE_PLAYER_ATK1_Recover:
							if (nivelDeColisao>0)
									SmState_Bot0 = STATE_COMBO;
								else
									SmState_Bot0 = STATE_MOVETOPUNISH;
							break;
		case STATE_PLAYER_ATK2_Recover:
					if (nivelDeColisao>0)
							SmState_Bot0 = STATE_COMBO;
						else
							SmState_Bot0 = STATE_MOVETOPUNISH;
					break;
		default:
			if (nivelDeColisao>0)
					SmState_Bot0 = STATE_COMBO;
				else
					SmState_Bot0 = STATE_RETREAT;
	}
	osDelay(1);
}


void Rodar_Maquina_Bot0(void)
{
	if(SmState_Bot0 < NUM_STATES_BOT)
	{
		(*StateMachine_Bot0[SmState_Bot0].func)();
	}
	else
	{
		return;
	}
}
