#include "AuxiliarFunctions.h"

float convertU4ToFloat(u4 u4input)
{
	float convertedU4;
	int s;
	int e;
	int m;

	if(u4input == 0x7f800000)
	{
		/*infinito positivo*/
	}
	else if(u4input == 0xff800000)
	{
		/*infinito negativo*/
	}
	else if(((u4input >= 0x7f800001) && (u4input <= 0x7fffffff)) || ((u4input >= 0xff800001) && (u4input <= 0xffffffff)))
	{
		/*nan*/
	}
	else
	{
		s = ((u4input >> 31) == 0) ? 1 : -1;
		e = ((u4input >> 23) & 0xff);
		m = (e == 0) ? (u4input & 0x7fffff) << 1 : (u4input & 0x7fffff) | 0x800000;

		convertedU4 = s*m*(pow(2, (e - 150)));
	}

	return convertedU4;
}

u1* getUTF8(CpInfo *cp, u2 index) {
    return cp[index].info.Utf8Info.bytes;
}


int methodArgsCount(char* descriptor) {
    int argNumber = 0, i = 0;
    char* aux;

    strcpy(aux, descriptor);
    while (aux[i] != ')') {
        if (aux[i] != '(' && aux[i] != '[') {
            argNumber++;
            if (aux[i] == 'L') {
                while (aux[i] != ';') i++;
            }
        }
        i++;
    }
	return argNumber;
}

ClassFile* getClassFileByName(ClassList* init, char* className) {

	u2 classNameIndex;
	char* classNameAux;
	ClassList* cListAux = init;

	while (cListAux != NULL) {
        classNameIndex = cListAux->classFile->constantPool[cListAux->classFile->thisClass].info.ClassInfo.nameIndex;
        classNameAux = cListAux->classFile->constantPool[classNameIndex].info.Utf8Info.bytes;
        if (strcmp(classNameAux, className) == 0)
            return &(cListAux->classFile);
        cListAux = cListAux->nextClass;
	}
	return NULL;
}

MethodInfo* getMethod(ClassFile cFile, char* methodName, char* methodDescriptor) {
    int i;
    char *methodNameAux, *methodDescriptorAux;

	for (i = 0; i < cFile.methodsCount; i++) {
	    methodNameAux = cFile.constantPool[cFile.methods[i].nameIndex].info.Utf8Info.bytes;
        methodDescriptorAux = cFile.constantPool[cFile.methods[i].descriptorIndex].info.Utf8Info.bytes;
        if (strcmp(methodNameAux, methodName) == 0 && strcmp(methodDescriptorAux, methodDescriptor) == 0)
            return &(cFile.methods[i]);
	}
	return NULL ;
}

char* getClassName(char *classpath)
{
	char* classname;
	char* aux;
	char* aux2;

	aux = strtok(classpath, "/\\\"");
	while(aux != NULL)
	{
		aux2 = aux;
		aux = strtok(NULL, "/\\\"");
	}
	if(strstr(aux2, ".class") != NULL)
	{
		classname = malloc(sizeof(char)*strlen(aux2));
		strncpy(classname, aux2, strlen(aux2)-6);
		classname[strlen(aux2)-6] = '\0';

		return classname;
	}
	return aux2;
}

/* Nem precisa receber Interpretador */
ClassFile* isLoaded(Interpretador* interpretador, char* className) {
	ClassFile* classFile;
	/* Verifica se a classe buscada ja foi carregada */
	classFile = getClassFileByName(interpretador->initClass, className);
	/* Nao foi carregada ainda */
	if (classFile == NULL ) {
		classFile = malloc(sizeof(ClassFile));
		/* Carrega a classe na memoria (se nao estiver ainda) e insere na lista */
		classFile = loadClass(interpretador, className);
	}
	return classFile;
}

void insertStaticFieldValue(ClassList* init, char* className, char* fieldName, Operand operand) {
	u2 classInfoIndex;
    ClassList *p;
	int i;

	p = init;
	while (p != NULL) {
		classInfoIndex = p->classFile->thisClass;
		if (strcmp(className, getUTF8(p->classFile->constantPool, p->classFile->constantPool[classInfoIndex].info.ClassInfo.nameIndex)) == 0) {
			for (i = 0; i < p->staticFieldsCount; i++) {
				if (strcmp(fieldName, p->staticFields[i].name) == 0) {
					p->staticFields[i].fieldType.longType = operand.operandType.longType;
					return;
				}
			}
			return;
		}
		p = p->nextClass;
	}
}

void fieldsInit(Interpretador *p, ClassFile classFile, Field* fields) {

	int i;
	int j = 0; // Contador dos fields do objeto
	ClassFile* classFile_aux;
	u2 superClassNameIndex, fieldDescriptorIndex, fieldNameIndex;
	char* descriptor, fieldName;
	char nomeSuperClasse[100];

	classFile_aux = &classFile;

	/* Inicializa os fields nao estaticos */
	for (i = 0; i < classFile_aux->fieldsCount; i++) {
		fieldDescriptorIndex = classFile_aux->fields[i].descriptorIndex;
		descriptor = getUTF8(classFile_aux->constantPool, fieldDescriptorIndex);
		fieldNameIndex = classFile_aux->fields[i].nameIndex;
		fieldName = getUTF8(classFile_aux->constantPool, fieldNameIndex);

		if ((classFile_aux->fields[i].accessFlags & ACC_STATIC) == 0) {
			fields[j].descriptor = descriptor;
			fields[j].name = fieldName;
			fields[j].fieldType.longType = 0;
			j++;
		}
	}

    /* Inicializa os fields das super classes */
	while (classFile_aux->superClass != 0) {
		superClassNameIndex = classFile_aux->constantPool[classFile_aux->superClass].info.ClassInfo.nameIndex;
		strcpy(nomeSuperClasse, getUTF8(classFile_aux->constantPool, superClassNameIndex));
		classFile_aux = loadClass(p, nomeSuperClasse);

		if (classFile_aux != NULL ) {
			for (i = 0; i < classFile_aux->fieldsCount; i++) {
				fieldDescriptorIndex = classFile_aux->fields[i].descriptorIndex;
				descriptor = getUTF8(classFile_aux->constantPool, fieldDescriptorIndex);
				fieldNameIndex = classFile_aux->fields[i].nameIndex;
				fieldName = getUTF8(classFile_aux->constantPool, fieldNameIndex);

				if (((classFile_aux->fields[i].accessFlags & ACC_STATIC) == 0)) {
					fields[j].descriptor = descriptor;
					fields[j].name = fieldName;
					fields[j].fieldType.longType = 0;
					j++;
				}
			}
		} else {
			printf("Super classe nao encontrada\n");
			exit(1);
		}
	}
}

Array* createMultiArray(int dimensions, int* intCounts) {
	Array *aux, *aux2;
	int i;
	int *intCounts_aux;
	if (dimensions == 1) {
		aux = malloc(sizeof(Array));
		aux->arraySize = intCounts[0];
		aux->type = T_INT;
		aux->array = calloc(intCounts[0], sizeof(Operand));
	} else {
		aux = malloc(sizeof(Array));
		aux->arraySize = intCounts[0];
		aux->type = T_INT;
		aux->array = calloc(intCounts[0], sizeof(Operand));
		//---------------------------------------------------
		intCounts_aux = calloc(dimensions - 1, sizeof(int));
		for (i = 1; i < dimensions; ++i) {
			intCounts_aux[i - 1] = intCounts[i];
		}
		//---------------------------------------------------
		for (i = 0; i < intCounts[0]; ++i) {
			aux2 = createMultiArray(dimensions - 1, intCounts_aux);
			aux->array[i].operandType.referenceType = aux2;
		}
	}
	return aux;
}

// Função que retorna o field estático dados o nome da classe e o nome do field
Field* getStaticFieldName(ClassList* init, char* className, char* fieldName) {
	u2 classInfoIndex;
	ClassList *p;
	int i;

	p = init;
	while (p != NULL ) {
		classInfoIndex = p->classFile->thisClass;

		if (strcmp(className, getUTF8(p->classFile->constantPool, p->classFile->constantPool[classInfoIndex].info.ClassInfo.nameIndex)) == 0) {
			for (i = 0; i < p->staticFieldsCount; i++) {
				if (strcmp(fieldName, p->staticFields[i].name) == 0) {
					return (&p->staticFields[i]);
				}
			}

			// Não há como ter duas classes com o mesmo nome, então
			// se o nome bateu, mas em nenhum dos fields foi encontrado
			// o esperado, então welp, retorne NULL.
			return NULL ;
		}

		p = p->nextClass;
	}

	return NULL ;
}
