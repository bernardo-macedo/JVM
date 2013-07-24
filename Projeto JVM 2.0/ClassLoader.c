#include "ClassLoader.h"

u1 readU1(FILE *fp)
{
	u1 u1Read;

	fread(&u1Read, sizeof(u1), 1, fp);
	
	return u1Read;
}

u2 readU2(FILE *fp)
{
	u1 aux1, aux2;
	u2 u2Read;

    fread(&aux1, sizeof(u1), 1, fp);
    fread(&aux2, sizeof(u1), 1, fp);

    u2Read = (aux1 << 8) | aux2;

    return u2Read;
}

u4 readU4(FILE *fp)
{
	u1 aux1, aux2, aux3, aux4;
	u4 u4Read;

    fread(&aux1, sizeof(u1), 1, fp);
    fread(&aux2, sizeof(u1), 1, fp);
    fread(&aux3, sizeof(u1), 1, fp);
    fread(&aux4, sizeof(u1), 1, fp);

    u4Read = (aux1 << 24) | (aux2 << 16) | (aux3 << 8) | aux4;

    return u4Read;
}

u8 readU8(FILE *fp) 
{
	u8 u8Read = getc(fp);

	u8Read = (u8Read << 8) | getc(fp);
	u8Read = (u8Read << 8) | getc(fp);
	u8Read = (u8Read << 8) | getc(fp);
	u8Read = (u8Read << 8) | getc(fp);
	u8Read = (u8Read << 8) | getc(fp);
	u8Read = (u8Read << 8) | getc(fp);
	u8Read = (u8Read << 8) | getc(fp);

	return u8Read;
}

// função responsável pela leitura da constant pool
void readConstantPool(ClassFile* class, FILE *fp)
{
	int i;
	int j;

	// alocando o vetor muito doido
	class->constantPool = malloc(sizeof(CpInfo) * (class->constantPoolCount));

	// lendo as constantes da piscina
	for (i = 1; i < class->constantPoolCount; i++) 
	{
		// lendo a tipagem da constante
		class->constantPool[i].tag = readU1(fp);

		// definindo o tratamento para cada tipo de constante
		switch (class->constantPool[i].tag) 
		{
			case CONSTANT_Class:
				class->constantPool[i].info.ClassInfo.nameIndex = readU2(fp);
				break;
			case CONSTANT_FieldRef:
				class->constantPool[i].info.FieldRefInfo.classIndex = readU2(fp);
				class->constantPool[i].info.FieldRefInfo.nameAndTypeIndex = readU2(fp);
				break;
			case CONSTANT_Methodref:
				class->constantPool[i].info.MethodRefInfo.classIndex = readU2(fp);
				class->constantPool[i].info.MethodRefInfo.nameAndTypeIndex = readU2(fp);
				break;
			case CONSTANT_InterfaceMethodRef:
				class->constantPool[i].info.InterfaceMethodRefInfo.classIndex = readU2(fp);
				class->constantPool[i].info.InterfaceMethodRefInfo.nameAndTypeIndex = readU2(fp);
				break;
			case CONSTANT_String:
				class->constantPool[i].info.StringInfo.stringIndex = readU2(fp);
				break;
			case CONSTANT_Integer:
				class->constantPool[i].info.IntegerInfo.bytes = readU4(fp);
				break;
			case CONSTANT_Float:
				class->constantPool[i].info.FloatInfo.f.bytes = readU4(fp);
				break;
			case CONSTANT_Long:
				class->constantPool[i].info.LongInfo.bytes = readU8(fp);
				i++;
				break;
			case CONSTANT_Double:
				class->constantPool[i].info.DoubleInfo.d.bytes = readU8(fp);
				i++;
				break;
			case CONSTANT_NameAndType:
				class->constantPool[i].info.NameAndTypeInfo.nameIndex = readU2(fp);
				class->constantPool[i].info.NameAndTypeInfo.descriptorIndex = readU2(fp);
				break;
			case CONSTANT_UTF8:
				class->constantPool[i].info.Utf8Info.length = readU2(fp);
				class->constantPool[i].info.Utf8Info.bytes = malloc((class->constantPool[i].info.Utf8Info.length) * sizeof(char)
								+ 1);
				for (j = 0; j < class->constantPool[i].info.Utf8Info.length; j++) 
				{
					class->constantPool[i].info.Utf8Info.bytes[j] = readU1(fp);
				}
				class->constantPool[i].info.Utf8Info.bytes[j] = '\0';
				break;
		}
	}
}

// função que carrega as interfaces
void readInterfaces(ClassFile* class, FILE *fp)
{
	int i;

	// alocando espaço necessário
	class->interfaces = malloc((class->interfacesCount) * sizeof(u2));

	for (i = 0; i < class->interfacesCount; i++) 
	{
		class->interfaces[i] = readU2(fp);
	}

}

// função que lê um atributo denominado ConstantValue
void readConstantValueAttribute(FILE *fp, AttributeInfo *attributes) 
{
	attributes->AttributeType.ConstantValueAttribute.constantValueIndex = readU2(fp);
}

// função que lê a tabela de exceções de um código
void readCodeExceptionTable(FILE *fp, ExceptionTable *exceptionTable)
{

	// lendo o PC inicial
	exceptionTable->startPC = readU2(fp);

	// lendo o PC final
	exceptionTable->endPC = readU2(fp);

	// lendo o PC do handler
	exceptionTable->handlerPC = readU2(fp);

	// lendo o tipo do catch
	exceptionTable->catchType = readU2(fp);

}

// função que lê um atributo denominado Code
void readCodeAttribute(ClassFile* class, FILE *fp, AttributeInfo *attributes)
{
	int i;

	// lê o número máximo de elementos da stack
	attributes->AttributeType.CodeAttribute.maxStack = readU2(fp);

	// lê o número máximo de variáveis locais
	attributes->AttributeType.CodeAttribute.maxLocals = readU2(fp);

	// lê o tamanho do código
	attributes->AttributeType.CodeAttribute.codeLength = readU4(fp);

	// aloca o espaço necessário para armazenar o código
	attributes->AttributeType.CodeAttribute.code = malloc((attributes->AttributeType.CodeAttribute.codeLength) * sizeof(u1));

	// bloco que lê o código em si
	for (i = 0; i < attributes->AttributeType.CodeAttribute.codeLength; i++) 
	{
		attributes->AttributeType.CodeAttribute.code[i] = readU1(fp);
	}

	// lê o tamanho da tabela de exceções
	attributes->AttributeType.CodeAttribute.exceptionTableLength = readU2(fp);

	// aloca o espaço necessário para a tabela de exceções
	attributes->AttributeType.CodeAttribute.exceptionTable = malloc((attributes->AttributeType.CodeAttribute.exceptionTableLength) * sizeof(ExceptionTable));

	// bloco que lê a tabela de exceções
	for (i = 0; i < attributes->AttributeType.CodeAttribute.exceptionTableLength; i++) 
	{
		readCodeExceptionTable(fp, &(attributes->AttributeType.CodeAttribute.exceptionTable[i]));
	}

	// lê o número de atributos que o código tem
	attributes->AttributeType.CodeAttribute.attributesCount = readU2(fp);

	// alocando o espaço necessário para os atributos do código
	attributes->AttributeType.CodeAttribute.attributes = malloc((attributes->AttributeType.CodeAttribute.attributesCount) * sizeof(AttributeInfo));

	// lê os atributos do código
	// As attributes de um code só podem ser: LineNumberTable e LocalVariableTable (ambas opcionais)
	for (i = 0; i < attributes->AttributeType.CodeAttribute.attributesCount; i++) 
	{
		readAttributes(class, fp, &(attributes->AttributeType.CodeAttribute.attributes[i]));
	}

}

// função que lê um attribute denominado Exceptions
void lerAttributeExceptionsAttribute(FILE *fp, AttributeInfo *attributes) 
{
	int i;

	// lê o número de exceções da tabela
	attributes->AttributeType.ExceptionsAttribute.numberOfExceptions = readU2(fp);

	// aloca o espaço necessário
	attributes->AttributeType.ExceptionsAttribute.exceptionIndexTable = malloc((attributes->AttributeType.ExceptionsAttribute.numberOfExceptions) * sizeof(u2));

	// bloco que faz a leitura
	for (i = 0; i < attributes->AttributeType.ExceptionsAttribute.numberOfExceptions; i++) 
	{
		attributes->AttributeType.ExceptionsAttribute.exceptionIndexTable[i] = readU2(fp);
	}

}

// função que lê as informações de um attribute denominado InnerClasses
void readInnerClassesAttribute(FILE *fp, AttributeInfo *attributes)
{
	int i;

	// lê o número de inner classes
	attributes->AttributeType.InnerClassAttribute.numberOfClasses = readU2(fp);

	// aloca o espaço necessário
	attributes->AttributeType.InnerClassAttribute.classes = malloc((attributes->AttributeType.InnerClassAttribute.numberOfClasses) * sizeof(InnerClass));

	// lê as classes em si
	for (i = 0; i < attributes->AttributeType.InnerClassAttribute.numberOfClasses; i++) 
	{
		attributes->AttributeType.InnerClassAttribute.classes[i].innerClassInfoIndex = readU2(fp);
		attributes->AttributeType.InnerClassAttribute.classes[i].outerClassInfoIndex = readU2(fp);
		attributes->AttributeType.InnerClassAttribute.classes[i].innerNameIndex = readU2(fp);
		attributes->AttributeType.InnerClassAttribute.classes[i].innerClassAccessFlags = readU2(fp);
	}
}

// função que lê as informações de um attribute denominado SourceFile
void readSourceFileAttribute(FILE *fp, AttributeInfo *attributes)
{
	// lê o índice na pool de constantes
	attributes->AttributeType.SourceFileAttribute.sourceFileIndex = readU2(fp);
}

// função que lê um attribute não reconhecido por essa JVM
void readUnknownAttribute(FILE *fp, AttributeInfo *attributes)
{
	int i;

	// aloca o espaço necessário para esse attribute
	attributes->AttributeType.UnknownAttribute.info = malloc((attributes->attributeLength) * sizeof(u1));

	for (i = 0; i < attributes->attributeLength; i++) 
	{
		attributes->AttributeType.UnknownAttribute.info[i] = readU1(fp);
	}

}

// função que le as informações de um atributo
void readAttributes(ClassFile *class, FILE *fp, AttributeInfo *attributes)
{
	char attributeName[50];

	// lendo o indice da constant pool que contem o nome do atributo
	attributes->attributeNameIndex = readU2(fp);

	// lendo o tamanho do atributo
	attributes->attributeLength = readU4(fp);

	// pegando e copiando o nome do atributo obtido pela constant pool em attributeName
	strcpy(attributeName, (char*)class->constantPool[attributes->attributeNameIndex].info.Utf8Info.bytes);

	if (strcmp(attributeName, "ConstantValue") == 0) 
	{
		readConstantValueAttribute(fp, attributes);
	} 
	else if (strcmp(attributeName, "Code") == 0) 
	{
		readCodeAttribute(class, fp, attributes);
	} 
	else if (strcmp(attributeName, "Exceptions") == 0) 
	{
		readExceptionsAttribute(fp, attributes);
	} 
	else if (strcmp(attributeName, "InnerClasses") == 0) 
	{
		readInnerClassesAttribute(fp, attributes);
	} 
	else if (strcmp(attributeName, "Synthetic") == 0) 
	{
		// não faz nada, Synthetic não tem nenhuma informação extra a ser lida
	} 
	else if (strcmp(attributeName, "SourceFile") == 0) 
	{
		readSourceFileAttribute(fp, attributes);
	} 
	else {
		readUnknownAttribute(fp, attributes);
	}

}

void readFields(ClassFile *class, FILE *fp)
{
	int i;
	int j;

	// alocando espaço necessário
	class->fields = malloc(class->fieldsCount * sizeof(FieldInfo));

	for (i = 0; i < class->fieldsCount; i++) 
	{
		// lendo o nivel de acesso do field
		class->fields[i].accessFlags = readU2(fp);

		// lendo o indice de seu nome na constant pool
		class->fields[i].nameIndex = readU2(fp);

		// lendo o indice de sua descricao na constant pool
		class->fields[i].descriptorIndex = readU2(fp);

		// lendo o número de atributos que esse field contem
		class->fields[i].attributesCount = readU2(fp);

		// alocando o espaço necessário para os attributes a serem lidos
		class->fields[i].attributes = malloc((class->fields->attributesCount) * sizeof(AttributeInfo));

		// bloco que le os atributos da field
		// As field infos só possuem as seguintes attributeInfos: ConstantValue, Synthetic e Deprecated
		for (j = 0; j < class->fields->attributesCount; j++) 
		{
			readAttributes(class, fp, &(class->fields[i].attributes[j]));
		}
	}
}

void readMethods(ClassFile *class, FILE *fp)
{
	int i;
	int j;

	// alocando espaço necessário
	class->methods = malloc(class->methodsCount * sizeof(MethodInfo));

	// bloco que lê os métodos
	for (i = 0; i < class->methodsCount; i++) 
	{
		// lê os access flags
		class->methods[i].accessFlags = readU2(fp);

		// lê o índice da constant pool relativo ao nome do método
		class->methods[i].nameIndex = readU2(fp);

		// lê o índice da constant pool relativo à descrição do método (tipos de argumento e retorno)
		class->methods[i].descriptorIndex = readU2(fp);

		// lê o número de atributos do método
		class->methods[i].attributesCount = readU2(fp);

		// aloca o espaço necessário
		class->methods[i].attributes = malloc((class->methods[i].attributesCount) * sizeof(AttributeInfo));

		// lê os atributos do método. Só podem ser do tipo Code, Exceptions, Synthetic e Deprecated
		for (j = 0; j < class->methods[i].attributesCount; j++) 
		{
			readAttributes(class, fp, &(class->methods[i].attributes[j]));
		}
	}
}

ClassFile readClass(char *classpath)
{
	FILE *fp;
	ClassFile class;
	char className[100];
	int i;

	strcpy(className, classpath);

	if (strstr(classpath, ".class") == NULL ) 
	{
		strcat(className, ".class");
	}

	// abre o arquivo .class. Caso o arquivo não exista, aborta o programa.
	fp = fopen(className, "rb");
	if (fp == NULL ) 
	{
		printf("ERRO: nao foi possivel abrir o arquivo .class\n");
		exit(1);
	}

	// lendo o nro mágico 0xCAFEBABE. Caso esteja errado, abora o programa.
	class.magic = readU4(fp);
	if (class.magic != 0xCAFEBABE) 
	{
		printf("\nO numero magico nao e magico.");
		exit(1);
	}

	// lendo a minor version.
	class.minorVersion = readU2(fp);

	// lendo a major version.
	class.majorVersion = readU2(fp);

	// lendo o constant pool count
	class.constantPoolCount = readU2(fp);

	// lendo a constant pool
	readConstantPool(&class, fp);

	// lendo flags de acesso a classe (i.e. Public, Final, etc.)
	class.accessFlags = readU2(fp);

	// lendo uma entrada na constant pool que identifica a this class
	class.thisClass = readU2(fp);

	// lendo uma entrada na constant pool que identifica a super class
	class.superClass = readU2(fp);

	// lendo o número de interfaces da tabela a ser lida a seguir
	class.interfacesCount = readU2(fp);

	// lendo as interfaces
	readInterfaces(&class, fp);

	// lendo o número de fields da seguinte tabela
	class.fieldsCount = readU2(fp);

	// lendo os fields
	readFields(&class, fp);

	// lendo o número de métodos da classe
	class.methodsCount = readU2(fp);

	// lendo os métodos
	readMethods(&class, fp);

	// lendo o número de atributos da classe
	class.attributesCount = readU2(fp);

	// alocando o espaço necessário
	class.attributes = malloc((class.attributesCount) * sizeof(AttributeInfo));

	// lendo os atributos da classe
	// Podem ser somente dos tipos: SourceFile e Deprecated
	for (i = 0; i < class.attributesCount; i++) 
	{
		readAttributes(&class, fp, &(class.attributes[i]));
	}

	fclose(fp);

	return class;
}
