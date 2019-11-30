/*
 * delay_asm.h
 *
 *  Created on: Aug 23, 2019
 *      Author: Aluno
 */

#ifndef DELAY_ASM_H_
#define DELAY_ASM_H_
#include "stm32f1xx_hal_def.h"
void prep_asm();
void atraso_us(uint32_t valor);
void atraso_ms(uint32_t valor);
void atraso_loops(uint32_t valor);

#endif /* DELAY_ASM_H_ */
