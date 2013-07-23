#ifndef AUXILIARFUNCTIONS_H
#define AUXILIARFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ClassStructure.h"
#include "ClassLoader.h"
#include "Controller.h"

float convertU4ToFloat(u4 u4input);

/** Função que retorna a constante UTF8 de um determinado índice
*/
u1* getUTF8(CpInfo *cp, u2 index);

/** Função que retorna o numero de arugmentos de um método baseando-se no seu descritor
*/
int methodArgsCount(char* descriptor);

/** Função que busca uma ClassFile a partir de seu nome na lista de classes (ClassList)
*/
ClassFile* getClassFileByName(ClassList* init, char* className);

/** Função que busca um método a partir de seu nome e descritor. Retorna NULL se não existir
*/
MethodInfo* getMethod(ClassFile, char* methodName, char* methodDescriptor);

char* getClassName(char *classpath);

ClassFile* isLoaded(Interpretador*, char*);

void insertStaticFieldValue(ClassList*, char*, char*, Operand);

/*// Função que preenche o array de fields do objeto com os fields de todas
// as classes ligadas a ele (classe + super classes) e inicializa o valor com */
void fieldsInit(Interpretador*, ClassFile, Field*);

Array* createMultiArray(int, int*);

//getStaticFieldName
Field* getStaticFieldName(ClassList* init, char* className, char* fieldName);

#endif
