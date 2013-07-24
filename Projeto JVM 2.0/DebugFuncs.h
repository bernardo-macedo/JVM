/*
 * DebugFuncs.h
 *
 *  Created on: 01/02/2013
 *      Author: Vitor
 */

#ifndef DEBUGFUNCS_H_
#define DEBUGFUNCS_H_

#include "ClassFile.h"

char* tagString(u1 tag);

void printConstantPool(ClassFile cf);

void printCodigoMetodo(attributeInfo codigoMetodo);

#endif /* DEBUGFUNCS_H_ */
