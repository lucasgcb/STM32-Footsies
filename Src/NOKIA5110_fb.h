#ifndef NOKIA5110_H_
#define NOKIA5110_H_

#include "stm32f1xx_hal.h"
#include "delay.h"
#include "cmsis_os.h"
#include "defPrincipais.h"
#include "globais.h"
#include "main.h"
#include <stdlib.h>

//-------------------------------------------------------------------------------------
// RST (A7)
#define SET_RST()		HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET)
#define CLR_RST()		HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET)

// CE (A6)
#define SET_CE()		HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET)
#define CLR_CE()		HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET)

// DC (A5)
#define SET_DC()		HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET)
#define CLR_DC()		HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET)

// DIN (A4)
#define SET_DIN()		HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, GPIO_PIN_SET)
#define CLR_DIN()		HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, GPIO_PIN_RESET)

// CLK (A3)
#define SET_CLK()		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET)
#define CLR_CLK()		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET)

//-------------------------------------------------------------------------------------
#define PULSO_CLK() atraso_us(1); SET_CLK(); atraso_us(1); CLR_CLK()

#define INVERTE_PIXELS()		cmd_LCD(0x0D)
#define NORMALIZA_PIXELS()		cmd_LCD(0x0C)
//-------------------------------------------------------------------------------------


void print_seguro(uint32_t x,uint32_t y, char *buff);
void print_figura_seguro(pontos_t *p, const figura_t *figura);
void print_figura_invertido_seguro(pontos_t *p, const figura_t *figura);
void deleta_figura_seguro(pontos_t *p, const figura_t *figura);
void deleta_figura_invertido_seguro(pontos_t *p, const figura_t *figura);
void caceta();
void cmd_LCD(uint32_t data);
void data_LCD(uint32_t data);
void inic_LCD();
void goto_XY(uint32_t x, uint32_t y);
void escreve2fb(unsigned char imagem[])	;
void imprime_LCD();
void caractere_LCD(char character);
void string_LCD(char *msg);
void limpa_LCD();

// Funções do Borges
void string_LCD_Nr(char * msg, uint32_t valor, uint32_t quant2Print);

void desenha_pixel(uint32_t x, uint32_t y, uint32_t propriedade);
void desenha_linha(pontos_t *coord, uint32_t prop);
void desenha_circulo(int32_t x0, int32_t y0, int32_t radius, uint32_t prop);
void desenha_retangulo( pontos_t *t, uint32_t prop);
void desenha_triangulo(pontos_t *p, uint32_t prop);
void desenha_fig( pontos_t *p, const figura_t *figura);
void desenha_fig_invertido( pontos_t *p, const figura_t *f);
void deleta_fig( pontos_t *p, const figura_t *figura);
void deleta_fig_invertido(pontos_t *p, const figura_t *figura);

void escreve_Nr_Peq(uint32_t x, uint32_t y, int32_t valor, uint32_t quant2Print);

//-------------------------------------------------------------------------------------
#endif /* NOKIA5110_H_ */
