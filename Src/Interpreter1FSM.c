#include "Interpreter1FSM.h"
char RightSymbol = 'R';
char LeftSymbol = 'L';
char NeutralSymbol = 'N';
char ATKSymbol = 'A';
char EdgeSymbol = 'E';

uint32_t adc_value1 = 0;
char  input_buffer1[12] = " N N N N N ";

void AdicionarNaLista1(char *add)
{
    if( xSemaphoreTake( input1, 1000 ) == pdTRUE )
 	{
    	  for(int i=9; i>=2;i=i-2)
    	  {
    		  input_buffer1[i] = input_buffer1[i-2];
    	  }
    	  input_buffer1[1] = *add;
		xSemaphoreGive( input1);
	 }
}

char  lerDoInput1(uint8_t index)
{
	char ret = '\0';
    if( xSemaphoreTake( input1, 1000 ) == pdTRUE )
 	{
    	ret = input_buffer1[index];
		xSemaphoreGive( input1);
	 }
    return ret;
}

typedef struct
{
	StateType_Int1 State;
	void (*func)(void);
}StateMachineType_Int1;

StateMachineType_Int1 StateMachine_Interpretador[] =
{
		{STATE_Right_Int1,Sm_Right_Int1},
		{STATE_RightPressed_Int1,Sm_RightPressed_Int1},
		{STATE_Left_Int1,Sm_Left_Int1},
		{STATE_LeftPressed_Int1,Sm_LeftPressed_Int1},
		{STATE_NeutralPressed_Int1, Sm_NeutralPressed_Int1},
		{STATE_Neutral_Int1,Sm_Neutral_Int1},
		{STATE_DEBOUNCE_Int1, Sm_DEBOUNCE_Int1},
		{STATE_ATK_Int1,Sm_ATK_Int1},
		{STATE_ATKPressed_Int1,Sm_ATKPressed_Int1},
		{STATE_Edge_Int1,Sm_Edge_Int1},
};

StateType_Int1 SmState_Int1 = STATE_DEBOUNCE_Int1;


uint32_t P1_INTERPRETER(uint32_t value)
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
		return ATK_1;
	}

	if(value>4050 && value<=4095)
	{
		return DIREITA_FRENTE_1;
	}
	else
	{
		if(value>4095 || value<=2000)
		{
			return ESQUER_ATRAS_1;
		}
		else
		{
			return NEUTRO_1;
		}
	}
}

void Sm_Right_Int1(void)
{
	AdicionarNaLista1(&RightSymbol);
	SmState_Int1=STATE_RightPressed_Int1;
}

void Sm_Left_Int1(void)
{
	AdicionarNaLista1(&LeftSymbol);
	SmState_Int1=STATE_LeftPressed_Int1;
}

void Sm_Neutral_Int1(void)
{
	AdicionarNaLista1(&NeutralSymbol);
	SmState_Int1=STATE_NeutralPressed_Int1;
}

void Sm_ATK_Int1(void)
{
	AdicionarNaLista1(&ATKSymbol);
	SmState_Int1=STATE_ATKPressed_Int1;
}

void Sm_RightPressed_Int1(void)
{
   #ifdef DEBUG
	print_seguro(1,1,"state: rpr");
   #endif
	adc_value1 = HAL_ADC_GetValue (&hadc1);
	switch(P1_INTERPRETER(adc_value1))
	{
					case DIREITA_FRENTE_1:
						SmState_Int1=STATE_RightPressed_Int1;
						break;
					default:
						SmState_Int1=STATE_DEBOUNCE_Int1;
	}
}

void Sm_NeutralPressed_Int1(void)
{
	#ifdef DEBUG
	print_seguro(1,1,"state: npr");
   #endif

	adc_value1 = HAL_ADC_GetValue (&hadc1);
	switch(P1_INTERPRETER(adc_value1))
	{
					case NEUTRO_1:
						SmState_Int1=STATE_NeutralPressed_Int1;
						break;
					default:
						SmState_Int1=STATE_DEBOUNCE_Int1;
	}
}

void Sm_ATKPressed_Int1(void)
{

	#ifdef DEBUG
	print_seguro(1,1,"state: atp");
	#endif
	adc_value1 = HAL_ADC_GetValue (&hadc1);
	switch(P1_INTERPRETER(adc_value1))
	{
					case ATK_1:
						SmState_Int1=STATE_ATKPressed_Int1;
						break;
					default:
						SmState_Int1=STATE_Edge_Int1;
	}
}
void Sm_LeftPressed_Int1(void)
{
	#ifdef DEBUG
	print_seguro(1,1,"state: lpr");
	#endif
	adc_value1 = HAL_ADC_GetValue (&hadc1);
	switch(P1_INTERPRETER(adc_value1))
	{
					case ESQUER_ATRAS_1:
						SmState_Int1=STATE_LeftPressed_Int1;
						break;
					default:
						SmState_Int1=STATE_DEBOUNCE_Int1;
	}
}
void Sm_Edge_Int1(void)
{
	adc_value1 = HAL_ADC_GetValue (&hadc1);
	osDelay(DELAY_INT1*15);
	switch(P1_INTERPRETER(adc_value1))
	{
					case ATK_1:
						SmState_Int1=STATE_ATKPressed_Int1;
						break;
					default:
						SmState_Int1=STATE_DEBOUNCE_Int1;
	}
}

void Sm_DEBOUNCE_Int1(void)
{
	#ifdef DEBUG
	print_seguro(1,1,"state: dbo");
	#endif
	adc_value1 = HAL_ADC_GetValue (&hadc1);

	switch(P1_INTERPRETER(adc_value1))
	{
					case DIREITA_FRENTE_1:
						osDelay(DELAY_INT1);
						adc_value1 = HAL_ADC_GetValue (&hadc1);
						if(P1_INTERPRETER(adc_value1) == DIREITA_FRENTE_1)
							SmState_Int1=STATE_Right_Int1;
						else
							SmState_Int1=STATE_DEBOUNCE_Int1;
						break;
					case ESQUER_ATRAS_1:
						osDelay(DELAY_INT1);
						adc_value1 = HAL_ADC_GetValue (&hadc1);
						if(P1_INTERPRETER(adc_value1) == ESQUER_ATRAS_1)
							SmState_Int1=STATE_Left_Int1;
						else
							SmState_Int1=STATE_DEBOUNCE_Int1;
						break;
					case NEUTRO_1:
						osDelay(DELAY_INT1*20);
						adc_value1 = HAL_ADC_GetValue (&hadc1);
						if(P1_INTERPRETER(adc_value1) == NEUTRO_1)
							SmState_Int1=STATE_Neutral_Int1;
						else
							SmState_Int1=STATE_DEBOUNCE_Int1;
						break;
					case ATK_1:
						osDelay(DELAY_INT1);
						adc_value1 = HAL_ADC_GetValue (&hadc1);
						if(P1_INTERPRETER(adc_value1) == ATK_1)
							SmState_Int1=STATE_ATK_Int1;
						else
							SmState_Int1=STATE_DEBOUNCE_Int1;
						break;
						break;
					default:
						SmState_Int1=STATE_DEBOUNCE_Int1;
	}
}


void Rodar_Maquina_Interpretador(void)
{
	osDelay(10);
	HAL_ADC_PollForConversion (&hadc1, 1000);
	if(SmState_Int1 < NUM_STATES_Int1)
	{
		#ifdef DEBUG
		print_seguro(20,20,input_buffer1);
		#endif
		(*StateMachine_Interpretador[SmState_Int1].func)();
	}
	else
	{
		return;
	}
}

