#ifndef CONTROLTRANSFERINSTRUCTIONS_H
#define CONTROLTRANSFERINSTRUCTIONS_H

#include "Controller.h"

/** Retira o primeiro valor da pilha de operandos e compara com zero.
* Se a comparação for bem sucedida (== 0), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int ifeq(Interpretador*); /*0x99*/

/** Retira o primeiro valor da pilha de operandos e compara com zero.
* Se a comparação for bem sucedida (!= 0), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int ifne(Interpretador*); /*0x9A*/

/** Retira o primeiro valor da pilha de operandos e compara com zero.
* Se a comparação for bem sucedida (< 0), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int iflt(Interpretador*); /*0x9B*/

/** Retira o primeiro valor da pilha de operandos e compara com zero.
* Se a comparação for bem sucedida (>= 0), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int ifge(Interpretador*); /*0x9C*/

/** Retira o primeiro valor da pilha de operandos e compara com zero.
* Se a comparação for bem sucedida (> 0), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int ifgt(Interpretador*); /*0x9D*/

/** Retira o primeiro valor da pilha de operandos e compara com zero.
* Se a comparação for bem sucedida (<= 0), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int ifle(Interpretador*); /*0x9E*/

/** Retira os dois primeiros valores da pilha de operandos e os compara. Ambos devem ser do tipo int.
* Se a comparação for bem sucedida (valor1 == valor2), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int if_icmpeq(Interpretador*); /*0x9F*/

/** Retira os dois primeiros valores da pilha de operandos e os compara. Ambos devem ser do tipo int.
* Se a comparação for bem sucedida (valor1 != valor2), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int if_icmpne(Interpretador*); /*0xA0*/

/** Retira os dois primeiros valores da pilha de operandos e os compara. Ambos devem ser do tipo int.
* Se a comparação for bem sucedida (valor1 < valor2), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int if_icmplt(Interpretador*); /*0xA1*/

/** Retira os dois primeiros valores da pilha de operandos e os compara. Ambos devem ser do tipo int.
* Se a comparação for bem sucedida (valor1 >= valor2), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int if_icmpge(Interpretador*); /*0xA2*/

/** Retira os dois primeiros valores da pilha de operandos e os compara. Ambos devem ser do tipo int.
* Se a comparação for bem sucedida (valor1 > valor2), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int if_icmpgt(Interpretador*); /*0xA3*/

/** Retira os dois primeiros valores da pilha de operandos e os compara. Ambos devem ser do tipo int.
* Se a comparação for bem sucedida (valor1 <= valor2), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int if_icmple(Interpretador*); /*0xA4*/

/** Retira os dois primeiros valores da pilha de operandos e os compara. Ambos devem ser do tipo referenceType.
* Se a comparação for bem sucedida (valor1 == valor2), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int if_acmpeq(Interpretador*); /*0xA5*/

/** Retira os dois primeiros valores da pilha de operandos e os compara. Ambos devem ser do tipo referenceType.
* Se a comparação for bem sucedida (valor1 != valor2), pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int if_acmpne(Interpretador*); /*0xA6*/

/** pc = (branchbyte1 << 8) | branchbyte2
*/
int goto_(Interpretador*); /*0xA7*/

/** Insere na pilha o endereço da instrução seguinte.
* pc = (branchbyte1 << 8) | branchbyte2
*/
int jsr(Interpretador*); /*0xA8*/

/** Lê um index e usa ele para acessar uma posição no vetor de variáveis locais. O valor desta posição deve ser do tipo returnAddress.
* pc = localVarArray[index]
*/
int ret(Interpretador*); /*0xA9*/


int tableswitch(Interpretador*); /*0xAA*/


int lookupswitch(Interpretador*); /*0xAB*/

/** Retira o primeiro valor da pilha de operandos e verifica se é NULL. O valor deve ser do tipo referenceType.
* Se a comparação for bem sucedida, pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int ifnull(Interpretador*); /*0xC6*/

/** Retira o primeiro valor da pilha de operandos e verifica se não é NULL. O valor deve ser do tipo referenceType.
* Se a comparação for bem sucedida, pc = (branchbyte1 << 8) | branchbyte2
* Se não, segue para a próxima instrução
*/
int ifnonnull(Interpretador*); /*0xC7*/

/** pc = (branchbyte1 << 24) | (branchbyte2 << 16) | (branchbyte3 << 8) | branchbyte4
*/
int goto_w(Interpretador*); /*0xC8*/

/** Insere na pilha o endereço da instrução seguinte.
* pc = (branchbyte1 << 24) | (branchbyte2 << 16) | (branchbyte3 << 8) | branchbyte4
*/
int jsr_w(Interpretador*); /*0xC9*/

#endif
