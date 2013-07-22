#include "ClassLoader.h"

/**
Vetor utilizado para pegar o nome das instrucoes para imprimir os mnemonicos do bytecode
*/
const char* instructionOpcode[202] =
{
	"nop", // 0x00
    "aconst_null",// 0x1
    "iconst_m1",// 0x2
    "iconst_0",// 0x3
    "iconst_1",// 0x4
    "iconst_2",// 0x5
    "iconst_3",// 0x6
    "iconst_4",// 0x7
    "iconst_5",// 0x8
    "lconst_0",// 0x9
    "lconst_1",// 0xA
    "fconst_0",// 0xB
    "fconst_1",// 0xC
    "fconst_2",// 0xD
    "dconst_0",// 0xE
    "dconst_1",// 0xF
    "bipush",// 0x10
    "sipush",// 0x11
    "ldc",// 0x12
    "ldc_w",// 0x13
    "ldc2_w",// 0x14
    "iload",// 0x15
    "lload",// 0x16
    "fload",// 0x17
    "dload",// 0x18
    "aload",// 0x19
    "iload_0",// 0x1A
    "iload_1",// 0x1B
    "iload_2",// 0x1C
    "iload_3",// 0x1D
    "lload_0",// 0x1E
    "lload_1",// 0x1F
    "lload_2",// 0x20
    "lload_3",// 0x21
    "fload_0",// 0x22
    "fload_1",// 0x23
    "fload_2",// 0x24
    "fload_3",// 0x25
    "dload_0",// 0x26
    "dload_1",// 0x27
    "dload_2",// 0x28
    "dload_3",// 0x29
    "aload_0",// 0x2A
    "aload_1",// 0x2B
    "aload_2",// 0x2C
    "aload_3",// 0x2D
    "iaload",// 0x2E
    "laload",// 0x2F
    "faload",// 0x30
    "daload",// 0x31
    "aaload",// 0x32
    "iaload",// 0x33
    "iaload",// 0x34
    "iaload",// 0x35
    "istore",// 0x36
    "lstore",// 0x37
    "fstore",// 0x38
    "dstore",// 0x39
    "astore",// 0x3A
    "istore_0",// 0x3B
    "istore_1",// 0x3C
    "istore_2",// 0x3D
    "istore_3",// 0x3E
    "lstore_0",// 0x3F
    "lstore_1",// 0x40
    "lstore_2",// 0x41
    "lstore_3",// 0x42
    "fstore_0",// 0x43
    "fstore_1",// 0x44
    "fstore_2",// 0x45
    "fstore_3",// 0x46
    "dstore_0",// 0x47
    "dstore_1",// 0x48
    "dstore_2",// 0x49
    "dstore_3",// 0x4A
    "astore_0",// 0x4B
    "astore_1",// 0x4C
    "astore_2",// 0x4D
    "astore_3",// 0x4E
    "iastore",// 0x4F
    "lastore",// 0x50
    "fastore",// 0x51
    "dastore",// 0x52
    "aastore",// 0x53
    "iastore",// 0x54
    "iastore",// 0x55
    "iastore",// 0x56
    "pop",// 0x57
    "pop2",// 0x58
    "dup",//0x59
    "dup_x1",//0x5A
    "dup_x2",//0x5B
    "dup2",// 0x5C
    "dup2_x1",// 0x5D
    "dup2_x2",// 0x5E
    "swap",// 0x5F
    "iadd",// 0x60
    "ladd",// 0x61
    "fadd",// 0x62
    "dadd",// 0x63
    "isub",// 0x64
    "lsub",// 0x65
    "fsub",// 0x66
    "dsub",// 0x67
    "imul",// 0x68
    "lmul",// 0x69
    "fmul",// 0x6A
    "dmul",// 0x6B
    "idiv",// 0x6C
    "ldiv",// 0x6D
    "fdiv",// 0x6E
    "ddiv",// 0x6F
    "irem",// 0x70
    "lrem",// 0x71
    "frem",// 0x72
    "drem",// 0x73
    "ineg",// 0x74
    "lneg",// 0x75
    "fneg",// 0x76
    "dneg",// 0x77
    "ishl",// 0x78
    "lshl",// 0x79
    "ishr",// 0x7A
    "lshr",// 0x7B
    "iushr",// 0x7C
    "lushr",// 0x7D
    "iand",// 0x7E
    "land",// 0x7F
    "ior",// 0x80
    "lor",// 0x81
    "ixor",// 0x82
    "lxor",// 0x83
    "iinc",// 0x84
    "i2l",// 0x85
    "i2f",// 0x86
    "i2d",// 0x87
    "l2i",// 0x88
    "l2f",// 0x89
    "l2d",// 0x8A
    "f2i",// 0x8B
    "f2l",// 0x8C
    "f2d",// 0x8D
    "d2i",// 0x8E
    "d2l",// 0x8F
    "d2f",// 0x90
    "i2c",// 0x91
    "i2c",// 0x92
    "i2s",// 0x93
    "lcmp",// 0x94
    "fcmpl",// 0x95
    "fcmpg",// 0x96
    "dcmpl",// 0x97
    "dcmpg",// 0x98
    "ifeq",// 0x99
    "ifne",// 0x9A
    "iflt",// 0x9B
    "ifge",// 0x9C
    "ifgt",// 0x9D
    "ifle",// 0x9E
    "if_icmpeq",// 0x9F
    "if_icmpne",// 0xA0
    "if_icmplt",// 0xA1
    "if_icmpge",// 0xA2
    "if_icmpgt",// 0xA3
    "if_icmple",// 0xA4
    "if_acmpeq",// 0XA5
    "if_acmpne",// 0xA6
    "goto_",// 0xA7
    "jsr",// 0xA8
    "ret",// 0xA9
    "tableswitch",// 0xAA
    "lookupswitch",// 0xAB
    "ireturn",// 0xAC
    "lreturn",// 0xAD
    "freturn",// 0xAE
    "dreturn",// 0xAF
    "areturn",// 0xB0
    "return_",// 0xB1
    "getstatic",// 0xB2
    "putstatic",// 0xB3
    "getfield",// 0xB4
    "putfield",// 0xB5
    "invokevirtual",// 0xB6
    "invokespecial",// 0xB7
    "invokestatic",// 0xB8
    "invokeinterface",// 0xB9
    "invokedynamic",// 0xBA
    "new",// 0xBB
    "newarray",// 0xBC
    "anewarray",// 0xBD
    "arraylength",// 0xBE
    "athrow",//athrow",// 0xBF
    "checkcast",// 0xC0
    "instanceof",// 0xC1
    "monitorenter",// 0xC2
    "monitorexit",// 0xC3
    "wide",// 0xC4
    "multianewarray",// 0xC5
    "ifnull",// 0xC6
    "ifnonnull",// 0xC7
    "goto_w",// 0xC8
    "jsr_w"// 0xC9
};

/**
A funcao faz a leitura do arquivo de forma a retornar um u1
*/
u1 readU1(FILE *fp)
{
	u1 u1Read;

	fread(&u1Read, sizeof(u1), 1, fp);
	return u1Read;
}

/**
A funcao faz a leitura do arquivo de forma a retornar um u2
*/
u2 readU2(FILE *fp)
{
	u1 aux1, aux2;
	u2 u2Read;

    fread(&aux1, sizeof(u1), 1, fp);
    fread(&aux2, sizeof(u1), 1, fp);

    u2Read = (aux1 << 8) | aux2;

    return u2Read;
}

/**
A funcao faz a leitura do arquivo de forma a retornar um u4
*/
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

/**
A funcao faz a leitura do atributo do tipo ConstantValue classfile
*/
void readConstantValueAttribute(FILE *fp, AttributeInfo *attributes)
{
	attributes->AttributeType.ConstantValueAttribute.constantValueIndex = readU2(fp);
}

/**
A funcao faz a leitura da tabela de excecoes classfile
*/
void readExceptionTable(FILE *fp, ExceptionTable *exceptionTable)
{
	exceptionTable->startPc = readU2(fp);
	exceptionTable->endPc = readU2(fp);
	exceptionTable->handlerPc = readU2(fp);
	exceptionTable->catchType = readU2(fp);
}

/**
A funcao faz a leitura do atributo do tipo Code classfile
*/
void readCodeAttribute(ClassFile* class, FILE *fp, AttributeInfo *attributes)
{
	int i;

	attributes->AttributeType.CodeAttribute.maxStack = readU2(fp);
	attributes->AttributeType.CodeAttribute.maxLocals = readU2(fp);
	attributes->AttributeType.CodeAttribute.codeLength = readU4(fp);
	attributes->AttributeType.CodeAttribute.code = malloc((attributes->AttributeType.CodeAttribute.codeLength) * sizeof(u1));
	for(i = 0; i < attributes->AttributeType.CodeAttribute.codeLength; i++)
	{
		attributes->AttributeType.CodeAttribute.code[i] = readU1(fp);
	}
	attributes->AttributeType.CodeAttribute.exceptionTableLength = readU2(fp);
	attributes->AttributeType.CodeAttribute.exceptionTable = malloc((attributes->AttributeType.CodeAttribute.exceptionTableLength) * sizeof(ExceptionTable));
	for(i = 0; i < attributes->AttributeType.CodeAttribute.exceptionTableLength; i++)
	{
		readExceptionTable(fp, &(attributes->AttributeType.CodeAttribute.exceptionTable[i]));
	}
	attributes->AttributeType.CodeAttribute.attributesCount = readU2(fp);
	attributes->AttributeType.CodeAttribute.attributes = malloc((attributes->AttributeType.CodeAttribute.attributesCount) * sizeof(AttributeInfo));
	for(i = 0; i < attributes->AttributeType.CodeAttribute.attributesCount; i++)
	{
		readAttribute(class, fp, &(attributes->AttributeType.CodeAttribute.attributes[i]));
	}
}

/**
A funcao faz a leitura do atributo do tipo Exception classfile
*/
void readExceptionsAttribute(FILE *fp, AttributeInfo *attributes)
{
	int i;

	attributes->AttributeType.ExceptionsAttribute.numberOfExceptions = readU2(fp);

	attributes->AttributeType.ExceptionsAttribute.exceptionIndexTable = malloc(attributes->AttributeType.ExceptionsAttribute.numberOfExceptions * sizeof(u2));
	for(i = 0; i < attributes->AttributeType.ExceptionsAttribute.numberOfExceptions; i++)
	{
		attributes->AttributeType.ExceptionsAttribute.exceptionIndexTable[i] = readU2(fp);
	}
}

/**
A funcao faz a leitura do atributo do tipo InnerClasses classfile
*/
void readInnerClassesAttribute(FILE *fp, AttributeInfo *attributes)
{
	int i;

	attributes->AttributeType.InnerClassAttribute.numberOfClasses = readU2(fp);
	attributes->AttributeType.InnerClassAttribute.classes = malloc((attributes->AttributeType.InnerClassAttribute.numberOfClasses) * sizeof(InnerClass));
	for(i = 0; i < attributes->AttributeType.InnerClassAttribute.numberOfClasses; i++)
	{
		attributes->AttributeType.InnerClassAttribute.classes[i].innerClassInfoIndex = readU2(fp);
		attributes->AttributeType.InnerClassAttribute.classes[i].outerClassInfoIndex = readU2(fp);
		attributes->AttributeType.InnerClassAttribute.classes[i].innerNameIndex = readU2(fp);
		attributes->AttributeType.InnerClassAttribute.classes[i].innerClassAccessFlags= readU2(fp);
	}
}

/**
A funcao faz a leitura do atributo do tipo SourceFile classfile
*/
void readSourceFileAttribute(FILE *fp, AttributeInfo *attributes)
{
	attributes->AttributeType.SourceFileAttribute.sourceFileIndex = readU2(fp);
}

/**
A funcao faz a leitura do atributo do tipo LineNumberTable classfile
*/
void readLineNumberTableAttribute(FILE *fp, AttributeInfo *attributes)
{
	int i;

	attributes->AttributeType.LineNumberTableAttribute.lineNumberTableLength = readU2(fp);
	attributes->AttributeType.LineNumberTableAttribute.lineNumberTable = malloc((attributes->AttributeType.LineNumberTableAttribute.lineNumberTableLength) * sizeof(LineNumberTable));
	for(i = 0; i < attributes->AttributeType.LineNumberTableAttribute.lineNumberTableLength; i++)
	{
		attributes->AttributeType.LineNumberTableAttribute.lineNumberTable[i].startPc = readU2(fp);
		attributes->AttributeType.LineNumberTableAttribute.lineNumberTable[i].lineNumber = readU2(fp);
	}
}

/**
A funcao faz a leitura de algum possivel atributo nao determinado no classfile
*/
void readUnknownAttribute(FILE *fp, AttributeInfo *attributes)
{
		int i;

		attributes->AttributeType.UnknownAttribute.info = malloc((attributes->attributeLength) * sizeof(u1));

		for (i = 0; i < attributes->attributeLength; i++)
		{
			attributes->AttributeType.UnknownAttribute.info[i] = readU1(fp);
		}
}

/**
A funcao faz a leitura das contantes do constantpool do classfile
*/
void readConstantPool(ClassFile* class, FILE *fp)
{
	int i;
	int j;

	class->constantPool = (CpInfo*)calloc(class->constantPoolCount, sizeof(CpInfo));
	for(i = 1; i < class->constantPoolCount; i++)
	{
		class->constantPool[i].tag = readU1(fp);

		switch(class->constantPool[i].tag)
		{
			case CONSTANT_Class:
				class->constantPool[i].info.ClassInfo.nameIndex = readU2(fp);
				break;
			case CONSTANT_Fieldref:
					class->constantPool[i].info.FieldrefInfo.classIndex = readU2(fp);
					class->constantPool[i].info.FieldrefInfo.nameAndTypeIndex = readU2(fp);
				break;
			case CONSTANT_Methodfef:
					class->constantPool[i].info.MethodrefInfo.classIndex = readU2(fp);
					class->constantPool[i].info.MethodrefInfo.nameAndTypeIndex = readU2(fp);
				break;
			case CONSTANT_InterfaceMethodref:
					class->constantPool[i].info.InterfaceMethodrefInfo.classIndex = readU2(fp);
					class->constantPool[i].info.InterfaceMethodrefInfo.nameAndTypeIndex = readU2(fp);
				break;
			case CONSTANT_String:
					class->constantPool[i].info.StringInfo.stringIndex = readU2(fp);
				break;
			case CONSTANT_Integer:
					class->constantPool[i].info.IntegerInfo.bytes = readU4(fp);
				break;
			case CONSTANT_Float:
					class->constantPool[i].info.FloatInfo.bytes = readU4(fp);
				break;
			case CONSTANT_Long:
					class->constantPool[i].info.LongInfo.highBytes = readU4(fp);
					class->constantPool[i].info.LongInfo.lowBytes = readU4(fp);
				break;
			case CONSTANT_Double:
					class->constantPool[i].info.DoubleInfo.highBytes = readU4(fp);
					class->constantPool[i].info.DoubleInfo.lowBytes = readU4(fp);
					i++;
				break;
			case CONSTANT_NameAndType:
					class->constantPool[i].info.NameAndTypeInfo.nameIndex = readU2(fp);
					class->constantPool[i].info.NameAndTypeInfo.descriptorIndex = readU2(fp);
				break;
			case CONSTANT_Utf8:
					class->constantPool[i].info.Utf8Info.length = readU2(fp);
					class->constantPool[i].info.Utf8Info.bytes = malloc(class->constantPool[i].info.Utf8Info.length * sizeof(char) + 1);
					for(j = 0; j < class->constantPool[i].info.Utf8Info.length; j++)
					{
						class->constantPool[i].info.Utf8Info.bytes[j] = readU1(fp);
					}
					class->constantPool[i].info.Utf8Info.bytes[class->constantPool[i].info.Utf8Info.length] = '\0';
				break;
		}
	}
}

/**
A funcao faz a leitura das interfaces do classfile
*/
void readInterfaces(ClassFile* class, FILE *fp)
{
	int i;

	class->interfaces = (u2*)calloc(class->interfacesCount, sizeof(u2));
	for(i = 0; i < class->interfacesCount; i++)
	{
		class->interfaces[i] = readU2(fp);
	}
}

/**
A funcao faz a leitura dos attributos do classfile
*/
void readAttribute(ClassFile *class, FILE *fp, AttributeInfo *attributes)
{
	char* attributeName;

	attributes->attributeNameIndex = readU2(fp);
	attributes->attributeLength = readU4(fp);

	attributeName = malloc((class->constantPool[attributes->attributeNameIndex].info.Utf8Info.length) * sizeof(char) + 1);

	strcpy(attributeName, (char*)class->constantPool[attributes->attributeNameIndex].info.Utf8Info.bytes);
	attributeName[class->constantPool[attributes->attributeNameIndex].info.Utf8Info.length] = '\0';

	if(strcmp(attributeName, "ConstantValue") == 0)
	{
		readConstantValueAttribute(fp, attributes);
	}
	else if(strcmp(attributeName, "Code") == 0)
	{
		readCodeAttribute(class, fp, attributes);
	}
	else if(strcmp(attributeName, "Exceptions") == 0)
	{
		readExceptionsAttribute(fp, attributes);
	}
	else if(strcmp(attributeName, "InnerClasses") == 0)
	{
		readInnerClassesAttribute(fp, attributes);
	}
	else if(strcmp(attributeName, "SourceFile") == 0)
	{
		readSourceFileAttribute(fp, attributes);
	}
	else if(strcmp(attributeName, "LineNumberTable") == 0)
	{
		readLineNumberTableAttribute(fp, attributes);
	}
	else
	{
		readUnknownAttribute(fp, attributes);
	}
}

/**
A funcao faz a leitura dos campos do classfile
*/
void readFields(ClassFile* class, FILE *fp)
{
	int i;
	int j;

	class->fields = (FieldInfo*)calloc(class->fieldsCount, sizeof(FieldInfo));
	for(i = 0; i < class->fieldsCount; i++)
	{
		class->fields[i].accessFlags = readU2(fp);
		class->fields[i].nameIndex = readU2(fp);
		class->fields[i].descriptorIndex = readU2(fp);
		class->fields[i].attributesCount = readU2(fp);
		for(j = 0; j < class->fields[i].attributesCount; j++)
		{
			readAttribute(class, fp, &(class->fields[i].attributes[j]));
		}
	}

}

/**
A funcao faz a leitura dos metodos do classfile
*/
void readMethods(ClassFile* class, FILE *fp)
{
	int i;
	int j;

	class->methods = malloc(class->methodsCount * sizeof(MethodInfo));
	for(i = 0; i < class->methodsCount; i++)
	{
		class->methods[i].accessFlags = readU2(fp);
		class->methods[i].nameIndex = readU2(fp);
		class->methods[i].descriptorIndex = readU2(fp);
		class->methods[i].attributesCount = readU2(fp);
		class->methods[i].attributes = malloc((class->methods[i].attributesCount) * sizeof(AttributeInfo));
		for(j = 0; j < class->methods[i].attributesCount; j++)
		{
			readAttribute(class, fp, &(class->methods[i].attributes[j]));
		}
	}

}

/**
A funcao faz a leitura de um arquivo .class e armazena as informacoes em uma estrutura de classfile.
Algumas leituras sao feitas diretamente nela e outras sao feitas dentro de algumas funcoes que ela chama
*/
ClassFile* readClass(char *classpath)
{
	ClassFile *class;
	FILE *fp;
	int i;
	char *filepath;

	fp = fopen(classpath, "rb");
	if(fp == NULL)
	{
		printf("ERRO: nao foi possivel abrir o arquivo .class\n");
		exit(1);
	}

	class = (ClassFile*)malloc(sizeof(ClassFile));
	class->magic = readU4(fp);
	if((class->magic != 0xcafebabe) || (class->magic != 0xCAFEBABE))
	{
		printf("ERRO: assinatura do arquivo .class incorreta\n");
		exit(1);
	}

	class->minorVersion = readU2(fp);
	class->majorVersion = readU2(fp);
	/*if ((class->minorVersion != 0) || (class->majorVersion > 46))
	{
        printf("ERRO: versao do arquivo nao suportada\n");
		exit(1);
	}*/
	class->constantPoolCount = readU2(fp);
	readConstantPool(class, fp);
	class->accessFlags = readU2(fp);
	class->thisClass = readU2(fp);
	filepath = malloc(sizeof(char)*strlen(classpath) + 1);
	strcpy(filepath, classpath);
	/*if(strcmp((char*)class->constantPool[class->constantPool[class->thisClass].info.ClassInfo.nameIndex].info.Utf8Info.bytes, getClassName(filepath)) != 0)
	{
		printf("ERRO: arquivo com nome diferente\n");
		exit(1);
	}*/
	class->superClass = readU2(fp);
	class->interfacesCount = readU2(fp);
	readInterfaces(class, fp);
	class->fieldsCount = readU2(fp);
	readFields(class, fp);
	class->methodsCount = readU2(fp);
	readMethods(class, fp);
	class->attributesCount = readU2(fp);
	class->attributes = malloc((class->attributesCount) * sizeof(AttributeInfo));
	for(i = 0; i < class->attributesCount; i++)
	{
		readAttribute(class, fp, &(class->attributes[i]));
	}

	fclose(fp);

	return class;
}

/**
A funcao imprime no arquivo as informacoes gerais do classfile
*/
void printGeneralInformations(ClassFile* class, FILE *fp)
{
	fprintf(fp, "=== GENERAL INFORMATION ===\n\n");
	fprintf(fp, "Magic: %#X\n", class->magic);
	fprintf(fp, "Minor Version: %hu\n", class->minorVersion);
	fprintf(fp, "Major Version: %hu\n", class->majorVersion);
	fprintf(fp, "Constant Pool Count: %hu\n", class->constantPoolCount);
	fprintf(fp, "Access Flags: %#06X\n", class->accessFlags);
	fprintf(fp, "This Class: cp_info #%hu <%s>\n", class->thisClass, class->constantPool[class->constantPool[class->thisClass].info.ClassInfo.nameIndex].info.Utf8Info.bytes);
	fprintf(fp, "Super Class: cp_info #%hu <%s>\n", class->superClass, class->constantPool[class->constantPool[class->superClass].info.ClassInfo.nameIndex].info.Utf8Info.bytes);
	fprintf(fp, "Interfaces Count:%hu\n", class->interfacesCount);
	fprintf(fp, "Fields Count:%hu\n", class->fieldsCount);
	fprintf(fp, "Methods Count:%hu\n", class->methodsCount);
	fprintf(fp, "Attributes Count:%hu\n", class->attributesCount);
}

/**
A funcao imprime no arquivo as constantes do constantpool do classfile
*/
void printConstantPool(ClassFile* class, FILE *fp)
{
	int i;

	fprintf(fp, "\n\n=== CONSTANT POOL ===\n\n");
	for(i = 1; i < class->constantPoolCount; i++)
	{
		switch(class->constantPool[i].tag)
		{
			case 7:
				fprintf(fp, "[%d] CONSTANT_Class\n", i);
				fprintf(fp, "\tClass name: cp_info #%hu <%s>\n", class->constantPool[i].info.ClassInfo.nameIndex, class->constantPool[class->constantPool[i].info.ClassInfo.nameIndex].info.Utf8Info.bytes);
				break;
			case 9:
				fprintf(fp, "[%d] CONSTANT_Fieldref\n", i);
				fprintf(fp, "\tClass name: cp_info #%hu <%s>\n", class->constantPool[i].info.FieldrefInfo.classIndex, class->constantPool[class->constantPool[class->constantPool[i].info.FieldrefInfo.classIndex].info.ClassInfo.nameIndex].info.Utf8Info.bytes);
				fprintf(fp, "\tName and Type: cp_info #%hu <%s%s>\n", class->constantPool[i].info.FieldrefInfo.nameAndTypeIndex, class->constantPool[class->constantPool[class->constantPool[i].info.FieldrefInfo.nameAndTypeIndex].info.NameAndTypeInfo.nameIndex].info.Utf8Info.bytes, class->constantPool[class->constantPool[class->constantPool[i].info.FieldrefInfo.nameAndTypeIndex].info.NameAndTypeInfo.descriptorIndex].info.Utf8Info.bytes);
				break;
			case 10:
				fprintf(fp, "[%d] CONSTANT_Methodref\n", i);
				fprintf(fp, "\tClass name: cp_info #%hu <%s>\n", class->constantPool[i].info.MethodrefInfo.classIndex, class->constantPool[class->constantPool[class->constantPool[i].info.MethodrefInfo.classIndex].info.ClassInfo.nameIndex].info.Utf8Info.bytes);
				fprintf(fp, "\tName and Type: cp_info #%hu <%s%s>\n", class->constantPool[i].info.MethodrefInfo.nameAndTypeIndex, class->constantPool[class->constantPool[class->constantPool[i].info.MethodrefInfo.nameAndTypeIndex].info.NameAndTypeInfo.nameIndex].info.Utf8Info.bytes, class->constantPool[class->constantPool[class->constantPool[i].info.MethodrefInfo.nameAndTypeIndex].info.NameAndTypeInfo.descriptorIndex].info.Utf8Info.bytes);
				break;
			case 11:
				fprintf(fp, "[%d] CONSTANT_InterfaceMethodref\n", i);
				fprintf(fp, "\tClass name: cp_info #%hu <%s>\n", class->constantPool[i].info.InterfaceMethodrefInfo.classIndex, class->constantPool[class->constantPool[class->constantPool[i].info.InterfaceMethodrefInfo.classIndex].info.ClassInfo.nameIndex].info.Utf8Info.bytes);
				fprintf(fp, "\tName and Type: cp_info #%hu <%s%s>\n", class->constantPool[i].info.InterfaceMethodrefInfo.nameAndTypeIndex, class->constantPool[class->constantPool[class->constantPool[i].info.InterfaceMethodrefInfo.nameAndTypeIndex].info.NameAndTypeInfo.nameIndex].info.Utf8Info.bytes, class->constantPool[class->constantPool[class->constantPool[i].info.InterfaceMethodrefInfo.nameAndTypeIndex].info.NameAndTypeInfo.descriptorIndex].info.Utf8Info.bytes);
				break;
			case 8:
				fprintf(fp, "[%d] CONSTANT_String\n", i);
				fprintf(fp, "\tString: cp_info #%hu <%s>\n", class->constantPool[i].info.StringInfo.stringIndex, class->constantPool[class->constantPool[i].info.StringInfo.stringIndex].info.Utf8Info.bytes);
				break;
			case 3:
				fprintf(fp, "[%d] CONSTANT_Integer\n", i);
				fprintf(fp, "\tBytes: %#06X\n", class->constantPool[i].info.IntegerInfo.bytes);
				fprintf(fp, "\tInteger: %d\n", class->constantPool[i].info.IntegerInfo.bytes);
				break;
			case 4:
				fprintf(fp, "[%d] CONSTANT_Float\n", i);
				fprintf(fp, "\tBytes: %#08X\n", class->constantPool[i].info.FloatInfo.bytes);
				fprintf(fp, "\tFloat: %.1f\n", convertU4ToFloat(class->constantPool[i].info.FloatInfo.bytes));
				break;
			case 5:
				fprintf(fp, "[%d] CONSTANT_Long\n", i);
				fprintf(fp, "\tHigh Bytes: %#08X\n", class->constantPool[i].info.LongInfo.highBytes);
				fprintf(fp, "\tLow Bytes: %#08X\n", class->constantPool[i].info.LongInfo.lowBytes);
				break;
			case 6:
				fprintf(fp, "[%d] CONSTANT_Double\n", i);
				fprintf(fp, "\tHigh Bytes: %#08X\n", class->constantPool[i].info.DoubleInfo.highBytes);
				fprintf(fp, "\tLow Bytes: %#08X\n", class->constantPool[i].info.DoubleInfo.lowBytes);
				break;
			case 12:
				fprintf(fp, "[%d] CONSTANT_NameAndType\n", i);
				fprintf(fp, "\tName: cp_info #%hu <%s>\n", class->constantPool[i].info.NameAndTypeInfo.nameIndex, class->constantPool[class->constantPool[i].info.NameAndTypeInfo.nameIndex].info.Utf8Info.bytes);
				fprintf(fp, "\tDescriptor: cp_info #%hu <%s>\n", class->constantPool[i].info.NameAndTypeInfo.descriptorIndex, class->constantPool[class->constantPool[i].info.NameAndTypeInfo.descriptorIndex].info.Utf8Info.bytes);
				break;
			case 1:
				fprintf(fp, "[%d] CONSTANT_Utf8\n", i);
				fprintf(fp, "\tLength of byte array: %hu\n", class->constantPool[i].info.Utf8Info.length);
				fprintf(fp, "\tLength of string: %hu\n", class->constantPool[i].info.Utf8Info.length);
				fprintf(fp, "\tString: %s\n", class->constantPool[i].info.Utf8Info.bytes);
				break;
		}
	}
}

/**
A funcao imprime no arquivo as interfaces do classfile
*/
void printInterfaces(ClassFile* class, FILE *fp)
{
	int i;

	fprintf(fp, "\n\n=== INTERFACES ===\n\n");
	for(i = 0; i < class->interfacesCount; i++)
	{
		fprintf(fp, "Interface %d\n", i);
		fprintf(fp, "\tInterface cp_info #%hu <%s>\n", class->interfaces[i], class->constantPool[class->constantPool[class->interfaces[i]].info.ClassInfo.nameIndex].info.Utf8Info.bytes);
	}
}

/**
A funcao imprime no arquivo os campos do classfile
*/
void printFields(ClassFile* class, FILE *fp)
{
	int i;

	fprintf(fp, "\n\n=== FIELDS ===\n\n");
	for(i = 0; i < class->fieldsCount; i++)
	{
		fprintf(fp, "[%d] %s\n", i, class->constantPool[class->fields[i].nameIndex].info.Utf8Info.bytes);
		fprintf(fp, "\tName: cp_info #%hu <%s>\n", class->fields[i].nameIndex, class->constantPool[class->fields[i].nameIndex].info.Utf8Info.bytes);
		fprintf(fp, "\tDescriptor: cp_info #%hu <%s>\n", class->fields[i].descriptorIndex, class->constantPool[class->fields[i].descriptorIndex].info.Utf8Info.bytes);
		fprintf(fp, "\tAccess Flags: %#06X ", class->fields[i].accessFlags);
		if(class->fields[i].accessFlags == 0x0001)
		{
			fprintf(fp, "[public]\n");
		}
		else if(class->fields[i].accessFlags == 0x0002)
		{
			fprintf(fp, "[private]\n");
		}
		else if(class->fields[i].accessFlags == 0x0004)
		{
			fprintf(fp, "[protected]\n");
		}
		else if(class->fields[i].accessFlags == 0x0008)
		{
			fprintf(fp, "[static]\n");
		}
		else if(class->fields[i].accessFlags == 0x0010)
		{
			fprintf(fp, "[final]\n");
		}
		else if(class->fields[i].accessFlags == 0x0040)
		{
			fprintf(fp, "[volatile]\n");
		}
		else if(class->fields[i].accessFlags == 0x0080)
		{
			fprintf(fp, "[transient]\n");
		}
	}
}

/**
A funcao imprime no arquivo os metodos do classfile
*/
void printMethods(ClassFile* class, FILE *fp)
{
	int i;
	int j;
	int k;
	int l;
	int auxOpcode;

	fprintf(fp, "\n\n=== METHODS ===\n\n");
	for(i = 0; i < class->methodsCount; i++)
	{
		fprintf(fp, "[%d] %s\n", i, class->constantPool[class->methods[i].nameIndex].info.Utf8Info.bytes);
		fprintf(fp, "\tName: cp_info #%d <%s>\n", class->methods[i].nameIndex, class->constantPool[class->methods[i].nameIndex].info.Utf8Info.bytes);
		fprintf(fp, "\tDescriptor: cp_info #%d <%s>\n", class->methods[i].nameIndex, class->constantPool[class->methods[i].descriptorIndex].info.Utf8Info.bytes);
		fprintf(fp, "\tAccess Flags: %#06X ", class->fields[i].accessFlags);
		if(class->methods[i].accessFlags == 0x0001)
		{
			fprintf(fp, "[public]\n");
		}
		else if(class->methods[i].accessFlags == 0x0002)
		{
			fprintf(fp, "[private]\n");
		}
		else if(class->methods[i].accessFlags == 0x0004)
		{
			fprintf(fp, "[protected]\n");
		}
		else if(class->methods[i].accessFlags == 0x0008)
		{
			fprintf(fp, "[static]\n");
		}
		else if(class->methods[i].accessFlags == 0x0010)
		{
			fprintf(fp, "[final]\n");
		}
		else if(class->methods[i].accessFlags == 0x0040)
		{
			fprintf(fp, "[volatile]\n");
		}
		else if(class->methods[i].accessFlags == 0x0080)
		{
			fprintf(fp, "[transient]\n");
		}
		for(j = 0; j < class->methods[i].attributesCount; j++)
		{
			fprintf(fp, "\t[%d] %s\n", j, class->constantPool[class->methods[i].attributes[j].attributeNameIndex].info.Utf8Info.bytes);
			fprintf(fp, "\t\tGeneric info:\n");
			fprintf(fp, "\t\t\tAttribute name index: cp_info #%hu\n", class->methods[i].attributes[j].attributeNameIndex);
			fprintf(fp, "\t\t\tAttribute length: %d\n", class->methods[i].attributes[j].attributeLength);
			fprintf(fp, "\t\tSpecific info:\n");
			if(strcmp("Code", (char*)class->constantPool[class->methods[i].attributes[j].attributeNameIndex].info.Utf8Info.bytes) == 0)
			{
				fprintf(fp, "\t\t\tBytecode:\n");
				for(k = 0; k < class->methods[i].attributes[j].AttributeType.CodeAttribute.codeLength; k++, class->methods[i].attributes[j].AttributeType.CodeAttribute.code++)
				{
					fprintf(fp, "\t\t\t\t%d %s\n", k, instructionOpcode[*class->methods[i].attributes[j].AttributeType.CodeAttribute.code]);
					auxOpcode = *class->methods[i].attributes[j].AttributeType.CodeAttribute.code;
					if((auxOpcode == 0xbc) ||
						(auxOpcode == 0x10) ||
						(auxOpcode == 0x12) ||
						(auxOpcode == 0x15) ||
						(auxOpcode == 0x16) ||
						(auxOpcode == 0x17) ||
						(auxOpcode == 0x18) ||
						(auxOpcode == 0x19) ||
						(auxOpcode == 0x36) ||
						(auxOpcode == 0x37) ||
						(auxOpcode == 0x38) ||
						(auxOpcode == 0x39) ||
						(auxOpcode == 0x3a) ||
						(auxOpcode == 0xa9))
					{
						k++;
						class->methods[i].attributes[j].AttributeType.CodeAttribute.code++;
					}
					else if(((auxOpcode >= 0x99) && (auxOpcode <= 0xa8)) ||
						(auxOpcode == 0xc6) ||
						(auxOpcode == 0xc7) ||
						(auxOpcode == 0x11) ||
						(auxOpcode == 0x84) ||
						(auxOpcode == 0xb2) ||
						(auxOpcode == 0xb4) ||
						(auxOpcode == 0x13) ||
						(auxOpcode == 0x14) ||
						(auxOpcode == 0xb3) ||
						(auxOpcode == 0xb5) ||
						(auxOpcode == 0xb6) ||
						(auxOpcode == 0xb7) ||
						(auxOpcode == 0xb8) ||
						(auxOpcode == 0xbb) ||
						(auxOpcode == 0xbd) ||
						(auxOpcode == 0xc0) ||
						(auxOpcode == 0xc1))
					{
						k = k + 2;
						class->methods[i].attributes[j].AttributeType.CodeAttribute.code++;
						class->methods[i].attributes[j].AttributeType.CodeAttribute.code++;
					}
					else if((auxOpcode == 0xc4) || (auxOpcode == 0xc5))
					{
						k = k + 3;
						class->methods[i].attributes[j].AttributeType.CodeAttribute.code++;
						class->methods[i].attributes[j].AttributeType.CodeAttribute.code++;
						class->methods[i].attributes[j].AttributeType.CodeAttribute.code++;
					}
					else if((auxOpcode == 0xab) ||
						(auxOpcode == 0xaa) ||
						(auxOpcode == 0xc8) ||
						(auxOpcode == 0xc9) ||
						(auxOpcode == 0xba) ||
						(auxOpcode == 0xb9))
					{
						k = k + 4;
						class->methods[i].attributes[j].AttributeType.CodeAttribute.code++;
						class->methods[i].attributes[j].AttributeType.CodeAttribute.code++;
						class->methods[i].attributes[j].AttributeType.CodeAttribute.code++;
					}
				}
				fprintf(fp, "\t\t\tMisc:\n");
				fprintf(fp, "\t\t\t\tMaximum stack deph: %d\n", class->methods[i].attributes[j].AttributeType.CodeAttribute.maxStack);
				fprintf(fp, "\t\t\t\tMaximum local variables: %d\n", class->methods[i].attributes[j].AttributeType.CodeAttribute.maxLocals);
				fprintf(fp, "\t\t\t\tCode length: %d\n", class->methods[i].attributes[j].AttributeType.CodeAttribute.codeLength);
				for(k = 0; k < class->methods[i].attributes[j].AttributeType.CodeAttribute.attributesCount; k++)
				{
					if(strcmp("LineNumberTable", (char*)class->constantPool[class->methods[i].attributes[j].AttributeType.CodeAttribute.attributes[k].attributeNameIndex].info.Utf8Info.bytes) == 0)
					{
						fprintf(fp, "\t\t[%d]Line number tables:\n", k);
						fprintf(fp, "\t\t\tGeneric info:\n");
						fprintf(fp, "\t\t\t\tAttribute name index: cp_info #%hu\n", class->methods[i].attributes[j].AttributeType.CodeAttribute.attributes[k].attributeNameIndex);
						fprintf(fp, "\t\t\t\tAttribute length: %d\n", class->methods[i].attributes[j].AttributeType.CodeAttribute.attributes[k].attributeLength);
						fprintf(fp, "\t\t\tSpecefic info:\n");
						fprintf(fp, "\t\t\t\tNr.\t\t\tstart_pc\t\tline_number\n");
						for(l = 0; l < class->methods[i].attributes[j].AttributeType.CodeAttribute.attributes[k].AttributeType.LineNumberTableAttribute.lineNumberTableLength; l++)
						{
							fprintf(fp, "\t\t\t\t%d", l);
							fprintf(fp, "\t\t\t%d", class->methods[i].attributes[j].AttributeType.CodeAttribute.attributes[k].AttributeType.LineNumberTableAttribute.lineNumberTable[l].startPc);
							fprintf(fp, "\t\t\t\t%d\n", class->methods[i].attributes[j].AttributeType.CodeAttribute.attributes[k].AttributeType.LineNumberTableAttribute.lineNumberTable[l].lineNumber);
						}
					}
				}
			}
		}
	}

}

/**
A funcao imprime no arquivo os atributos do classfile
*/
void printAttributes(ClassFile* class, FILE *fp)
{
	int i;
	int k;

	fprintf(fp, "\n\n=== ATTRIBUTES ===\n\n");
	for(i = 0; i < class->attributesCount; i++)
	{
		fprintf(fp, "[%d] %s\n", i, class->constantPool[class->attributes[i].attributeNameIndex].info.Utf8Info.bytes);
		fprintf(fp, "\tGeneric info:\n");
		fprintf(fp, "\t\tAttribute name index: cp_info #%hu\n", class->attributes[i].attributeNameIndex);
			fprintf(fp, "\t\tAttribute length: %d\n", class->attributes[i].attributeLength);
		fprintf(fp, "\tSpecific info:\n");
		if(strcmp("ConstantValue", (char*)class->constantPool[class->attributes[i].attributeNameIndex].info.Utf8Info.bytes) == 0)
		{
			fprintf(fp, "\t\tConstant value name index: cp_info #%hu <%s>\n", class->attributes[i].AttributeType.ConstantValueAttribute.constantValueIndex, class->constantPool[class->attributes[i].AttributeType.ConstantValueAttribute.constantValueIndex].info.Utf8Info.bytes);
		}
		else if(strcmp("Code", (char*)class->constantPool[class->attributes[i].attributeNameIndex].info.Utf8Info.bytes) == 0)
		{
			fprintf(fp, "\t\t\tBytecode:\n");
			for(k = 0; k < class->attributes[i].AttributeType.CodeAttribute.codeLength; k++, class->attributes[i].AttributeType.CodeAttribute.code++)
			{
				fprintf(fp, "\t\t\t\t%d %s\n", k, instructionOpcode[*class->attributes[i].AttributeType.CodeAttribute.code]);
			}
			fprintf(fp, "\t\t\tMisc:\n");
			fprintf(fp, "\t\t\t\tMaximum stack deph: %d\n", class->attributes[i].AttributeType.CodeAttribute.maxStack);
			fprintf(fp, "\t\t\t\tMaximum local variables: %d\n", class->attributes[i].AttributeType.CodeAttribute.maxLocals);
			fprintf(fp, "\t\t\t\tCode length: %d\n", class->attributes[i].AttributeType.CodeAttribute.codeLength);
		}
		else if(strcmp("SourceFile", (char*)class->constantPool[class->attributes[i].attributeNameIndex].info.Utf8Info.bytes) == 0)
		{
			fprintf(fp, "\t\tSource file name index: cp_info #%hu <%s>\n", class->attributes[i].AttributeType.SourceFileAttribute.sourceFileIndex, class->constantPool[class->attributes[i].AttributeType.SourceFileAttribute.sourceFileIndex].info.Utf8Info.bytes);
		}
	}
}

/**
A funcao recebe uma estrutura no formato de ClassFile e sera responsavel por fazer as chamadas para as funcoes especificas de imprimir.
Também recebe o nome de um arquivo que sera utilizado para criar o arquivo de saida.

*/
void printClass(ClassFile* class, char *classpath)
{
	FILE *fp;
	char *filename;

	filename = malloc(sizeof(strlen(classpath) + 4));
	strncpy(filename, classpath, (strlen(classpath) - 6));
	filename[strlen(classpath) - 6] = '\0';
	strcat(filename, "Class");
	strcat(filename, ".txt");
	fp = fopen(filename, "w");
	printGeneralInformations(class, fp);
	printConstantPool(class, fp);
	printInterfaces(class, fp);
	printFields(class, fp);
	//printMethods(class, fp);
	//printAttributes(class, fp);
	fclose(fp);
	printf("\nArquivo %s gerado com sucesso\n\nTecle <ENTER> para continuar a execucao", filename);
	getchar();
}
