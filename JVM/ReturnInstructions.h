#ifndef RETURNINSTRUCTIONS_H
#define RETURNINSTRUCTIONS_H

/** Retira o primeiro valor (int) da pilha de operandos do frame atual
* e o insere na pilha de operandos do frame que chamou o frame atual.
*/
int ireturn(Interpretador*); /*0xAC*/

/** Retira o primeiro valor (long) da pilha de operandos do frame atual
* e o insere na pilha de operandos do frame que chamou o frame atual.
*/
int lreturn(Interpretador*); /*0xAD*/

/** Retira o primeiro valor (float) da pilha de operandos do frame atual
* e o insere na pilha de operandos do frame que chamou o frame atual.
*/
int freturn(Interpretador*); /*0xAE*/

/** Retira o primeiro valor (double) da pilha de operandos do frame atual
* e o insere na pilha de operandos do frame que chamou o frame atual.
*/
int dreturn(Interpretador*); /*0xAF*/

/** Retira o primeiro valor (reference) da pilha de operandos do frame atual
* e o insere na pilha de operandos do frame que chamou o frame atual.
*/
int areturn(Interpretador*); /*0xB0*/

/** Retira o primeiro valor (void) da pilha de operandos do frame atual
* e o insere na pilha de operandos do frame que chamou o frame atual.
*/
int return_(Interpretador*);  /*0xB1*/

#endif

