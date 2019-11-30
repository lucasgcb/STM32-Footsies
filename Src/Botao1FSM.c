#include "Botao1FSM.h"
StateType_Botao1 SmState_Botao1 = STATE_DEBOUNCE;

typedef struct
{
	StateType_Botao1 State;
	void (*func)(void);
}StateMachineType_Botao1;

StateMachineType_Botao1 StateMachine_Botao1[] =
{
		{ STATE_BotaoON, Sm_BotaoON },
		{ STATE_DEBOUNCE, Sm_DEBOUNCE },
		{ STATE_BotaoOFF, Sm_BotaoOFF },
};


void Sm_BotaoON(void)
{
   #ifdef DEBUG
	//char ONTEXTO[4]="ON";
	//ONTEXTO[2]=0x20;
	#endif
	if(HAL_GPIO_ReadPin(P1_ATK_GPIO_Port,P1_ATK_Pin)==0)
	{
		SmState_Botao1 = STATE_BotaoON;
		#ifdef DEBUG
		//print_seguro(0,0,ONTEXTO);
		#endif
	}else
		if(HAL_GPIO_ReadPin(P1_ATK_GPIO_Port,P1_ATK_Pin)==1)
		{
			SmState_Botao1 = STATE_DEBOUNCE;
		}
}
void Sm_BotaoOFF(void)
{
	if(HAL_GPIO_ReadPin(P1_ATK_GPIO_Port,P1_ATK_Pin)==1)
	{
		#ifdef DEBUG
		//print_seguro(0,0,"OFF");
		#endif
		SmState_Botao1 = STATE_BotaoOFF;

	}
	else
		if(HAL_GPIO_ReadPin(P1_ATK_GPIO_Port,P1_ATK_Pin)==0)
		{
			SmState_Botao1 = STATE_DEBOUNCE;
		}
}

void Sm_DEBOUNCE(void)
{
	if(HAL_GPIO_ReadPin(P1_ATK_GPIO_Port,P1_ATK_Pin)==1)
		{
				osDelay(BOTAO_DEBOUNCE);
				if(HAL_GPIO_ReadPin(P1_ATK_GPIO_Port,P1_ATK_Pin)==1)
					SmState_Botao1 = STATE_BotaoOFF;
				else
					SmState_Botao1 = STATE_DEBOUNCE;
		}
	else
	{
		if(HAL_GPIO_ReadPin(P1_ATK_GPIO_Port,P1_ATK_Pin)==0)
		{
					osDelay(BOTAO_DEBOUNCE);
					if(HAL_GPIO_ReadPin(P1_ATK_GPIO_Port,P1_ATK_Pin)==0)
						SmState_Botao1 = STATE_BotaoON;
					else
						SmState_Botao1 = STATE_DEBOUNCE;
				}
	}

}

void Rodar_Maquina_Botao1(void)
{
	if(SmState_Botao1 < NUM_STATES)
	{
		(*StateMachine_Botao1[SmState_Botao1].func)();
	}
	else
	{
		return;
	}
}
