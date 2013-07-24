/*
 * Frame.c
 *
 *  Created on: 22/01/2013
 *      Author: Vitor
 */

#include <stdlib.h>
#include <stdio.h>
#include "Frame.h"
#include "ClassFile.h"
#include "FuncoesGerais.h"
#include <string.h>

/*
 * Checa se a pilha está vazia. Retorna 1, se sim, 0 se não.
 */
int emptyStack(OperandStack *topoPilha) {
	return topoPilha == NULL ;
}

/*
 * Dados um ponteiro de pilha e um operando, atualiza o topo dessa pilha com o operando passado
 */
void pushOperand(OperandStack **endTopoPilha, tipoOperando operandoPassado,
		int operandoTipo) {

	OperandStack *p1;

	p1 = malloc(sizeof(OperandStack));
	p1->operando = operandoPassado;
	p1->operandoTipo1 = operandoTipo;
	p1->elementoAbaixo = *endTopoPilha;
	*endTopoPilha = p1;

	return;

}

/*
 * Sempre que uma pilha for iniciada, chame essa função.
 */
void stackInit(OperandStack **endPilha) {
	*endPilha = NULL;

	return;
}

/*
 * Retorna o operando do topo da pilha e libera a memória antes utilizada por ele.
 */
tipoOperando popOperand(OperandStack **endTopoPilha) {

	OperandStack *p1;
	tipoOperando operandoARetornar;

	if (!emptyStack(*endTopoPilha)) {
		operandoARetornar = (*endTopoPilha)->operando;
		p1 = *endTopoPilha;
		*endTopoPilha = (*endTopoPilha)->elementoAbaixo;
		free(p1);
	} else {
		printf("ERRO em popOperand: pilha vazia\n");
		exit(1);
	}

	return operandoARetornar;

}

/*
 * Função que checa se a pilha de frames está vazia
 */
int pilhaFramesVazia(frame *frameAtual) {
	return frameAtual == NULL ;
}

/*
 * Função que inicializa a pilha de frames, semelhante à pilha de operandos
 */
void stackFrameInit(frame **endFrameAtual) {
	*endFrameAtual = NULL;
}

/*
 * Função que coloca uma frame nova na pilha.
 *
 * !! ATENÇÃO !! - Inicializar a frame após dar o push.
 */
void pushFrame(frame **endFrameAtual) {

	frame *p1;

	p1 = malloc(sizeof(frame));

	p1->frameAbaixo = *endFrameAtual;
	*endFrameAtual = p1;

}

/*
 * Função que retira uma frame da pilha de frames
 */
void popFrame(frame **endFrameAtual) {

	frame *p1;

	if (!pilhaFramesVazia(*endFrameAtual)) {
		p1 = *endFrameAtual;
		*endFrameAtual = (*endFrameAtual)->frameAbaixo;
		free(p1);
	} else {
		printf("ERRO em popFrame : pilha vazia\n");
		exit(1);
	}

}

/*
 * Função que inicializa uma frame, com o código correto a ser executado
 *
 * Caso o método que quer ser executado não possa ser achado na classe atual, procuramos nas super classes.
 */
void frameInit(listaClasses *inicioLista, ClassFile cf, frame *frame,
		char* nomeMetodo, char* descriptor) {

	ClassFile* cfAux;
	methodInfo* metodo;
	attributeInfo codigoMetodo;
	u2 indiceSuperClasse;
	char nomeSuperClasse[100];
	int i;

	metodo = NULL;
	cfAux = &cf;
	indiceSuperClasse = cfAux->super_class;

	// Achar o método pelo nome
	// Se não acharmos, passamos para a super classe para ver se está lá
	while (cfAux != NULL
			&& (metodo = buscaMetodoNome(*cfAux, nomeMetodo, descriptor))
					== NULL && indiceSuperClasse != 0) {

		strcpy(nomeSuperClasse,
				buscaUTF8ConstPool(cfAux->constant_pool,
						cfAux->constant_pool[indiceSuperClasse].info.classInfo.nameIndex));

		cfAux = buscaClassFileNome(inicioLista, nomeSuperClasse);
		if (cfAux != NULL ) {
			indiceSuperClasse = cfAux->super_class;
		}
	}

	// Não conseguimos achar o método :(
	if (metodo == NULL ) {
		printf("ERRO: NoSuchMethodError - %s %s\n", nomeMetodo, descriptor);
		exit(1);
	}

	//achar o atributo Code , percorre a lista de atributos buscando o atributo Code
	for (i = 0; i < metodo->attributesCount; i++) {
		if (strcmp(
				buscaUTF8ConstPool(cfAux->constant_pool,
						metodo->attributes[i].attributeNameIndex), "Code")
				== 0) {
			codigoMetodo = metodo->attributes[i];
			break;
		}
	}

	frame->constantPool = cfAux->constant_pool;
	//inicializando a pilha de operandos
	stackInit(&(frame->topoPilhaOperandos));
	//Copiando a referência do código do método a ser executado.
	frame->codigoAExecutar = codigoMetodo.tipoInfo.code.code;
	//inicializando o array de variáveis locais
	frame->arrayLocal = malloc(
			codigoMetodo.tipoInfo.code.maxLocals * sizeof(tipoOperando));
	frame->pc = frame->codigoAExecutar;

}
