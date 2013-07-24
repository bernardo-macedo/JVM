/*
 * DebugFuncs.c
 *
 *  Created on: 01/02/2013
 *      Author: Vitor
 */

#include <stdio.h>
#include "ClassFile.h"
#include "DebugFuncs.h"

char* tagString(u1 tag) {
	switch (tag) {
	case CONSTANT_Class:
		return "Class";
		break;
	case CONSTANT_FieldRef:
		return "FieldRef";
		break;
	case CONSTANT_Methodref:
		return "MethodRef";
		break;
	case CONSTANT_InterfaceMethodRef:
		return "InterfaceMethodRef";
		break;
	case CONSTANT_String:
		return "String";
		break;
	case CONSTANT_Integer:
		return "Integer";
		break;
	case CONSTANT_Float:
		return "Float";
		break;
	case CONSTANT_Long:
		return "Long";
		break;
	case CONSTANT_Double:
		return "Double";
		break;
	case CONSTANT_NameAndType:
		return "NameAndType";
		break;
	case CONSTANT_UTF8:
		return "UTF8";
		break;
	default:
		return "Nao conheco essa tag :(";
	}
}

void printConstantPool(ClassFile classFile) {

	int i;

	for (i = 1; i < classFile.constant_pool_count; i++) {

		//Printa a posicao da const pool.
		printf("#%d\t", i);

		switch (classFile.constant_pool[i].tag) {
		case CONSTANT_Class:
			printf("%s\t\t%hu\n", tagString(classFile.constant_pool[i].tag),
					classFile.constant_pool[i].info.classInfo.nameIndex);
			break;
		case CONSTANT_FieldRef:
			printf("%s\t%hu.%hu\n", tagString(classFile.constant_pool[i].tag),
					classFile.constant_pool[i].info.fieldRefInfo.classIndex,
					classFile.constant_pool[i].info.fieldRefInfo.nameAndTypeIndex);
			break;
		case CONSTANT_Methodref:
			printf("%s\t%hu.%hu\n", tagString(classFile.constant_pool[i].tag),
					classFile.constant_pool[i].info.methodRefInfo.classIndex,
					classFile.constant_pool[i].info.methodRefInfo.nameAndTypeIndex);
			break;
		case CONSTANT_InterfaceMethodRef:
			printf("%s\t%hu.%hu\n", tagString(classFile.constant_pool[i].tag),
					classFile.constant_pool[i].info.interfaceMethodRefInfo.classIndex,
					classFile.constant_pool[i].info.interfaceMethodRefInfo.nameAndTypeIndex);
			break;
		case CONSTANT_String:
			printf("%s\t\t%hu\n", tagString(classFile.constant_pool[i].tag),
					classFile.constant_pool[i].info.stringInfo.stringIndex);
			break;
		case CONSTANT_Integer:
			printf("%s\t\t%u\n", tagString(classFile.constant_pool[i].tag),
					classFile.constant_pool[i].info.integerInfo.bytes);
			break;
		case CONSTANT_Float:
			printf("%s\t\t%f\n", tagString(classFile.constant_pool[i].tag),
					classFile.constant_pool[i].info.floatInfo.f.num);
			break;
		case CONSTANT_Long:
			printf("%s\t\t%llu\n", tagString(classFile.constant_pool[i].tag),
					classFile.constant_pool[i].info.longInfo.bytes);
			i++;
			break;
		case CONSTANT_Double:
			printf("%s\t\t%g\n", tagString(classFile.constant_pool[i].tag),
					classFile.constant_pool[i].info.doubleInfo.d.num);
			i++;
			break;
		case CONSTANT_NameAndType:
			printf("%s\t%hu.%hu\n", tagString(classFile.constant_pool[i].tag),
					classFile.constant_pool[i].info.nameAndTypeInfo.nameIndex,
					classFile.constant_pool[i].info.nameAndTypeInfo.descriptorIndex);
			break;
		case CONSTANT_UTF8:
			printf("%s\t\t%s\n", tagString(classFile.constant_pool[i].tag),
					classFile.constant_pool[i].info.UTF8Info.bytes);
			break;
		default:
			printf("%s\n", tagString(classFile.constant_pool[i].tag));
			break;
		}

	}

}

void printCodigoMetodo(attributeInfo methodCode) {

	int i;

	for (i = 0; i < methodCode.tipoInfo.code.codeLength; i++) {
		if (i % 6 == 0) {
			printf("\n");
		}
		printf("%x ", methodCode.tipoInfo.code.code[i]);
	}

}
