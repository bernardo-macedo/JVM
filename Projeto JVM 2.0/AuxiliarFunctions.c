#include "AuxiliarFunctions.h"
#include "ClassFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


MethodInfo* getMethodByName(ClassFile classFile, char* methodName, char* descriptor) {
	int i;

	for (i = 0; i < classFile.methods_count; i++) {
		if (strcmp((char*) getUtf8(classFile.constant_pool, classFile.methods[i].nameIndex), methodName) == 0
				&& strcmp((char*) getUtf8(classFile.constant_pool,classFile.methods[i].descriptorIndex), descriptor) == 0) {
			return &(classFile.methods[i]);
		}
	}
	return NULL ;
}

void getClassNameFiltered(char* classNameFiltered, char* className) {
	int i;
	int j = 0;

	i = strlen(className) - 1;

	/* Ignora o ".class" */
	if (strstr(className, ".class") != NULL ) {
		while (className[i] != '.') {
			i--;
		}
		i--;
	}

	/* Procura o primeiro divisor ou o início da string */
	while (className[i] != '\\' && className[i] != '/' && &(className[i]) != className) {
		i--;
	}
	if (className[i] == '\\' || className[i] == '/') {
		i++;
	}

	/* Coloca o nome da classe em classNameFiltered */
	while (className[i] != '.' && className[i] != '\0') {
		classNameFiltered[j] = className[i];
		i++;
		j++;
	}
	classNameFiltered[j] = '\0';
}

ClassFile* getClassFileName(ClassList* init, char* className) {
	ClassList* p1;
	u2 classInfoIndex;

	p1 = init;
	while (p1 != NULL ) {
		classInfoIndex = p1->classFile.this_class;
		if (strcmp(getUtf8(p1->classFile.constant_pool,
						p1->classFile.constant_pool[classInfoIndex].info.classInfo.nameIndex), className) == 0) {
			return &(p1->classFile);
		}
		p1 = p1->nextClass;
	}
	return NULL ;
}

u1 readU1Code(StackFrame *topFrame) {
	u1 returnVar;
	returnVar = *(topFrame->frame->pc);
	topFrame->frame->pc++;
	return returnVar;
}

u2 readU2Code(StackFrame *topFrame) {
	u2 returnVar;
	returnVar = *(topFrame->frame->pc);
	topFrame->frame->pc++;
	returnVar = (returnVar << 8) | *(topFrame->frame->pc);
	topFrame->frame->pc++;
	return returnVar;
}

u4 readU4Code(StackFrame *topFrame) {
	u4 returnVar;
	returnVar = *(topFrame->frame->pc);
	topFrame->frame->pc++;
	returnVar = (returnVar << 8) | *(topFrame->frame->pc);
	topFrame->frame->pc++;
	returnVar = (returnVar << 8) | *(topFrame->frame->pc);
	topFrame->frame->pc++;
	returnVar = (returnVar << 8) | *(topFrame->frame->pc);
	topFrame->frame->pc++;
	return returnVar;
}

int methodArgumentCount(u1* descriptor) {
	u1* searcher;
	int i = 0;
	int numArgs = 0;

	searcher = descriptor;
	/* Percorre o descritor até encontrar ')' */
	while (searcher[i] != ')') {
		if (searcher[i] != '(' && searcher[i] != '[') {
			numArgs++;
			if (searcher[i] == 'L') {
				while (searcher[i] != ';') {
					i++;
				}
			}
		}
		i++;
	}
	return numArgs;
}

Field* getStaticFieldName(ClassList* init, char* className, char* fieldName) {
	u2 classInfoIndex;
	ClassList *p1;
	int i;

	p1 = init;
	while (p1 != NULL ) {
		classInfoIndex = p1->classFile.this_class;
		if (strcmp(className, getUtf8(p1->classFile.constant_pool,
                                p1->classFile.constant_pool[classInfoIndex].info.classInfo.nameIndex)) == 0) {
			for (i = 0; i < p1->staticFieldsCount; i++) {
				if (strcmp(fieldName, p1->staticFields[i].name) == 0) {
					return (&p1->staticFields[i]);
				}
			}
			return NULL ;
		}
		p1 = p1->nextClass;
	}
	return NULL ;
}

void insertStaticFieldValue(ClassList* init, char* className, char* fieldName, OperandType operand) {
	u2 classInfoIndex;
	ClassList *p1;
	int i;

	p1 = init;
	while (p1 != NULL ) {
		classInfoIndex = p1->classFile.this_class;
		if (strcmp(className, getUtf8(p1->classFile.constant_pool,
                                p1->classFile.constant_pool[classInfoIndex].info.classInfo.nameIndex)) == 0) {
			for (i = 0; i < p1->staticFieldsCount; i++) {
				if (strcmp(fieldName, p1->staticFields[i].name) == 0) {
					p1->staticFields[i].fieldType.longType = operand.longType;
					return;
				}
			}
			return;
		}
		p1 = p1->nextClass;
	}
}


u1* getUtf8(CpInfo *cpInfo, u2 index) {
	return cpInfo[index].info.UTF8Info.bytes;
}

Array* allocateMultiArray(int dimensions, int* sizesArray) {
	Array *aux, *aux2;
	int i;
	int *auxTamanhos;
	if (dimensions == 1) {
		aux = malloc(sizeof(Array));
		aux->size = sizesArray[0];
		aux->type = T_INT;
		aux->array = calloc(sizesArray[0], sizeof(OperandType));
	} else {
		aux = malloc(sizeof(Array));
		aux->size = sizesArray[0];
		aux->type = T_INT;
		aux->array = calloc(sizesArray[0], sizeof(OperandType));

		auxTamanhos = calloc(dimensions - 1, sizeof(int));
		for (i = 1; i < dimensions; ++i) {
			auxTamanhos[i - 1] = sizesArray[i];
		}

		for (i = 0; i < sizesArray[0]; ++i) {
			aux2 = allocateMultiArray(dimensions - 1, auxTamanhos);
			aux->array[i].tipoReferencia = aux2;
		}
	}
	return aux;
}

int fieldsCount(Interpretador *interpretador, ClassFile classFile) {
	int i;
	ClassFile* classFile_aux;
	u2 superClassNameIndex;
	char superClassName[100];
	int numFields = 0;

	classFile_aux = &classFile;
	for (i = 0; i < classFile_aux->fields_count; i++) {
		/* Os campos estáticos não podem ser adicionados aos campos do objeto */
		if ((classFile_aux->fields[i].accessFlags & ACC_STATIC) == 0) {
			numFields++;
		}
	}

	/* Percorre as super classes contando os fields */
	while (classFile_aux->super_class != 0) {
		superClassNameIndex = classFile_aux->constant_pool[classFile_aux->super_class].info.classInfo.nameIndex;
		strcpy(superClassName, etUtf8(classFile_aux->constant_pool, superClassNameIndex));
		classFile_aux = checkClass(interpretador, superClassName);
		for (i = 0; i < classFile_aux->fields_count; i++) {
			/* Só conta quando o field não é estático */
			if (((classFile_aux->fields[i].accessFlags & ACC_STATIC) == 0)) {
				numFields++;
			}
		}
	}
	return numFields;
}


void fieldsObjectInit(Interpretador *interpretador, ClassFile classFile, Field* fields) {

	int i;
	int j = 0;
	ClassFile* classFile_aux;
	u2 superClassNameIndex;
	u2 fieldDescriptorIndex;
	u2 fieldNameIndex;
	char* descriptor;
	char* fieldName;
	char superClassName[100];

	classFile_aux = &classFile;
	/* Inicializa os fields estáticos*/
	for (i = 0; i < classFile_aux->fields_count; i++) {
		fieldDescriptorIndex = classFile_aux->fields[i].descriptorIndex;
		descriptor = getUtf8(classFile_aux->constant_pool, fieldDescriptorIndex);
		fieldNameIndex = classFile_aux->fields[i].nameIndex;
		fieldName = getUtf8(classFile_aux->constant_pool, fieldNameIndex);
		if ((classFile_aux->fields[i].accessFlags & ACC_STATIC) == 0) {
			fields[j].descriptor = descriptor;
			fields[j].name = fieldName;
			fields[j].fieldType.longType = 0;
			j++;
		}
	}

	/* Inicializa os fields não-estáticos das super classes */
	while (classFile_aux->super_class != 0) {
		superClassNameIndex = classFile_aux->constant_pool[classFile_aux->super_class].info.classInfo.nameIndex;
		strcpy(superClassName, getUtf8(classFile_aux->constant_pool, superClassNameIndex));
		classFile_aux = checkClass(interpretador, superClassName);
		if (classFile_aux != NULL ) {
			for (i = 0; i < classFile_aux->fields_count; i++) {
				fieldDescriptorIndex = classFile_aux->fields[i].descriptorIndex;
				descriptor = getUtf8(classFile_aux->constant_pool, fieldDescriptorIndex);
				fieldNameIndex = classFile_aux->fields[i].nameIndex;
				fieldName = getUtf8(classFile_aux->constant_pool, fieldNameIndex);
				if (((classFile_aux->fields[i].accessFlags & ACC_STATIC) == 0)) {
					fields[j].descriptor = descriptor;
					fields[j].name = fieldName;
					fields[j].fieldType.longType = 0;
					j++;
				}
			}
		} else {
			printf("Erro - AuxiliarFunctions.c: fieldsObjectInit: Super classe nao encontrada\n");
			exit(1);
		}
	}
}

Field* getFieldName(char* name, char* descriptor, object* object) {
	Field* field;
	int i;
	for (i = 0; i < object->fieldsCount; ++i) {
		if ((strcmp(name, (object->fields[i].name)) == 0) && (strcmp(descriptor, (object->fields->descriptor)) == 0)) {
			field = &(object->fields[i]);
			return field;
		}
	}
	field = NULL;
	return field;
}
