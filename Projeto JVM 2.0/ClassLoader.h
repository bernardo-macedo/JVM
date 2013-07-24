#ifndef CLASSLOADER_H_
#define CLASSLOADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClassFile.h"

u1 readU1(FILE *fp);
u2 readU2(FILE *fp);
u4 readU4(FILE *fp);
u8 readU8(FILE *fp);


void readConstantValueAttribute(FILE *fp, AttributeInfo *attributes);
void readCodeAttribute(ClassFile *class, FILE *fp, AttributeInfo *attributes);
void readCodeExceptionTable(FILE *fp, ExceptionTable *exceptionTable);
void readExceptionsAttribute(FILE *fp, AttributeInfo *attributes);
void readInnerClassesAttribute(FILE *fp, AttributeInfo *attributes);
void readSourceFileAttribute(FILE *fp, AttributeInfo *attributes);
void readUnknownAttribute(FILE *fp, AttributeInfo *attributes);

void readConstantPool(ClassFile *class, FILE *fp);
void readInterfaces(ClassFile *class, FILE *fp);
void readFields(ClassFile *class, FILE *fp);
void readAttributes(ClassFile *class, FILE *fp, AttributeInfo *attributes);
void readMethods(ClassFile *class, FILE *fp);

ClassFile readClass(char *classpath);

#endif /* CLASSLOADER_H_ */
