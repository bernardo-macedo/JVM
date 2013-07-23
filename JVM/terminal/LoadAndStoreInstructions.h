#ifndef LOADANDSTOREINSTRUCTIONS_H
#define LOADANDSTOREINSTRUCTIONS_H

#include "Controller.h"
#include "ClassStructure.h"
#include "InstructionManager.h"

/** Chamada para substituir instruções não implementadas */
int nop(Interpretador*);
/** Insere na pilha de operandos do frame corrente uma referência nula */
int aconst_null(Interpretador*); /*0x01*/
/** Insere na pilha de operandos do frame corrente a constante int -1 */
int iconst_m1(Interpretador*); /*0x02*/
/** Insere na pilha de operandos do frame corrente a constante int 0 */
int iconst_0(Interpretador*); /*0x03*/
/** Insere na pilha de operandos do frame corrente a constante int 1 */
int iconst_1(Interpretador*); /*0x04*/
/** Insere na pilha de operandos do frame corrente a constante int 2 */
int iconst_2(Interpretador*); /*0x05*/
/** Insere na pilha de operandos do frame corrente a constante int 3 */
int iconst_3(Interpretador*); /*0x06*/
/** Insere na pilha de operandos do frame corrente a constante int 4 */
int iconst_4(Interpretador*); /*0x07*/
/** Insere na pilha de operandos do frame corrente a constante int 5 */
int iconst_5(Interpretador*); /*0x08*/
/** Insere na pilha de operandos do frame corrente a constante long 0 */
int lconst_0(Interpretador*); /*0x09*/
/** Insere na pilha de operandos do frame corrente a constante long 1 */
int lconst_1(Interpretador*); /*0x0A*/
/** Insere na pilha de operandos do frame corrente a constante float 0.0 */
int fconst_0(Interpretador*); /*0x0B*/
/** Insere na pilha de operandos do frame corrente a constante float 1.0 */
int fconst_1(Interpretador*); /*0x0C*/
/** Insere na pilha de operandos do frame corrente a constante float 2.0 */
int fconst_2(Interpretador*); /*0x0D*/
/** Insere na pilha de operandos do frame corrente a constante double 0.0 */
int dconst_0(Interpretador*); /*0x0E*/
/** Insere na pilha de operandos do frame corrente a constante double 1.0 */
int dconst_1(Interpretador*); /*0x0F*/
/** Insere na pilha de operandos do frame corrente o valor (u1) apontado pelo índice
*   representado pelo byte que segue logo após o opcode
*/
int bipush(Interpretador*); /*0x10*/
/** Insere na pilha de operandos do frame corrente o valor (u2) apontado pelo índice
*   representado pelos 2 bytes que seguem logo após o opcode
*/
int sipush(Interpretador*); /*0x11*/
/** Insere na pilha de operandos do frame corrente o valor (32 bits) presente no pool de constantes
*   apontado pelo índice representado pelo byte que segue logo após o opcode
*/
int ldc(Interpretador*); /*0x12*/
/** Insere na pilha de operandos do frame corrente o valor (32 bits) presente no pool de constantes
*   apontado pelo índice representado pelos 2 bytes que seguem logo após o opcode
*/
int ldc_w(Interpretador*); /*0x13*/
/** Insere na pilha de operandos do frame corrente o valor (64 bits) presente no pool de constantes
*   apontado pelo índice representado pelos 2 bytes que seguem logo após o opcode
*/
int ldc2_w(Interpretador*); /*0x14*/
/** Insere na pilha de operandos do frame corrente o int presente no vetor de variaveis locais
*   apontado pelo índice representado pelo byte que segue logo após o opcode
*/
int iload(Interpretador*); /*0x15*/
/** Insere na pilha de operandos do frame corrente o long presente no vetor de variaveis locais
*   apontado pelo índice (e índice + 1) representado pelo byte que segue logo após o opcode
*/
int lload(Interpretador*); /*0x16*/
/** Insere na pilha de operandos do frame corrente o float presente no vetor de variaveis locais
*   apontado pelo índice representado pelo byte que segue logo após o opcode
*/
int fload(Interpretador*); /*0x17*/
/** Insere na pilha de operandos do frame corrente o double presente no vetor de variaveis locais
*   apontado pelo índice (e índice + 1) representado pelo byte que segue logo após o opcode
*/
int dload(Interpretador*); /*0x18*/
/** Insere na pilha de operandos do frame corrente a referência de objeto presente no vetor de variaveis locais
*   apontado pelo índice representado pelo byte que segue logo após o opcode
*/
int aload(Interpretador*); /*0x19*/
/** Insere na pilha de operandos do frame corrente o int presente no vetor de variaveis locais
*   apontado pelo índice 0
*/
int iload_0(Interpretador*); /*0x1A*/
/** Insere na pilha de operandos do frame corrente o int presente no vetor de variaveis locais
*   apontado pelo índice 1
*/
int iload_1(Interpretador*); /*0x1B*/
/** Insere na pilha de operandos do frame corrente o int presente no vetor de variaveis locais
*   apontado pelo índice 2
*/
int iload_2(Interpretador*); /*0x1C*/
/** Insere na pilha de operandos do frame corrente o int presente no vetor de variaveis locais
*   apontado pelo índice 3
*/
int iload_3(Interpretador*); /*0x1D*/
/** Insere na pilha de operandos do frame corrente o long presente no vetor de variaveis locais
*   apontado pelo índice 0
*/
int lload_0(Interpretador*); /*0x1E*/
/** Insere na pilha de operandos do frame corrente o long presente no vetor de variaveis locais
*   apontado pelo índice 1
*/
int lload_1(Interpretador*); /*0x1F*/
/** Insere na pilha de operandos do frame corrente o long presente no vetor de variaveis locais
*   apontado pelo índice 2
*/
int lload_2(Interpretador*); /*0x20*/
/** Insere na pilha de operandos do frame corrente o long presente no vetor de variaveis locais
*   apontado pelo índice 3
*/
int lload_3(Interpretador*); /*0x21*/
/** Insere na pilha de operandos do frame corrente o float presente no vetor de variaveis locais
*   apontado pelo índice 0
*/
int fload_0(Interpretador*); /*0x22*/
/** Insere na pilha de operandos do frame corrente o float presente no vetor de variaveis locais
*   apontado pelo índice 1
*/
int fload_1(Interpretador*); /*0x23*/
/** Insere na pilha de operandos do frame corrente o float presente no vetor de variaveis locais
*   apontado pelo índice 2
*/
int fload_2(Interpretador*); /*0x24*/
/** Insere na pilha de operandos do frame corrente o float presente no vetor de variaveis locais
*   apontado pelo índice 3
*/
int fload_3(Interpretador*); /*0x25*/
/** Insere na pilha de operandos do frame corrente o double presente no vetor de variaveis locais
*   apontado pelo índice 0
*/
int dload_0(Interpretador*); /*0x26*/
/** Insere na pilha de operandos do frame corrente o double presente no vetor de variaveis locais
*   apontado pelo índice 1
*/
int dload_1(Interpretador*); /*0x27*/
/** Insere na pilha de operandos do frame corrente o double presente no vetor de variaveis locais
*   apontado pelo índice 2
*/
int dload_2(Interpretador*); /*0x28*/
/** Insere na pilha de operandos do frame corrente o double presente no vetor de variaveis locais
*   apontado pelo índice 3
*/
int dload_3(Interpretador*); /*0x29*/
/** Insere na pilha de operandos do frame corrente a referência de objeto presente no vetor de variaveis locais
*   apontado pelo índice 0
*/
int aload_0(Interpretador*); /*0x2A*/
/** Insere na pilha de operandos do frame corrente a referência de objeto presente no vetor de variaveis locais
*   apontado pelo índice 1
*/
int aload_1(Interpretador*); /*0x2B*/
/** Insere na pilha de operandos do frame corrente a referência de objeto presente no vetor de variaveis locais
*   apontado pelo índice 2
*/
int aload_2(Interpretador*); /*0x2C*/
/** Insere na pilha de operandos do frame corrente a referência de objeto presente no vetor de variaveis locais
*   apontado pelo índice 3
*/
int aload_3(Interpretador*); /*0x2D*/
/** Retira da pilha de operandos o primeiro valor e insere no vetor de variáveis locais como int
*   no indice representado pelo byte que segue logo após o opcode
*/
int istore(Interpretador*); /*0x36*/
/** Retira da pilha de operandos o primeiro valor e insere no vetor de variáveis locais como long
*   no indice (e indice + 1) representado pelo byte que segue logo após o opcode
*/
int lstore(Interpretador*); /*0x37*/
/** Retira da pilha de operandos o primeiro valor e insere no vetor de variáveis locais como float
*   no indice representado pelo byte que segue logo após o opcode
*/
int fstore(Interpretador*); /*0x38*/
/** Retira da pilha de operandos o primeiro valor e insere no vetor de variáveis locais como double
*   no indice (e indice + 1)  representado pelo byte que segue logo após o opcode
*/
int dstore(Interpretador*); /*0x39*/
int astore(Interpretador*); /*0x3A*/
int istore_0(Interpretador*); /*0x3B*/
int istore_1(Interpretador*); /*0x3C*/
int istore_2(Interpretador*); /*0x3D*/
int istore_3(Interpretador*); /*0x3E*/
int lstore_0(Interpretador*); /*0x3F*/
int lstore_1(Interpretador*); /*0x40*/
int lstore_2(Interpretador*); /*0x41*/
int lstore_3(Interpretador*); /*0x42*/
int fstore_0(Interpretador*); /*0x43*/
int fstore_1(Interpretador*); /*0x44*/
int fstore_2(Interpretador*); /*0x45*/
int fstore_3(Interpretador*); /*0x46*/
int dstore_0(Interpretador*); /*0x47*/
int dstore_1(Interpretador*); /*0x48*/
int dstore_2(Interpretador*); /*0x49*/
int dstore_3(Interpretador*); /*0x4A*/
int astore_0(Interpretador*); /*0x4B*/
int astore_1(Interpretador*); /*0x4C*/
int astore_2(Interpretador*); /*0x4D*/
int astore_3(Interpretador*); /*0x4E*/

int wide(Interpretador*); /*0xC4*/

#endif
