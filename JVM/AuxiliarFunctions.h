#ifndef AUXILIARFUNCTIONS_H
#define AUXILIARFUNCTIONS_H

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
#endif
