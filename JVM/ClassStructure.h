/*
u1
u2
u4
ConstantPoolConstType
CpInfo
ClassInfo
FieldrefInfo
MethodrefInfo
InterfaceMethodrefInfo
StringInfo
IntegerInfo
FloatInfo
LongInfo
DoubleInfo
NameAndTypeInfo
Utf8Info
AttributeInfo
FieldInfo
MethodInfo
ExceptionTable
InnerClass
LineNumberTable
LocalVariableTable
ConstantValueAttribute
CodeAttribute
DeprecatedAttribute
ExceptionsAttribute
InnerClassAttribute
LineNumberTableAttribute
LocalVariableTableAttribute
SourceFileAttribute
ClassFile
*/
#ifndef CLASSSTRUCTURE_H
#define CLASSSTRUCTURE_H

#define ACC_PUBLIC			0x0001
#define ACC_PRIVATE			0x0002
#define ACC_PROTECTED		0x0004
#define ACC_STATIC			0x0008
#define ACC_FINAL			0x0010
#define ACC_SUPER			0x0020
#define ACC_SYNCHRONIZED	0x0020
#define ACC_VOLATILE		0x0040
#define ACC_TRANSIENT		0x0080
#define ACC_NATIVE 			0x0100
#define ACC_INTERFACE		0x0200
#define ACC_ABSTRACT		0x0400
#define ACC_STRICT 			0x0800

#define	CONSTANT_Class					7
#define	CONSTANT_Fieldref				9
#define	CONSTANT_Methodfef				10
#define	CONSTANT_InterfaceMethodref		11
#define	CONSTANT_String					8
#define	CONSTANT_Integer				3
#define	CONSTANT_Float					4
#define	CONSTANT_Long					5
#define	CONSTANT_Double					6
#define	CONSTANT_NameAndType			12
#define	CONSTANT_Utf8					1

#define T_BOOLEAN	4
#define T_CHAR     	5
#define T_FLOAT 	6
#define T_DOUBLE 	7
#define T_BYTE      8
#define T_SHORT 	9
#define T_INT       10
#define T_LONG      11

typedef unsigned char 	u1;
typedef unsigned short 	u2;
typedef unsigned int 	u4;

typedef struct utf8Info
{
	/*valor 1*/
	u2 length;
	u1 *bytes;
} Utf8InfoType;

typedef union constantPoolConstType
{
	struct
	{
		/*valor 7*/
		u2 nameIndex;
	} ClassInfo;

	struct
	{
		/*valor 9*/
		u2 classIndex;
		u2 nameAndTypeIndex;
	} FieldrefInfo;

	struct
	{
		/*valor 10*/
		u2 classIndex;
		u2 nameAndTypeIndex;
	} MethodrefInfo;

	struct
	{
		/*valor 11*/
		u2 classIndex;
		u2 nameAndTypeIndex;
	} InterfaceMethodrefInfo;

	struct
	{
		/*valor 8*/
		u2 stringIndex;
	} StringInfo;

	struct
	{
		/*valor 3*/
		u4 bytes;
	} IntegerInfo;

	struct
	{
		/*valor 4*/
		u4 bytes;
	} FloatInfo;

	struct
	{
		/*valor 5*/
		u4 highBytes;
		u4 lowBytes;
	} LongInfo;

	struct
	{
		/*valor 6*/
		u4 highBytes;
		u4 lowBytes;
	} DoubleInfo;

	struct
	{
		/*valor 12*/
		u2 nameIndex;
		u2 descriptorIndex;
	} NameAndTypeInfo;

	/*valor 1*/
	Utf8InfoType Utf8Info;

} ConstantPoolConstType;

typedef struct cpInfo
{
	u1 tag;
	ConstantPoolConstType info;
} CpInfo;

typedef struct exceptionTable
{
	u2 startPc;
	u2 endPc;
	u2 handlerPc;
	u2 catchType;
} ExceptionTable;

typedef struct innerClass
{
	u2 innerClassInfoIndex;
	u2 outerClassInfoIndex;
	u2 innerNameIndex;
	u2 innerClassAccessFlags;
} InnerClass;

typedef struct lineNumberTable
{
	u2 startPc;
	u2 lineNumber;
} LineNumberTable;

typedef struct localVariableTable
{
	u2 attributeNameIndex;
	u2 length;
	u2 nameIndex;
	u2 descriptorIndex;
	u2 index;
} LocalVariableTable;

typedef struct attributeInfo
{
	u2 attributeNameIndex;
	u4 attributeLength;
	union
	{
		struct
		{
		    u2 constantValueIndex;
		} ConstantValueAttribute;

		struct
		{
			u2 maxStack;
			u2 maxLocals;
			u4 codeLength;
			u1 *code;
			u2 exceptionTableLength;
			ExceptionTable *exceptionTable;
			u2 attributesCount;
			struct attributeInfo *attributes;
		} CodeAttribute;

		struct
		{
		} DeprecatedAttribute;

		struct
		{
			u2 numberOfExceptions;
			u2 *exceptionIndexTable;
		} ExceptionsAttribute;

		struct
		{
			u2 numberOfClasses;
			InnerClass *classes;
		} InnerClassAttribute;

		/*ignorados*/
		struct
		{
			u2 lineNumberTableLength;
			LineNumberTable *lineNumberTable;
		} LineNumberTableAttribute;

		struct
		{
			u2 localVariableTableLength;
			LocalVariableTable *localVariableTable;
		} LocalVariableTableAttribute;
		/*******/

		struct
		{
			u2 sourceFileIndex;
		} SourceFileAttribute;

		struct
		{
			u1 *info;
		} UnknownAttribute;
	} AttributeType;
} AttributeInfo;

typedef struct fieldInfo
{
	u2 accessFlags;
	u2 nameIndex;
	u2 descriptorIndex;
	u2 attributesCount;
	AttributeInfo *attributes;
} FieldInfo;

typedef struct methodInfo
{
	u2 accessFlags;
	u2 nameIndex;
	u2 descriptorIndex;
	u2 attributesCount;
	AttributeInfo *attributes;
} MethodInfo;

typedef struct classFile
{
	u4				magic;
	u2 				minorVersion;
	u2 				majorVersion;
	u2 				constantPoolCount;
	CpInfo 			*constantPool;
	u2 				accessFlags;
	u2 				thisClass;
	u2 				superClass;
	u2 				interfacesCount;
	u2 				*interfaces;
	u2 				fieldsCount;
	FieldInfo 		*fields;
	u2 				methodsCount;
	MethodInfo 		*methods;
	u2 				attributesCount;
	AttributeInfo	*attributes;
} ClassFile;

#endif
