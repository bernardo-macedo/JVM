#include "Execucao.h"
#include "ClassLoader.h"
#include "ClassFile.h"
#include "Controller.h"
#include "AuxiliarFunctions.h"


void classListInit(ClassList** listAddress) {
	*listAddress = NULL;
}

void classListInsert(ClassList** listAddress, ClassFile classFile) {
	ClassList* p1;
	ClassList* p2;
	u2 fieldNameIndex;
	u2 fieldDescriptorIndex;
	int i;
	int j;

	p1 = malloc(sizeof(ClassList));
	p1->classFile = classFile;
	p1->staticFieldsCount = 0;

	/* Conta os fields estáticos */
	for (i = 0; i < classFile.fields_count; i++) {
		if ((classFile.fields[i].accessFlags & ACC_STATIC) != 0) {
			p1->staticFieldsCount++;
		}
	}

	/* Aloca espaço para os fields */
	p1->staticFields = malloc(sizeof(Field) * p1->staticFieldsCount);
	j = 0;

	/* Preenche os fields */
	for (i = 0; i < classFile.fields_count; i++) {
		fieldNameIndex = classFile.fields[i].nameIndex;
		fieldDescriptorIndex = classFile.fields[i].descriptorIndex;
		if ((classFile.fields[i].accessFlags & ACC_STATIC) != 0) {
			p1->staticFields[j].name = classFile.constant_pool[fieldNameIndex].info.UTF8Info.bytes;
			p1->staticFields[j].descriptor = classFile.constant_pool[fieldDescriptorIndex].info.UTF8Info.bytes;
			p1->staticFields[j].fieldType.longType = 0;
			j++;
		}
	}

	p1->objectsList = NULL;
	if (*listAddress == NULL ) {
		*listAddress = p1;
	} else {
		p2 = *listAddress;
		while (p2->nextClass != NULL ) {
			p2 = p2->nextClass;
		}
		p2->nextClass = p1;
	}
	p1->nextClass = NULL;
}

ClassFile* checkClass(Interpretador* interpretador, char* className) {
	ClassFile* classFile;

	/* Verifica se a classe já está na lista */
	classFile = getClassFileName(interpretador->topClass, className);
	/* Se não estiver */
	if (classFile == NULL ) {
		classFile = malloc(sizeof(ClassFile));
		*classFile = carregaClassFile(className);
		classListInsert(&(interpretador->topClass), *classFile);
        /* Inicializa os parâmetros estáticos, se existirem */
		if (getMethodByName(*classFile, "<clinit>", "()V") != NULL ) {
			prepareMethod(className, "<clinit>", "()V", interpretador, 0);
			runMethod(interpretador);
		}
	}
	return classFile;
}

void prepareMethod(char* className, char* methodName, char* descriptor, Interpretador *interpretador, int numArgs) {
	ClassFile* classFile;
	OperandStack* pilhaAux;
	int i;
	int indexNumber = 0;
	int type32_64;

	classFile = checkClass(interpretador, className);
	/* Aloca e empilha um novo frame */
	pushFrame(&(interpretador->topStackFrame));
    /* Inicializa o frame */
	frameInit(interpretador->topClass, *classFile, interpretador->topFrame, methodName, descriptor);
    /* Se entrar no if, não é a main*/
	if (interpretador->topFrame->nextFrame != NULL ) {
        /* Passa os operandos para uma pilha auxiliar e faz a contagem */
		stackInit(&pilhaAux);
		/* Verifica quantos índices serão usados no localVarArray */
		for (i = 0; i < numArgs; i++) {
			type32_64 = interpretador->topFrame->nextFrame->topoPilhaOperandos->type32_64;
			pushOperand(&pilhaAux, popOperand(&(interpretador->topFrame->nextFrame->topoPilhaOperandos)),type32_64);
			if (type32_64 == TIPO2) {
				indexNumber++;
			}
			indexNumber++;
		}
		/* Coloca os operandos de volta na pilha inicial */
		for (i = 0; i < numArgs; i++) {
			type32_64 = pilhaAux->type32_64;
			pushOperand(&(interpretador->topFrame->nextFrame->topoPilhaOperandos), popOperand(&pilhaAux), type32_64);
		}

		/* Passa os argumentos para o novo frame */
		for (i = (indexNumber - 1); i >= 0; i--) {
			if (interpretador->topFrame->nextFrame->topoPilhaOperandos->type32_64 == TIPO2) {
				i--; /* Pula um se for do Tipo 2 */
			}
			interpretador->topFrame->arrayLocal[i] = popOperand(&(interpretador->topFrame->nextFrame->topoPilhaOperandos));
		}
	}
}

void runMethod(Interpretador *interpretador) {
	int isRetInstr = 0;
	u1 instruction;
	while (!isRetInstr) {
		instruction = readU1Code(interpretador->topFrame);
		isRetInstr = vetInstr[instruction](interpretador);
	}
}
