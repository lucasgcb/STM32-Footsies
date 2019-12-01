#include "P2_FSM.h"
StateType_PLAYER SmState_P2=STATE_PLAYER_MENU;
typedef struct
{
	StateType_PLAYER State;
	void (*func)(void);
}StateMachineType_P2;

StateMachineType_P2 StateMachine_P2[] =
{
		{STATE_PLAYER_MENU, Sm_P2_MENU},
		{STATE_PLAYER_RoundStart, Sm_P2_RoundStart},
		{STATE_PLAYER_Idle, Sm_P2_Idle},
		{STATE_PLAYER_Idle_Recover, Sm_P2_Idle_Recover},
		{STATE_PLAYER_Forward, Sm_P2_Forward},
		{STATE_PLAYER_DashForward, Sm_P2_DashForward},
		{STATE_PLAYER_Back, Sm_P2_Back},
		{STATE_PLAYER_DashBack, Sm_P2_DashBack},
		{STATE_PLAYER_ATK1, Sm_P2_ATK1},
		{STATE_PLAYER_ATK1_Recover, Sm_P2_ATK1_Recover},
		{STATE_PLAYER_ATK2,Sm_P2_ATK2},
		{STATE_PLAYER_ATK2_Recover, Sm_P2_ATK2_Recover},
		{STATE_PLAYER_Block,Sm_P2_Block},
		{STATE_PLAYER_Hit,Sm_P2_Hit},
		{STATE_PLAYER_Dying,Sm_P2_Dying},
		{STATE_PLAYER_Dead,Sm_P2_Dead},
		{STATE_PLAYER_CLEAN,Sm_P2_CLEAN},
};
StateType_Int2 SmState_Int2 = STATE_NeutralPressed_Int2;

void Sm_P2_CLEAN(void)
{
	osDelay(1);
}
void Sm_P2_MENU(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_men");
	#endif
	SmState_P2 = STATE_PLAYER_MENU;
	if(SmState_Menu==STATE_Arena1P_RoundStart || SmState_Menu==STATE_Arena2P_RoundStart )
		SmState_P2 = STATE_PLAYER_RoundStart;

}
void Sm_P2_RoundStart(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_rst");
	#endif
	SmState_P2 = STATE_PLAYER_RoundStart;
	if(SmState_Menu==STATE_Arena1P_ONGOING || SmState_Menu==STATE_Arena2P_ONGOING)
			SmState_P2 = STATE_PLAYER_Idle;

}
void Sm_P2_Idle(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_idl");
	#endif
	SmState_P2 = STATE_PLAYER_Idle;
	if(SmState_Menu==STATE_Menu1P || SmState_Menu==STATE_Menu2P)
	{
		SmState_P2 = STATE_PLAYER_MENU;
		return;
	}

	if(SmState_Int2==STATE_RightPressed_Int2)
					SmState_P2 = STATE_PLAYER_Back;
			else
				if(SmState_Int2==STATE_LeftPressed_Int2)
					SmState_P2 = STATE_PLAYER_Forward;
				else
					if(SmState_Int2==STATE_ATKPressed_Int2)
							SmState_P2 = STATE_PLAYER_ATK1;


}
void Sm_P2_Idle_Recover(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_idr");
	#endif
	SmState_P2 = STATE_PLAYER_Idle_Recover;
	if(SmState_Menu==STATE_Menu1P || SmState_Menu==STATE_Menu2P)
	{
		SmState_P2 = STATE_PLAYER_MENU;
		return;
	}

	if(SmState_Int2==STATE_RightPressed_Int2)
	{
					SmState_P2 = STATE_PLAYER_Back;
	}
	else
	{
		if(SmState_Int2==STATE_LeftPressed_Int2)
			SmState_P2 = STATE_PLAYER_Forward;
		else
		{
			if(SmState_Int2==STATE_NeutralPressed_Int2)
			{
					SmState_P2 = STATE_PLAYER_Idle;
			}
		}
	}
}
void Sm_P2_Forward(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_fwd");
	#endif
	SmState_P2 = STATE_PLAYER_Forward;
	if(lerDoInput2(1) == 'L' && lerDoInput2(3)== 'L')
	{
		SmState_P2 = STATE_PLAYER_DashForward;
		return;
	}
	if(SmState_Int2==STATE_RightPressed_Int2)
			SmState_P2 = STATE_PLAYER_Back;
	if(SmState_Int2==STATE_NeutralPressed_Int2)
			SmState_P2 = STATE_PLAYER_Idle;
	if(SmState_Int2==STATE_ATKPressed_Int2)
			SmState_P2 = STATE_PLAYER_ATK1;

}

void Sm_P2_DashForward(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_dfw");
	#endif
	osDelay(40);
	if(SmState_Int2==STATE_RightPressed_Int2)
			SmState_P2 = STATE_PLAYER_Back;
	if(SmState_Int2==STATE_NeutralPressed_Int2)
			SmState_P2 = STATE_PLAYER_Idle;
	if(SmState_Int2==STATE_ATKPressed_Int2)
			SmState_P2 = STATE_PLAYER_ATK1;

}

void Sm_P2_DashBack(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_dba");
	#endif
	osDelay(40);
	if(SmState_Int2==STATE_LeftPressed_Int2)
			SmState_P2 = STATE_PLAYER_Forward;
	if(SmState_Int2==STATE_RightPressed_Int2)
			SmState_P2 = STATE_PLAYER_Back;
	if(SmState_Int2==STATE_NeutralPressed_Int2)
			SmState_P2 = STATE_PLAYER_Idle;
	if(SmState_Int2==STATE_ATKPressed_Int2)
			SmState_P2 = STATE_PLAYER_ATK1;

}
void Sm_P2_Back(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_bck");
	#endif
	SmState_P2 = STATE_PLAYER_Back;
	if(lerDoInput2(1) == 'R' && lerDoInput2(3)== 'R')
	{
		SmState_P2 = STATE_PLAYER_DashBack;
		return;
	}
	if(SmState_Int2==STATE_LeftPressed_Int2)
		SmState_P2 = STATE_PLAYER_Forward;
	if(SmState_Int2==STATE_NeutralPressed_Int2)
		SmState_P2 = STATE_PLAYER_Idle;
	if(SmState_Int2==STATE_ATKPressed_Int2)
		SmState_P2 = STATE_PLAYER_ATK1;
}
void Sm_P2_ATK1(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_at1");
#endif
	osDelay(400);
	if(SmState_P2 == STATE_PLAYER_ATK1)
		SmState_P2 = STATE_PLAYER_ATK1_Recover;
}
void Sm_P2_ATK2(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_at2");
#endif
	osDelay(600);
	if(SmState_P2 == STATE_PLAYER_ATK2)
		SmState_P2 = STATE_PLAYER_ATK2_Recover;
}

void Sm_P2_ATK2_Recover(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_2re");
	#endif
	osDelay(1000);
	if(SmState_P2 == STATE_PLAYER_ATK2_Recover )
	{
		if(SmState_Int2==STATE_RightPressed_Int2)
				SmState_P2 = STATE_PLAYER_Back;
		else
			if(SmState_Int2==STATE_LeftPressed_Int2)
				SmState_P2 = STATE_PLAYER_Forward;
			else
				SmState_P2 = STATE_PLAYER_Idle_Recover;
	}
}

void Sm_P2_ATK1_Recover(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_1re");
	#endif
	osDelay(200);
	if(SmState_P2 == STATE_PLAYER_ATK1_Recover )
	{
		if(lerDoInput2(1) == 'A' && lerDoInput2(3)== 'A')
		{
					SmState_P2 = STATE_PLAYER_ATK2;
		}
		else
		{
			if(SmState_Int2==STATE_RightPressed_Int2)
			{
					SmState_P2 = STATE_PLAYER_Back;
			}
			else
			{
				if(SmState_Int2==STATE_LeftPressed_Int2)
					SmState_P2 = STATE_PLAYER_Forward;
				else
					SmState_P2 = STATE_PLAYER_Idle_Recover;
			}
		}
	}
}

void Sm_P2_Hit(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_hit");
	#endif
	osDelay(800);
	if (SmState_P2 == STATE_PLAYER_Hit)
		SmState_P2 = STATE_PLAYER_Idle_Recover;
}

void Sm_P2_Block(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_blk");
	#endif
	osDelay(150);
	SmState_P2 = STATE_PLAYER_Idle_Recover;
}
void Sm_P2_Dying(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_die");
	#endif
	osDelay(800);
	SmState_P2 = STATE_PLAYER_Dead;
}
void Sm_P2_Dead(void)
{
	#ifdef DEBUG_P2
	print_seguro(0,0,"state: P2_ded");
	#endif
	SmState_P2 = STATE_PLAYER_Dead;
}

void Rodar_Maquina_P2(void)
{
	if(SmState_P2 < NUM_STATES_PLAYER)
	{
		(*StateMachine_P2[SmState_P2].func)();
	}
	else
	{
		return;
	}
}
