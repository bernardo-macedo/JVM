#ifndef INSTRUCTION_MANAGER_H
#define INSTRUCTION_MANAGER_H

#include "Controller.h"
/*#include "ArithmeticInstructions.h"
#include "ControlTransferInstructions.h"
#include "LoadAndStoreInstructions.h"
#include "ObjectInstructions.h"
#include "OperandStackInstructions.h"
#include "ReturnInstructions.h"
#include "TypeConversionInstructions.h"
#include "MethodInvocationInstructions.h"
#include "AuxiliarFunctions.h"*/

/** Variavel global que indica se a instru��o wide foi chamada */
int isWide;

/** Ponteiro para fun��es de execu��o de instru��es */
extern int (*InstructionArray[])(Interpretador*);

/** Unions que permitem acesso � mesma regi�o de mem�ria com tipos diferentes
*   sem efetuar convers�o de valores, apenas lendo o dado de maneira distinta.
*/
typedef union FloatToInt {
    float f;
    int i;
} FloatToInt;

typedef union DoubleToInt {
    double d;
    int pairedInt[2];
} DoubleToInt;

typedef union LongToInt {
    long long l;
    int pairedInt[2];
} LongToInt;

typedef union VoidToInt {
    void* voidAddress;
    int intAddress;
} VoidToInt;

#endif
