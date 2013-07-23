#ifndef OBJECTINSTRUCTIONS_H
#define OBJECTINSTRUCTIONS_H

#include "Controller.h"

/** Insere um valor do tipo int, retirado de um array, na pilha de operandos.
* Retira os dois primeiros operandos da pilha. O primeiro é um index e o segundo, um arrayref.
* Insere na pilha o valor retirado de *(arrayref[index]).
* arrayref, index -> valor
*/
int iaload(Interpretador*); /*0x2E*/

/** Insere um valor do tipo long, retirado de um array, na pilha de operandos.
* Retira os dois primeiros operandos da pilha. O primeiro é um index e o segundo, um arrayref.
* Insere na pilha o valor retirado de *(arrayref[index]).
* arrayref, index -> valor
*/
int laload(Interpretador*); /*0x2F*/

/** Insere um valor do tipo float, retirado de um array, na pilha de operandos.
* Retira os dois primeiros operandos da pilha. O primeiro é um index e o segundo, um arrayref.
* Insere na pilha o valor retirado de *(arrayref[index]).
* arrayref, index -> valor
*/
int faload(Interpretador*); /*0x30*/

/** Insere um valor do tipo double, retirado de um array, na pilha de operandos.
* Retira os dois primeiros operandos da pilha. O primeiro é um index e o segundo, um arrayref.
* Insere na pilha o valor retirado de *(arrayref[index]).
* arrayref, index -> valor
*/
int daload(Interpretador*); /*0x31*/

/** Insere um valor do tipo reference, retirado de um array, na pilha de operandos.
* Retira os dois primeiros operandos da pilha. O primeiro é um index e o segundo, um arrayref.
* Insere na pilha o valor retirado de *(arrayref[index]).
* arrayref, index -> valor
*/
int aaload(Interpretador*); /*0x32*/

/** Insere um valor do tipo int na pilha de operandos.
* Retira os dois primeiros operandos da pilha. O primeiro é um index e o segundo, um arrayref.
* Verifica se o valor de *(arrayref[index]) é um byte ou um boolean.
* Se for um byte, o valor é convertido para um signed int e inserido na pilha.
* Se for um boolean, o valor é convertido para um unsigned int e inserido na pilha.
* arrayref, index -> valor
*/
int baload(Interpretador*); /*0x33*/

/** Insere um valor do tipo int na pilha de operandos.
* Retira os dois primeiros operandos da pilha. O primeiro é um index e o segundo, um arrayref.
* Pega o valor retirado de *(arrayref[index]), que é um char, converte para um unsigned int e o insere na pilha.
* arrayref, index -> valor
*/
int caload(Interpretador*); /*0x34*/

/** Insere um valor do tipo int na pilha de operandos.
* Retira os dois primeiros operandos da pilha. O primeiro é um index e o segundo, um arrayref.
* Pega o valor retirado de *(arrayref[index]), que é um short, converte para um signed int e o insere na pilha.
* arrayref, index -> valor
*/
int saload(Interpretador*); /*0x35*/

/** Insere um int num array de ints, em um dado índice.
* Retira os três primeiros valores da pilha de operandos.
* O primeiro é um valor, do tipo int.
* O segundo é um index, do tipo int.
* O terceiro é um arrayref, que é uma referência para um array de ints.
* O valor deve ser armazenado no array no índice dado por index.
* arrayref, index, valor -> ...
*/
int iastore(Interpretador*); /*0x4F*/

/** Insere um long num array de longs, em um dado índice.
* Retira os três primeiros valores da pilha de operandos.
* O primeiro é um valor, do tipo long.
* O segundo é um index, do tipo int.
* O terceiro é um arrayref, que é uma referência para um array de longs.
* O valor deve ser armazenado no array no índice dado por index.
* arrayref, index, valor -> ...
*/
int lastore(Interpretador*); /*0x50*/

/** Insere um float num array de floats, em um dado índice.
* Retira os três primeiros valores da pilha de operandos.
* O primeiro é um valor, do tipo float.
* O segundo é um index, do tipo int.
* O terceiro é um arrayref, que é uma referência para um array de floats.
* O valor deve ser armazenado no array no índice dado por index.
* arrayref, index, valor -> ...
*/
int fastore(Interpretador*); /*0x51*/

/** Insere um double num array de doubles, em um dado índice.
* Retira os três primeiros valores da pilha de operandos.
* O primeiro é um valor, do tipo double.
* O segundo é um index, do tipo int.
* O terceiro é um arrayref, que é uma referência para um array de doubles.
* O valor deve ser armazenado no array no índice dado por index.
* arrayref, index, valor -> ...
*/
int dastore(Interpretador*); /*0x52*/

/** Insere um reference num array de references, em um dado índice.
* Retira os três primeiros valores da pilha de operandos.
* O primeiro é um valor, do tipo reference.
* O segundo é um index, do tipo int.
* O terceiro é um arrayref, que é uma referência para um array de references.
* O valor deve ser armazenado no array no índice dado por index.
* arrayref, index, valor -> ...
*/
int aastore(Interpretador*); /*0x53*/

/** Insere um byte ou um boolean num array de bytes ou booleans, em um dado índice.
* Retira os três primeiros valores da pilha de operandos.
* O primeiro é um valor, do tipo int.
* O segundo é um index, do tipo int.
* O terceiro é um arrayref, que é uma referência para um array de bytes ou de booleans.
* Se o array for de bytes, o valor deve ser truncado para ficar com 8 bits apenas.
* Se o array for de booleans, o valor deve ser truncado para ficar apenas com seu bit de mais baixa ordem e
* deve ser estendido de zero para ficar com 8 bits.
* O valor deve ser armazenado no array no índice dado por index.
* arrayref, index, valor -> ...
*/
int bastore(Interpretador*); /*0x54*/

/** Insere um char num array de chars, em um dado índice.
* Retira os três primeiros valores da pilha de operandos.
* O primeiro é um valor, do tipo int.
* O segundo é um index, do tipo int.
* O terceiro é um arrayref, que é uma referência para um array de chars.
* O valor deve ser truncado para ficar com o tamanho de um char e
* deve ser armazenado no array no índice dado por index.
* arrayref, index, valor -> ...
*/
int castore(Interpretador*); /*0x55*/

/** Insere um short num array de shorts, em um dado índice.
* Retira os três primeiros valores da pilha de operandos.
* O primeiro é um valor, do tipo int.
* O segundo é um index, do tipo int.
* O terceiro é um arrayref, que é uma referência para um array de shorts.
* O valor deve ser truncado para ficar com o tamanho de um short e
* deve ser armazenado no array no índice dado por index.
* arrayref, index, valor -> ...
*/
int sastore(Interpretador*); /*0x56*/

/** Usa os indexbyte1 e indexbyte2 para construir um indice para acessar o constant pool da classe corrente.
* O item neste índice deve ser uma referência para um field, com o nome e o descritor do field,
* bem como uma referência para a classe ou interface na qual o field se encontra.
* O valor do field é usado para definir o tipo do operando que deve ser colocado na pilha.
*/
int getstatic(Interpretador*); /*0xB2*/

/** Usa os indexbyte1 e indexbyte2 para construir um indice para acessar o constant pool da classe corrente.
* O item neste índice deve ser uma referência para um field, com o nome e o descritor do field,
* bem como uma referência para a classe ou interface na qual o field se encontra.
* O valor retirado da pilha de operandos é usado para setar o valor do field.
*/
int putstatic(Interpretador*); /*0xB3*/

/** Retira o primeiro valor da pilha, que é do tipo referência.
* Lê indexbyte1 e indexbyte2 para formar um índice de acesso ao constant pool da classe corrente.
* O item neste índice deve ser uma referência para um field, com o nome e o descritor dele e uma referência
* para a classe na qual ele se encontra.
* O valor do field referenciado é inserido na pilha de operandos.
*/
int getfield(Interpretador*); /*0xB4*/

/** Retira os dois primeiros valores da pilha, um valor e uma referência.
* Lê indexbyte1 e indexbyte2 para formar um índice de acesso ao constant pool da classe corrente.
* O item neste índice deve ser uma referência para um field, com o nome e o descritor dele e uma referência
* para a classe na qual ele se encontra.
* O valor retirado da pilha de operandos é usado para setar o valor do field referenciado.
*/
int putfield(Interpretador*); /*0xB5*/

/** Cria um novo objeto.
* Insere na pilha de operandos uma referência para o objeto criado.
*/
int new_(Interpretador*); /*0xBB*/

/** Cria um novo array. Seu tamanho é dado pelo primeiro operando da pilha e o codigo atype indica qual vai ser o tipo do array.
* Insere na pilha de operandos uma referência para o array criado.
*/
int newarray(Interpretador*); /*0xBC*/

/** Cria um novo array de referências.
* Insere na pilha de operandos uma referência para o array criado.
*/
int anewarray(Interpretador*); /*0xBD*/

/** Retira o primeiro valor da pilha de operandos, que é uma referência para um array.
* Insere na pilha o tamanho desse array.
*/
int arraylength(Interpretador*); /*0xBE*/


int checkcast(Interpretador*); /*0xC0*/


int instanceof(Interpretador*); /*0xC1*/

/** Cria um array multidimensional.
*/
int multianewarray(Interpretador*); /*0xC5*/


#endif
