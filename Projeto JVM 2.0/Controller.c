#include <stdlib.h>
#include <stdio.h>
#include "Controller.h"
#include "ClassFile.h"
#include "AuxiliarFunctions.h"
#include <string.h>


int emptyStack(OperandStack *top) {
	return top == NULL ;
}

void pushOperand(OperandStack **topAddress, OperandType operand, int type32_64) {
	OperandStack *p1;

	p1 = malloc(sizeof(OperandStack));
	p1->operand = operand;
	p1->type32_64 = type32_64;
	p1->nextOperand = *topAddress;
	*topAddress = p1;
	return;
}

void stackInit(OperandStack **stackAddress) {
	*stackAddress = NULL;
	return;
}

OperandType popOperand(OperandStack **topAddress) {
	OperandStack *p1;
	OperandType operand_result;

	if (!emptyStack(*topAddress)) {
		operand_result = (*topAddress)->operand;
		p1 = *topAddress;
		*topAddress = (*topAddress)->nextOperand;
		free(p1);
	} else {
		printf("Error - Controller.c: popOperand: Pilha vazia\n");
		exit(1);
	}
	return operand_result;
}

int emptyStackFrame(StackFrame *topFrame) {
	return topFrame == NULL ;
}

void stackFrameInit(StackFrame **topFrameAddress) {
	*topFrameAddress = NULL;
}

void pushFrame(StackFrame **topFrameAddress) {
	StackFrame *p1;

	p1 = malloc(sizeof(StackFrame));
	p1->nextFrame = *topFrameAddress;
	*topFrameAddress = p1;
}

void popFrame(StackFrame **topFrameAddress) {
	StackFrame *p1;

	if (!emptyStackFrame(*topFrameAddress)) {
		p1 = *topFrameAddress;
		*topFrameAddress = (*topFrameAddress)->nextFrame;
		free(p1);
	} else {
		printf("Erro - Controller.c: popFrame: Pilha vazia\n");
		exit(1);
	}
}

void frameInit(ClassList *init, ClassFile classFile, StackFrame *stackFrame, char* methodName, char* descriptor) {
	ClassFile* classFile_aux;
	MethodInfo* method;
	attributeInfo methodCode;
	u2 superClassIndex;
	char superClassName[100];
	int i;

	method = NULL;
	classFile_aux = &classFile;
	superClassIndex = classFile_aux->super_class;

	/* Procura o método pelo nome e se não encontrar, procura na super classe */
	while (classFile_aux != NULL && (method = getMethodByName(*classFile_aux, methodName, descriptor)) == NULL && superClassIndex != 0) {
		strcpy(superClassName, getUtf8(classFile_aux->constant_pool, classFile_aux->constant_pool[superClassIndex].info.classInfo.nameIndex));
		classFile_aux = getClassFileName(init, superClassName);
		if (classFile_aux != NULL ) {
			superClassIndex = classFile_aux->super_class;
		}
	}

	/* Se o método não for encontrado */
	if (method == NULL ) {
		printf("Erro: Controller.c: frameInit: Metodo nao encontrado - %s %s\n", methodName, descriptor);
		exit(1);
	}

	/* Procura o atributo Code */
	for (i = 0; i < method->attributesCount; i++) {
		if (strcmp(getUtf8(classFile_aux->constant_pool, method->attributes[i].attributeNameIndex), "Code") == 0) {
			methodCode = method->attributes[i];
			break;
		}
	}

    /* Atribui o constantPool*/
	stackFrame->frame->constantPool = classFile_aux->constant_pool;
	/* Inicializa a pilha de operandos */
	stackInit(&(stackFrame->frame->topOperand));
	/* Copia a referência do código do método a ser executado */
	stackFrame->frame->currOpcode = methodCode.tipoInfo.code.code;
	/* Inicializa o array de variáveis locais */
	stackFrame->frame->arrayLocal = malloc(methodCode.tipoInfo.code.maxLocals * sizeof(OperandType));
	/* Inicializa pc */
	stackFrame->frame->pc = stackFrame->frame->currOpcode;
}
