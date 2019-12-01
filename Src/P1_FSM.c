#include "P1_FSM.h"
StateType_PLAYER SmState_P1=STATE_PLAYER_MENU;
typedef struct
{
	StateType_PLAYER State;
	void (*func)(void);
}StateMachineType_P1;

StateMachineType_P1 StateMachine_P1[] =
{
		{STATE_PLAYER_MENU, Sm_P1_MENU},
		{STATE_PLAYER_RoundStart, Sm_P1_RoundStart},
		{STATE_PLAYER_Idle, Sm_P1_Idle},
		{STATE_PLAYER_Idle_Recover, Sm_P1_Idle_Recover},
		{STATE_PLAYER_Forward, Sm_P1_Forward},
		{STATE_PLAYER_DashForward, Sm_P1_DashForward},
		{STATE_PLAYER_Back, Sm_P1_Back},
		{STATE_PLAYER_DashBack, Sm_P1_DashBack},
		{STATE_PLAYER_ATK1, Sm_P1_ATK1},
		{STATE_PLAYER_ATK1_Recover, Sm_P1_ATK1_Recover},
		{STATE_PLAYER_ATK2,Sm_P1_ATK2},
		{STATE_PLAYER_ATK2_Recover, Sm_P1_ATK2_Recover},
		{STATE_PLAYER_Block,Sm_P1_Block},
		{STATE_PLAYER_Hit,Sm_P1_Hit},
		{STATE_PLAYER_Dying,Sm_P1_Dying},
		{STATE_PLAYER_Dead,Sm_P1_Dead},
		{STATE_PLAYER_CLEAN,Sm_P1_CLEAN},
};

void Sm_P1_CLEAN(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_clen");
	#endif
}

void Sm_P1_MENU(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_men");
	#endif
	SmState_P1 = STATE_PLAYER_MENU;
	if(SmState_Menu==STATE_Arena1P_RoundStart || SmState_Menu==STATE_Arena2P_RoundStart )
		SmState_P1 = STATE_PLAYER_RoundStart;

}
void Sm_P1_RoundStart(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_rst");
	#endif
	SmState_P1 = STATE_PLAYER_RoundStart;
	if(SmState_Menu==STATE_Arena1P_ONGOING || SmState_Menu==STATE_Arena2P_ONGOING)
			SmState_P1 = STATE_PLAYER_Idle;

}
void Sm_P1_Idle(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_idl");
	#endif
	SmState_P1 = STATE_PLAYER_Idle;
	if(SmState_Menu==STATE_Menu1P || SmState_Menu==STATE_Menu2P)
	{
		SmState_P1 = STATE_PLAYER_MENU;
		return;
	}

	if(SmState_Int1==STATE_LeftPressed_Int1)
					SmState_P1 = STATE_PLAYER_Back;
			else
				if(SmState_Int1==STATE_RightPressed_Int1)
					SmState_P1 = STATE_PLAYER_Forward;
				else
					if(SmState_Int1==STATE_ATKPressed_Int1)
							SmState_P1 = STATE_PLAYER_ATK1;


}
void Sm_P1_Idle_Recover(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_idr");
	#endif
	SmState_P1 = STATE_PLAYER_Idle_Recover;
	if(SmState_Menu==STATE_Menu1P || SmState_Menu==STATE_Menu2P)
	{
		SmState_P1 = STATE_PLAYER_MENU;
		return;
	}

	if(SmState_Int1==STATE_LeftPressed_Int1)
	{
					SmState_P1 = STATE_PLAYER_Back;
	}
	else
	{
		if(SmState_Int1==STATE_RightPressed_Int1)
			SmState_P1 = STATE_PLAYER_Forward;
		else
		{
			if(SmState_Int1==STATE_NeutralPressed_Int1)
			{
					SmState_P1 = STATE_PLAYER_Idle;
			}
		}
	}
}
void Sm_P1_Forward(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_fwd");
	#endif
	if(SmState_P1 == STATE_PLAYER_Forward)
	{
		if(lerDoInput1(1) == 'R' && lerDoInput1(3)== 'R' )
		{
			SmState_P1 = STATE_PLAYER_DashForward;
			return;
		}
		if(SmState_Int1==STATE_LeftPressed_Int1)
				SmState_P1 = STATE_PLAYER_Back;
		if(SmState_Int1==STATE_NeutralPressed_Int1)
				SmState_P1 = STATE_PLAYER_Idle;
		if(SmState_Int1==STATE_ATKPressed_Int1)
				SmState_P1 = STATE_PLAYER_ATK1;
	}
}

void Sm_P1_DashForward(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_dfw");
	#endif
	osDelay(40);
	if(SmState_P1 == STATE_PLAYER_DashForward)
	{
		if(SmState_Int1==STATE_LeftPressed_Int1)
			SmState_P1 = STATE_PLAYER_Back;
		if(SmState_Int1==STATE_NeutralPressed_Int1)
			SmState_P1 = STATE_PLAYER_Idle;
		if(SmState_Int1==STATE_ATKPressed_Int1)
			SmState_P1 = STATE_PLAYER_ATK1;
	}

}

void Sm_P1_DashBack(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_dba");
	#endif
	osDelay(40);
	if(SmState_P1 == STATE_PLAYER_DashBack)
	{
		if(SmState_Int1==STATE_RightPressed_Int1)
					SmState_P1 = STATE_PLAYER_Forward;
		if(SmState_Int1==STATE_LeftPressed_Int1)
				SmState_P1 = STATE_PLAYER_Back;
		if(SmState_Int1==STATE_NeutralPressed_Int1)
				SmState_P1 = STATE_PLAYER_Idle;
		if(SmState_Int1==STATE_ATKPressed_Int1)
				SmState_P1 = STATE_PLAYER_ATK1;
	}
}
void Sm_P1_Back(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_bck");
	#endif
	if(SmState_P1 == STATE_PLAYER_Back)
	{
		if(lerDoInput1(1) == 'L' && lerDoInput1(3)== 'L')
		{
			SmState_P1 = STATE_PLAYER_DashBack;
			return;
		}
		if(SmState_Int1==STATE_RightPressed_Int1)
			SmState_P1 = STATE_PLAYER_Forward;
		if(SmState_Int1==STATE_NeutralPressed_Int1)
			SmState_P1 = STATE_PLAYER_Idle;
		if(SmState_Int1==STATE_ATKPressed_Int1)
			SmState_P1 = STATE_PLAYER_ATK1;
	}
}
void Sm_P1_ATK1(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_at1");
#endif
	osDelay(400);
	if(SmState_P1 == STATE_PLAYER_ATK1)
		SmState_P1 = STATE_PLAYER_ATK1_Recover;
}
void Sm_P1_ATK2(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_at2");
#endif
	osDelay(600);
	if(SmState_P1 == STATE_PLAYER_ATK2)
		SmState_P1 = STATE_PLAYER_ATK2_Recover;
}

void Sm_P1_ATK2_Recover(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_2re");
	#endif
	osDelay(1000);
	if(SmState_P1 == STATE_PLAYER_ATK2_Recover  )
	{
		if(SmState_Int1==STATE_LeftPressed_Int1)
				SmState_P1 = STATE_PLAYER_Back;
		else
			if(SmState_Int1==STATE_RightPressed_Int1)
				SmState_P1 = STATE_PLAYER_Forward;
			else
				SmState_P1 = STATE_PLAYER_Idle_Recover;
	}
}

void Sm_P1_ATK1_Recover(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_1re");
#endif
	osDelay(200);
	if(SmState_P1 == STATE_PLAYER_ATK1_Recover )
	{
		if(lerDoInput1(1) == 'A' && lerDoInput1(3)== 'A')
		{
			SmState_P1 = STATE_PLAYER_ATK2;
		}
		else
		{
			if(SmState_Int1==STATE_LeftPressed_Int1)
			{
					SmState_P1 = STATE_PLAYER_Back;
			}
			else
			{
				if(SmState_Int1==STATE_RightPressed_Int1)
					SmState_P1 = STATE_PLAYER_Forward;
				else
					SmState_P1 = STATE_PLAYER_Idle_Recover;
			}
		}
	}
}

void Sm_P1_Hit(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_hit");
	#endif
	osDelay(800);
	SmState_P1 = STATE_PLAYER_Idle_Recover;
}

void Sm_P1_Block(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_blk");
	#endif
	osDelay(150);
	SmState_P1 = STATE_PLAYER_Idle_Recover;
}
void Sm_P1_Dying(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_die");
	#endif
	osDelay(800);
	SmState_P1 = STATE_PLAYER_Dead;
}
void Sm_P1_Dead(void)
{
	#ifdef DEBUG_p1
	print_seguro(0,0,"state: p1_ded");
	#endif
	SmState_P1 = STATE_PLAYER_Dead;
}

void Rodar_Maquina_P1(void)
{
	if(SmState_P1 < NUM_STATES_PLAYER)
	{
		(*StateMachine_P1[SmState_P1].func)();
	}
	else
	{
		return;
	}
}
