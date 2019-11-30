#include "Interpreter2FSM.h"
char RightSymbol2 = 'R';
char LeftSymbol2 = 'L';
char NeutralSymbol2 = 'N';
char ATKSymbol2 = 'A';
char EdgeSymbol2 = 'E';

uint32_t adc_value2 = 0;
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

typedef struct
{
	StateType_Int2 State;
	void (*func)(void);
}StateMachineType_Int2;

StateMachineType_Int2 StateMachine_Interpretador2[] =
{
		{STATE_Right_Int2,Sm_Right_Int2},
		{STATE_RightPressed_Int2,Sm_RightPressed_Int2},
		{STATE_Left_Int2,Sm_Left_Int2},
		{STATE_LeftPressed_Int2,Sm_LeftPressed_Int2},
		{STATE_NeutralPressed_Int2, Sm_NeutralPressed_Int2},
		{STATE_Neutral_Int2,Sm_Neutral_Int2},
		{STATE_DEBOUNCE_Int2, Sm_DEBOUNCE_Int2},
		{STATE_ATK_Int2,Sm_ATK_Int2},
		{STATE_ATKPressed_Int2,Sm_ATKPressed_Int2},
		{STATE_Edge_Int2,Sm_Edge_Int2},
};

StateType_Int2 SmState_Int2 = STATE_DEBOUNCE_Int2;


uint32_t P2_INTERPRETER(uint32_t value)
{
	/// Direcional:
	///     8
	///  4 5 6
	///     2
	/// 4 = Esquerda/Back
	/// 5 = Neutro
	/// 6 = Direita/Forward
	if(SmState_Botao1==STATE_BotaoON)
	{
		return ATK_2;
	}

	if(value>4050 && value<=4095)
	{
		return DIREITA_FRENTE_2;
	}
	else
	{
		if(value>4095 || value<=2000)
		{
			return ESQUER_ATRAS_2;
		}
		else
		{
			return NEUTRO_2;
		}
	}
}

void Sm_Right_Int2(void)
{
	AdicionarNaLista1(&RightSymbol2);
	SmState_Int2=STATE_RightPressed_Int2;
}

void Sm_Left_Int2(void)
{
	AdicionarNaLista1(&LeftSymbol2);
	SmState_Int2=STATE_LeftPressed_Int2;
}

void Sm_Neutral_Int2(void)
{
	AdicionarNaLista1(&NeutralSymbol2);
	SmState_Int2=STATE_NeutralPressed_Int2;
}

void Sm_ATK_Int2(void)
{
	AdicionarNaLista1(&ATKSymbol2);
	SmState_Int2=STATE_ATKPressed_Int2;
}

void Sm_RightPressed_Int2(void)
{
   #ifdef DEBUG
	print_seguro(1,1,"state: rpr");
   #endif
	adc_value2 = HAL_ADC_GetValue (&hadc2);
	switch(P2_INTERPRETER(adc_value2))
	{
					case DIREITA_FRENTE_2:
						SmState_Int2=STATE_RightPressed_Int2;
						break;
					default:
						SmState_Int2=STATE_DEBOUNCE_Int2;
	}
}

void Sm_NeutralPressed_Int2(void)
{
	#ifdef DEBUG
	print_seguro(1,1,"state: npr");
   #endif

	adc_value2 = HAL_ADC_GetValue (&hadc2);
	switch(P2_INTERPRETER(adc_value2))
	{
					case NEUTRO_2:
						SmState_Int2=STATE_NeutralPressed_Int2;
						break;
					default:
						SmState_Int2=STATE_DEBOUNCE_Int2;
	}
}

void Sm_ATKPressed_Int2(void)
{

	#ifdef DEBUG
	print_seguro(1,1,"state: atp");
	#endif
	adc_value2 = HAL_ADC_GetValue (&hadc2);
	switch(P2_INTERPRETER(adc_value2))
	{
					case ATK_2:
						SmState_Int2=STATE_ATKPressed_Int2;
						break;
					default:
						SmState_Int2=STATE_Edge_Int2;
	}
}
void Sm_LeftPressed_Int2(void)
{
	#ifdef DEBUG
	print_seguro(1,1,"state: lpr");
	#endif
	adc_value2 = HAL_ADC_GetValue (&hadc2);
	switch(P2_INTERPRETER(adc_value2))
	{
					case ESQUER_ATRAS_2:
						SmState_Int2=STATE_LeftPressed_Int2;
						break;
					default:
						SmState_Int2=STATE_DEBOUNCE_Int2;
	}
}
void Sm_Edge_Int2(void)
{
	adc_value2 = HAL_ADC_GetValue (&hadc2);
	osDelay(DELAY_INT2*15);
	switch(P2_INTERPRETER(adc_value2))
	{
					case ATK_2:
						SmState_Int2=STATE_ATKPressed_Int2;
						break;
					default:
						SmState_Int2=STATE_DEBOUNCE_Int2;
	}
}

void Sm_DEBOUNCE_Int2(void)
{
	#ifdef DEBUG
	print_seguro(1,1,"state: dbo");
	#endif
	adc_value2 = HAL_ADC_GetValue (&hadc2);

	switch(P2_INTERPRETER(adc_value2))
	{
					case DIREITA_FRENTE_2:
						osDelay(DELAY_INT2);
						adc_value2 = HAL_ADC_GetValue (&hadc2);
						if(P2_INTERPRETER(adc_value2) == DIREITA_FRENTE_2)
							SmState_Int2=STATE_Right_Int2;
						else
							SmState_Int2=STATE_DEBOUNCE_Int2;
						break;
					case ESQUER_ATRAS_2:
						osDelay(DELAY_INT2);
						adc_value2 = HAL_ADC_GetValue (&hadc2);
						if(P2_INTERPRETER(adc_value2) == ESQUER_ATRAS_2)
							SmState_Int2=STATE_Left_Int2;
						else
							SmState_Int2=STATE_DEBOUNCE_Int2;
						break;
					case NEUTRO_2:
						osDelay(DELAY_INT2*20);
						adc_value2 = HAL_ADC_GetValue (&hadc2);
						if(P2_INTERPRETER(adc_value2) == NEUTRO_2)
							SmState_Int2=STATE_Neutral_Int2;
						else
							SmState_Int2=STATE_DEBOUNCE_Int2;
						break;
					case ATK_2:
						osDelay(DELAY_INT2);
						adc_value2 = HAL_ADC_GetValue (&hadc2);
						if(P2_INTERPRETER(adc_value2) == ATK_2)
							SmState_Int2=STATE_ATK_Int2;
						else
							SmState_Int2=STATE_DEBOUNCE_Int2;
						break;
						break;
					default:
						SmState_Int2=STATE_DEBOUNCE_Int2;
	}
}


void Rodar_Maquina_Interpretador2(void)
{
	osDelay(10);
	HAL_ADC_PollForConversion (&hadc2, 1000);
	if(SmState_Int2 < NUM_STATES_Int2)
	{
		#ifdef DEBUG
		print_seguro(20,20,input_buffer1);
		#endif
		(*StateMachine_Interpretador2[SmState_Int2].func)();
	}
	else
	{
		return;
	}
}

