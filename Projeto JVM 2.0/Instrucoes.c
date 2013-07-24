#include "Instrucoes.h"
#include "math.h"
// tags de tipo para implementação dos arrays

int nop(Interpretador *interpretador) {
	return 0;
}

int aconst_null(Interpretador *interpretador) { // empty -> value (NULL) operand: 0x01

	OperandType operand;

	operand.tipoReferencia = NULL;

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);

	return 0;
}

//const --------------------------------------------------------------------------------------------------------------------------------------------------------------------
int iconst_m1(Interpretador *interpretador) {

	OperandType operand;

	operand.tipoInt = -1;

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int iconst_0(Interpretador *interpretador) {

	OperandType operand;

	operand.tipoInt = 0;

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int iconst_1(Interpretador *interpretador) {

	OperandType operand;

	operand.tipoInt = 1;

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int iconst_2(Interpretador *interpretador) {

	OperandType operand;

	operand.tipoInt = 2;

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int iconst_3(Interpretador *interpretador) {

	OperandType operand;

	operand.tipoInt = 3;

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int iconst_4(Interpretador *interpretador) {

	OperandType operand;

	operand.tipoInt = 4;

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int iconst_5(Interpretador *interpretador) {

	OperandType operand;

	operand.tipoInt = 5;

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int lconst_0(Interpretador *interpretador) { // Insere na pilha a constante long 0 operand: 0x9
	OperandType operand;
	operand.longType = 0;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int lconst_1(Interpretador *interpretador) { // Insere na pilha a constante long 1 operand: 0xA

	OperandType operand;
	operand.longType = 1;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;

}

int fconst_0(Interpretador *interpretador) { // Insere na pilha a constante float 0.0 operand: 0xB
	OperandType operand;
	operand.tipoFloat = 0.0;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int fconst_1(Interpretador *interpretador) { // Insere na pilha a constante float 1.0 operand: 0xC
	OperandType operand;
	operand.tipoFloat = 1.0;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int fconst_2(Interpretador *interpretador) { // Insere na pilha a constante long 2.0 operand: 0xD
	OperandType operand;
	operand.tipoFloat = 2.0;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int dconst_0(Interpretador *interpretador) { // Insere na pilha a constante float 0.0 operand: 0xE
	OperandType operand;
	operand.tipoDouble = 0.0;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int dconst_1(Interpretador *interpretador) { // Insere na pilha a constante float 0.0 operand: 0xF
	OperandType operand;
	operand.tipoDouble = 1.0;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

//Push --------------------------------------------------------------------------------------------------------------------------------------------------------------------
int bipush(Interpretador *interpretador) { //insere na pilha o fieldType lido do índice operand: 0x10

	OperandType operand;
	char byteLido;

	byteLido = readU1Code(interpretador->topFrame);
	operand.tipoInt = byteLido;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);

	return 0;
}

int sipush(Interpretador *interpretador) { //insere na pilha o fieldType (u2) lido do índice operand: 0x11

	OperandType operand;
	short shortLido;

	shortLido = readU2Code(interpretador->topFrame);
	operand.tipoInt = shortLido;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);

	return 0;
}

//Ldc -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Lê um índice de 2 bytes e carrega o fieldType que estiver na constant pool neste índice operand: 0x12
 No caso da String, é carregado sua referência*/
int ldc(Interpretador *interpretador) {

	u2 index;
	OperandType operand;

	index = readU1Code(interpretador->topFrame);

	switch (interpretador->topFrame->constantPool[index].tag) {
	case CONSTANT_Integer:
		operand.tipoInt = interpretador->topFrame->constantPool[index].info.integerInfo.bytes;
		break;
	case CONSTANT_Float:
		operand.tipoFloat = interpretador->topFrame->constantPool[index].info.floatInfo.f.num;
		break;
	case CONSTANT_String:
		operand.tipoReferencia =
				(char*) getUtf8(interpretador->topFrame->constantPool,
						interpretador->topFrame->constantPool[index].info.stringInfo.stringIndex);
		break;
	default:
		printf("\nInstrução ldc sendo utilizado com index invalido\n");
		exit(1);
	}

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);

	return 0;
}

int ldc_w(Interpretador *interpretador) {  // ldc com index duplo operand: 0x13

	u2 index;
	OperandType operand;

	index = readU2Code(interpretador->topFrame);

	switch (interpretador->topFrame->constantPool[index].tag) {
	case CONSTANT_Integer:
		operand.tipoInt = interpretador->topFrame->constantPool[index].info.integerInfo.bytes;
		break;
	case CONSTANT_Float:
		operand.tipoFloat = interpretador->topFrame->constantPool[index].info.floatInfo.f.num;
		break;
	case CONSTANT_String:
		operand.tipoReferencia =
				(char*) getUtf8(interpretador->topFrame->constantPool,
						interpretador->topFrame->constantPool[index].info.stringInfo.stringIndex);
		break;
	default:
		printf("\nInstrução ldc_w sendo utilizado com index invalido\n");
		exit(1);
	}

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);

	return 0;
}

int ldc2_w(Interpretador *interpretador) {  // ldc com index duplo operand: 0x14

	u2 index;
	OperandType operand;

	index = readU2Code(interpretador->topFrame);

	switch (interpretador->topFrame->constantPool[index].tag) {
	case CONSTANT_Double:
		operand.tipoDouble =
				interpretador->topFrame->constantPool[index].info.doubleInfo.d.num;
		break;
	case CONSTANT_Long:
		operand.longType = interpretador->topFrame->constantPool[index].info.longInfo.bytes;
		break;
	default:
		printf("\nInstrução ldc2_w sendo utilizado com index invalido\n");
		exit(1);
	}

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);

	return 0;
}

//Load --------------------------------------------------------------------------------------------------------------------------------------------------------------------
int iload(Interpretador *interpretador) { //insere na pilha o fieldType da posicao apontada por um index do vetor de variáveis locais operand: 0x15 , 0x16 , 0x17 ,0x18 , 0x19
	u1 index;
	OperandType operand;
	index = readU1Code(interpretador->topFrame);
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int iload_0(Interpretador *interpretador) { //insere na pilha o fieldType da posicao 0 do vetor de variáveis locais operand: 0x1A , 0X1E ,0X22 , 0X26 ,0X2A
	u1 index;
	OperandType operand;
	index = 0;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int iload_1(Interpretador *interpretador) { //insere na pilha um int da constant pool operand: 0X1B , 0X1F , 0X23 , 0X27 , 0X2B
	u1 index;
	OperandType operand;
	index = 1;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int iload_2(Interpretador *interpretador) { //insere na pilha um int da constant pool operand: 0X1C , 0X20 , 0X24 , 0X28 , OX2C
	u1 index;
	OperandType operand;
	index = 2;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int iload_3(Interpretador *interpretador) { //insere na pilha um int da constant pool operand: 0X1D , 0X21 , 0X25 , 0X29 , 0X2D
	u1 index;
	OperandType operand;
	index = 3;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int fload(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = readU1Code(interpretador->topFrame);
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int fload_0(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 0;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int fload_1(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 1;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int fload_2(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 2;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int fload_3(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 3;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int lload(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = readU1Code(interpretador->topFrame);
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int lload_0(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 0;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int lload_1(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 1;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int lload_2(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 2;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int lload_3(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 3;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int dload(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = readU1Code(interpretador->topFrame);
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int dload_0(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 0;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int dload_1(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 1;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int dload_2(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 2;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int dload_3(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 3;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
	return 0;
}

int aload(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = readU1Code(interpretador->topFrame);
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int aload_0(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 0;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int aload_1(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 1;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int aload_2(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 2;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

int aload_3(Interpretador *interpretador) {
	u1 index;
	OperandType operand;
	index = 3;
	operand = interpretador->topFrame->arrayLocal[index];
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 0;
}

// Aload ---------------------------------------------------------------------------------------------------------------------------------------------------

int iaload(Interpretador *interpretador) { //carrega um int de um vetor operand: 0x2E , 0X33 , 0X34 , 0X35
	OperandType arrayref, index;
	Array *vet;
	index = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	arrayref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos),
			vet->array[index.tipoInt], TIPO1);
	return 0;
}

int laload(Interpretador *interpretador) { //carrega um long de um vetor operand: 0x2F
	OperandType arrayref, index;
	Array *vet;
	index = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	arrayref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos),
			vet->array[index.tipoInt], TIPO2);
	return 0;
}

int faload(Interpretador *interpretador) { //carrega um float de um vetor operand: 0x30
	OperandType arrayref, index;
	Array *vet;
	index = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	arrayref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos),
			vet->array[index.tipoInt], TIPO1);
	return 0;
}

int daload(Interpretador *interpretador) { //carrega um double de um vetor operand: 0x31
	OperandType arrayref, index;
	Array *vet;
	index = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	arrayref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos),
			vet->array[index.tipoInt], TIPO2);
	return 0;
}

int aaload(Interpretador *interpretador) { //carrega um float de um vetor operand: 0x32
	OperandType arrayref, index;
	Array *vet;
	index = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	arrayref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos),
			vet->array[index.tipoInt], TIPO1);
	return 0;
}
//Store --------------------------------------------------------------------------------------------------------------------------------------------------------------------
int store(Interpretador *interpretador) { //recebe um index e salva o topo da pilha de operandos no index do vetor de variaveis locais 0x36 , 0X37 , 0X38 , 0X39 , 0X3A
	u1 index;
	OperandType operand;
	index = readU1Code(interpretador->topFrame);
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	interpretador->topFrame->arrayLocal[index] = operand;
	return 0;
}

int store_0(Interpretador *interpretador) { //salva o fieldType na posicao 0 0X3B,0X3F,0X43,0X47,0x4C
	OperandType operand;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	interpretador->topFrame->arrayLocal[0] = operand;
	return 0;
}

int store_1(Interpretador *interpretador) { //salva o fieldType na posicao 1 0X3C,0X40,0X44,0X48,0x4D
	OperandType operand;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	interpretador->topFrame->arrayLocal[1] = operand;
	return 0;
}

int store_2(Interpretador *interpretador) { //salva o fieldType na posicao 2 0X3D,0X41,0X45,0X49,0x4E
	OperandType operand;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	interpretador->topFrame->arrayLocal[2] = operand;
	return 0;
}

int store_3(Interpretador *interpretador) { //salva o fieldType na posicao 3 0X3E,0X42,0X46,0X4A
	OperandType operand;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	interpretador->topFrame->arrayLocal[3] = operand;
	return 0;
}

//Astore ----------------------------------------------------------------------------------------------------------------------------------------------------------------

int iastore(Interpretador *interpretador) { // salva um int num vetor operand:0x4F , 0x54 , 0x55 , 0x56
	OperandType arrayref, index, value;
	Array *vet;
	value = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	index = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	arrayref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	vet->array[index.tipoInt].tipoInt = value.tipoInt;
	return 0;
}

int lastore(Interpretador *interpretador) { // salva um long num vetor operand:0x50
	OperandType arrayref, index, value;
	Array *vet;
	value = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	index = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	arrayref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	vet->array[index.tipoInt].longType = value.longType;
	return 0;
}

int fastore(Interpretador *interpretador) { // salva um float num vetor 0p:0x51
	OperandType arrayref, index, value;
	Array *vet;
	value = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	index = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	arrayref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	vet->array[index.tipoInt].tipoFloat = value.tipoFloat;
	return 0;
}

int dastore(Interpretador *interpretador) { // salva um double num vetor 0p:0x52
	OperandType arrayref, index, value;
	Array *vet;
	value = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	index = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	arrayref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	vet->array[index.tipoInt].tipoDouble = value.tipoDouble;
	return 0;
}

int aastore(Interpretador *interpretador) { // salva uma referencia num vetor 0p:0x53
	OperandType arrayref, index, value;
	Array *vet;
	value = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	index = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	arrayref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	vet->array[index.tipoInt].tipoReferencia = value.tipoReferencia;
	return 0;
}

//pop ------------------------------------------------------------------------------------------------------------------------------------------------

int pop(Interpretador *interpretador) { // retira um tipo 1 da pilha de operandos operand: 0x57
	if (interpretador->topFrame->topoPilhaOperandos->type32_64 == TIPO1) {
		popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	} else {
		printf("Pop chamado sobre fieldType de tipo 2");
		exit(1);
	}
	return 0;
}

int pop2(Interpretador *interpretador) { // retira dois tipo 1 da pilha de operandos ou um tipo 2 operand: 0x58
	if ((interpretador->topFrame->topoPilhaOperandos->type32_64 == TIPO1)
			&& (interpretador->topFrame->topoPilhaOperandos->nextOperand->type32_64
					== TIPO1)) {
		popOperand(&(interpretador->topFrame->topoPilhaOperandos));
		popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	} else {
		popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	}
	return 0;
}

//dup  --------------------------------------------------------------------------------------------------------------------------------------------------------------------
int dup(Interpretador *interpretador) { // duplica o elemento no topo da pilha operand: 0x59
	OperandType operand;
	int type32_64;

	type32_64 = interpretador->topFrame->topoPilhaOperandos->type32_64;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, type32_64);
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, type32_64);
	return 0;
}

int dup_x1(Interpretador *interpretador) { // duplica o elemento no topo da pilha , dois elementos a baixo  operand: 0x5A
	OperandType operand, op1;
	int operandoTipoOp, operandoTipoOp1;

	operandoTipoOp = interpretador->topFrame->topoPilhaOperandos->type32_64;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	operandoTipoOp1 = interpretador->topFrame->topoPilhaOperandos->type32_64;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, operandoTipoOp1);
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	return 0;
}

int dup_x2(Interpretador *interpretador) { // duplica o elemento no topo da pilha tres a baixo operand: 0x5B
	OperandType operand, op1, op2;
	int operandoTipoOp, operandoTipoOp1, operandoTipoOp2;

	operandoTipoOp = interpretador->topFrame->topoPilhaOperandos->type32_64;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	operandoTipoOp1 = interpretador->topFrame->topoPilhaOperandos->type32_64;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	operandoTipoOp2 = interpretador->topFrame->topoPilhaOperandos->type32_64;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, operandoTipoOp2);
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, operandoTipoOp1);
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	return 0;
}

int dup2(Interpretador *interpretador) { // duplica o elemento no topo da pilha , dois elementos a baixo  operand: 0x5C
	OperandType operand, op1;
	int operandoTipoOp, operandoTipoOp1;

	operandoTipoOp = interpretador->topFrame->topoPilhaOperandos->type32_64;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	if (operandoTipoOp == TIPO1) {
		operandoTipoOp1 = interpretador->topFrame->topoPilhaOperandos->type32_64;
		op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	} else {
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	}

	return 0;
}

int dup2_x1(Interpretador *interpretador) { //duplica os dois primeiros elementos da pilha a baixo do terceiro 0x5D
	OperandType operand, op1, op2;
	int operandoTipoOp, operandoTipoOp1, operandoTipoOp2;

	operandoTipoOp = interpretador->topFrame->topoPilhaOperandos->type32_64;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	if (operandoTipoOp == TIPO1) {
		operandoTipoOp1 = interpretador->topFrame->topoPilhaOperandos->type32_64;
		op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	}

	operandoTipoOp2 = interpretador->topFrame->topoPilhaOperandos->type32_64;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	if (operandoTipoOp == TIPO1) {
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	} else {
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	}

	return 0;
}

int dup2_x2(Interpretador *interpretador) { //duplica os dois primeiros elementos da pilha a baixo do quarto 0x5E
	OperandType operand, op1, op2, op3;
	int operandoTipoOp, operandoTipoOp1, operandoTipoOp2, operandoTipoOp3;

	operandoTipoOp = interpretador->topFrame->topoPilhaOperandos->type32_64;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	if (operandoTipoOp == TIPO1) {
		operandoTipoOp1 = interpretador->topFrame->topoPilhaOperandos->type32_64;
		op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	}

	operandoTipoOp2 = interpretador->topFrame->topoPilhaOperandos->type32_64;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	if (operandoTipoOp2 == TIPO1) {
		operandoTipoOp3 = interpretador->topFrame->topoPilhaOperandos->type32_64;
		op3 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	}

	if (operandoTipoOp == TIPO1 && operandoTipoOp2 == TIPO1) {
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op3,
				operandoTipoOp3);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	} else if (operandoTipoOp2 == TIPO1) {
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op3,
				operandoTipoOp3);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	} else if (operandoTipoOp == TIPO1) {
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1,
				operandoTipoOp1);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	} else {
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2,
				operandoTipoOp2);
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, operandoTipoOp);
	}
	return 0;
}

int swap(Interpretador *interpretador) { //troca os dois elementos do topo da pilha operand:0x5F
	OperandType op1, op2;
	int operandoTipoOp1, operandoTipoOp2;

	operandoTipoOp1 = interpretador->topFrame->topoPilhaOperandos->type32_64;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	operandoTipoOp2 = interpretador->topFrame->topoPilhaOperandos->type32_64;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	if (operandoTipoOp1 != TIPO1 || operandoTipoOp2 != TIPO1) {
		printf("ERRO em swap: um dos operandos é tipo 2 (double ou long)\n");
		exit(1);
	}

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, operandoTipoOp1);
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, operandoTipoOp2);
	return 0;
}

// add --------------------------------------------------------------------------------------
int iadd(Interpretador *interpretador) { // v1 , v2 -> v1+v2 operand: 0x60
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoInt = op2.tipoInt + op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int ladd(Interpretador *interpretador) { // v1 , v2 -> v1+v2 operand: 0x61
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.longType = op2.longType + op1.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int fadd(Interpretador *interpretador) { // v1 , v2 -> v1+v2 operand: 0x62
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoFloat = op2.tipoFloat + op1.tipoFloat;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int dadd(Interpretador *interpretador) { // v1 , v2 -> v1+v2 operand: 0x63
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoDouble = op2.tipoDouble + op1.tipoDouble;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// sub --------------------------------------------------------------------------------------
int isub(Interpretador *interpretador) { // v1 , v2 -> v1-v2 operand: 0x64
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoInt = op2.tipoInt - op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lsub(Interpretador *interpretador) { // v1 , v2 -> v1-v2 operand: 0x65
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoFloat = op2.tipoFloat - op1.tipoFloat;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int fsub(Interpretador *interpretador) { // v1 , v2 -> v1-v2 operand: 0x66
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoFloat = op2.tipoFloat - op1.tipoFloat;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int dsub(Interpretador *interpretador) { // v1 , v2 -> v1-v2 operand: 0x67
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoDouble = op2.tipoDouble - op1.tipoDouble;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// mul --------------------------------------------------------------------------------------
int imul(Interpretador *interpretador) { // v1 , v2 -> v1*v2 operand: 0x68
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoInt = op2.tipoInt * op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lmul(Interpretador *interpretador) { // v1 , v2 -> v1*v2 operand: 0x69
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.longType = op2.longType * op1.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int fmul(Interpretador *interpretador) { // v1 , v2 -> v1*v2 operand: 0x6A
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoFloat = op2.tipoFloat * op1.tipoFloat;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int dmul(Interpretador *interpretador) { // v1 , v2 -> v1*v2 operand: 0x6B
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoDouble = op2.tipoDouble * op1.tipoDouble;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// div --------------------------------------------------------------------------------------
int idiv(Interpretador *interpretador) { // v1 , v2 -> v1/v2 operand: 0x6C
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoInt = op2.tipoInt / op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int ldiv_(Interpretador *interpretador) { // v1 , v2 -> v1 / v2 operand: 0x6D
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	op1.longType = op2.longType / op1.longType;

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);

	return 0;

}

int fdiv(Interpretador *interpretador) { // v1 , v2 -> v1/v2 operand: 0x6E
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoFloat = op2.tipoFloat / op1.tipoFloat;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int ddiv(Interpretador *interpretador) { // v1 , v2 -> v1/v2 operand: 0x6F
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoDouble = op2.tipoDouble / op1.tipoDouble;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// rem --------------------------------------------------------------------------------------
int irem(Interpretador *interpretador) { // v1 , v2 -> v1 mod v2 operand: 0x70
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoInt = op2.tipoInt % op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lrem(Interpretador *interpretador) { // v1 , v2 -> v1 mod v2 operand: 0x71
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.longType = op2.longType % op1.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int frem(Interpretador *interpretador) { // v1 , v2 -> v1 mod v2 operand: 0x72
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoFloat = (float) fmod(op2.tipoFloat, op1.tipoFloat);
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int drem_(Interpretador *interpretador) { // v1 , v2 -> v1 mod v2 operand: 0x73
	OperandType op1, op2;

	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	op1.tipoDouble = fmod(op2.tipoDouble, op1.tipoDouble);

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);

	return 0;
}

//neg --------------------------------------------------------------------------------------
int ineg(Interpretador *interpretador) { // v1 -> -v1 operand: 0x74
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoInt = 0 - op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lneg(Interpretador *interpretador) { // v1 -> -v1 operand: 0x74
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.longType = 0 - op1.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int fneg(Interpretador *interpretador) { // v1 -> -v1 operand: 0x76
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoFloat = 0 - op1.tipoFloat;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int dneg(Interpretador *interpretador) { // v1 -> -v1 operand: 0x74
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoDouble = 0 - op1.tipoDouble;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// shifts --------------------------------------------------------------------------------
int ishl(Interpretador *interpretador) { // v1 , v2 -> v1<<5 bits de baixo de v2 operand: 0x78
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v2
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v1
	op1.tipoInt = op1.tipoInt & 0x1F;// isolando os 5 bits menos significativos de v2
	op1.tipoInt = op2.tipoInt << op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lshl(Interpretador *interpretador) { // v1 , v2 -> v1<<6 bits de baixo de v2 operand: 0x79
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v2
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v1
	op1.longType = op1.longType & 0x3F;	// isolando os 6 bits menos significativos de v2
	op1.longType = op2.longType << op1.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int ishr(Interpretador *interpretador) { // v1 , v2 -> v1>>5 bits de baixo de v2 operand: 0x7A
	OperandType op1, op2;
	int mask = 0x80000000;
	int count = 0;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v2
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v1
	op1.tipoInt = op1.tipoInt & 0x1F;// isolando os 5 bits menos significativos de v2
	if (op2.tipoInt < 0) {
		int i;
		for (i = 0; i < op1.tipoInt; ++i) {
			count = count >> 1;
			count = count | mask;
		}
		op1.tipoInt = op2.tipoInt >> op1.tipoInt; //fieldType shiftado
		op1.tipoInt = op1.tipoInt | count;
	} else {
		op1.tipoInt = op2.tipoInt >> op1.tipoInt;
	}
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lshr(Interpretador *interpretador) { // v1 , v2 -> v1>>5 bits de baixo de v2 operand: 0x7B
	OperandType op1, op2;
	long long mask = 0x8000000000000000;
	long long count = 0;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v2
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v1
	op1.longType = op1.longType & 0x3F;	// isolando os 5 bits menos significativos de v2
	if (op2.longType < 0) {
		int i;
		for (i = 0; i < op1.tipoInt; ++i) {
			count = count >> 1;
			count = count | mask;
		}
		op1.longType = op2.longType >> op1.longType; //fieldType shiftado
		op1.longType = op1.longType | count;
	} else {
		op1.longType = op2.longType >> op1.longType;
	}
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int iushr(Interpretador *interpretador) { // v1 , v2 -> v1>>5 bits de baixo de v2 operand: 0x7C
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v2
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v1
	op1.tipoInt = op1.tipoInt & 0x1F;// isolando os 5 bits menos significativos de v2
	op1.tipoInt = op2.tipoInt >> op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lushr(Interpretador *interpretador) { // operand: 0x7D
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v2
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));	// v1
	op1.longType = op1.longType & 0x3F;	// isolando os 6 bits menos significativos de v2
	op1.longType = op2.longType >> op1.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

// bitwise ----------------------------------------------------------------------------------------------
int iand(Interpretador *interpretador) {	// V1 , V2 -> V1 AND V2 operand: 0x7E

	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoInt = op1.tipoInt & op2.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int land(Interpretador *interpretador) {	// V1 , V2 -> V1 AND V2 operand: 0x7F
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.longType = op1.longType & op2.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int ior(Interpretador *interpretador) {	// V1 , V2 -> V1 OR V2 operand: 0x80
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoInt = op1.tipoInt | op2.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lor(Interpretador *interpretador) {	// V1 , V2 -> V1 OR V2 operand: 0x81
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.longType = op1.longType | op2.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int ixor(Interpretador *interpretador) {	// V1 , V2 -> V1 OR V2 operand: 0x82
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.tipoInt = op1.tipoInt ^ op2.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	return 0;
}

int lxor(Interpretador *interpretador) {	// V1 , V2 -> V1 OR V2 operand: 0x83
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1.longType = op1.longType ^ op2.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO2);
	return 0;
}

int iinc(Interpretador *interpretador) {
	u1 index;
	char constante;
	index = readU1Code(interpretador->topFrame);
	constante = readU1Code(interpretador->topFrame);
	interpretador->topFrame->arrayLocal[index].tipoInt++;
	return 0;
}

// x2y-----------------------------------------------------------------------------------------------------------
int i2l(Interpretador *interpretador) {//  Converte o fieldType do topo da pilha de int para long operand: 0x85
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.longType = op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int i2f(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de int para float operand: 0x86
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.tipoFloat = (float) op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int i2d(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de int para double operand: 0x87
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.tipoDouble = (double) op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int l2i(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de long para int operand: 0x88
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.tipoInt = (int) op1.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int l2f(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de long para float operand: 0x89
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.tipoFloat = (float) op1.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int l2d(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de long para double operand: 0x8A
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.tipoDouble = (double) op1.longType;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int f2i(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de float para int operand: 0x8B
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.tipoInt = (int) op1.tipoFloat;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int f2l(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de float para long operand: 0x8C
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.longType = (long long) op1.tipoFloat;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int f2d(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de float para double operand: 0x8D
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.tipoDouble = (double) op1.tipoFloat;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int d2i(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de double para int operand: 0x8E
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.tipoInt = (int) op1.tipoDouble;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int d2l(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de double para long operand: 0x8F
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.longType = (long long) op1.tipoDouble;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int d2f(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de double para float operand: 0x90
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.tipoFloat = (float) op1.tipoDouble;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO1);
	return 0;
}

int i2c(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de int para char , cobre tambem o caso do byte - i2b operand: 0x91 ,0x92
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.tipoInt = (char) op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

int i2s(Interpretador *interpretador) { //  Converte o fieldType do topo da pilha de int para short - i2b operand: 0x93
	OperandType op1, op2;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op2.tipoInt = (short) op1.tipoInt;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op2, TIPO2);
	return 0;
}

//XcmpY -----------------------------------------------------------------------------------------------------------
int lcmp(Interpretador *interpretador) { //compara dois valores long 0x94
	OperandType op1, op2, resultado;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	if (op1.longType > op2.longType) {
		resultado.tipoInt = 1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.longType == op2.longType) {
		resultado.tipoInt = 0;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else {
		resultado.tipoInt = -1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	}
	return 0;
}

int fcmpl(Interpretador *interpretador) { // comparação entre floats , caso NAN resultado -1 operand: 0x95
	OperandType op1, op2, resultado;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	if (op1.tipoFloat > op2.tipoFloat) {
		resultado.tipoInt = 1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoFloat == op2.tipoFloat) {
		resultado.tipoInt = 0;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoFloat < op2.tipoFloat) {
		resultado.tipoInt = -1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else {
		resultado.tipoInt = -1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	}
	return 0;
}

int fcmpg(Interpretador *interpretador) { // comparação entre floats , caso NAN resultado 1 operand: 0x96
	OperandType op1, op2, resultado;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	if (op1.tipoFloat > op2.tipoFloat) {
		resultado.tipoInt = 1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoFloat == op2.tipoFloat) {
		resultado.tipoInt = 0;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoFloat < op2.tipoFloat) {
		resultado.tipoInt = -1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else {
		resultado.tipoInt = 1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	}
	return 0;
}

int dcmpl(Interpretador *interpretador) { // comparação entre doubles , caso NAN resultado 1 operand: 0x97
	OperandType op1, op2, resultado;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	if (op1.tipoDouble > op2.tipoDouble) {
		resultado.tipoInt = 1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoDouble == op2.tipoDouble) {
		resultado.tipoInt = 0;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoDouble < op2.tipoDouble) {
		resultado.tipoInt = -1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else {
		resultado.tipoInt = -1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	}
	return 0;
}

int dcmpg(Interpretador *interpretador) { // comparação entre doubles , caso NAN resultado 1 operand: 0x98
	OperandType op1, op2, resultado;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	if (op1.tipoDouble > op2.tipoDouble) {
		resultado.tipoInt = 1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoDouble == op2.tipoDouble) {
		resultado.tipoInt = 0;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else if (op1.tipoDouble < op2.tipoDouble) {
		resultado.tipoInt = -1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	} else {
		resultado.tipoInt = -1;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), resultado, TIPO1);
	}
	return 0;
}
// Ifs -----------------------------------------------------------------------------------------------------

int ifeq(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0x99
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt == 0) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int ifne(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0x9A
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt != 0) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int iflt(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0x9B
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt < 0) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int ifge(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0x9C
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt >= 0) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int ifgt(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0x9D
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt > 0) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int ifle(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0x9E
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt <= 0) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int if_icmpeq(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0x9F
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1, op2;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt == op2.tipoInt) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int if_icmpne(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0xA0
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1, op2;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt != op2.tipoInt) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int if_icmplt(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0xA1
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1, op2;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt < op2.tipoInt) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int if_icmpge(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0xA2
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1, op2;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt >= op2.tipoInt) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int if_icmpgt(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0xA3
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1, op2;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt > op2.tipoInt) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int if_icmple(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0xA4
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1, op2;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoInt <= op2.tipoInt) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int if_acmpeq(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0xA5
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1, op2;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoReferencia == op2.tipoReferencia) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int if_acmpne(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0xA6
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	OperandType op1, op2;
	op2 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoReferencia != op2.tipoReferencia) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

// controle -----------------------------------------------------------------------------------------------
int goto_(Interpretador *interpretador) { // operand: 0xA7
	short offset;
	offset = (short) readU2Code(interpretador->topFrame);
	offset -= 3; // serve para corrigir o offset do PC
	interpretador->topFrame->pc += offset;
	return 0;
}

int jsr(Interpretador *interpretador) {  // 0xA8
	u2 offset;
	OperandType operand;
	offset = readU2Code(interpretador->topFrame);
	offset -= 3; // serve para corrigir o offset do PC
	operand.tipoReferencia = interpretador->topFrame->pc;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	interpretador->topFrame->pc += offset;
	return 0;
}

int ret(Interpretador *interpretador) { // VAI DAR MERDA CAPITÃO  // 0xA9
	u1 index;
	index = readU1Code(interpretador->topFrame);
	interpretador->topFrame->pc = interpretador->topFrame->arrayLocal[index].tipoReferencia;
	return 0;
}

// Switch -------------------------------------------------------------------------------------------------------
int tableswitch(Interpretador *interpretador) {
	int default_, low, high, switchsize, i, sizepads;
	u1 *pcVolta;
	OperandType index;
	pcVolta = interpretador->topFrame->pc - 1;

	index = popOperand(&(interpretador->topFrame->topoPilhaOperandos)); // tirando o indeice do case da pilha

	sizepads = (4 - (interpretador->topFrame->pc - interpretador->topFrame->currOpcode) % 4)
			% 4; // calculando quantos bits de pad são necessários
	for (i = 0; i < sizepads; ++i) {
		readU1Code(interpretador->topFrame); // padding de bytes no inicio
	}

	default_ = (int) readU4Code(interpretador->topFrame); // leitura do offset de default
	low = (int) readU4Code(interpretador->topFrame); // leitura do offset do menor case
	high = (int) readU4Code(interpretador->topFrame); // leitura do offset ddo maior case

	switchsize = (high - low + 1); // tirando o tamanho do switch
	if (switchsize < 0) { // checando para erros
		printf("Erro tableswitch , low maior do que high");
		exit(1);
	}

	int *offsets;
	offsets = calloc(switchsize, sizeof(int));
	for (i = 0; i < switchsize; ++i) { // preenchendo a tabela dos offsets do case
		offsets[i] = readU4Code(interpretador->topFrame);
	}

	interpretador->topFrame->pc = pcVolta; // recuperando o fieldType do pc
	if ((index.tipoInt > high) || (index.tipoInt < low)) { // caso default
		interpretador->topFrame->pc = interpretador->topFrame->pc + default_;
	} else {
		interpretador->topFrame->pc = interpretador->topFrame->pc + (offsets[index.tipoInt - low]);
	}
	free(offsets);
	return 0;
}

int lookupswitch(Interpretador *interpretador) {
	int default_, npairs, i, sizepads;
	u1 *endBaseInstr;
	OperandType key;
	endBaseInstr = interpretador->topFrame->pc - 1; // salva o edereço do opcode da instrução

	key = popOperand(&(interpretador->topFrame->topoPilhaOperandos)); // tirando o indeice do case da pilha
	sizepads = (4 - (interpretador->topFrame->pc - interpretador->topFrame->currOpcode) % 4)
			% 4; // calculando quantos bits de pad são necessários
	for (i = 0; i < sizepads; ++i) {
		readU1Code(interpretador->topFrame); // padding de bytes no inicio
	}
	default_ = readU4Code(interpretador->topFrame); // le o offset do default
	npairs = readU4Code(interpretador->topFrame); // le o numero  de pares

	int offsets[npairs][2];
	for (i = 0; i < npairs; ++i) { // povoa a matriz de pares
		offsets[i][0] = readU4Code(interpretador->topFrame); // match
		offsets[i][1] = readU4Code(interpretador->topFrame); // offset
	}
	interpretador->topFrame->pc = endBaseInstr;
	for (i = 0; i < npairs; ++i) {
		if (key.tipoInt == offsets[i][0]) {
			interpretador->topFrame->pc += offsets[i][1];
			return 0;
		}
	}
	interpretador->topFrame->pc += default_;
	return 0;
}
// retornos ----------------------------------------------------------------------------------------------

int ireturn(Interpretador *interpretador) { // value -> empty , joga value na pilha de operandos  do frame que chamou operand: 0xAC
	OperandType operand;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	popFrame(&(interpretador->topFrame));
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 1;
}

int lreturn(Interpretador *interpretador) { // value -> empty operand: 0xAD

	OperandType operand;

	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	popFrame(&(interpretador->topFrame));
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);

	return 1;
}

int freturn(Interpretador *interpretador) { // value -> empty operand: 0xAE
	OperandType operand;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	popFrame(&(interpretador->topFrame));
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 1;
}

int dreturn(Interpretador *interpretador) { // value -> empty operand: 0xAF
	OperandType operand;

	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	popFrame(&(interpretador->topFrame));
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);

	return 1;
}

int areturn(Interpretador *interpretador) { // value -> empty operand: 0xB0
	OperandType operand;
	operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	popFrame(&(interpretador->topFrame));
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	return 1;
}

int return_(Interpretador *interpretador) { // -> empty, não retorna nada OP: 0xB1
	popFrame(&(interpretador->topFrame));
	return 1;
}

// Static Field -------------------------------------------------------------------------------------------

// Função que pega um field estático do array de campos estáticos da classe e o empilha
int getstatic(Interpretador *interpretador) { // operand: 0xB2

	ClassFile *classFile;
	OperandType operand;
	Field* fieldAProcurar;
	char* className;
	char* fieldName;
	char* descriptor;
	u2 indiceFieldRefInfo;
	u2 classInfoIndex;
	u2 indiceNomeClasse;
	u2 indiceNameAndTypeInfo;
	u2 fieldNameIndex;
	u2 indiceTipoField;

	indiceFieldRefInfo = readU2Code(interpretador->topFrame);

	classInfoIndex =
			interpretador->topFrame->constantPool[indiceFieldRefInfo].info.fieldRefInfo.classIndex;
	indiceNomeClasse =
			interpretador->topFrame->constantPool[classInfoIndex].info.classInfo.nameIndex;

	className = getUtf8(interpretador->topFrame->constantPool,
			indiceNomeClasse);

	indiceNameAndTypeInfo =
			interpretador->topFrame->constantPool[indiceFieldRefInfo].info.fieldRefInfo.nameAndTypeIndex;
	fieldNameIndex =
			interpretador->topFrame->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.nameIndex;
	fieldName = getUtf8(interpretador->topFrame->constantPool,
			fieldNameIndex);

	indiceTipoField =
			interpretador->topFrame->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.descriptorIndex;
	descriptor = getUtf8(interpretador->topFrame->constantPool,
			indiceTipoField);

	// Se o field atender a essas condições, é um field que significa print
	if (strcmp(className, "java/lang/System") == 0
			&& strcmp(fieldName, "out") == 0
			&& strcmp(descriptor, "Ljava/io/PrintStream;") == 0) {

		operand.longType = 0;

		// Empilhamos esse operand relativemente inútil pois temos que empilhar algo dessa instrução
		// Ele será descartado assim que o invokevirtual do print for chamado
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
	} else { // Senão, temos que buscar nos fields da classe requisitada

		// Verificamos se estamos requisitando uma classe que já está carregada
		classFile = checkClass(interpretador, className);

		fieldAProcurar = getStaticFieldName(interpretador->topClass, className,
				fieldName);

		// Não achei :(
		if (fieldAProcurar == NULL ) {
			printf("ERRO em getstatic: Field nao encontrado - %s %s %s\n",
					className, fieldName, descriptor);
			exit(1);
		} else {
			// Agora vemos o tipo do Field para podermos carregá-lo na pilha
			if (descriptor[0] == 'B' || descriptor[0] == 'C') {
				operand.tipoInt = fieldAProcurar->fieldType.tipoChar;
				pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
			} else if (descriptor[0] == 'S') {
				operand.tipoInt = fieldAProcurar->fieldType.tipoShort;
				pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
			} else if (descriptor[0] == 'D') {
				operand.tipoDouble = fieldAProcurar->fieldType.tipoDouble;
				pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
			} else if (descriptor[0] == 'F') {
				operand.tipoFloat = fieldAProcurar->fieldType.tipoFloat;
				pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
			} else if (descriptor[0] == 'I' || descriptor[0] == 'Z') {
				operand.tipoInt = fieldAProcurar->fieldType.tipoInt;
				pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
			} else if (descriptor[0] == 'J') {
				operand.longType = fieldAProcurar->fieldType.longType;
				pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO2);
			} else if (descriptor[0] == 'L' || descriptor[0] == '[') {
				operand.tipoReferencia = fieldAProcurar->fieldType.tipoReferencia;
				pushOperand(&(interpretador->topFrame->topoPilhaOperandos), operand, TIPO1);
			}
		}
	}

	return 0;
}

int putstatic(Interpretador *interpretador) { // 0xB3

	ClassFile *classFile;
	OperandType operand;
	Field* fieldAProcurar;
	char* className;
	char* fieldName;
	char* descriptor;
	u2 indiceFieldRefInfo;
	u2 classInfoIndex;
	u2 indiceNomeClasse;
	u2 indiceNameAndTypeInfo;
	u2 fieldNameIndex;
	u2 indiceTipoField;

	indiceFieldRefInfo = readU2Code(interpretador->topFrame);

	classInfoIndex =
			interpretador->topFrame->constantPool[indiceFieldRefInfo].info.fieldRefInfo.classIndex;
	indiceNomeClasse =
			interpretador->topFrame->constantPool[classInfoIndex].info.classInfo.nameIndex;

	className = getUtf8(interpretador->topFrame->constantPool,
			indiceNomeClasse);

	indiceNameAndTypeInfo =
			interpretador->topFrame->constantPool[indiceFieldRefInfo].info.fieldRefInfo.nameAndTypeIndex;
	fieldNameIndex =
			interpretador->topFrame->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.nameIndex;
	fieldName = getUtf8(interpretador->topFrame->constantPool,
			fieldNameIndex);

	indiceTipoField =
			interpretador->topFrame->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.descriptorIndex;
	descriptor = getUtf8(interpretador->topFrame->constantPool,
			indiceTipoField);

	// Verificamos se estamos requisitando uma classe que já está carregada
	classFile = checkClass(interpretador, className);

	fieldAProcurar = getStaticFieldName(interpretador->topClass, className,
			fieldName);

	// Não achei :(
	if (fieldAProcurar == NULL ) {
		printf("ERRO em putstatic: Field nao encontrado - %s %s %s\n",
				className, fieldName, descriptor);
		exit(1);
	} else {
		operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
		insertStaticFieldValue(interpretador->topClass, className, fieldName, operand);
	}

	return 0;
}

//Field -------------------------------------------------------------------------------------------------------
int getfield(Interpretador *interpretador) { //recebe um index e empilha o fieldType do field correspondente a este index na pilha de opeandos 0xB4
	u2 index;
	u2 nameAndTypeIndexAux;
	u2 nameIndexaux, descriptorIndexAux;
	object *object;
	Field* field;
	char *fieldName, *descritorField;
	OperandType objectref, value;
	index = readU2Code(interpretador->topFrame);
	objectref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	object = (object*) objectref.tipoReferencia;
	// resolução de nomes -----------------------
	nameAndTypeIndexAux =
			interpretador->topFrame->constantPool[index].info.fieldRefInfo.nameAndTypeIndex;
	nameIndexaux =
			interpretador->topFrame->constantPool[nameAndTypeIndexAux].info.nameAndTypeInfo.nameIndex;
	fieldName = interpretador->topFrame->constantPool[nameIndexaux].info.UTF8Info.bytes;
	descriptorIndexAux =
			interpretador->topFrame->constantPool[nameAndTypeIndexAux].info.nameAndTypeInfo.descriptorIndex;
	descritorField =
			interpretador->topFrame->constantPool[descriptorIndexAux].info.UTF8Info.bytes;

	field = getFieldName(fieldName, descritorField, object);
	if (descritorField[0] == 'B' || descritorField[0] == 'C') {
		value.tipoInt = field->fieldType.tipoChar;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), value, TIPO1);
	} else if (descritorField[0] == 'S') {
		value.tipoInt = field->fieldType.tipoShort;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), value, TIPO1);
	} else if (descritorField[0] == 'D') {
		value.tipoDouble = field->fieldType.tipoDouble;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), value, TIPO2);
	} else if (descritorField[0] == 'F') {
		value.tipoFloat = field->fieldType.tipoFloat;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), value, TIPO1);
	} else if (descritorField[0] == 'I' || descritorField[0] == 'Z') {
		value.tipoInt = field->fieldType.tipoInt;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), value, TIPO1);
	} else if (descritorField[0] == 'J') {
		value.longType = field->fieldType.longType;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), value, TIPO2);
	} else if (descritorField[0] == 'L' || descritorField[0] == '[') {
		value.tipoReferencia = field->fieldType.tipoReferencia;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), value, TIPO1);
	}
	return 0;
}

int putfield(Interpretador *interpretador) { //recebe um index e um fieldType e seta o field correspondente em um objeto para o fieldType de value operand: 0xB5
	u2 index;
	u2 nameAndTypeIndexAux;
	u2 nameIndexaux, descriptorIndexAux;
	object *object;
	Field* field;
	char *fieldName, *descritorField;
	OperandType objectref, value;
	index = readU2Code(interpretador->topFrame);
	value = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	objectref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	object = (object*) objectref.tipoReferencia;
	nameAndTypeIndexAux =
			interpretador->topFrame->constantPool[index].info.fieldRefInfo.nameAndTypeIndex;
	nameIndexaux =
			interpretador->topFrame->constantPool[nameAndTypeIndexAux].info.nameAndTypeInfo.nameIndex;
	fieldName = interpretador->topFrame->constantPool[nameIndexaux].info.UTF8Info.bytes;
	descriptorIndexAux =
			interpretador->topFrame->constantPool[nameAndTypeIndexAux].info.nameAndTypeInfo.descriptorIndex;
	descritorField =
			interpretador->topFrame->constantPool[descriptorIndexAux].info.UTF8Info.bytes;
	field = getFieldName(fieldName, descritorField, object);
	if (field != NULL ) {
		field->fieldType.longType = value.longType;
	} else {
		printf("field = NULL , problema na getFieldName");
		exit(1);
	}
	return 0;
}

// invokes -------------------------------------------------------------------------------------------

// ATENÇÃO: O invokevirtual serve apenas para simular o print/println, não faz o que devia
int invokevirtual(Interpretador *interpretador) { // operand: 0xB6

	int numArgs;
	char* className;
	char* methodName;
	char* descriptor;
	u2 indiceMethodRefInfo;
	u2 classInfoIndex;
	u2 indiceNameAndTypeInfo;
	u2 indiceNomeMetodo;
	u2 indiceTipoMetodo;
	OperandType operand;

	indiceMethodRefInfo = readU2Code(interpretador->topFrame);

	classInfoIndex =
			interpretador->topFrame->constantPool[indiceMethodRefInfo].info.methodRefInfo.classIndex;
	className =
			getUtf8(interpretador->topFrame->constantPool,
					interpretador->topFrame->constantPool[classInfoIndex].info.classInfo.nameIndex);

	indiceNameAndTypeInfo =
			interpretador->topFrame->constantPool[indiceMethodRefInfo].info.methodRefInfo.nameAndTypeIndex;
	indiceNomeMetodo =
			interpretador->topFrame->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.nameIndex;
	methodName = getUtf8(interpretador->topFrame->constantPool,
			indiceNomeMetodo);

	indiceTipoMetodo =
			interpretador->topFrame->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.descriptorIndex;
	descriptor = getUtf8(interpretador->topFrame->constantPool,
			indiceTipoMetodo);

	if (strcmp(className, "java/io/PrintStream") == 0
			&& (strcmp(methodName, "println") == 0
					|| strcmp(methodName, "print") == 0)) {
		if (descriptor[1] == 'I') {
			operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
			printf("%d", operand.tipoInt);
		} else if (descriptor[1] == 'J') {
			operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
			printf("%lld", operand.longType);
		} else if (descriptor[1] == 'F') {
			operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
			printf("%g", operand.tipoFloat);
		} else if (descriptor[1] == 'D') {
			operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
			printf("%g", operand.tipoDouble);
		} else if (descriptor[1] == 'S') {
			operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
			printf("%hi", (short) operand.tipoInt);
		} else if (descriptor[1] == 'C') {
			operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
			printf("%c", (char) operand.tipoInt);
		} else if (descriptor[1] == 'L') {
			operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
			if (strstr(descriptor, "java/lang/String") != NULL ) {
				printf("%s", (char*) operand.tipoReferencia);
			} else {
				printf("%interpretador", operand.tipoReferencia);
			}
		} else if (descriptor[1] == 'Z') {
			operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
			printf("%s", !operand.tipoInt ? "false" : "true");
		} else if (descriptor[1] == 'B') {
			operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
			printf("%d", operand.tipoInt);
		} else if (descriptor[1] == '[') {
			operand = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
			printf("%interpretador", operand.tipoReferencia);
		}

		if (strcmp(methodName, "println") == 0) {
			printf("\n");
		}

		// Tirando a referência desnecessária para essa simulação
		popOperand(&(interpretador->topFrame->topoPilhaOperandos));

	} else {
		numArgs = methodArgumentCount(descriptor);

		//numArgs + 1 é para incluir a referência ao objeto
		prepareMethod(className, methodName, descriptor, interpretador,
				numArgs + 1);
		runMethod(interpretador);
	}

	return 0;
}

// Instrução que dada uma pilha com os argumentos, invoca um método
// Opcode: 0xB7
int invokespecial(Interpretador *interpretador) { // Opcode: 0xB7

	int numArgs;
	char* className;
	char* methodName;
	char* descriptor;
	u2 indiceMethodRefInfo;
	u2 classInfoIndex;
	u2 indiceNameAndTypeInfo;
	u2 indiceNomeMetodo;
	u2 indiceTipoMetodo;

	indiceMethodRefInfo = readU2Code(interpretador->topFrame);

	classInfoIndex =
			interpretador->topFrame->constantPool[indiceMethodRefInfo].info.methodRefInfo.classIndex;
	className =
			getUtf8(interpretador->topFrame->constantPool,
					interpretador->topFrame->constantPool[classInfoIndex].info.classInfo.nameIndex);

	indiceNameAndTypeInfo =
			interpretador->topFrame->constantPool[indiceMethodRefInfo].info.methodRefInfo.nameAndTypeIndex;
	indiceNomeMetodo =
			interpretador->topFrame->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.nameIndex;
	methodName = getUtf8(interpretador->topFrame->constantPool,
			indiceNomeMetodo);

	indiceTipoMetodo =
			interpretador->topFrame->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.descriptorIndex;
	descriptor = getUtf8(interpretador->topFrame->constantPool,
			indiceTipoMetodo);

	numArgs = methodArgumentCount(descriptor);

	//numArgs + 1 é para incluir a referência ao objeto
	prepareMethod(className, methodName, descriptor, interpretador, numArgs + 1);
	runMethod(interpretador);

	return 0;
}

int invokestatic(Interpretador *interpretador) { //  operand: 0xB8

	ClassFile *classFile;
	int numArgs;
	char* className;
	char* methodName;
	char* descriptor;
	u2 indiceMethodRefInfo;
	u2 classInfoIndex;
	u2 indiceNameAndTypeInfo;
	u2 indiceNomeMetodo;
	u2 indiceTipoMetodo;

	indiceMethodRefInfo = readU2Code(interpretador->topFrame);

	classInfoIndex =
			interpretador->topFrame->constantPool[indiceMethodRefInfo].info.methodRefInfo.classIndex;
	className =
			getUtf8(interpretador->topFrame->constantPool,
					interpretador->topFrame->constantPool[classInfoIndex].info.classInfo.nameIndex);

	indiceNameAndTypeInfo =
			interpretador->topFrame->constantPool[indiceMethodRefInfo].info.methodRefInfo.nameAndTypeIndex;
	indiceNomeMetodo =
			interpretador->topFrame->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.nameIndex;
	methodName = getUtf8(interpretador->topFrame->constantPool,
			indiceNomeMetodo);

	indiceTipoMetodo =
			interpretador->topFrame->constantPool[indiceNameAndTypeInfo].info.nameAndTypeInfo.descriptorIndex;
	descriptor = getUtf8(interpretador->topFrame->constantPool,
			indiceTipoMetodo);

	numArgs = methodArgumentCount(descriptor);

	// O método registerNatives é um método da classe Object.class, é um método nativo
	// portanto, devemos ignorá-lo
	if (strcmp(className, "java/lang/Object") == 0
			&& strcmp(methodName, "registerNatives") == 0
			&& strcmp(descriptor, "()V") == 0) {
		return 0;
	} else {

		// Verificamos se estamos requisitando uma classe que já está carregada
		classFile = checkClass(interpretador, className);

		prepareMethod(className, methodName, descriptor, interpretador, numArgs);
		runMethod(interpretador);

		return 0;
	}
}

//Objetos ---------------------------------------------------------------------------------------------
int new_(Interpretador *interpretador) { // operand: 0xBB

	object* object;
	OperandType objRef;
	ClassFile* classFile;
	u2 indexClassInfo;
	u2 indiceNomeClasse;
	char* className;

	indexClassInfo = readU2Code(interpretador->topFrame); // lê index
	indiceNomeClasse =
			interpretador->topFrame->constantPool[indexClassInfo].info.classInfo.nameIndex;
	className = getUtf8(interpretador->topFrame->constantPool,
			indiceNomeClasse);

	classFile = checkClass(interpretador, className);

	object = malloc(sizeof(object));

	object->fieldsCount = fieldsCount(interpretador, *classFile);

	object->fields = malloc(sizeof(Field) * object->fieldsCount);
	fiieldsObjectInit(interpretador, *classFile, object->fields);

	objRef.tipoReferencia = object;

	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), objRef, TIPO1);

	return 0;
}

//Array -------------------------------------------------------------------------------------------------
int newarray(Interpretador *interpretador) { // recebe da pilha um size e do código um tipo e aloca um array operand: 0xBC
	OperandType count, arrayref;
	Array *vet;
	vet = malloc(sizeof(Array));
	vet->type = readU1Code(interpretador->topFrame);
	count = popOperand(&(interpretador->topFrame->topoPilhaOperandos)); // tamanho do vetor
	vet->size = count.tipoInt;
	switch (vet->type) {
	case T_BOOLEAN:
		vet->array = calloc(vet->size, sizeof(OperandType)); // deixado como int
		break;
	case T_CHAR:
		vet->array = calloc(vet->size, sizeof(OperandType));
		break;
	case T_FLOAT:
		vet->array = calloc(vet->size, sizeof(OperandType));
		break;
	case T_DOUBLE:
		vet->array = calloc(vet->size, sizeof(OperandType));
		break;
	case T_BYTE:
		vet->array = calloc(vet->size, sizeof(OperandType)); // deixado como int
		break;
	case T_SHORT:
		vet->array = calloc(vet->size, sizeof(OperandType)); // deixado como int
		break;
	case T_INT:
		vet->array = calloc(vet->size, sizeof(OperandType)); // deixado como int
		break;
	case T_LONG:
		vet->array = calloc(vet->size, sizeof(OperandType));
		break;
	default:
		printf("Erro no newarray - tipo incompativel");
		exit(1);
	}
	arrayref.tipoReferencia = vet;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), arrayref, TIPO1);
	return 0;
}

int anewarray(Interpretador *interpretador) { // cria um array de  referencias 0xBD
	u2 index;
	OperandType count, arrayref;
	Array *vet;
	vet = calloc(1, sizeof(Array));
	index = readU2Code(interpretador->topFrame);
	count = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	if (count.tipoInt < 0) {
		printf(
				"tamanho do vetor em anewarray menor que  zero , lançar exceção - NegativeArraySize");
		exit(1);
	}
	vet->size = count.tipoInt;
	vet->type = T_INT;
	vet->array = calloc(vet->size, sizeof(OperandType));
	arrayref.tipoReferencia = vet;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), arrayref, TIPO1);
	return 0;
}

int arraylength(Interpretador *interpretador) { //retona pela pilha o tamanho de um array operand: 0xBE
	OperandType arrayref, length;
	Array *vet;
	arrayref = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	vet = arrayref.tipoReferencia;
	length.tipoInt = vet->size;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), length, TIPO1);
	return 0;
}

// Array -------------------------------------------------------------------------------------
int multianewarray(Interpretador *interpretador) {
	u1 dimensions;
	u2 index;
	Array *vet;
	int i;
	index = readU2Code(interpretador->topFrame);
	dimensions = readU1Code(interpretador->topFrame);
	OperandType count[dimensions], arrayref;
	int count1[dimensions];
	if (dimensions <= 0) {
		printf("dimensões zero ou negativas em multianewarray");
		exit(1);
	} else {
		for (i = 0; i < dimensions; ++i) {
			count[i] = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
			count1[i] = count[i].tipoInt; // gambiarra
		}
		vet = allocateMultiArray(dimensions, count1);
		arrayref.tipoReferencia = vet;
		pushOperand(&(interpretador->topFrame->topoPilhaOperandos), arrayref, TIPO1);
	}
	return 0;
}
//ifnulls ------------------------------------------------------------------------------------------------
int ifnull(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0xC6
	u2 offset;
	offset = readU2Code(interpretador->topFrame);
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoReferencia == NULL ) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

int ifnonnull(Interpretador *interpretador) { // Compara o topo da pilha(int) com 0 , e dá branch operand: 0xC7
	u2 offset;
	offset = readU2Code(interpretador->topFrame);
	OperandType op1;
	op1 = popOperand(&(interpretador->topFrame->topoPilhaOperandos));
	offset -= 3; // para corrigir o PC
	if (op1.tipoReferencia != NULL ) {
		interpretador->topFrame->pc += offset;
	}
	return 0;
}

//goto_w ------------------------------------------------------------------------------------------------
int goto_w(Interpretador *interpretador) { // goto com index de 32 bits operand: 0xC8
	u2 off1, off2;
	int offset;
	off1 = readU2Code(interpretador->topFrame);
	off2 = readU2Code(interpretador->topFrame);
	offset = off1;
	offset = (offset << 16) | (off2);
	offset -= 5; // Para  corrigir o PC
	interpretador->topFrame->pc += offset;
	return 0;
}

int jsr_w(Interpretador *interpretador) { // similar ao goto mas joga o pc na pilha operand: 0xC9
	u2 off1, off2;
	OperandType op1;
	unsigned int offset;
	off1 = readU2Code(interpretador->topFrame);
	off2 = readU2Code(interpretador->topFrame);
	offset = off1;
	offset = (offset << 16) | (off2);
	offset -= 5; // Para  corrigir o PC
	op1.tipoReferencia = interpretador->topFrame->pc;
	pushOperand(&(interpretador->topFrame->topoPilhaOperandos), op1, TIPO1);
	interpretador->topFrame->pc += offset;
	return 0;
}

int (*vetInstr[])(Interpretador *interpretador) = {
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
