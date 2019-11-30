/*
 * delay_asm.c
 *
 *  Created on: Aug 23, 2019
 *      Author: Aluno
 */

/*Assembler passado em aula:
 * __asm__ volatile ("movw r1, #:lower16:const_ms \n\t"
				  "movt r1, #:upper16:const_ms \n\t" // Modificar para movt
				  "muls r0,r0, r1 \n\t"
				  "subs r0,r0,#1 \n\t"
				  "bme \n \t");
*/
// Exemplo de entrada/saida:
// unsigned int DataIn=5, DataOut=0; /* variables for input and output */
//	__asm (
//	 "mov r0, %0\n" // Carrega DataIn em r0
//	 "mov r3, #5\n" // Carrega 5 em registrador 3
//	 "udiv r0, r0, r3\n" // Divide valor em r0 pelo valor em r3, guarda em r0
//	 "mov %1, r0\n" // Salva valor de r0 em DataOut
//	 :"=r" (DataOut) : "r" (DataIn) : "cc", "r3" );
//
// Exemplo de loop:
//	__asm volatile (
//		 "mov r0, %0 \n\t" // Move valor para r0
//		 "L%=: \n\t" // Label
//		 "subs r0, r0, #1 \n\t" // Subtrai 1 de r0
//		 "cbz r0, done%= \n\t" //Se flag de zero estiver apagada, vá para L. CBZ Pula apenas para frente.
//		 "b L%=  \n\t" //Volte pro começo
//		 "done%=: \n\t"
//		 :"=r" (valorsaida): "r" (valor) : "cc", "memory", "r0" );

#include "stm32f1xx_hal.h"
void prep_asm() // Chamar no main
{
	asm(".equ fcpu, 24000000 \n\t"); // Define constante com a freq da cpu
	asm(".equ const_ms, fcpu/4000 \n\t"); // Define constante para contar um milisegundo
	asm(".equ const_us, fcpu/4000000 \n\t"); // Define constante para contra um microsegundo
}

void atraso_ms(uint32_t valor)
{
	asm volatile("mov r1, #const_ms \n\t" // guarda valor da constante milisegundo em r1
				 "mul r1,r1, %0 \n\t" // multiplica pelo valor de entrada
				 "r_ms%=: \n\t" // inicia loop, %= é um numero unico para essa call
				 "subs r1,r1,#1 \n\t" //subtrai 1 de r1, guarda em r1
				 "bne r_ms%= \n\t" // compara se r1 == 0, pula para r_ms se falso
				 ::"r" (valor): "cc", "r1" ); // define variavel de c para entrada,
											  // O "cc" clobber indica que o assembler modifica o registrador de flags
											  // "r1" clobber indica que r1 é modificado

	return;
}


void atraso_us(uint32_t valor)
{
	asm volatile("mov r1, #const_us \n\t" // guarda em r1 valor da constante microsegundo para a frequencia
				 "mul r1,r1, %0 \n\t" // multiplica pela pelo valor de entrada
				 "r_ms%=: \n\t" // inicia loop, %= é um numero unico para essa call
				 "subs r1,r1,#1 \n\t" //subtrai 1 de r1, guarda em r1
				 "bne r_ms%= \n\t" // compara se r1 == 0, pula para r_ms se falso
				 ::"r" (valor): "cc", "r1" ); // define variavel de c para entrada,
											  // O "cc" clobber indica que o assembler modifica o registrador de flags
											  // "r1" clobber indica que r1 é modificado


	return;
}


void atraso_loops(uint32_t valor)
{
	volatile uint32_t index = 0; // Mantem valor da variavel
	for(index = 520 * valor; index != 0; index--) {} //só deus sabe
}
