#ifndef CLASSLOADER_H
#define CLASSLOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClassStructure.h"
#include "AuxiliarFunctions.h"

u1 readU1(FILE *fp);
u2 readU2(FILE *fp);
u4 readU4(FILE *fp);

void readConstantValueAttribute(FILE *fp, AttributeInfo *attributes);
void readExceptionTable(FILE *fp, ExceptionTable *exceptionTable);
void readCodeAttribute(ClassFile* class, FILE *fp, AttributeInfo *attributes);
void readExceptionsAttribute(FILE *fp, AttributeInfo *attributes);
void readInnerClassesAttribute(FILE *fp, AttributeInfo *attributes);
void readSourceFileAttribute(FILE *fp, AttributeInfo *attributes);
void readLineNumberTableAttribute(FILE *fp, AttributeInfo *attributes);
void readLocalVariableTableAttribute(FILE *fp, AttributeInfo *attributes);
void readUnknownttribute(FILE *fp, AttributeInfo *attributes);

void readConstantPool(ClassFile* class, FILE *fp);
void readInterfaces(ClassFile* class, FILE *fp);
void readFields(ClassFile* class, FILE *fp);
void readAttribute(ClassFile* class, FILE *fp, AttributeInfo *attributes);
void readMethods(ClassFile* class, FILE *fp);

void printGeneralInformations(ClassFile* class, FILE *fp);
void printConstantPool(ClassFile* class, FILE *fp);
void printInterfaces(ClassFile* class, FILE *fp);
void printFields(ClassFile* class, FILE *fp);
void printMethods(ClassFile* class, FILE *fp);
void printAttributes(ClassFile* class, FILE *fp);

ClassFile* readClass(char *classpath);
void printClass(ClassFile* class, char *classpath);



#endif