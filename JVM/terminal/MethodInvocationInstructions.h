#ifndef METHODINVOCATIONINSTRUCTIONS_H
#define METHODINVOCATIONINSTRUCTIONS_H

#include "ClassStructure.h"
#include "AuxiliarFunctions.h"
#include "InstructionManager.h"
#include "Controller.h"

/*Teste*/
int invokevirtual(Interpretador*); /*0xB6*/
int invokespecial(Interpretador*); /*0xB7*/
int invokestatic(Interpretador*); /*0xB8*/
int invokeinterface(Interpretador*); /*0xB9*/

#endif
