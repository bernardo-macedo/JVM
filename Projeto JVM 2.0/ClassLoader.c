/*
 * ClassLoader.c
 *
 *  Created on: 03/02/2013
 *      Author: Vitor
 */

#include "ClassLoader.h"

u1 lerU1(FILE *fp) {

	u1 u1Lido = getc(fp);

	return u1Lido;
}

u2 lerU2(FILE *fp) {

	u2 u2Lido = getc(fp);

	u2Lido = (u2Lido << 8) | getc(fp);

	return u2Lido;
}

u4 lerU4(FILE *fp) {

	u4 u4Lido = getc(fp);

	u4Lido = (u4Lido << 8) | getc(fp);
	u4Lido = (u4Lido << 8) | getc(fp);
	u4Lido = (u4Lido << 8) | getc(fp);

	return u4Lido;
}

u8 lerU8(FILE *fp) {

	u8 u8Lido = getc(fp);

	u8Lido = (u8Lido << 8) | getc(fp);
	u8Lido = (u8Lido << 8) | getc(fp);
	u8Lido = (u8Lido << 8) | getc(fp);
	u8Lido = (u8Lido << 8) | getc(fp);
	u8Lido = (u8Lido << 8) | getc(fp);
	u8Lido = (u8Lido << 8) | getc(fp);
	u8Lido = (u8Lido << 8) | getc(fp);

	return u8Lido;
}

// função responsável pela leitura da constant pool
void lerConstantPool(FILE *fp, ClassFile *cf) {
	int i;
	int j;

	// alocando o vetor muito doido
	cf->constant_pool = malloc(sizeof(cpInfo) * (cf->constant_pool_count));

	// lendo as constantes da piscina
	for (i = 1; i < cf->constant_pool_count; i++) {
		// lendo a tipagem da constante
		cf->constant_pool[i].tag = lerU1(fp);

		// definindo o tratamento para cada tipo de constante
		switch (cf->constant_pool[i].tag) {

		case CONSTANT_Class:
			cf->constant_pool[i].info.classInfo.nameIndex = lerU2(fp);
			break;

		case CONSTANT_FieldRef:
			cf->constant_pool[i].info.fieldRefInfo.classIndex = lerU2(fp);
			cf->constant_pool[i].info.fieldRefInfo.nameAndTypeIndex = lerU2(fp);
			break;

		case CONSTANT_Methodref:
			cf->constant_pool[i].info.methodRefInfo.classIndex = lerU2(fp);
			cf->constant_pool[i].info.methodRefInfo.nameAndTypeIndex = lerU2(
					fp);
			break;

		case CONSTANT_InterfaceMethodRef:
			cf->constant_pool[i].info.interfaceMethodRefInfo.classIndex = lerU2(
					fp);
			cf->constant_pool[i].info.interfaceMethodRefInfo.nameAndTypeIndex =
					lerU2(fp);
			break;

		case CONSTANT_String:
			cf->constant_pool[i].info.stringInfo.stringIndex = lerU2(fp);
			break;

		case CONSTANT_Integer:
			cf->constant_pool[i].info.integerInfo.bytes = lerU4(fp);
			break;

		case CONSTANT_Float:
			cf->constant_pool[i].info.floatInfo.f.bytes = lerU4(fp);
			break;

		case CONSTANT_Long:
			cf->constant_pool[i].info.longInfo.bytes = lerU8(fp);
			i++;
			break;

		case CONSTANT_Double:
			cf->constant_pool[i].info.doubleInfo.d.bytes = lerU8(fp);
			i++;
			break;

		case CONSTANT_NameAndType:
			cf->constant_pool[i].info.nameAndTypeInfo.nameIndex = lerU2(fp);
			cf->constant_pool[i].info.nameAndTypeInfo.descriptorIndex = lerU2(
					fp);
			break;

		case CONSTANT_UTF8:
			cf->constant_pool[i].info.UTF8Info.length = lerU2(fp);
			cf->constant_pool[i].info.UTF8Info.bytes = malloc(
					(cf->constant_pool[i].info.UTF8Info.length) * sizeof(char)
							+ 1);
			for (j = 0; j < cf->constant_pool[i].info.UTF8Info.length; j++) {
				cf->constant_pool[i].info.UTF8Info.bytes[j] = lerU1(fp);
			}
			cf->constant_pool[i].info.UTF8Info.bytes[j] = '\0';
			break;
		}
	}
}

// função que carrega as interfaces
void lerInterfaces(FILE *fp, ClassFile *cf) {

	int i;

	// alocando espaço necessário
	cf->interfaces = malloc((cf->interfaces_count) * sizeof(u2));

	for (i = 0; i < cf->interfaces_count; i++) {
		cf->interfaces[i] = lerU2(fp);
	}

}

// função que lê um atributo denominado ConstantValue
void lerAttributeConstantValue(FILE *fp, attributeInfo *attr) {

	attr->tipoInfo.constantValue.constantValueIndex = lerU2(fp);

}

// função que lê a tabela de exceções de um código
void lerCodeExceptionTable(FILE *fp, exceptionTable *excTab) {

	// lendo o PC inicial
	excTab->startPC = lerU2(fp);

	// lendo o PC final
	excTab->endPC = lerU2(fp);

	// lendo o PC do handler
	excTab->handlerPC = lerU2(fp);

	// lendo o tipo do catch
	excTab->catchType = lerU2(fp);

}

// função que lê um atributo denominado Code
void lerAttributeCode(FILE *fp, ClassFile *cf, attributeInfo *attr) {

	int i;

	// lê o número máximo de elementos da stack
	attr->tipoInfo.code.maxStack = lerU2(fp);

	// lê o número máximo de variáveis locais
	attr->tipoInfo.code.maxLocals = lerU2(fp);

	// lê o tamanho do código
	attr->tipoInfo.code.codeLength = lerU4(fp);

	// aloca o espaço necessário para armazenar o código
	attr->tipoInfo.code.code = malloc(
			(attr->tipoInfo.code.codeLength) * sizeof(u1));

	// bloco que lê o código em si
	for (i = 0; i < attr->tipoInfo.code.codeLength; i++) {
		attr->tipoInfo.code.code[i] = lerU1(fp);
	}

	// lê o tamanho da tabela de exceções
	attr->tipoInfo.code.exceptionTableLength = lerU2(fp);

	// aloca o espaço necessário para a tabela de exceções
	attr->tipoInfo.code.excTable = malloc(
			(attr->tipoInfo.code.exceptionTableLength)
					* sizeof(exceptionTable));

	// bloco que lê a tabela de exceções
	for (i = 0; i < attr->tipoInfo.code.exceptionTableLength; i++) {
		lerCodeExceptionTable(fp, &(attr->tipoInfo.code.excTable[i]));
	}

	// lê o número de atributos que o código tem
	attr->tipoInfo.code.attributesCount = lerU2(fp);

	// alocando o espaço necessário para os atributos do código
	attr->tipoInfo.code.attributes = malloc(
			(attr->tipoInfo.code.attributesCount) * sizeof(attributeInfo));

	// lê os atributos do código
	// As attributes de um code só podem ser: LineNumberTable e LocalVariableTable (ambas opcionais)
	for (i = 0; i < attr->tipoInfo.code.attributesCount; i++) {
		lerAttributeInfo(fp, cf, &(attr->tipoInfo.code.attributes[i]));
	}

}

// função que lê um attribute denominado Exceptions
void lerAttributeExceptions(FILE *fp, attributeInfo *attr) {

	int i;

	// lê o número de exceções da tabela
	attr->tipoInfo.exceptions.numberOfExceptions = lerU2(fp);

	// aloca o espaço necessário
	attr->tipoInfo.exceptions.exceptionIndexTable = malloc(
			(attr->tipoInfo.exceptions.numberOfExceptions) * sizeof(u2));

	// bloco que faz a leitura
	for (i = 0; i < attr->tipoInfo.exceptions.numberOfExceptions; i++) {
		attr->tipoInfo.exceptions.exceptionIndexTable[i] = lerU2(fp);
	}

}

// função que lê as informações de um attribute denominado InnerClasses
void lerAttributeInnerClasses(FILE *fp, attributeInfo *attr) {

	int i;

	// lê o número de inner classes
	attr->tipoInfo.innerClasses.numberOfClasses = lerU2(fp);

	// aloca o espaço necessário
	attr->tipoInfo.innerClasses.classes = malloc(
			(attr->tipoInfo.innerClasses.numberOfClasses) * sizeof(classes));

	// lê as classes em si
	for (i = 0; i < attr->tipoInfo.innerClasses.numberOfClasses; i++) {
		attr->tipoInfo.innerClasses.classes[i].innerClassInfoIndex = lerU2(fp);
		attr->tipoInfo.innerClasses.classes[i].outerClassInfoIndex = lerU2(fp);
		attr->tipoInfo.innerClasses.classes[i].innerNameIndex = lerU2(fp);
		attr->tipoInfo.innerClasses.classes[i].innerClassAccessFlags = lerU2(
				fp);
	}

}

// função que lê as informações de um attribute denominado SourceFile
void lerAttributeSourceFile(FILE *fp, attributeInfo *attr) {

	// lê o índice na pool de constantes
	attr->tipoInfo.sourceFile.sourceFileIndex = lerU2(fp);

}

// função que lê um attribute não reconhecido por essa JVM
void lerAttributeUnknown(FILE *fp, attributeInfo *attr) {

	int i;

	// aloca o espaço necessário para esse attribute
	attr->tipoInfo.unknown.info = malloc((attr->attributeLength) * sizeof(u1));

	for (i = 0; i < attr->attributeLength; i++) {
		attr->tipoInfo.unknown.info[i] = lerU1(fp);
	}

}

// função que le as informações de um atributo
void lerAttributeInfo(FILE *fp, ClassFile *cf, attributeInfo *attr) {

	char nomeAtributo[50];

	// lendo o indice da constant pool que contem o nome do atributo
	attr->attributeNameIndex = lerU2(fp);

	// lendo o tamanho do atributo
	attr->attributeLength = lerU4(fp);

	// pegando e copiando o nome do atributo obtido pela constant pool em nomeAtributo
	strcpy(nomeAtributo,
			cf->constant_pool[attr->attributeNameIndex].info.UTF8Info.bytes);

	if (strcmp(nomeAtributo, "ConstantValue") == 0) {
		lerAttributeConstantValue(fp, attr);
	} else if (strcmp(nomeAtributo, "Code") == 0) {
		lerAttributeCode(fp, cf, attr);
	} else if (strcmp(nomeAtributo, "Exceptions") == 0) {
		lerAttributeExceptions(fp, attr);
	} else if (strcmp(nomeAtributo, "InnerClasses") == 0) {
		lerAttributeInnerClasses(fp, attr);
	} else if (strcmp(nomeAtributo, "Synthetic") == 0) {
		// não faz nada, Synthetic não tem nenhuma informação extra a ser lida
	} else if (strcmp(nomeAtributo, "SourceFile") == 0) {
		lerAttributeSourceFile(fp, attr);
	} else {
		lerAttributeUnknown(fp, attr);
	}

}

void lerFieldInfo(FILE *fp, ClassFile *cf) {

	int i;
	int j;

	// alocando espaço necessário
	cf->fields = malloc(cf->fields_count * sizeof(fieldInfo));

	for (i = 0; i < cf->fields_count; i++) {

		// lendo o nivel de acesso do field
		cf->fields[i].accessFlags = lerU2(fp);

		// lendo o indice de seu nome na constant pool
		cf->fields[i].nameIndex = lerU2(fp);

		// lendo o indice de sua descricao na constant pool
		cf->fields[i].descriptorIndex = lerU2(fp);

		// lendo o número de atributos que esse field contem
		cf->fields[i].attributesCount = lerU2(fp);

		// alocando o espaço necessário para os attributes a serem lidos
		cf->fields[i].attributes = malloc(
				(cf->fields->attributesCount) * sizeof(attributeInfo));

		// bloco que le os atributos da field
		// As field infos só possuem as seguintes attributeInfos: ConstantValue, Synthetic e Deprecated
		for (j = 0; j < cf->fields->attributesCount; j++) {
			lerAttributeInfo(fp, cf, &(cf->fields[i].attributes[j]));
		}

	}

}

void lerMetodos(FILE *fp, ClassFile *cf) {

	int i;
	int j;

	// alocando espaço necessário
	cf->methods = malloc(cf->methods_count * sizeof(methodInfo));

	// bloco que lê os métodos
	for (i = 0; i < cf->methods_count; i++) {

		// lê os access flags
		cf->methods[i].accessFlags = lerU2(fp);

		// lê o índice da constant pool relativo ao nome do método
		cf->methods[i].nameIndex = lerU2(fp);

		// lê o índice da constant pool relativo à descrição do método (tipos de argumento e retorno)
		cf->methods[i].descriptorIndex = lerU2(fp);

		// lê o número de atributos do método
		cf->methods[i].attributesCount = lerU2(fp);

		// aloca o espaço necessário
		cf->methods[i].attributes = malloc(
				(cf->methods[i].attributesCount) * sizeof(attributeInfo));

		// lê os atributos do método. Só podem ser do tipo Code, Exceptions, Synthetic e Deprecated
		for (j = 0; j < cf->methods[i].attributesCount; j++) {
			lerAttributeInfo(fp, cf, &(cf->methods[i].attributes[j]));
		}

	}

}

ClassFile carregaClassFile(char *nomeClasse) {

	FILE *fp;
	ClassFile cf;
	char nomeClasseExt[100];
	int i;

	strcpy(nomeClasseExt, nomeClasse);

	if (strstr(nomeClasse, ".class") == NULL ) {
		strcat(nomeClasseExt, ".class");
	}

	// abre o arquivo .class. Caso o arquivo não exista, aborta o programa.
	fp = fopen(nomeClasseExt, "rb");
	if (fp == NULL ) {
		printf("\nO arquivo %s nao existe.", nomeClasse);
		exit(1);
	}

	// lendo o nro mágico 0xCAFEBABE. Caso esteja errado, abora o programa.
	cf.magic = lerU4(fp);
	if (cf.magic != 0xCAFEBABE) {
		printf("\nO numero magico nao e magico.");
		exit(1);
	}

	// lendo a minor version.
	cf.minor_version = lerU2(fp);

	// lendo a major version.
	cf.major_version = lerU2(fp);

	// lendo o constant pool count
	cf.constant_pool_count = lerU2(fp);

	// lendo a constant pool
	lerConstantPool(fp, &cf);

	// lendo flags de acesso a classe (i.e. Public, Final, etc.)
	cf.access_flags = lerU2(fp);

	// lendo uma entrada na constant pool que identifica a this class
	cf.this_class = lerU2(fp);

	// lendo uma entrada na constant pool que identifica a super class
	cf.super_class = lerU2(fp);

	// lendo o número de interfaces da tabela a ser lida a seguir
	cf.interfaces_count = lerU2(fp);

	// lendo as interfaces
	lerInterfaces(fp, &cf);

	// lendo o número de fields da seguinte tabela
	cf.fields_count = lerU2(fp);

	// lendo os fields
	lerFieldInfo(fp, &cf);

	// lendo o número de métodos da classe
	cf.methods_count = lerU2(fp);

	// lendo os métodos
	lerMetodos(fp, &cf);

	// lendo o número de atributos da classe
	cf.attributes_count = lerU2(fp);

	// alocando o espaço necessário
	cf.attributes = malloc((cf.attributes_count) * sizeof(attributeInfo));

	// lendo os atributos da classe
	// Podem ser somente dos tipos: SourceFile e Deprecated
	for (i = 0; i < cf.attributes_count; i++) {
		lerAttributeInfo(fp, &cf, &(cf.attributes[i]));
	}

	fclose(fp);

	return cf;

}
