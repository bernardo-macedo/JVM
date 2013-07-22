#ifndef ARITHMETICINSTRUCTIONS_H
#define ARITHMETICINSTRUCTIONS_H

#include "InstructionManager.h"
#include "Controller.h"

/* Adição */

/** Retira dois operandos do tipo int da pilha e insere o resultado da soma deles.
* valor1, valor2 -> valor1 + valor2
*/
int iadd(Interpretador*); /*0x60*/

/** Retira dois operandos do tipo long da pilha e insere o resultado da soma deles.
* valor1, valor2 -> valor1 + valor2
*/
int ladd(Interpretador*); /*0x61*/

/** Retira dois operandos do tipo float da pilha e insere o resultado da soma deles.
* valor1, valor2 -> valor1 + valor2
*/
int fadd(Interpretador*); /*0x62*/

/** Retira dois operandos do tipo double da pilha e insere o resultado da soma deles.
* valor1, valor2 -> valor1 + valor2
*/
int dadd(Interpretador*); /*0x63*/

/* Subtração */

/** Retira dois operandos do tipo int da pilha e insere o resultado da subtração deles.
* valor1, valor2 -> valor1 - valor2
*/
int isub(Interpretador*); /*0x64*/

/** Retira dois operandos do tipo long da pilha e insere o resultado da subtração deles.
* valor1, valor2 -> valor1 - valor2
*/
int lsub(Interpretador*); /*0x65*/

/** Retira dois operandos do tipo float da pilha e insere o resultado da subtração deles.
* valor1, valor2 -> valor1 - valor2
*/
int fsub(Interpretador*); /*0x66*/

/** Retira dois operandos do tipo double da pilha e insere o resultado da subtração deles.
* valor1, valor2 -> valor1 - valor2
*/
int dsub(Interpretador*); /*0x67*/

/* Multiplicação */

/** Retira dois operandos do tipo int da pilha e insere o resultado da multiplicação deles.
* valor1, valor2 -> valor1 * valor2
*/
int imul(Interpretador*); /*0x68*/

/** Retira dois operandos do tipo long da pilha e insere o resultado da multiplicação deles.
* valor1, valor2 -> valor1 * valor2
*/
int lmul(Interpretador*); /*0x69*/

/** Retira dois operandos do tipo float da pilha e insere o resultado da multiplicação deles.
* valor1, valor2 -> valor1 * valor2
*/
int fmul(Interpretador*); /*0x6A*/

/** Retira dois operandos do tipo double da pilha e insere o resultado da multiplicação deles.
* valor1, valor2 -> valor1 * valor2
*/
int dmul(Interpretador*); /*0x6B*/

/* Divisão */

/** Retira dois operandos do tipo int da pilha e insere o resultado da divisão deles.
* valor1, valor2 -> valor1 / valor2
*/
int idiv(Interpretador*); /*0x6C*/

/** Retira dois operandos do tipo long da pilha e insere o resultado da divisão deles.
* valor1, valor2 -> valor1 / valor2
*/
int ldiv_(Interpretador*); /*0x6D*/

/** Retira dois operandos do tipo float da pilha e insere o resultado da divisão deles.
* valor1, valor2 -> valor1 / valor2
*/
int fdiv(Interpretador*); /*0x6E*/

/** Retira dois operandos do tipo double da pilha e insere o resultado da divisão deles.
* valor1, valor2 -> valor1 / valor2
*/
int ddiv(Interpretador*); /*0x6F*/

/* Resto */

/** Retira dois operandos do tipo int da pilha e insere o resto da divisão deles.
* valor1, valor2 -> valor1 % valor2
*/
int irem(Interpretador*); /*0x70*/

/** Retira dois operandos do tipo long da pilha e insere o resto da divisão deles.
* valor1, valor2 -> valor1 % valor2
*/
int lrem(Interpretador*); /*0x71*/

/** Retira dois operandos do tipo float da pilha e insere o resto da divisão deles.
* valor1, valor2 -> valor1 % valor2
*/
int frem(Interpretador*); /*0x72*/

/** Retira dois operandos do tipo double da pilha e insere o resto da divisão deles.
* valor1, valor2 -> valor1 % valor2
*/
int drem_(Interpretador*); /*0x73*/

/* Negação */

/** Retira um operando do tipo int da pilha e insere sua negação
* valor -> -valor
*/
int ineg(Interpretador*); /*0x74*/

/** Retira um operando do tipo long da pilha e insere sua negação
* valor -> -valor
*/
int lneg(Interpretador*); /*0x75*/

/** Retira um operando do tipo float da pilha e insere sua negação
* valor -> -valor
*/
int fneg(Interpretador*); /*0x76*/

/** Retira um operando do tipo double da pilha e insere sua negação
* valor -> -valor
*/
int dneg(Interpretador*); /*0x77*/

/* Operações lógicas */

/** Retira dois operandos do tipo int da pilha e insere o resultado do valor1 shiftado à esquerda em s posições,
* em que s é o valor dos 5 bits mais baixos de valor2.
* valor1, valor2 -> valor1 << valor2 and 0x1F
*/
int ishl(Interpretador*); /*0x78*/

/** Retira dois operandos do tipo int da pilha e insere o resultado do valor1 shiftado à direita em s posições,
* em que s é o valor dos 5 bits mais baixos de valor2.
* valor1, valor2 -> valor1 >> valor2 and 0x1F
*/
int ishr(Interpretador*); /*0x79*/

/** Retira dois operandos do tipo int da pilha e insere o resultado do valor1 shiftado à direita em s posições,
* em que s é o valor dos 5 bits mais baixos de valor2 extendidos de 0.
* valor1, valor2 -> valor1 << zero_extended(valor2 and 0x1F)
*/
int iushr(Interpretador*); /*0x7A*/

/** Retira dois operandos do tipo long da pilha e insere o resultado do valor1 shiftado à esquerda em s posições,
* em que s é o valor dos 6 bits mais baixos de valor2.
* valor1, valor2 -> valor1 << valor2 and 0x11F
*/
int lshl(Interpretador*); /*0x7B*/

/** Retira dois operandos do tipo long da pilha e insere o resultado do valor1 shiftado à direita em s posições,
* em que s é o valor dos 6 bits mais baixos de valor2.
* valor1, valor2 -> valor1 << valor2 and 0x11F
*/
int lshr(Interpretador*); /*0x7C*/

/** Retira dois operandos do tipo long da pilha e insere o resultado do valor1 shiftado à direita em s posições,
* em que s é o valor dos 6 bits mais baixos de valor2 extendidos de 0.
* valor1, valor2 -> valor1 << zero_extended(valor2 and 0x11F)
*/
int lushr(Interpretador*); /*0x7D*/

/** Retira dois operandos do tipo int da pilha e insere o resultado do and entre eles.
* valor1, valor2 -> valor1 & valor2
*/
int iand(Interpretador*); /*0x7E*/

/** Retira dois operandos do tipo long da pilha e insere o resultado do and entre eles.
* valor1, valor2 -> valor1 & valor2
*/
int land(Interpretador*); /*0x7F*/

/** Retira dois operandos do tipo int da pilha e insere o resultado do or entre eles.
* valor1, valor2 -> valor1 | valor2
*/
int ior(Interpretador*); /*0x80*/

/** Retira dois operandos do tipo long da pilha e insere o resultado do or entre eles.
* valor1, valor2 -> valor1 | valor2
*/
int lor(Interpretador*); /*0x81*/

/** Retira dois operandos do tipo int da pilha e insere o resultado do xor entre eles.
* valor1, valor2 -> valor1 ^ valor2
*/
int ixor(Interpretador*); /*0x82*/

/** Retira dois operandos do tipo long da pilha e insere o resultado do xor entre eles.
* valor1, valor2 -> valor1 ^ valor2
*/
int lxor(Interpretador*); /*0x83*/

/* Incremento */

/** A variável em localVarArray[index] é incrementada de um valor definido pelo const extendido de sinal.
* index é um byte sem sinal que deve ser um índice no vetor de variáveis locais do frame atual.
* const é um byte com sinal, que deve ser extendido de sinal para um inteiro
*/
int iinc(Interpretador*); /*0x84*/

/* Comparação */

/** Retira dois valores do tipo long da pilha e faz uma comparação entre eles.
* valor1, valor2 -> 1, se valor1 > valor2
* valor1, valor2 -> 0, se valor1 = valor2
* valor1, valor2 -> -1, se valor1 < valor2
*/
int lcmp(Interpretador*); /*0x94*/

/** Retira dois valores do tipo float da pilha e faz uma comparação entre eles.
* valor1, valor2 -> 1, se valor1 > valor2
* valor1, valor2 -> 0, se valor1 = valor2
* valor1, valor2 -> -1, se valor1 < valor2
* valor1, valor2 -> -1, se algum deles for NaN
*/
int fcmpl(Interpretador*); /*0x95*/

/** Retira dois valores do tipo float da pilha e faz uma comparação entre eles.
* valor1, valor2 -> 1, se valor1 > valor2
* valor1, valor2 -> 0, se valor1 = valor2
* valor1, valor2 -> -1, se valor1 < valor2
* valor1, valor2 -> 1, se algum deles for NaN
*/
int fcmpg(Interpretador*); /*0x96*/

/** Retira dois valores do tipo double da pilha e faz uma comparação entre eles.
* valor1, valor2 -> 1, se valor1 > valor2
* valor1, valor2 -> 0, se valor1 = valor2
* valor1, valor2 -> -1, se valor1 < valor2
* valor1, valor2 -> -1, se algum deles for NaN
*/
int dcmpl(Interpretador*); /*0x97*/

/** Retira dois valores do tipo double da pilha e faz uma comparação entre eles.
* valor1, valor2 -> 1, se valor1 > valor2
* valor1, valor2 -> 0, se valor1 = valor2
* valor1, valor2 -> -1, se valor1 < valor2
* valor1, valor2 -> 1, se algum deles for NaN
*/
int dcmpg(Interpretador*); /*0x98*/

#endif
