/*
 * Frame.h
 *
 *  Created on: 22/01/2013
 *      Author: Vitor
 */

#ifndef FRAMECONTROLLER_H_
#define FRAMECONTROLLER_H_

#define CAT1 1
#define CAT2 0

#include "DebugFuncs.h"
#include "ClassFile.h"

/*
 * A pilha s� mantem operandos de 32 ou 64 bits, os outros sao promovidos a estes tamanhos.
 *
 */
typedef union _operandType {

	int int_type;
	long long long_type;
	float float_type;
	double double_type;
	void* objref_type;

} operandType;

typedef struct _Vetor {
	int size, type;
	operandType* array;
} Vetor;
/*
 * A pilha mant�m o top dela como refer�ncia (pilha Homero).
 *
 */
typedef struct _operandStack {

	operandType operando;
	int type32_64;
	struct _operandStack *nextOperand;

} operandStack;

/*
 * Estrutura de uma frame. Criada quando um m�todo � invocado
 */
typedef struct _frame {
	cpInfo *constantPool;
	operandType *arrayLocal;	// ATEN��O: Doubles e longs ocupam 2 �ndices!!
	operandStack *topoperandStack;
	u1* codigoAExecutar;
	struct _frame *frameAbaixo;
	u1 *pc;
} frame;

typedef union _tipoField {
	int int_type;
	short tipoShort;
	float float_type;
	long long long_type;
	double double_type;
	char tipoChar;
	void* objref_type;
} tipoField;

typedef struct _field {
	char* nome;
	char* descritor;
	tipoField valor;
} field;

typedef struct _Object {
	int fieldsCount;
	field* fields;
} object;

typedef struct _listaObject {
	object obj;
	struct _listaObject *proxObj;
} listaObject;

typedef struct _listaClasses {
	ClassFile cf;
	int numStaticFields;
	field* staticFields;
	listaObject* listaObjetos;
	struct _listaClasses *proxClasse;
} listaClasses;

typedef struct EXECUCAO {
	frame* frameAtual;
	listaClasses* pInicioLista;
} execucao;

int pilhaVazia(operandStack *topPilha);

void pushOperando(operandStack **endtopPilha, operandType operandoPassado,
		int operandoTipo);

void inicializaPilha(operandStack **endPilha);

operandType popOperando(operandStack **endtopPilha);

void pilhaVaziaFrame(frame *frameAtual);

void inicializaPilhaFrames(frame **endFrameAtual);

void pushFrame(frame **endFrameAtual);

void popFrame(frame **endFrameAtual);

void inicializaFrame(listaClasses *inicioLista, ClassFile cf, frame *frame,
		char* nomeMetodo, char* descriptor);

#endif /* PILHAOPERANDOS_H_ */
