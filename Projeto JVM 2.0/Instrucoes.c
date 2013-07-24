/*
 * Instrucoes.c
 *
 *  Created on: 08/02/2013
 *      Author: Vitor
 *
 *  Arquivo das instruções da JVM. Inclui as de alocação.
 */
#include "Instrucoes.h"
#include "math.h"
// tags de tipo para implementação dos arrays

int nop(execucao *p) {
	return 0;
}

int aconst_null(execucao *p) { // empty -> value (NULL) op: 0x01

	tipoOperando op;

	op.tipoReferencia = NULL;

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);

	return 0;
}

//const --------------------------------------------------------------------------------------------------------------------------------------------------------------------
int iconst_m1(execucao *p) {

	tipoOperando op;

	op.tipoInt = -1;

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int iconst_0(execucao *p) {

	tipoOperando op;

	op.tipoInt = 0;

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int iconst_1(execucao *p) {

	tipoOperando op;

	op.tipoInt = 1;

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int iconst_2(execucao *p) {

	tipoOperando op;

	op.tipoInt = 2;

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int iconst_3(execucao *p) {

	tipoOperando op;

	op.tipoInt = 3;

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int iconst_4(execucao *p) {

	tipoOperando op;

	op.tipoInt = 4;

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int iconst_5(execucao *p) {

	tipoOperando op;

	op.tipoInt = 5;

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int lconst_0(execucao *p) { // Insere na pilha a constante long 0 op: 0x9
	tipoOperando op;
	op.tipoLong = 0;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int lconst_1(execucao *p) { // Insere na pilha a constante long 1 op: 0xA

	tipoOperando op;
	op.tipoLong = 1;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;

}

int fconst_0(execucao *p) { // Insere na pilha a constante float 0.0 op: 0xB
	tipoOperando op;
	op.tipoFloat = 0.0;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int fconst_1(execucao *p) { // Insere na pilha a constante float 1.0 op: 0xC
	tipoOperando op;
	op.tipoFloat = 1.0;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int fconst_2(execucao *p) { // Insere na pilha a constante long 2.0 op: 0xD
	tipoOperando op;
	op.tipoFloat = 2.0;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int dconst_0(execucao *p) { // Insere na pilha a constante float 0.0 op: 0xE
	tipoOperando op;
	op.tipoDouble = 0.0;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int dconst_1(execucao *p) { // Insere na pilha a constante float 0.0 op: 0xF
	tipoOperando op;
	op.tipoDouble = 1.0;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

//Push --------------------------------------------------------------------------------------------------------------------------------------------------------------------
int bipush(execucao *p) { //insere na pilha o valor lido do índice op: 0x10

	tipoOperando op;
	char byteLido;

	byteLido = lerU1Codigo(p->frameAtual);
	op.tipoInt = byteLido;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);

	return 0;
}

int sipush(execucao *p) { //insere na pilha o valor (u2) lido do índice op: 0x11

	tipoOperando op;
	short shortLido;

	shortLido = lerU2Codigo(p->frameAtual);
	op.tipoInt = shortLido;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);

	return 0;
}

//Ldc -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Lê um índice de 2 bytes e carrega o valor que estiver na constant pool neste índice op: 0x12
 No caso da String, é carregado sua referência*/
int ldc(execucao *p) {

	u2 indice;
	tipoOperando op;

	indice = lerU1Codigo(p->frameAtual);

	switch (p->frameAtual->constantPool[indice].tag) {
	case CONSTANT_Integer:
		op.tipoInt = p->frameAtual->constantPool[indice].info.integerInfo.bytes;
		break;
	case CONSTANT_Float:
		op.tipoFloat = p->frameAtual->constantPool[indice].info.floatInfo.f.num;
		break;
	case CONSTANT_String:
		op.tipoReferencia =
				(char*) buscaUTF8ConstPool(p->frameAtual->constantPool,
						p->frameAtual->constantPool[indice].info.stringInfo.stringIndex);
		break;
	default:
		printf("\nInstrução ldc sendo utilizado com indice invalido\n");
		exit(1);
	}

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);

	return 0;
}

int ldc_w(execucao *p) {  // ldc com index duplo op: 0x13

	u2 indice;
	tipoOperando op;

	indice = lerU2Codigo(p->frameAtual);

	switch (p->frameAtual->constantPool[indice].tag) {
	case CONSTANT_Integer:
		op.tipoInt = p->frameAtual->constantPool[indice].info.integerInfo.bytes;
		break;
	case CONSTANT_Float:
		op.tipoFloat = p->frameAtual->constantPool[indice].info.floatInfo.f.num;
		break;
	case CONSTANT_String:
		op.tipoReferencia =
				(char*) buscaUTF8ConstPool(p->frameAtual->constantPool,
						p->frameAtual->constantPool[indice].info.stringInfo.stringIndex);
		break;
	default:
		printf("\nInstrução ldc_w sendo utilizado com indice invalido\n");
		exit(1);
	}

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);

	return 0;
}

int ldc2_w(execucao *p) {  // ldc com index duplo op: 0x14

	u2 indice;
	tipoOperando op;

	indice = lerU2Codigo(p->frameAtual);

	switch (p->frameAtual->constantPool[indice].tag) {
	case CONSTANT_Double:
		op.tipoDouble =
				p->frameAtual->constantPool[indice].info.doubleInfo.d.num;
		break;
	case CONSTANT_Long:
		op.tipoLong = p->frameAtual->constantPool[indice].info.longInfo.bytes;
		break;
	default:
		printf("\nInstrução ldc2_w sendo utilizado com indice invalido\n");
		exit(1);
	}

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);

	return 0;
}

//Load --------------------------------------------------------------------------------------------------------------------------------------------------------------------
int iload(execucao *p) { //insere na pilha o valor da posicao apontada por um indice do vetor de variáveis locais op: 0x15 , 0x16 , 0x17 ,0x18 , 0x19
	u1 index;
	tipoOperando op;
	index = lerU1Codigo(p->frameAtual);
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int iload_0(execucao *p) { //insere na pilha o valor da posicao 0 do vetor de variáveis locais op: 0x1A , 0X1E ,0X22 , 0X26 ,0X2A
	u1 index;
	tipoOperando op;
	index = 0;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int iload_1(execucao *p) { //insere na pilha um int da constant pool op: 0X1B , 0X1F , 0X23 , 0X27 , 0X2B
	u1 index;
	tipoOperando op;
	index = 1;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int iload_2(execucao *p) { //insere na pilha um int da constant pool op: 0X1C , 0X20 , 0X24 , 0X28 , OX2C
	u1 index;
	tipoOperando op;
	index = 2;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int iload_3(execucao *p) { //insere na pilha um int da constant pool op: 0X1D , 0X21 , 0X25 , 0X29 , 0X2D
	u1 index;
	tipoOperando op;
	index = 3;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int fload(execucao *p) {
	u1 index;
	tipoOperando op;
	index = lerU1Codigo(p->frameAtual);
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int fload_0(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 0;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int fload_1(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 1;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int fload_2(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 2;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int fload_3(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 3;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int lload(execucao *p) {
	u1 index;
	tipoOperando op;
	index = lerU1Codigo(p->frameAtual);
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int lload_0(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 0;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int lload_1(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 1;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int lload_2(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 2;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int lload_3(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 3;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int dload(execucao *p) {
	u1 index;
	tipoOperando op;
	index = lerU1Codigo(p->frameAtual);
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int dload_0(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 0;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int dload_1(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 1;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int dload_2(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 2;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int dload_3(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 3;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
	return 0;
}

int aload(execucao *p) {
	u1 index;
	tipoOperando op;
	index = lerU1Codigo(p->frameAtual);
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int aload_0(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 0;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int aload_1(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 1;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int aload_2(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 2;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

int aload_3(execucao *p) {
	u1 index;
	tipoOperando op;
	index = 3;
	op = p->frameAtual->arrayLocal[index];
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 0;
}

// Aload ---------------------------------------------------------------------------------------------------------------------------------------------------

int iaload(execucao *p) { //carrega um int de um vetor op: 0x2E , 0X33 , 0X34 , 0X35
	tipoOperando arrayref, index;
	Vetor *vet;
	index = popOperand(&(p->frameAtual->topoPilhaOperandos));
	arrayref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	pushOperand(&(p->frameAtual->topoPilhaOperandos),
			vet->array[index.tipoInt], TIPO1);
	return 0;
}

int laload(execucao *p) { //carrega um long de um vetor op: 0x2F
	tipoOperando arrayref, index;
	Vetor *vet;
	index = popOperand(&(p->frameAtual->topoPilhaOperandos));
	arrayref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	pushOperand(&(p->frameAtual->topoPilhaOperandos),
			vet->array[index.tipoInt], TIPO2);
	return 0;
}

int faload(execucao *p) { //carrega um float de um vetor op: 0x30
	tipoOperando arrayref, index;
	Vetor *vet;
	index = popOperand(&(p->frameAtual->topoPilhaOperandos));
	arrayref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	pushOperand(&(p->frameAtual->topoPilhaOperandos),
			vet->array[index.tipoInt], TIPO1);
	return 0;
}

int daload(execucao *p) { //carrega um double de um vetor op: 0x31
	tipoOperando arrayref, index;
	Vetor *vet;
	index = popOperand(&(p->frameAtual->topoPilhaOperandos));
	arrayref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	pushOperand(&(p->frameAtual->topoPilhaOperandos),
			vet->array[index.tipoInt], TIPO2);
	return 0;
}

int aaload(execucao *p) { //carrega um float de um vetor op: 0x32
	tipoOperando arrayref, index;
	Vetor *vet;
	index = popOperand(&(p->frameAtual->topoPilhaOperandos));
	arrayref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	pushOperand(&(p->frameAtual->topoPilhaOperandos),
			vet->array[index.tipoInt], TIPO1);
	return 0;
}
//Store --------------------------------------------------------------------------------------------------------------------------------------------------------------------
int store(execucao *p) { //recebe um indice e salva o topo da pilha de operandos no indice do vetor de variaveis locais 0x36 , 0X37 , 0X38 , 0X39 , 0X3A
	u1 index;
	tipoOperando op;
	index = lerU1Codigo(p->frameAtual);
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));
	p->frameAtual->arrayLocal[index] = op;
	return 0;
}

int store_0(execucao *p) { //salva o valor na posicao 0 0X3B,0X3F,0X43,0X47,0x4C
	tipoOperando op;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));
	p->frameAtual->arrayLocal[0] = op;
	return 0;
}

int store_1(execucao *p) { //salva o valor na posicao 1 0X3C,0X40,0X44,0X48,0x4D
	tipoOperando op;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));
	p->frameAtual->arrayLocal[1] = op;
	return 0;
}

int store_2(execucao *p) { //salva o valor na posicao 2 0X3D,0X41,0X45,0X49,0x4E
	tipoOperando op;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));
	p->frameAtual->arrayLocal[2] = op;
	return 0;
}

int store_3(execucao *p) { //salva o valor na posicao 3 0X3E,0X42,0X46,0X4A
	tipoOperando op;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));
	p->frameAtual->arrayLocal[3] = op;
	return 0;
}

//Astore ----------------------------------------------------------------------------------------------------------------------------------------------------------------

int iastore(execucao *p) { // salva um int num vetor op:0x4F , 0x54 , 0x55 , 0x56
	tipoOperando arrayref, index, value;
	Vetor *vet;
	value = popOperand(&(p->frameAtual->topoPilhaOperandos));
	index = popOperand(&(p->frameAtual->topoPilhaOperandos));
	arrayref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	vet->array[index.tipoInt].tipoInt = value.tipoInt;
	return 0;
}

int lastore(execucao *p) { // salva um long num vetor op:0x50
	tipoOperando arrayref, index, value;
	Vetor *vet;
	value = popOperand(&(p->frameAtual->topoPilhaOperandos));
	index = popOperand(&(p->frameAtual->topoPilhaOperandos));
	arrayref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	vet->array[index.tipoInt].tipoLong = value.tipoLong;
	return 0;
}

int fastore(execucao *p) { // salva um float num vetor 0p:0x51
	tipoOperando arrayref, index, value;
	Vetor *vet;
	value = popOperand(&(p->frameAtual->topoPilhaOperandos));
	index = popOperand(&(p->frameAtual->topoPilhaOperandos));
	arrayref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	vet->array[index.tipoInt].tipoFloat = value.tipoFloat;
	return 0;
}

int dastore(execucao *p) { // salva um double num vetor 0p:0x52
	tipoOperando arrayref, index, value;
	Vetor *vet;
	value = popOperand(&(p->frameAtual->topoPilhaOperandos));
	index = popOperand(&(p->frameAtual->topoPilhaOperandos));
	arrayref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	vet->array[index.tipoInt].tipoDouble = value.tipoDouble;
	return 0;
}

int aastore(execucao *p) { // salva uma referencia num vetor 0p:0x53
	tipoOperando arrayref, index, value;
	Vetor *vet;
	value = popOperand(&(p->frameAtual->topoPilhaOperandos));
	index = popOperand(&(p->frameAtual->topoPilhaOperandos));
	arrayref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	vet->array[index.tipoInt].tipoReferencia = value.tipoReferencia;
	return 0;
}

//pop ------------------------------------------------------------------------------------------------------------------------------------------------

int pop(execucao *p) { // retira um tipo 1 da pilha de operandos op: 0x57
	if (p->frameAtual->topoPilhaOperandos->operandoTipo1 == TIPO1) {
		popOperand(&(p->frameAtual->topoPilhaOperandos));
	} else {
		printf("Pop chamado sobre valor de tipo 2");
		exit(1);
	}
	return 0;
}

int pop2(execucao *p) { // retira dois tipo 1 da pilha de operandos ou um tipo 2 op: 0x58
	if ((p->frameAtual->topoPilhaOperandos->operandoTipo1 == TIPO1)
			&& (p->frameAtual->topoPilhaOperandos->elementoAbaixo->operandoTipo1
					== TIPO1)) {
		popOperand(&(p->frameAtual->topoPilhaOperandos));
		popOperand(&(p->frameAtual->topoPilhaOperandos));
	} else {
		popOperand(&(p->frameAtual->topoPilhaOperandos));
	}
	return 0;
}

//dup  --------------------------------------------------------------------------------------------------------------------------------------------------------------------
int dup(execucao *p) { // duplica o elemento no topo da pilha op: 0x59
	tipoOperando op;
	int operandoTipo;

	operandoTipo = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipo);
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipo);
	return 0;
}

int dup_x1(execucao *p) { // duplica o elemento no topo da pilha , dois elementos a baixo  op: 0x5A
	tipoOperando op, op1;
	int operandoTipoOp, operandoTipoOp1;

	operandoTipoOp = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));

	operandoTipoOp1 = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, operandoTipoOp1);
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	return 0;
}

int dup_x2(execucao *p) { // duplica o elemento no topo da pilha tres a baixo op: 0x5B
	tipoOperando op, op1, op2;
	int operandoTipoOp, operandoTipoOp1, operandoTipoOp2;

	operandoTipoOp = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));

	operandoTipoOp1 = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));

	operandoTipoOp2 = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, operandoTipoOp2);
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, operandoTipoOp1);
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	return 0;
}

int dup2(execucao *p) { // duplica o elemento no topo da pilha , dois elementos a baixo  op: 0x5C
	tipoOperando op, op1;
	int operandoTipoOp, operandoTipoOp1;

	operandoTipoOp = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));

	if (operandoTipoOp == TIPO1) {
		operandoTipoOp1 = p->frameAtual->topoPilhaOperandos->operandoTipo1;
		op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));

		pushOperand(&(p->frameAtual->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	} else {
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	}

	return 0;
}

int dup2_x1(execucao *p) { //duplica os dois primeiros elementos da pilha a baixo do terceiro 0x5D
	tipoOperando op, op1, op2;
	int operandoTipoOp, operandoTipoOp1, operandoTipoOp2;

	operandoTipoOp = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));

	if (operandoTipoOp == TIPO1) {
		operandoTipoOp1 = p->frameAtual->topoPilhaOperandos->operandoTipo1;
		op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	}

	operandoTipoOp2 = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));

	if (operandoTipoOp == TIPO1) {
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	} else {
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	}

	return 0;
}

int dup2_x2(execucao *p) { //duplica os dois primeiros elementos da pilha a baixo do quarto 0x5E
	tipoOperando op, op1, op2, op3;
	int operandoTipoOp, operandoTipoOp1, operandoTipoOp2, operandoTipoOp3;

	operandoTipoOp = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));

	if (operandoTipoOp == TIPO1) {
		operandoTipoOp1 = p->frameAtual->topoPilhaOperandos->operandoTipo1;
		op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	}

	operandoTipoOp2 = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));

	if (operandoTipoOp2 == TIPO1) {
		operandoTipoOp3 = p->frameAtual->topoPilhaOperandos->operandoTipo1;
		op3 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	}

	if (operandoTipoOp == TIPO1 && operandoTipoOp2 == TIPO1) {
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op3,
				operandoTipoOp3);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	} else if (operandoTipoOp2 == TIPO1) {
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op3,
				operandoTipoOp3);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	} else if (operandoTipoOp == TIPO1) {
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	} else {
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, operandoTipoOp);
	}
	return 0;
}

int swap(execucao *p) { //troca os dois elementos do topo da pilha op:0x5F
	tipoOperando op1, op2;
	int operandoTipoOp1, operandoTipoOp2;

	operandoTipoOp1 = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));

	operandoTipoOp2 = p->frameAtual->topoPilhaOperandos->operandoTipo1;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));

	if (operandoTipoOp1 != TIPO1 || operandoTipoOp2 != TIPO1) {
		printf("ERRO em swap: um dos operandos é tipo 2 (double ou long)\n");
		exit(1);
	}

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, operandoTipoOp1);
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, operandoTipoOp2);
	return 0;
}

// add --------------------------------------------------------------------------------------
int iadd(execucao *p) { // v1 , v2 -> v1+v2 op: 0x60
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoInt = op2.tipoInt + op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int ladd(execucao *p) { // v1 , v2 -> v1+v2 op: 0x61
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoLong = op2.tipoLong + op1.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int fadd(execucao *p) { // v1 , v2 -> v1+v2 op: 0x62
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoFloat = op2.tipoFloat + op1.tipoFloat;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int dadd(execucao *p) { // v1 , v2 -> v1+v2 op: 0x63
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoDouble = op2.tipoDouble + op1.tipoDouble;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// sub --------------------------------------------------------------------------------------
int isub(execucao *p) { // v1 , v2 -> v1-v2 op: 0x64
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoInt = op2.tipoInt - op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lsub(execucao *p) { // v1 , v2 -> v1-v2 op: 0x65
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoFloat = op2.tipoFloat - op1.tipoFloat;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int fsub(execucao *p) { // v1 , v2 -> v1-v2 op: 0x66
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoFloat = op2.tipoFloat - op1.tipoFloat;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int dsub(execucao *p) { // v1 , v2 -> v1-v2 op: 0x67
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoDouble = op2.tipoDouble - op1.tipoDouble;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// mul --------------------------------------------------------------------------------------
int imul(execucao *p) { // v1 , v2 -> v1*v2 op: 0x68
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoInt = op2.tipoInt * op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lmul(execucao *p) { // v1 , v2 -> v1*v2 op: 0x69
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoLong = op2.tipoLong * op1.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int fmul(execucao *p) { // v1 , v2 -> v1*v2 op: 0x6A
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoFloat = op2.tipoFloat * op1.tipoFloat;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int dmul(execucao *p) { // v1 , v2 -> v1*v2 op: 0x6B
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoDouble = op2.tipoDouble * op1.tipoDouble;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// div --------------------------------------------------------------------------------------
int idiv(execucao *p) { // v1 , v2 -> v1/v2 op: 0x6C
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoInt = op2.tipoInt / op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int ldiv_(execucao *p) { // v1 , v2 -> v1 / v2 op: 0x6D
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));

	op1.tipoLong = op2.tipoLong / op1.tipoLong;

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);

	return 0;

}

int fdiv(execucao *p) { // v1 , v2 -> v1/v2 op: 0x6E
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoFloat = op2.tipoFloat / op1.tipoFloat;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int ddiv(execucao *p) { // v1 , v2 -> v1/v2 op: 0x6F
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoDouble = op2.tipoDouble / op1.tipoDouble;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// rem --------------------------------------------------------------------------------------
int irem(execucao *p) { // v1 , v2 -> v1 mod v2 op: 0x70
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoInt = op2.tipoInt % op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lrem(execucao *p) { // v1 , v2 -> v1 mod v2 op: 0x71
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoLong = op2.tipoLong % op1.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int frem(execucao *p) { // v1 , v2 -> v1 mod v2 op: 0x72
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoFloat = (float) fmod(op2.tipoFloat, op1.tipoFloat);
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int drem_(execucao *p) { // v1 , v2 -> v1 mod v2 op: 0x73
	tipoOperando op1, op2;

	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));

	op1.tipoDouble = fmod(op2.tipoDouble, op1.tipoDouble);

	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);

	return 0;
}

//neg --------------------------------------------------------------------------------------
int ineg(execucao *p) { // v1 -> -v1 op: 0x74
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoInt = 0 - op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lneg(execucao *p) { // v1 -> -v1 op: 0x74
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoLong = 0 - op1.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int fneg(execucao *p) { // v1 -> -v1 op: 0x76
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoFloat = 0 - op1.tipoFloat;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int dneg(execucao *p) { // v1 -> -v1 op: 0x74
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoDouble = 0 - op1.tipoDouble;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// shifts --------------------------------------------------------------------------------
int ishl(execucao *p) { // v1 , v2 -> v1<<5 bits de baixo de v2 op: 0x78
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v2
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v1
	op1.tipoInt = op1.tipoInt & 0x1F;// isolando os 5 bits menos significativos de v2
	op1.tipoInt = op2.tipoInt << op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lshl(execucao *p) { // v1 , v2 -> v1<<6 bits de baixo de v2 op: 0x79
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v2
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v1
	op1.tipoLong = op1.tipoLong & 0x3F;	// isolando os 6 bits menos significativos de v2
	op1.tipoLong = op2.tipoLong << op1.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int ishr(execucao *p) { // v1 , v2 -> v1>>5 bits de baixo de v2 op: 0x7A
	tipoOperando op1, op2;
	int mask = 0x80000000;
	int count = 0;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v2
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v1
	op1.tipoInt = op1.tipoInt & 0x1F;// isolando os 5 bits menos significativos de v2
	if (op2.tipoInt < 0) {
		int i;
		for (i = 0; i < op1.tipoInt; ++i) {
			count = count >> 1;
			count = count | mask;
		}
		op1.tipoInt = op2.tipoInt >> op1.tipoInt; //valor shiftado
		op1.tipoInt = op1.tipoInt | count;
	} else {
		op1.tipoInt = op2.tipoInt >> op1.tipoInt;
	}
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lshr(execucao *p) { // v1 , v2 -> v1>>5 bits de baixo de v2 op: 0x7B
	tipoOperando op1, op2;
	long long mask = 0x8000000000000000;
	long long count = 0;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v2
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v1
	op1.tipoLong = op1.tipoLong & 0x3F;	// isolando os 5 bits menos significativos de v2
	if (op2.tipoLong < 0) {
		int i;
		for (i = 0; i < op1.tipoInt; ++i) {
			count = count >> 1;
			count = count | mask;
		}
		op1.tipoLong = op2.tipoLong >> op1.tipoLong; //valor shiftado
		op1.tipoLong = op1.tipoLong | count;
	} else {
		op1.tipoLong = op2.tipoLong >> op1.tipoLong;
	}
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int iushr(execucao *p) { // v1 , v2 -> v1>>5 bits de baixo de v2 op: 0x7C
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v2
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v1
	op1.tipoInt = op1.tipoInt & 0x1F;// isolando os 5 bits menos significativos de v2
	op1.tipoInt = op2.tipoInt >> op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lushr(execucao *p) { // op: 0x7D
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v2
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));	// v1
	op1.tipoLong = op1.tipoLong & 0x3F;	// isolando os 6 bits menos significativos de v2
	op1.tipoLong = op2.tipoLong >> op1.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// bitwise ----------------------------------------------------------------------------------------------
int iand(execucao *p) {	// V1 , V2 -> V1 AND V2 op: 0x7E

	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoInt = op1.tipoInt & op2.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int land(execucao *p) {	// V1 , V2 -> V1 AND V2 op: 0x7F
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoLong = op1.tipoLong & op2.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int ior(execucao *p) {	// V1 , V2 -> V1 OR V2 op: 0x80
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoInt = op1.tipoInt | op2.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lor(execucao *p) {	// V1 , V2 -> V1 OR V2 op: 0x81
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoLong = op1.tipoLong | op2.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int ixor(execucao *p) {	// V1 , V2 -> V1 OR V2 op: 0x82
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoInt = op1.tipoInt ^ op2.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lxor(execucao *p) {	// V1 , V2 -> V1 OR V2 op: 0x83
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1.tipoLong = op1.tipoLong ^ op2.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int iinc(execucao *p) {
	u1 index;
	char constante;
	index = lerU1Codigo(p->frameAtual);
	constante = lerU1Codigo(p->frameAtual);
	p->frameAtual->arrayLocal[index].tipoInt++;
	return 0;
}

// x2y-----------------------------------------------------------------------------------------------------------
int i2l(execucao *p) {//  Converte o valor do topo da pilha de int para long op: 0x85
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoLong = op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int i2f(execucao *p) { //  Converte o valor do topo da pilha de int para float op: 0x86
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoFloat = (float) op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int i2d(execucao *p) { //  Converte o valor do topo da pilha de int para double op: 0x87
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoDouble = (double) op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int l2i(execucao *p) { //  Converte o valor do topo da pilha de long para int op: 0x88
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoInt = (int) op1.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int l2f(execucao *p) { //  Converte o valor do topo da pilha de long para float op: 0x89
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoFloat = (float) op1.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int l2d(execucao *p) { //  Converte o valor do topo da pilha de long para double op: 0x8A
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoDouble = (double) op1.tipoLong;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int f2i(execucao *p) { //  Converte o valor do topo da pilha de float para int op: 0x8B
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoInt = (int) op1.tipoFloat;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int f2l(execucao *p) { //  Converte o valor do topo da pilha de float para long op: 0x8C
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoLong = (long long) op1.tipoFloat;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int f2d(execucao *p) { //  Converte o valor do topo da pilha de float para double op: 0x8D
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoDouble = (double) op1.tipoFloat;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int d2i(execucao *p) { //  Converte o valor do topo da pilha de double para int op: 0x8E
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoInt = (int) op1.tipoDouble;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int d2l(execucao *p) { //  Converte o valor do topo da pilha de double para long op: 0x8F
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoLong = (long long) op1.tipoDouble;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int d2f(execucao *p) { //  Converte o valor do topo da pilha de double para float op: 0x90
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoFloat = (float) op1.tipoDouble;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int i2c(execucao *p) { //  Converte o valor do topo da pilha de int para char , cobre tambem o caso do byte - i2b op: 0x91 ,0x92
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoInt = (char) op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int i2s(execucao *p) { //  Converte o valor do topo da pilha de int para short - i2b op: 0x93
	tipoOperando op1, op2;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op2.tipoInt = (short) op1.tipoInt;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

//XcmpY -----------------------------------------------------------------------------------------------------------
int lcmp(execucao *p) { //compara dois valores long 0x94
	tipoOperando op1, op2, resultado;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	if (op1.tipoLong > op2.tipoLong) {
		resultado.tipoInt = 1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoLong == op2.tipoLong) {
		resultado.tipoInt = 0;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else {
		resultado.tipoInt = -1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	}
	return 0;
}

int fcmpl(execucao *p) { // comparação entre floats , caso NAN resultado -1 op: 0x95
	tipoOperando op1, op2, resultado;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	if (op1.tipoFloat > op2.tipoFloat) {
		resultado.tipoInt = 1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoFloat == op2.tipoFloat) {
		resultado.tipoInt = 0;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoFloat < op2.tipoFloat) {
		resultado.tipoInt = -1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else {
		resultado.tipoInt = -1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	}
	return 0;
}

int fcmpg(execucao *p) { // comparação entre floats , caso NAN resultado 1 op: 0x96
	tipoOperando op1, op2, resultado;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	if (op1.tipoFloat > op2.tipoFloat) {
		resultado.tipoInt = 1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoFloat == op2.tipoFloat) {
		resultado.tipoInt = 0;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoFloat < op2.tipoFloat) {
		resultado.tipoInt = -1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else {
		resultado.tipoInt = 1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	}
	return 0;
}

int dcmpl(execucao *p) { // comparação entre doubles , caso NAN resultado 1 op: 0x97
	tipoOperando op1, op2, resultado;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	if (op1.tipoDouble > op2.tipoDouble) {
		resultado.tipoInt = 1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoDouble == op2.tipoDouble) {
		resultado.tipoInt = 0;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoDouble < op2.tipoDouble) {
		resultado.tipoInt = -1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else {
		resultado.tipoInt = -1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	}
	return 0;
}

int dcmpg(execucao *p) { // comparação entre doubles , caso NAN resultado 1 op: 0x98
	tipoOperando op1, op2, resultado;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	if (op1.tipoDouble > op2.tipoDouble) {
		resultado.tipoInt = 1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoDouble == op2.tipoDouble) {
		resultado.tipoInt = 0;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoDouble < op2.tipoDouble) {
		resultado.tipoInt = -1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	} else {
		resultado.tipoInt = -1;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), resultado, TIPO1);
	}
	return 0;
}
// Ifs -----------------------------------------------------------------------------------------------------

int ifeq(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0x99
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt == 0) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int ifne(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0x9A
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt != 0) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int iflt(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0x9B
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt < 0) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int ifge(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0x9C
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt >= 0) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int ifgt(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0x9D
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt > 0) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int ifle(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0x9E
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt <= 0) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int if_icmpeq(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0x9F
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1, op2;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt == op2.tipoInt) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int if_icmpne(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0xA0
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1, op2;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt != op2.tipoInt) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int if_icmplt(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0xA1
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1, op2;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt < op2.tipoInt) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int if_icmpge(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0xA2
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1, op2;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt >= op2.tipoInt) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int if_icmpgt(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0xA3
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1, op2;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt > op2.tipoInt) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int if_icmple(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0xA4
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1, op2;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt <= op2.tipoInt) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int if_acmpeq(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0xA5
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1, op2;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoReferencia == op2.tipoReferencia) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int if_acmpne(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0xA6
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	tipoOperando op1, op2;
	op2 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoReferencia != op2.tipoReferencia) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

// controle -----------------------------------------------------------------------------------------------
int goto_(execucao *p) { // op: 0xA7
	short offset;
	offset = (short) lerU2Codigo(p->frameAtual);
	offset -= 3; // serve para corrigir o offset do PC
	p->frameAtual->pc += offset;
	return 0;
}

int jsr(execucao *p) {  // 0xA8
	u2 offset;
	tipoOperando op;
	offset = lerU2Codigo(p->frameAtual);
	offset -= 3; // serve para corrigir o offset do PC
	op.tipoReferencia = p->frameAtual->pc;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	p->frameAtual->pc += offset;
	return 0;
}

int ret(execucao *p) { // VAI DAR MERDA CAPITÃO  // 0xA9
	u1 index;
	index = lerU1Codigo(p->frameAtual);
	p->frameAtual->pc = p->frameAtual->arrayLocal[index].tipoReferencia;
	return 0;
}

// Switch -------------------------------------------------------------------------------------------------------
int tableswitch(execucao *p) {
	int default_, low, high, switchsize, i, sizepads;
	u1 *pcVolta;
	tipoOperando index;
	pcVolta = p->frameAtual->pc - 1;

	index = popOperand(&(p->frameAtual->topoPilhaOperandos)); // tirando o indeice do case da pilha

	sizepads = (4 - (p->frameAtual->pc - p->frameAtual->codigoAExecutar) % 4)
			% 4; // calculando quantos bits de pad são necessários
	for (i = 0; i < sizepads; ++i) {
		lerU1Codigo(p->frameAtual); // padding de bytes no inicio
	}

	default_ = (int) lerU4Codigo(p->frameAtual); // leitura do offset de default
	low = (int) lerU4Codigo(p->frameAtual); // leitura do offset do menor case
	high = (int) lerU4Codigo(p->frameAtual); // leitura do offset ddo maior case

	switchsize = (high - low + 1); // tirando o tamanho do switch
	if (switchsize < 0) { // checando para erros
		printf("Erro tableswitch , low maior do que high");
		exit(1);
	}

	int *offsets;
	offsets = calloc(switchsize, sizeof(int));
	for (i = 0; i < switchsize; ++i) { // preenchendo a tabela dos offsets do case
		offsets[i] = lerU4Codigo(p->frameAtual);
	}

	p->frameAtual->pc = pcVolta; // recuperando o valor do pc
	if ((index.tipoInt > high) || (index.tipoInt < low)) { // caso default
		p->frameAtual->pc = p->frameAtual->pc + default_;
	} else {
		p->frameAtual->pc = p->frameAtual->pc + (offsets[index.tipoInt - low]);
	}
	free(offsets);
	return 0;
}

int lookupswitch(execucao *p) {
	int default_, npairs, i, sizepads;
	u1 *endBaseInstr;
	tipoOperando key;
	endBaseInstr = p->frameAtual->pc - 1; // salva o edereço do opcode da instrução

	key = popOperand(&(p->frameAtual->topoPilhaOperandos)); // tirando o indeice do case da pilha
	sizepads = (4 - (p->frameAtual->pc - p->frameAtual->codigoAExecutar) % 4)
			% 4; // calculando quantos bits de pad são necessários
	for (i = 0; i < sizepads; ++i) {
		lerU1Codigo(p->frameAtual); // padding de bytes no inicio
	}
	default_ = lerU4Codigo(p->frameAtual); // le o offset do default
	npairs = lerU4Codigo(p->frameAtual); // le o numero  de pares

	int offsets[npairs][2];
	for (i = 0; i < npairs; ++i) { // povoa a matriz de pares
		offsets[i][0] = lerU4Codigo(p->frameAtual); // match
		offsets[i][1] = lerU4Codigo(p->frameAtual); // offset
	}
	p->frameAtual->pc = endBaseInstr;
	for (i = 0; i < npairs; ++i) {
		if (key.tipoInt == offsets[i][0]) {
			p->frameAtual->pc += offsets[i][1];
			return 0;
		}
	}
	p->frameAtual->pc += default_;
	return 0;
}
// retornos ----------------------------------------------------------------------------------------------

int ireturn(execucao *p) { // value -> empty , joga value na pilha de operandos  do frame que chamou op: 0xAC
	tipoOperando op;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));
	popFrame(&(p->frameAtual));
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 1;
}

int lreturn(execucao *p) { // value -> empty op: 0xAD

	tipoOperando op;

	op = popOperand(&(p->frameAtual->topoPilhaOperandos));
	popFrame(&(p->frameAtual));
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);

	return 1;
}

int freturn(execucao *p) { // value -> empty op: 0xAE
	tipoOperando op;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));
	popFrame(&(p->frameAtual));
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 1;
}

int dreturn(execucao *p) { // value -> empty op: 0xAF
	tipoOperando op;

	op = popOperand(&(p->frameAtual->topoPilhaOperandos));
	popFrame(&(p->frameAtual));
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);

	return 1;
}

int areturn(execucao *p) { // value -> empty op: 0xB0
	tipoOperando op;
	op = popOperand(&(p->frameAtual->topoPilhaOperandos));
	popFrame(&(p->frameAtual));
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	return 1;
}

int return_(execucao *p) { // -> empty, não retorna nada OP: 0xB1
	popFrame(&(p->frameAtual));
	return 1;
}

// Static Field -------------------------------------------------------------------------------------------

// Função que pega um campo estático do array de campos estáticos da classe e o empilha
int getstatic(execucao *p) { // op: 0xB2

	ClassFile *cf;
	tipoOperando op;
	field* fieldAProcurar;
	char* nomeClasse;
	char* nomeField;
	char* descritor;
	u2 indiceFieldRefInfo;
	u2 indiceClassInfo;
	u2 indiceNomeClasse;
	u2 indiceNameAndTypeInfo;
	u2 indiceNomeField;
	u2 indiceTipoField;

	indiceFieldRefInfo = lerU2Codigo(p->frameAtual);

	indiceClassInfo =
			p->frameAtual->constantPool[indiceFieldRefInfo].info.fieldRefInfo.classIndex;
	indiceNomeClasse =
			p->frameAtual->constantPool[indiceClassInfo].info.classInfo.nameIndex;

	nomeClasse = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceNomeClasse);

	indiceNameAndTypeInfo =
			p->frameAtual->constantPool[indiceFieldRefInfo].info.fieldRefInfo.nameAndTypeIndex;
	indiceNomeField =
			p->frameAtual->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.nameIndex;
	nomeField = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceNomeField);

	indiceTipoField =
			p->frameAtual->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.descriptorIndex;
	descritor = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceTipoField);

	// Se o campo atender a essas condições, é um campo que significa print
	if (strcmp(nomeClasse, "java/lang/System") == 0
			&& strcmp(nomeField, "out") == 0
			&& strcmp(descritor, "Ljava/io/PrintStream;") == 0) {

		op.tipoLong = 0;

		// Empilhamos esse operando relativemente inútil pois temos que empilhar algo dessa instrução
		// Ele será descartado assim que o invokevirtual do print for chamado
		pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
	} else { // Senão, temos que buscar nos fields da classe requisitada

		// Verificamos se estamos requisitando uma classe que já está carregada
		cf = verificaClasse(p, nomeClasse);

		fieldAProcurar = buscaStaticFieldNome(p->pInicioLista, nomeClasse,
				nomeField);

		// Não achei :(
		if (fieldAProcurar == NULL ) {
			printf("ERRO em getstatic: field nao encontrado - %s %s %s\n",
					nomeClasse, nomeField, descritor);
			exit(1);
		} else {
			// Agora vemos o tipo do field para podermos carregá-lo na pilha
			if (descritor[0] == 'B' || descritor[0] == 'C') {
				op.tipoInt = fieldAProcurar->valor.tipoChar;
				pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
			} else if (descritor[0] == 'S') {
				op.tipoInt = fieldAProcurar->valor.tipoShort;
				pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
			} else if (descritor[0] == 'D') {
				op.tipoDouble = fieldAProcurar->valor.tipoDouble;
				pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
			} else if (descritor[0] == 'F') {
				op.tipoFloat = fieldAProcurar->valor.tipoFloat;
				pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
			} else if (descritor[0] == 'I' || descritor[0] == 'Z') {
				op.tipoInt = fieldAProcurar->valor.tipoInt;
				pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
			} else if (descritor[0] == 'J') {
				op.tipoLong = fieldAProcurar->valor.tipoLong;
				pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO2);
			} else if (descritor[0] == 'L' || descritor[0] == '[') {
				op.tipoReferencia = fieldAProcurar->valor.tipoReferencia;
				pushOperand(&(p->frameAtual->topoPilhaOperandos), op, TIPO1);
			}
		}
	}

	return 0;
}

int putstatic(execucao *p) { // 0xB3

	ClassFile *cf;
	tipoOperando op;
	field* fieldAProcurar;
	char* nomeClasse;
	char* nomeField;
	char* descritor;
	u2 indiceFieldRefInfo;
	u2 indiceClassInfo;
	u2 indiceNomeClasse;
	u2 indiceNameAndTypeInfo;
	u2 indiceNomeField;
	u2 indiceTipoField;

	indiceFieldRefInfo = lerU2Codigo(p->frameAtual);

	indiceClassInfo =
			p->frameAtual->constantPool[indiceFieldRefInfo].info.fieldRefInfo.classIndex;
	indiceNomeClasse =
			p->frameAtual->constantPool[indiceClassInfo].info.classInfo.nameIndex;

	nomeClasse = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceNomeClasse);

	indiceNameAndTypeInfo =
			p->frameAtual->constantPool[indiceFieldRefInfo].info.fieldRefInfo.nameAndTypeIndex;
	indiceNomeField =
			p->frameAtual->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.nameIndex;
	nomeField = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceNomeField);

	indiceTipoField =
			p->frameAtual->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.descriptorIndex;
	descritor = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceTipoField);

	// Verificamos se estamos requisitando uma classe que já está carregada
	cf = verificaClasse(p, nomeClasse);

	fieldAProcurar = buscaStaticFieldNome(p->pInicioLista, nomeClasse,
			nomeField);

	// Não achei :(
	if (fieldAProcurar == NULL ) {
		printf("ERRO em putstatic: field nao encontrado - %s %s %s\n",
				nomeClasse, nomeField, descritor);
		exit(1);
	} else {
		op = popOperand(&(p->frameAtual->topoPilhaOperandos));
		insereValorStaticField(p->pInicioLista, nomeClasse, nomeField, op);
	}

	return 0;
}

//Field -------------------------------------------------------------------------------------------------------
int getfield(execucao *p) { //recebe um index e empilha o valor do campo correspondente a este index na pilha de opeandos 0xB4
	u2 index;
	u2 nameAndTypeIndexAux;
	u2 nameIndexaux, descriptorIndexAux;
	object *obj;
	field* campo;
	char *nomeField, *descritorField;
	tipoOperando objectref, value;
	index = lerU2Codigo(p->frameAtual);
	objectref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	obj = (object*) objectref.tipoReferencia;
	// resolução de nomes -----------------------
	nameAndTypeIndexAux =
			p->frameAtual->constantPool[index].info.fieldRefInfo.nameAndTypeIndex;
	nameIndexaux =
			p->frameAtual->constantPool[nameAndTypeIndexAux].info.nameAndTypeInfo.nameIndex;
	nomeField = p->frameAtual->constantPool[nameIndexaux].info.UTF8Info.bytes;
	descriptorIndexAux =
			p->frameAtual->constantPool[nameAndTypeIndexAux].info.nameAndTypeInfo.descriptorIndex;
	descritorField =
			p->frameAtual->constantPool[descriptorIndexAux].info.UTF8Info.bytes;

	campo = buscaFieldNome(nomeField, descritorField, obj);
	if (descritorField[0] == 'B' || descritorField[0] == 'C') {
		value.tipoInt = campo->valor.tipoChar;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), value, TIPO1);
	} else if (descritorField[0] == 'S') {
		value.tipoInt = campo->valor.tipoShort;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), value, TIPO1);
	} else if (descritorField[0] == 'D') {
		value.tipoDouble = campo->valor.tipoDouble;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), value, TIPO2);
	} else if (descritorField[0] == 'F') {
		value.tipoFloat = campo->valor.tipoFloat;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), value, TIPO1);
	} else if (descritorField[0] == 'I' || descritorField[0] == 'Z') {
		value.tipoInt = campo->valor.tipoInt;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), value, TIPO1);
	} else if (descritorField[0] == 'J') {
		value.tipoLong = campo->valor.tipoLong;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), value, TIPO2);
	} else if (descritorField[0] == 'L' || descritorField[0] == '[') {
		value.tipoReferencia = campo->valor.tipoReferencia;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), value, TIPO1);
	}
	return 0;
}

int putfield(execucao *p) { //recebe um index e um valor e seta o campo correspondente em um objeto para o valor de value op: 0xB5
	u2 index;
	u2 nameAndTypeIndexAux;
	u2 nameIndexaux, descriptorIndexAux;
	object *obj;
	field* campo;
	char *nomeField, *descritorField;
	tipoOperando objectref, value;
	index = lerU2Codigo(p->frameAtual);
	value = popOperand(&(p->frameAtual->topoPilhaOperandos));
	objectref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	obj = (object*) objectref.tipoReferencia;
	nameAndTypeIndexAux =
			p->frameAtual->constantPool[index].info.fieldRefInfo.nameAndTypeIndex;
	nameIndexaux =
			p->frameAtual->constantPool[nameAndTypeIndexAux].info.nameAndTypeInfo.nameIndex;
	nomeField = p->frameAtual->constantPool[nameIndexaux].info.UTF8Info.bytes;
	descriptorIndexAux =
			p->frameAtual->constantPool[nameAndTypeIndexAux].info.nameAndTypeInfo.descriptorIndex;
	descritorField =
			p->frameAtual->constantPool[descriptorIndexAux].info.UTF8Info.bytes;
	campo = buscaFieldNome(nomeField, descritorField, obj);
	if (campo != NULL ) {
		campo->valor.tipoLong = value.tipoLong;
	} else {
		printf("campo = NULL , problema na buscaFieldNome");
		exit(1);
	}
	return 0;
}

// invokes -------------------------------------------------------------------------------------------

// ATENÇÃO: O invokevirtual serve apenas para simular o print/println, não faz o que devia
int invokevirtual(execucao *p) { // op: 0xB6

	int numArgs;
	char* nomeClasse;
	char* nomeMetodo;
	char* descritor;
	u2 indiceMethodRefInfo;
	u2 indiceClassInfo;
	u2 indiceNameAndTypeInfo;
	u2 indiceNomeMetodo;
	u2 indiceTipoMetodo;
	tipoOperando op;

	indiceMethodRefInfo = lerU2Codigo(p->frameAtual);

	indiceClassInfo =
			p->frameAtual->constantPool[indiceMethodRefInfo].info.methodRefInfo.classIndex;
	nomeClasse =
			buscaUTF8ConstPool(p->frameAtual->constantPool,
					p->frameAtual->constantPool[indiceClassInfo].info.classInfo.nameIndex);

	indiceNameAndTypeInfo =
			p->frameAtual->constantPool[indiceMethodRefInfo].info.methodRefInfo.nameAndTypeIndex;
	indiceNomeMetodo =
			p->frameAtual->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.nameIndex;
	nomeMetodo = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceNomeMetodo);

	indiceTipoMetodo =
			p->frameAtual->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.descriptorIndex;
	descritor = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceTipoMetodo);

	if (strcmp(nomeClasse, "java/io/PrintStream") == 0
			&& (strcmp(nomeMetodo, "println") == 0
					|| strcmp(nomeMetodo, "print") == 0)) {
		if (descritor[1] == 'I') {
			op = popOperand(&(p->frameAtual->topoPilhaOperandos));
			printf("%d", op.tipoInt);
		} else if (descritor[1] == 'J') {
			op = popOperand(&(p->frameAtual->topoPilhaOperandos));
			printf("%lld", op.tipoLong);
		} else if (descritor[1] == 'F') {
			op = popOperand(&(p->frameAtual->topoPilhaOperandos));
			printf("%g", op.tipoFloat);
		} else if (descritor[1] == 'D') {
			op = popOperand(&(p->frameAtual->topoPilhaOperandos));
			printf("%g", op.tipoDouble);
		} else if (descritor[1] == 'S') {
			op = popOperand(&(p->frameAtual->topoPilhaOperandos));
			printf("%hi", (short) op.tipoInt);
		} else if (descritor[1] == 'C') {
			op = popOperand(&(p->frameAtual->topoPilhaOperandos));
			printf("%c", (char) op.tipoInt);
		} else if (descritor[1] == 'L') {
			op = popOperand(&(p->frameAtual->topoPilhaOperandos));
			if (strstr(descritor, "java/lang/String") != NULL ) {
				printf("%s", (char*) op.tipoReferencia);
			} else {
				printf("%p", op.tipoReferencia);
			}
		} else if (descritor[1] == 'Z') {
			op = popOperand(&(p->frameAtual->topoPilhaOperandos));
			printf("%s", !op.tipoInt ? "false" : "true");
		} else if (descritor[1] == 'B') {
			op = popOperand(&(p->frameAtual->topoPilhaOperandos));
			printf("%d", op.tipoInt);
		} else if (descritor[1] == '[') {
			op = popOperand(&(p->frameAtual->topoPilhaOperandos));
			printf("%p", op.tipoReferencia);
		}

		if (strcmp(nomeMetodo, "println") == 0) {
			printf("\n");
		}

		// Tirando a referência desnecessária para essa simulação
		popOperand(&(p->frameAtual->topoPilhaOperandos));

	} else {
		numArgs = contaArgumentosMetodo(descritor);

		//numArgs + 1 é para incluir a referência ao objeto
		preparaExecucaoMetodo(nomeClasse, nomeMetodo, descritor, p,
				numArgs + 1);
		executaMetodo(p);
	}

	return 0;
}

// Instrução que dada uma pilha com os argumentos, invoca um método
// Opcode: 0xB7
int invokespecial(execucao *p) { // Opcode: 0xB7

	int numArgs;
	char* nomeClasse;
	char* nomeMetodo;
	char* descritor;
	u2 indiceMethodRefInfo;
	u2 indiceClassInfo;
	u2 indiceNameAndTypeInfo;
	u2 indiceNomeMetodo;
	u2 indiceTipoMetodo;

	indiceMethodRefInfo = lerU2Codigo(p->frameAtual);

	indiceClassInfo =
			p->frameAtual->constantPool[indiceMethodRefInfo].info.methodRefInfo.classIndex;
	nomeClasse =
			buscaUTF8ConstPool(p->frameAtual->constantPool,
					p->frameAtual->constantPool[indiceClassInfo].info.classInfo.nameIndex);

	indiceNameAndTypeInfo =
			p->frameAtual->constantPool[indiceMethodRefInfo].info.methodRefInfo.nameAndTypeIndex;
	indiceNomeMetodo =
			p->frameAtual->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.nameIndex;
	nomeMetodo = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceNomeMetodo);

	indiceTipoMetodo =
			p->frameAtual->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.descriptorIndex;
	descritor = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceTipoMetodo);

	numArgs = contaArgumentosMetodo(descritor);

	//numArgs + 1 é para incluir a referência ao objeto
	preparaExecucaoMetodo(nomeClasse, nomeMetodo, descritor, p, numArgs + 1);
	executaMetodo(p);

	return 0;
}

int invokestatic(execucao *p) { //  op: 0xB8

	ClassFile *cf;
	int numArgs;
	char* nomeClasse;
	char* nomeMetodo;
	char* descritor;
	u2 indiceMethodRefInfo;
	u2 indiceClassInfo;
	u2 indiceNameAndTypeInfo;
	u2 indiceNomeMetodo;
	u2 indiceTipoMetodo;

	indiceMethodRefInfo = lerU2Codigo(p->frameAtual);

	indiceClassInfo =
			p->frameAtual->constantPool[indiceMethodRefInfo].info.methodRefInfo.classIndex;
	nomeClasse =
			buscaUTF8ConstPool(p->frameAtual->constantPool,
					p->frameAtual->constantPool[indiceClassInfo].info.classInfo.nameIndex);

	indiceNameAndTypeInfo =
			p->frameAtual->constantPool[indiceMethodRefInfo].info.methodRefInfo.nameAndTypeIndex;
	indiceNomeMetodo =
			p->frameAtual->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.nameIndex;
	nomeMetodo = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceNomeMetodo);

	indiceTipoMetodo =
			p->frameAtual->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.descriptorIndex;
	descritor = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceTipoMetodo);

	numArgs = contaArgumentosMetodo(descritor);

	// O método registerNatives é um método da classe Object.class, é um método nativo
	// portanto, devemos ignorá-lo
	if (strcmp(nomeClasse, "java/lang/Object") == 0
			&& strcmp(nomeMetodo, "registerNatives") == 0
			&& strcmp(descritor, "()V") == 0) {
		return 0;
	} else {

		// Verificamos se estamos requisitando uma classe que já está carregada
		cf = verificaClasse(p, nomeClasse);

		preparaExecucaoMetodo(nomeClasse, nomeMetodo, descritor, p, numArgs);
		executaMetodo(p);

		return 0;
	}
}

//Objetos ---------------------------------------------------------------------------------------------
int new_(execucao *p) { // op: 0xBB

	object* obj;
	tipoOperando objRef;
	ClassFile* cf;
	u2 indexClassInfo;
	u2 indiceNomeClasse;
	char* nomeClasse;

	indexClassInfo = lerU2Codigo(p->frameAtual); // lê index
	indiceNomeClasse =
			p->frameAtual->constantPool[indexClassInfo].info.classInfo.nameIndex;
	nomeClasse = buscaUTF8ConstPool(p->frameAtual->constantPool,
			indiceNomeClasse);

	cf = verificaClasse(p, nomeClasse);

	obj = malloc(sizeof(object));

	obj->fieldsCount = contaNumFields(p, *cf);

	obj->fields = malloc(sizeof(field) * obj->fieldsCount);
	inicializaFieldsObjeto(p, *cf, obj->fields);

	objRef.tipoReferencia = obj;

	pushOperand(&(p->frameAtual->topoPilhaOperandos), objRef, TIPO1);

	return 0;
}

//Array -------------------------------------------------------------------------------------------------
int newarray(execucao *p) { // recebe da pilha um size e do código um tipo e aloca um array op: 0xBC
	tipoOperando count, arrayref;
	Vetor *vet;
	vet = malloc(sizeof(Vetor));
	vet->type = lerU1Codigo(p->frameAtual);
	count = popOperand(&(p->frameAtual->topoPilhaOperandos)); // tamanho do vetor
	vet->size = count.tipoInt;
	switch (vet->type) {
	case T_BOOLEAN:
		vet->array = calloc(vet->size, sizeof(tipoOperando)); // deixado como int
		break;
	case T_CHAR:
		vet->array = calloc(vet->size, sizeof(tipoOperando));
		break;
	case T_FLOAT:
		vet->array = calloc(vet->size, sizeof(tipoOperando));
		break;
	case T_DOUBLE:
		vet->array = calloc(vet->size, sizeof(tipoOperando));
		break;
	case T_BYTE:
		vet->array = calloc(vet->size, sizeof(tipoOperando)); // deixado como int
		break;
	case T_SHORT:
		vet->array = calloc(vet->size, sizeof(tipoOperando)); // deixado como int
		break;
	case T_INT:
		vet->array = calloc(vet->size, sizeof(tipoOperando)); // deixado como int
		break;
	case T_LONG:
		vet->array = calloc(vet->size, sizeof(tipoOperando));
		break;
	default:
		printf("Erro no newarray - tipo incompativel");
		exit(1);
	}
	arrayref.tipoReferencia = vet;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), arrayref, TIPO1);
	return 0;
}

int anewarray(execucao *p) { // cria um array de  referencias 0xBD
	u2 index;
	tipoOperando count, arrayref;
	Vetor *vet;
	vet = calloc(1, sizeof(Vetor));
	index = lerU2Codigo(p->frameAtual);
	count = popOperand(&(p->frameAtual->topoPilhaOperandos));
	if (count.tipoInt < 0) {
		printf(
				"tamanho do vetor em anewarray menor que  zero , lançar exceção - NegativeArraySize");
		exit(1);
	}
	vet->size = count.tipoInt;
	vet->type = T_INT;
	vet->array = calloc(vet->size, sizeof(tipoOperando));
	arrayref.tipoReferencia = vet;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), arrayref, TIPO1);
	return 0;
}

int arraylength(execucao *p) { //retona pela pilha o tamanho de um array op: 0xBE
	tipoOperando arrayref, length;
	Vetor *vet;
	arrayref = popOperand(&(p->frameAtual->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	length.tipoInt = vet->size;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), length, TIPO1);
	return 0;
}

// Array -------------------------------------------------------------------------------------
int multianewarray(execucao *p) {
	u1 dimensions;
	u2 index;
	Vetor *vet;
	int i;
	index = lerU2Codigo(p->frameAtual);
	dimensions = lerU1Codigo(p->frameAtual);
	tipoOperando count[dimensions], arrayref;
	int count1[dimensions];
	if (dimensions <= 0) {
		printf("dimensões zero ou negativas em multianewarray");
		exit(1);
	} else {
		for (i = 0; i < dimensions; ++i) {
			count[i] = popOperand(&(p->frameAtual->topoPilhaOperandos));
			count1[i] = count[i].tipoInt; // gambiarra
		}
		vet = alocaMultiArray(dimensions, count1);
		arrayref.tipoReferencia = vet;
		pushOperand(&(p->frameAtual->topoPilhaOperandos), arrayref, TIPO1);
	}
	return 0;
}
//ifnulls ------------------------------------------------------------------------------------------------
int ifnull(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0xC6
	u2 offset;
	offset = lerU2Codigo(p->frameAtual);
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoReferencia == NULL ) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

int ifnonnull(execucao *p) { // Compara o topo da pilha(int) com 0 , e dá branch op: 0xC7
	u2 offset;
	offset = lerU2Codigo(p->frameAtual);
	tipoOperando op1;
	op1 = popOperand(&(p->frameAtual->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoReferencia != NULL ) {
		p->frameAtual->pc += offset;
	}
	return 0;
}

//goto_w ------------------------------------------------------------------------------------------------
int goto_w(execucao *p) { // goto com index de 32 bits op: 0xC8
	u2 off1, off2;
	int offset;
	off1 = lerU2Codigo(p->frameAtual);
	off2 = lerU2Codigo(p->frameAtual);
	offset = off1;
	offset = (offset << 16) | (off2);
	offset -= 5; // Para  corrigir o PC
	p->frameAtual->pc += offset;
	return 0;
}

int jsr_w(execucao *p) { // similar ao goto mas joga o pc na pilha op: 0xC9
	u2 off1, off2;
	tipoOperando op1;
	unsigned int offset;
	off1 = lerU2Codigo(p->frameAtual);
	off2 = lerU2Codigo(p->frameAtual);
	offset = off1;
	offset = (offset << 16) | (off2);
	offset -= 5; // Para  corrigir o PC
	op1.tipoReferencia = p->frameAtual->pc;
	pushOperand(&(p->frameAtual->topoPilhaOperandos), op1, TIPO1);
	p->frameAtual->pc += offset;
	return 0;
}

int (*vetInstr[])(execucao *p) = {
	nop, // 0x00
		aconst_null,// 0x1
		iconst_m1,// 0x2
		iconst_0,// 0x3
		iconst_1,// 0x4
		iconst_2,// 0x5
		iconst_3,// 0x6
		iconst_4,// 0x7
		iconst_5,// 0x8
		lconst_0,// 0x9
		lconst_1,// 0xA
		fconst_0,// 0xB
		fconst_1,// 0xC
		fconst_2,// 0xD
		dconst_0,// 0xE
		dconst_1,// 0xF
		bipush,// 0x10
		sipush,// 0x11
		ldc,// 0x12
		ldc_w,// 0x13
		ldc2_w,// 0x14
		iload,// 0x15
		lload,// 0x16
		fload,// 0x17
		dload,// 0x18
		aload,// 0x19
		iload_0,// 0x1A
		iload_1,// 0x1B
		iload_2,// 0x1C
		iload_3,// 0x1D
		lload_0,// 0x1E
		lload_1,// 0x1F
		lload_2,// 0x20
		lload_3,// 0x21
		fload_0,// 0x22
		fload_1,// 0x23
		fload_2,// 0x24
		fload_3,// 0x25
		dload_0,// 0x26
		dload_1,// 0x27
		dload_2,// 0x28
		dload_3,// 0x29
		aload_0,// 0x2A
		aload_1,// 0x2B
		aload_2,// 0x2C
		aload_3,// 0x2D
		iaload,// 0x2E
		laload,// 0x2F
		faload,// 0x30
		daload,// 0x31
		aaload,// 0x32
		iaload,// 0x33
		iaload,// 0x34
		iaload,// 0x35
		store,// 0x36
		store,// 0x37
		store,// 0x38
		store,// 0x39
		store,// 0x3A
		store_0,// 0x3B
		store_1,// 0x3C
		store_2,// 0x3D
		store_3,// 0x3E
		store_0,// 0x3F
		store_1,// 0x40
		store_2,// 0x41
		store_3,// 0x42
		store_0,// 0x43
		store_1,// 0x44
		store_2,/// 0x45
		store_3,// 0x46
		store_0,// 0x47
		store_1,// 0x48
		store_2,/// 0x49
		store_3,// 0x4A
		store_0,// 0x4B
		store_1,// 0x4C
		store_2,/// 0x4D
		store_3,// 0x4E
		iastore,// 0x4F
		lastore,// 0x50
		fastore,// 0x51
		dastore,// 0x52
		aastore,// 0x53
		iastore,// 0x54
		iastore,// 0x55
		iastore,// 0x56
		pop,// 0x57
		pop2,// 0x58
		dup,//0x59
		dup_x1,//0x5A
		dup_x2,//0x5B
		dup2,// 0x5C
		dup2_x1,// 0x5D
		dup2_x2,// 0x5E
		swap,// 0x5F
		iadd,// 0x60
		ladd,// 0x61
		fadd,// 0x62
		dadd,// 0x63
		isub,// 0x64
		lsub,// 0x65
		fsub,// 0x66
		dsub,// 0x67
		imul,// 0x68
		lmul,// 0x69
		fmul,// 0x6A
		dmul,// 0x6B
		idiv,// 0x6C
		ldiv_,// 0x6D
		fdiv,// 0x6E
		ddiv,// 0x6F
		irem,// 0x70
		lrem,// 0x71
		frem,// 0x72
		drem_,// 0x73
		ineg,// 0x74
		lneg,// 0x75
		fneg,// 0x76
		dneg,// 0x77
		ishl,// 0x78
		lshl,// 0x79
		ishr,// 0x7A
		lshr,// 0x7B
		iushr,// 0x7C
		lushr,// 0x7D
		iand,// 0x7E
		land,// 0x7F
		ior,// 0x80
		lor,// 0x81
		ixor,// 0x82
		lxor,// 0x83
		iinc,// 0x84
		i2l,// 0x85
		i2f,// 0x86
		i2d,// 0x87
		l2i,// 0x88
		l2f,// 0x89
		l2d,// 0x8A
		f2i,// 0x8B
		f2l,// 0x8C
		f2d,// 0x8D
		d2i,// 0x8E
		d2l,// 0x8F
		d2f,// 0x90
		i2c,// 0x91
		i2c,// 0x92
		i2s,// 0x93
		lcmp,// 0x94
		fcmpl,// 0x95
		fcmpg,// 0x96
		dcmpl,// 0x97
		dcmpg,// 0x98
		ifeq,// 0x99
		ifne,// 0x9A
		iflt,// 0x9B
		ifge,// 0x9C
		ifgt,// 0x9D
		ifle,// 0x9E
		if_icmpeq,// 0x9F
		if_icmpne,// 0xA0
		if_icmplt,// 0xA1
		if_icmpge,// 0xA2
		if_icmpgt,// 0xA3
		if_icmple,// 0xA4
		if_acmpeq,// 0XA5
		if_acmpne,// 0xA6
		goto_,// 0xA7
		jsr,// 0xA8
		ret,// 0xA9
		tableswitch,// 0xAA
		lookupswitch,// 0xAB
		ireturn,// 0xAC
		lreturn,// 0xAD
		freturn,// 0xAE
		dreturn,// 0xAF
		areturn,// 0xB0
		return_,// 0xB1
		getstatic,// 0xB2
		putstatic,// 0xB3
		getfield,// 0xB4
		putfield,// 0xB5
		invokevirtual,// 0xB6
		invokespecial,// 0xB7
		invokestatic,// 0xB8
		nop,//nop,// 0xB9
		nop,//nop,// 0xBA
		new_,// 0xBB
		newarray,// 0xBC
		anewarray,// 0xBD
		arraylength,// 0xBE
		nop,//athrow,// 0xBF
		nop,//checkcast,// 0xC0
		nop,//instanceof,// 0xC1
		nop,//nop,// 0xC2
		nop,//nop,// 0xC3
		nop,//wide,// 0xC4
		multianewarray,// 0xC5
		ifnull,// 0xC6
		ifnonnull,// 0xC7
		goto_w,// 0xC8
		jsr_w// 0xC9
};
