#include "Bot.h"


StateType_Bot SmState_Bot1 = STATE_OFFLINE;

typedef struct
{
	StateType_Bot State;
	void (*func)(void);
}StateMachineType_Bot1;


StateMachineType_Bot1 StateMachine_Bot1[] =
{
		{ STATE_OFFLINE, Sm_OFFLINE },
		{ STATE_APPROACH, Sm_APPROACH },
		{ STATE_RETREAT, Sm_RETREAT},
		{ STATE_MOVETOPUNISH, Sm_MOVETOPUNISH },
		{ STATE_ATTACK, Sm_ATTACK },
		{ STATE_COMBO, Sm_COMBO },
		{ STATE_BAIT, Sm_BAIT },
		{ STATE_DEFEND, Sm_DEFEND},
		{ STATE_OBSERVE, Sm_OBSERVE}
};

char  input_buffer2[12] = " N N N N N ";

void AdicionarNaLista2(char *add)
{
    if( xSemaphoreTake( input2, 1000 ) == pdTRUE )
 	{
    	  for(int i=9; i>=2;i=i-2)
    	  {
    		  input_buffer2[i] = input_buffer2[i-2];
    	  }
    	  input_buffer2[1] = *add;
		xSemaphoreGive( input2);
	 }
}

char  lerDoInput2(uint8_t index)
{
	char ret = '\0';
    if( xSemaphoreTake( input2, 1000 ) == pdTRUE )
 	{
    	ret = input_buffer2[index];
		xSemaphoreGive( input2);
	 }
    return ret;
}


void Sm_OFFLINE(void)
{
	osDelay(updateRate);
}
void Sm_APPROACH(void)
{
	SmState_Int2 = STATE_LeftPressed_Int2;
	osDelay(updateRate);
	SmState_Bot1 = STATE_OBSERVE;
}
void Sm_RETREAT(void)
{
	SmState_Int2 = STATE_RightPressed_Int2;
	osDelay(updateRate);
	SmState_Bot0 = STATE_OBSERVE;
}
void Sm_MOVETOPUNISH(void)
{
	SmState_Int2 = STATE_LeftPressed_Int2;
	while(nivelDeColisao<0)
	{
		AdicionarNaLista2("L");
		AdicionarNaLista2("L");
	}
	osDelay(updateRate);
	SmState_Bot1 = STATE_OBSERVE;
}
void Sm_ATTACK(void)
{
	SmState_Int2 = STATE_ATKPressed_Int2;
	AdicionarNaLista2("A");
	osDelay(updateRate);
	SmState_Bot1 = STATE_OBSERVE;
}
void Sm_COMBO(void)
{
	SmState_Int2 = STATE_ATKPressed_Int2;
	AdicionarNaLista2("A");
	AdicionarNaLista2("A");
	osDelay(updateRate);
	SmState_Bot1 = STATE_OBSERVE;
}
void Sm_BAIT(void)
{
	osDelay(updateRate);
}
void Sm_DEFEND(void)
{
	SmState_Int2 = STATE_RightPressed_Int2;

	osDelay(updateRate);
	SmState_Bot1 = STATE_OBSERVE;

}
void Sm_OBSERVE(void)
{
	AdicionarNaLista2("N");
	switch(SmState_P1)
	{
		case STATE_PLAYER_Forward:
			SmState_Bot1 = STATE_RETREAT;
		case STATE_PLAYER_Hit:
			SmState_Bot1 = STATE_COMBO;
			break;
		case STATE_PLAYER_ATK2_Recover:
					if (nivelDeColisao>0)
							SmState_Bot1 = STATE_COMBO;
						else
							SmState_Bot1 = STATE_MOVETOPUNISH;
					break;
		default:
			if (nivelDeColisao>0)
					SmState_Bot1 = STATE_COMBO;
				else
					SmState_Bot1 = STATE_APPROACH;
	}
	osDelay(1);
}


void Rodar_Maquina_Bot1(void)
{
	if(SmState_Bot1 < NUM_STATES_BOT)
	{
		(*StateMachine_Bot1[SmState_Bot1].func)();
	}
	else
	{
		return;
	}
}
