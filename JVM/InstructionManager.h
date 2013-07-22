#ifndef INSTRUCTION_MANAGER_H
#define INSTRUCTION_MANAGER_H

#include "Controller.h"

/** Variavel global que indica se a instrução wide foi chamada */
int isWide = 0;

/** Ponteiro para funções de execução de instruções */
int (*InstructionArray[])(Interpretador*);

/** Unions que permitem acesso à mesma região de memória com tipos diferentes
*   sem efetuar conversão de valores, apenas lendo o dado de maneira distinta.
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
