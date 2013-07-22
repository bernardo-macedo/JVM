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

void readConstantValueAttribute(FILE *fp, AttributeInfo *attributes)
{
	attributes->AttributeType.ConstantValueAttribute.constantValueIndex = readU2(fp);
}

void readExceptionTable(FILE *fp, ExceptionTable *exceptionTable)
{
	exceptionTable->startPc = readU2(fp);
	exceptionTable->endPc = readU2(fp);
	exceptionTable->handlerPc = readU2(fp);
	exceptionTable->catchType = readU2(fp);
}

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

void readSourceFileAttribute(FILE *fp, AttributeInfo *attributes)
{
	attributes->AttributeType.SourceFileAttribute.sourceFileIndex = readU2(fp);
}

void readUnknownAttribute(FILE *fp, AttributeInfo *attributes)
{
		int i;

		attributes->AttributeType.UnknownAttribute.info = malloc((attributes->attributeLength) * sizeof(u1));

		for (i = 0; i < attributes->attributeLength; i++) 
		{
			attributes->AttributeType.UnknownAttribute.info[i] = readU1(fp);
		}
}

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
				break;
		}
	}
}

void readInterfaces(ClassFile* class, FILE *fp)
{
	int i;

	class->interfaces = (u2*)calloc(class->interfacesCount, sizeof(u2));	
	for(i = 0; i < class->interfacesCount; i++)
	{
		class->interfaces[i] = readU2(fp);
	}
}

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
	else
	{
		readUnknownAttribute(fp, attributes);
	}
}

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

ClassFile* readClass(char *classpath)
{
	ClassFile *class;
	FILE *fp;
	int i;

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
	class->constantPoolCount = readU2(fp);
	readConstantPool(class, fp);
	class->accessFlags = readU2(fp);
	class->thisClass = readU2(fp);
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
				fprintf(fp, "\tString: %hu <%s>\n", class->constantPool[i].info.StringInfo.stringIndex, class->constantPool[class->constantPool[i].info.StringInfo.stringIndex].info.Utf8Info.bytes);
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

void printInterfaces(ClassFile* class, FILE *fp)
{
	fprintf(fp, "\n\n=== INTERFACES ===\n\n");
}

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

void printMethods(ClassFile* class, FILE *fp)
{
	int i;
	int j;

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
			fprintf(fp, "\t[%d] %s\n", i, class->constantPool[class->methods[i].attributes[j].attributeNameIndex].info.Utf8Info.bytes);
		}
	}

}

void printAttributes(ClassFile* class, FILE *fp)
{
	fprintf(fp, "\n\n=== ATTRIBUTES ===\n\n");
}

void printClass(ClassFile* class, char *classpath)
{
	FILE *fp;
	char *filename;

	filename = malloc(sizeof(strlen(classpath) + 4));
	strncpy(filename, classpath, (strlen(classpath) - 6));
	filename[strlen(classpath) - 6] = '\0';
	strcat(filename, "Class");
	strcat(filename, ".txt");
	printf("%s\n", filename);
	fp = fopen(filename, "w");	
	printGeneralInformations(class, fp);
	printConstantPool(class, fp);
	printInterfaces(class, fp);
	printFields(class, fp);
	printMethods(class, fp);
	printAttributes(class, fp);
	fclose(fp);
	printf("\nArquivo %s gerado com sucesso\n\nTecle <ENTER> para continuar a execucao", filename);
	getchar();
}