#include "main.h"
#include "stm32f1xx_hal_def.h"
#include "cmsis_os.h"

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
RTC_HandleTypeDef hrtc;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ADC1_Init(void);
void MX_ADC2_Init(void);
void MX_RTC_Init(void);
