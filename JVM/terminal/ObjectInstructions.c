#include "ObjectInstructions.h"
#include "AuxiliarFunctions.h"

/*0x2E*/
int iaload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand2.operandType.referenceType; /* p aponta para o array referenciado */
    operand_result = p->array[operand1.operandType.intType]; /* operand_result recebe o operando que está na posição index do array */
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result); /* coloca operand_result na pilha de operandos */
    return 0;
}

/*0x2F*/
int laload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand2.operandType.referenceType; /* p aponta para o array referenciado */
    operand_result = p->array[operand1.operandType.intType]; /* operand_result recebe o operando que está na posição index do array */
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result); /* coloca operand_result na pilha de operandos */
    return 0;
}

/*0x30*/
int faload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand2.operandType.referenceType; /* p aponta para o array referenciado */
    operand_result = p->array[operand1.operandType.intType]; /* operand_result recebe o operando que está na posição index do array */
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result); /* coloca operand_result na pilha de operandos */
    return 0;
}

/*0x31*/
int daload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand2.operandType.referenceType; /* p aponta para o array referenciado */
    operand_result = p->array[operand1.operandType.intType]; /* operand_result recebe o operando que está na posição index do array */
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result); /* coloca operand_result na pilha de operandos */
    return 0;
}

/*0x32*/
int aaload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand2.operandType.referenceType; /* p aponta para o array referenciado */
    operand_result = p->array[operand1.operandType.intType]; /* operand_result recebe o operando que está na posição index do array */
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result); /* coloca operand_result na pilha de operandos */
    return 0;
}

/*0x33*/
int baload(Interpretador* interpretador) { /* Não verifica se é byte ou boolean, trata apenas como byte */
    Operand operand1, operand2, operand_result;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand2.operandType.referenceType; /* p aponta para o array referenciado */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = p->array[operand1.operandType.intType].operandType.byteType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result); /* coloca operand_result na pilha de operandos */
    return 0;
}

/*0x34*/
int caload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand2.operandType.referenceType; /* p aponta para o array referenciado */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = p->array[operand1.operandType.intType].operandType.charType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result); /* coloca operand_result na pilha de operandos */
    return 0;
}

/*0x35*/
int saload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand2.operandType.referenceType; /* p aponta para o array referenciado */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = p->array[operand1.operandType.intType].operandType.shortType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result); /* coloca operand_result na pilha de operandos */
    return 0;
}

/*0x4F*/
int iastore(Interpretador* interpretador) {
    Operand operand1, operand2, operand3;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand3.operandType.referenceType; /* p aponta para o array referenciado */
    p->array[operand2.operandType.intType] = operand1; /* array[index] = valor */
    return 0;
}

/*0x50*/
int lastore(Interpretador* interpretador) {
    Operand operand1, operand2, operand3;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand3.operandType.referenceType; /* p aponta para o array referenciado */
    p->array[operand2.operandType.intType] = operand1; /* array[index] = valor */
    return 0;
}

/*0x51*/
int fastore(Interpretador* interpretador) {
    Operand operand1, operand2, operand3;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand3.operandType.referenceType; /* p aponta para o array referenciado */
    p->array[operand2.operandType.intType] = operand1; /* array[index] = valor */
    return 0;
}

/*0x52*/
int dastore(Interpretador* interpretador) {
    Operand operand1, operand2, operand3;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand3.operandType.referenceType; /* p aponta para o array referenciado */
    p->array[operand2.operandType.intType] = operand1; /* array[index] = valor */
    return 0;
}

/*0x53*/
int aastore(Interpretador* interpretador) {
    Operand operand1, operand2, operand3;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand3.operandType.referenceType; /* p aponta para o array referenciado */
    p->array[operand2.operandType.intType] = operand1; /* array[index] = valor */
    return 0;
}

/*0x54*/
int bastore(Interpretador* interpretador) {
    Operand operand1, operand2, operand3;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand3.operandType.referenceType; /* p aponta para o array referenciado */
    p->array[operand2.operandType.intType].operandType.byteType = operand1.operandType.intType; /* PROBLEMA: int -> byte? */
    p->array[operand2.operandType.intType].type32_64 = CAT1;
    return 0;
}

/*0x55*/
int castore(Interpretador* interpretador) {
    Operand operand1, operand2, operand3;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand3.operandType.referenceType; /* p aponta para o array referenciado */
    p->array[operand2.operandType.intType].operandType.charType = operand1.operandType.intType; /* PROBLEMA: int -> char? */
    p->array[operand2.operandType.intType].type32_64 = CAT1;
    return 0;
}

/*0x56*/
int sastore(Interpretador* interpretador) {
    Operand operand1, operand2, operand3;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    p = operand3.operandType.referenceType; /* p aponta para o array referenciado */
    p->array[operand2.operandType.intType].operandType.shortType = operand1.operandType.intType; /* PROBLEMA: int -> short? */
    p->array[operand2.operandType.intType].type32_64 = CAT1;
    return 0;
}

/*0xB2*/
int getstatic(Interpretador* interpretador) {
    ClassFile *classFile;
    Operand operand;
    Field *field;
    char *className, *fieldName, *descriptor;
    u2 fieldrefInfoIndex, classInfoIndex, classNameIndex, nameAndTypeInfoIndex, fieldNameIndex, fieldTypeIndex;
    u1 indexbyte1, indexbyte2;

    /* Calcula o indice */
    indexbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* le indexbyte1 */
    interpretador->topStackFrame->frame->execEnvir->pc++;
    indexbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* le indexbyte2 */
    interpretador->topStackFrame->frame->execEnvir->pc++; /* Deixa pc na proxima instrucao */

    /* Seta o indice do fieldrefInfo */
    fieldrefInfoIndex = (indexbyte1 << 8) | indexbyte2;

    /* Seta o indice do classInfo */
    classInfoIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[fieldrefInfoIndex].info.FieldrefInfo.classIndex;

    /*  Seta o indice do className */
    classNameIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[classInfoIndex].info.ClassInfo.nameIndex;

    /* Pega o className a partir do indice classNameIndex */
    className = (char*)getUTF8(interpretador->topStackFrame->frame->execEnvir->belongingClass, classNameIndex);

    /* Seta o indice do nameAndTypeInfo */
    nameAndTypeInfoIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[fieldrefInfoIndex].info.FieldrefInfo.nameAndTypeIndex;

    /* Seta o indice do fieldName */
    fieldNameIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[nameAndTypeInfoIndex].info.NameAndTypeInfo.nameIndex;

    /* Pega o fieldName a partir do indice fieldNameIndex */
    fieldName = (char*)getUTF8(interpretador->topStackFrame->frame->execEnvir->belongingClass, fieldNameIndex);

    /* Seta o indice fieldType */
    fieldTypeIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[nameAndTypeInfoIndex].info.NameAndTypeInfo.descriptorIndex;

    /* Pega o descriptor a partir do fieldTypeIndex */
    descriptor = (char*)getUTF8(interpretador->topStackFrame->frame->execEnvir->belongingClass, fieldTypeIndex);


    /* Se for um print */
    if(strcmp(className, "java/lang/System") == 0 && strcmp(fieldName, "out") == 0 && strcmp(descriptor, "Ljava/io/PrintStream;") == 0) {

        /* PROBLEMA: Empilha um operando inutil que vai ser descartado quando o invokevirtual for chamado */
        operand.operandType.intType = 0;
        operand.type32_64 = CAT1;
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);

	} else { /* Senão, buscar o field e verificar seu tipo */


		/* Checa se a classe ja foi carregada (inicializa uma se ainda nao foi) */
		classFile = isLoaded(interpretador, className);

        /* Procura o field nas classes */
        field = getStaticFieldName(interpretador->initClass, className, fieldName);

		/* Caso nao tenha encontrado */
		if (field == NULL) {
			printf("Field nao encontrado\n");
			exit(1);
		} else { /* Encontrou o field */
		    switch(descriptor[0]) {
            case 'B': case 'C': /* Byte ou char */
                operand.type32_64 = CAT1;
                operand.operandType.intType = field->fieldType.charType;
                pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
                break;
            case 'D': /* Double */
                operand.type32_64 = CAT2;
                operand.operandType.doubleType = field->fieldType.doubleType;
                pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
                break;
            case 'F': /* Float */
                operand.type32_64 = CAT1;
                operand.operandType.floatType = field->fieldType.floatType;
                pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
                break;
            case 'I': case 'Z': /* Int */
                operand.type32_64 = CAT1;
                operand.operandType.intType = field->fieldType.intType;
                pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
                break;
            case 'J': /* Long */
                operand.type32_64 = CAT2;
                operand.operandType.longType = field->fieldType.longType;
                pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
                break;
            case 'L': case '[': /* Reference */
                operand.type32_64 = CAT1;
                operand.operandType.referenceType = field->fieldType.referenceType;
                pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
                break;
            case 'S':
                operand.type32_64 = CAT1;
                operand.operandType.intType = field->fieldType.shortType;
                pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
                break;
			}
		}
	}
	return 0;
}

/*0xB3*/
int putstatic(Interpretador* interpretador) {

    ClassFile *classFile;
    Operand operand;
    Field *field;
    char *className, *fieldName, *descriptor;
    u2 fieldrefInfoIndex, classInfoIndex, classNameIndex, nameAndTypeInfoIndex, fieldNameIndex, fieldTypeIndex;
    u1 indexbyte1, indexbyte2;
    ClassList *p;
    int i;


    /* Calcula o indice */
    indexbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* le indexbyte1 */
    interpretador->topStackFrame->frame->execEnvir->pc++;
    indexbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* le indexbyte2 */
    interpretador->topStackFrame->frame->execEnvir->pc++; /* Deixa pc na proxima instrucao */

    /* Seta o indice do fieldrefInfo */
    fieldrefInfoIndex = (indexbyte1 << 8) | indexbyte2;

    /* Seta o indice do classInfo */
    classInfoIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[fieldrefInfoIndex].info.FieldrefInfo.classIndex;

    /*  Seta o indice do className */
    classNameIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[classInfoIndex].info.ClassInfo.nameIndex;

    /* Pega o className a partir do indice classNameIndex */
    className = (char*)getUTF8(interpretador->topStackFrame->frame->execEnvir->belongingClass, classNameIndex);

    /* Seta o indice do nameAndTypeInfo */
    nameAndTypeInfoIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[fieldrefInfoIndex].info.FieldrefInfo.nameAndTypeIndex;

    /* Seta o indice do fieldName */
    fieldNameIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[nameAndTypeInfoIndex].info.NameAndTypeInfo.nameIndex;

    /* Pega o fieldName a partir do indice fieldNameIndex */
    fieldName = (char*)getUTF8(interpretador->topStackFrame->frame->execEnvir->belongingClass, fieldNameIndex);

    /* Seta o indice fieldType */
    fieldTypeIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[nameAndTypeInfoIndex].info.NameAndTypeInfo.descriptorIndex;

    /* Pega o descriptor a partir do fieldTypeIndex */
    descriptor = (char*)getUTF8(interpretador->topStackFrame->frame->execEnvir->belongingClass, fieldTypeIndex);

    /* Checa se a classe ja foi carregada (inicializa uma se ainda nao foi) */
    classFile = isLoaded(interpretador, className);

    /* Procura o field nas classes */
    field = getStaticFieldName(interpretador->initClass, className, fieldName);

    /* Caso nao tenha encontrado */
    if (field == NULL ) {
        printf("Field nao encontrado\n");
        exit(1);
    } else { /* Encontrou o field */
        operand = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* Pega o valor */
		p = interpretador->initClass;
		while (p != NULL) { /* Enquanto ainda tem elementos na lista de classes */
            classInfoIndex = p->classFile->thisClass; /* Pega o indice do classInfo*/
            /* Verifica se className == nome da classe no indice classInfo */
            if (strcmp(className, (char*)getUTF8(p->classFile->constantPool, p->classFile->constantPool[classInfoIndex].info.ClassInfo.nameIndex)) == 0) {
                for (i = 0; i < p->staticFieldsCount; i++) { /* Verifica se o field esta nos staticFields da classe */
                    if (strcmp(fieldName, p->staticFields[i].name) == 0) { /* Se estiver, atribui o operando que retirou da pilha */
                        p->staticFields[i].fieldType.doubleType = operand.operandType.doubleType;
                        return 0;
                    }
                }
                return 0;
            }
            p = p->nextClass;
		}
    }
    return 0;
}

/*0xB4*/
int getfield(Interpretador* interpretador) {
    u1 indexbyte1, indexbyte2;
	u2 index, nameAndTypeIndex, fieldNameIndex, descriptorIndex;
	Object *object;
	Field *field;
	char *fieldName, *descriptorName;
	Operand operand1, operand_result;
	int i;

    /* Calcula o indice */
    indexbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* le indexbyte1 */
    interpretador->topStackFrame->frame->execEnvir->pc++;
    indexbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* le indexbyte2 */
    interpretador->topStackFrame->frame->execEnvir->pc++; /* Deixa pc na proxima instrucao */

    /* Seta o indice index*/
    index = (indexbyte1 << 8) | indexbyte2;

    /* Pega objectref da pilha de operandos */
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    /* Converte o ponteiro para void (referenceType) para um ponteiro para Object */
    object = (Object*) operand1.operandType.referenceType;

    /* Seta o indice do nameAndType */
    nameAndTypeIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.FieldrefInfo.nameAndTypeIndex;

    /* Seta o indice do fieldName */
    fieldNameIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[nameAndTypeIndex].info.NameAndTypeInfo.nameIndex;

    /* Pega o fieldName a partir do fieldNameIndex */
    fieldName = (char*)interpretador->topStackFrame->frame->execEnvir->belongingClass[fieldNameIndex].info.Utf8Info.bytes;

    /* Seta o indice do descriptor */
    descriptorIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[nameAndTypeIndex].info.NameAndTypeInfo.descriptorIndex;

    /* Pega o descriptorName a partir do descriptorIndex */
    descriptorName = (char*)interpretador->topStackFrame->frame->execEnvir->belongingClass[descriptorIndex].info.Utf8Info.bytes;

    /* Compara o nome e o descritor do field com os dos fields de object*/
    field = NULL;
    for (i = 0; i < object->fieldsCount; i++) {
        if ((strcmp(fieldName, object->fields[i].name) == 0) && strcmp(descriptorName, object->fields->descriptor) == 0) {
            field = &(object->fields[i]);
                return 0;
        }
    }

    /* Se encontrou field */
    if (field != NULL) {
        switch(descriptorName[0]) {
        case 'B': case 'C': /* Byte ou char */
            operand_result.operandType.intType = field->fieldType.charType;
            operand_result.type32_64 = CAT1;
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
            break;
        case 'D': /* Double */
            operand_result.type32_64 = CAT2;
            operand_result.operandType.doubleType = field->fieldType.doubleType;
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
            break;
        case 'F': /* Float */
            operand_result.type32_64 = CAT1;
            operand_result.operandType.floatType = field->fieldType.floatType;
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
            break;
        case 'I': case 'Z': /* Int */
            operand_result.type32_64 = CAT1;
            operand_result.operandType.intType = field->fieldType.intType;
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
            break;
        case 'J': /* Long */
            operand_result.type32_64 = CAT2;
            operand_result.operandType.longType = field->fieldType.longType;
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
            break;
        case 'L': case '[': /* Reference */
            operand_result.type32_64 = CAT1;
            operand_result.operandType.referenceType = field->fieldType.referenceType;
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
            break;
        case 'S':
            operand_result.type32_64 = CAT1;
            operand_result.operandType.intType = field->fieldType.shortType;
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
            break;
        }
    } else {
        printf("Field nao encontrado\n");
        exit(1);
    }
	return 0;
}

/*0xB5*/
int putfield(Interpretador* interpretador) {
    u1 indexbyte1, indexbyte2;
	u2 index, nameAndTypeIndex, fieldNameIndex, descriptorIndex;
	Object *object;
	Field *field;
	char *fieldName, *descriptorName;
	Operand operand1, operand2;
	int i;

    /* Calcula o indice */
    indexbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* le indexbyte1 */
    interpretador->topStackFrame->frame->execEnvir->pc++;
    indexbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* le indexbyte2 */
    interpretador->topStackFrame->frame->execEnvir->pc++; /* Deixa pc na proxima instrucao */

    /* Seta o indice index*/
    index = (indexbyte1 << 8) | indexbyte2;

    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* Pega valor */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* Pega objectref */

    /* Converte o ponteiro para void (referenceType) para um ponteiro para Object */
    object = (Object*) operand2.operandType.referenceType;

    /* Seta o indice do nameAndType */
    nameAndTypeIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.FieldrefInfo.nameAndTypeIndex;

    /* Seta o indice do fieldName */
    fieldNameIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[nameAndTypeIndex].info.NameAndTypeInfo.nameIndex;

    /* Pega o fieldName a partir do fieldNameIndex */
    fieldName = (char*)interpretador->topStackFrame->frame->execEnvir->belongingClass[fieldNameIndex].info.Utf8Info.bytes;

    /* Seta o indice do descriptor */
    descriptorIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[nameAndTypeIndex].info.NameAndTypeInfo.descriptorIndex;

    /* Pega o descriptorName a partir do descriptorIndex */
    descriptorName = (char*)interpretador->topStackFrame->frame->execEnvir->belongingClass[descriptorIndex].info.Utf8Info.bytes;

    /* Procura o nome e o descritor do field com os dos fields de object*/
    field = NULL;
    for (i = 0; i < object->fieldsCount; i++) {
        if ((strcmp(fieldName, object->fields[i].name) == 0) && strcmp(descriptorName, object->fields->descriptor) == 0) {
            field = &(object->fields[i]);
                return 0;
        }
    }

	if (field != NULL ) {
        field->fieldType.doubleType = operand1.operandType.doubleType;
	} else {
		printf("Field nao encontrado\n");
		exit(1);
	}
	return 0;
}

/*0xBB*/
int new_(Interpretador* interpretador) {
    Object *object;
    Operand objectReference;
    ClassFile *classFile, *classFile_aux;
    u1 indexbyte1, indexbyte2;
    u2 classInfoIndex, classNameIndex, superClassNameIndex;
    char *className, superClassName[100];
	int i, fieldsCount = 0;


    /* Calcula o indice */
    indexbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* le indexbyte1 */
    interpretador->topStackFrame->frame->execEnvir->pc++;
    indexbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* le indexbyte2 */
    interpretador->topStackFrame->frame->execEnvir->pc++; /* Deixa pc na proxima instrucao */

    /* Seta o indice do classInfo */
    classInfoIndex = (indexbyte1 << 8) | indexbyte2;

    /* Seta o indice do className */
    classNameIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[classInfoIndex].info.ClassInfo.nameIndex;

    /* Pega o className a partir do classNameIndex */
    className = (char*)getUTF8(interpretador->topStackFrame->frame->execEnvir->belongingClass, classNameIndex);

    /* Checa se a classe ja foi carregada (inicializa uma se ainda nao foi) */
    classFile = isLoaded(interpretador, className);

    /* Conta a quantidade de fields: */
	classFile_aux = classFile;

    /* Conta a quantidade de fields da classe */
	for (i = 0; i < classFile_aux->fieldsCount; i++) {
        /* Campos estaticos nao podem ser contabilizados */
		if ((classFile_aux->fields[i].accessFlags & ACC_STATIC) == 0) {
			fieldsCount++;
		}
	}

	/* Conta os fields das super classes (exceto os static) */
	while (classFile_aux->superClass != 0) {
        /* Seta o indice do superClassName */
        superClassNameIndex = classFile_aux->constantPool[classFile_aux->superClass].info.ClassInfo.nameIndex;
        /* Pega o superClassName a partir do indice */
        strcpy(superClassName, (char*)getUTF8(classFile_aux->constantPool, superClassNameIndex));

        /* Checa se a classe ja foi carregada (inicializa uma se ainda nao foi) */
        classFile = isLoaded(interpretador, superClassName);

        /* Conta a quantidade de fields da classe */
        for (i = 0; i < classFile_aux->fieldsCount; i++) {
            /* Campos estaticos nao podem ser contabilizados */
            if ((classFile_aux->fields[i].accessFlags & ACC_STATIC) == 0) {
                fieldsCount++;
            }
        }
	}

    /* Seta o objeto */
    object = malloc(sizeof(Object));
    object->fieldsCount = fieldsCount;
    object->fields = malloc(sizeof(Field) * object->fieldsCount);

    /* Inicializa os fields do objeto */
    fieldsInit(interpretador, *classFile, object->fields);

    /* Seta o operando que vai conter a referencia para o objeto */
    objectReference.operandType.referenceType = object;
    objectReference.type32_64 = CAT1;

    /* Insere o operando na pilha */
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), objectReference);

	return 0;
}

/*0xBC*/
int newarray(Interpretador* interpretador) {
    Operand operand1, operand_result;
    Array *p;

    /* Cria um array */
    p = malloc(sizeof(Array));
    /* Seta o tipo do array de acordo com o indicado */
    p->type = *(interpretador->topStackFrame->frame->execEnvir->pc);
    /* pc aponta para a proxima instrucao */
    interpretador->topStackFrame->frame->execEnvir->pc++;

    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* Pega o count */

    /* Seta o tamanho do array */
    p->arraySize = operand1.operandType.intType;

    switch (p->type) {
	case T_BOOLEAN:
		p->array = calloc(p->arraySize, sizeof(Operand));
		break;
	case T_CHAR:
		p->array = calloc(p->arraySize, sizeof(Operand));
		break;
	case T_FLOAT:
		p->array = calloc(p->arraySize, sizeof(Operand));
		break;
	case T_DOUBLE:
		p->array = calloc(p->arraySize, sizeof(Operand));
		break;
	case T_BYTE:
		p->array = calloc(p->arraySize, sizeof(Operand));
		break;
	case T_SHORT:
		p->array = calloc(p->arraySize, sizeof(Operand));
		break;
	case T_INT:
		p->array = calloc(p->arraySize, sizeof(Operand));
		break;
	case T_LONG:
		p->array = calloc(p->arraySize, sizeof(Operand));
		break;
	default:
		printf("Tipo inexistente");
		exit(1);
	}

	/* Seja o operando que vai conter a referencia para o array */
	operand_result.type32_64 = CAT1;
	operand_result.operandType.referenceType = p;

	/* Insere o operando na pilha */
	pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);

	return 0;
}

/*0xBD*/
int anewarray(Interpretador* interpretador) {
    Operand operand1, operand_result;
    Array *p;
    u2 index;
    u1 indexbyte1, indexbyte2;

    /* Cria um array */
    p = calloc(1, sizeof(Array));

    /* Pega os indexbyte */
    indexbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    indexbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    /* pc aponta para a proxima instrucao */
    interpretador->topStackFrame->frame->execEnvir->pc++;

    /* Calcula index */
    index =  (indexbyte1 << 8) | indexbyte2;

    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* Pega o count */

    /* Verifica se o tamanho dado por count e' valido */
	if (operand1.operandType.intType < 0) {
		printf("Tamanho negativo\n");
		exit(1);
	}

    /* Seta o array */
	p->arraySize = operand1.operandType.intType;
	p->type = T_INT;
	p->array = calloc(p->arraySize, sizeof(Operand));
	operand_result.type32_64 = CAT1;

	/* Seta o operando que vai conter a referencia para o array */
	operand_result.type32_64 = CAT1;
	operand_result.operandType.referenceType = p;

	/* Insere o operando na pilha */
	pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);

	return 0;
}

/*0xBE*/
int arraylength(Interpretador* interpretador) {
    Operand operand1, operand_result;
    Array *p;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* Pega o arrayref */
    p = operand1.operandType.referenceType;
    /* Seta o operando a ser empilhado */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = p->arraySize;
    /* Empilha o resultado */
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0xC0*/
int checkcast(Interpretador* interpretador) {
    return 0;
}

/*0xC1*/
int instanceof(Interpretador* interpretador) {
    return 0;
}

/*0xC5*/
int multianewarray(Interpretador* interpretador) {
    u1 dimensions, indexbyte1, indexbyte2;
    Array *p;
    int i;
    Operand operand_result;

    indexbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* Pega indexbyte1 */
    interpretador->topStackFrame->frame->execEnvir->pc++;
    indexbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc); /* Pega indexbyte2 */
    interpretador->topStackFrame->frame->execEnvir->pc++;
    dimensions = *(interpretador->topStackFrame->frame->execEnvir->pc); /* Pega dimensions */
    interpretador->topStackFrame->frame->execEnvir->pc++; /* pc aponta para a proxima instrucao */

    Operand counts[dimensions]; /* Cria um vetor de counts com tamanho igual a quantidade de dimensoes */
    int intCounts[dimensions];

    /* Testa se a dimensao dada e' um numero valido */
    if (dimensions <= 0) {
        printf("Tamanho negativo\n");
        exit(1);
    } else { /* Se for */
        for (i = 0; i < dimensions; i++) {
            counts[i] = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* Pega os counts da pilha de operandos */
            intCounts[i] = counts[i].operandType.intType; /* Coloca os counts em um vetor de ints */
        }
        /* Cria um multiarray */
        p = createMultiArray(dimensions, intCounts);

        /* Seta o operando a ser empilhado */
        operand_result.type32_64 = CAT1;
        operand_result.operandType.intType = p->arraySize;
        /* Empilha o resultado */
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
    }

	return 0;
}

