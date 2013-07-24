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

void printConstantPool(ClassFile classFile);

void printCodigoMetodo(attributeInfo methodCode);

#endif /* DEBUGFUNCS_H_ */
