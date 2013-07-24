/*
 * ClassLoader.h
 *
 *  Created on: 03/02/2013
 *      Author: Vitor
 */

#ifndef CLASSLOADER_H_
#define CLASSLOADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClassFile.h"

u1 lerU1(FILE *fp);
u2 lerU2(FILE *fp);
u4 lerU4(FILE *fp);
u8 lerU8(FILE *fp);

void lerConstantPool(FILE *fp, ClassFile *cf);
void lerInterfaces(FILE *fp, ClassFile *cf);
void lerAttributeConstantValue(FILE *fp, attributeInfo *attr);
void lerAttributeCode(FILE *fp, ClassFile *cf, attributeInfo *attr);
void lerAttributeException(FILE *fp, attributeInfo *attr);
void lerAttributeInnerClasses(FILE *fp, attributeInfo *attr);
void lerAttributeSourceFile(FILE *fp, attributeInfo *attr);
void lerAttributeUnknown(FILE *fp, attributeInfo *attr);
void lerAttributeInfo(FILE *fp, ClassFile *cf, attributeInfo *attr);
void lerFieldInfo(FILE *fp, ClassFile *cf);
void lerMetodos(FILE *fp, ClassFile *cf);
ClassFile carregaClassFile(char *nomeClasse);

#endif /* CLASSLOADER_H_ */
