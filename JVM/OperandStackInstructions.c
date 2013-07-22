#include "OperandStackInstructions.h"

/*0x57*/
int pop(Interpretador* interpretador) {
    if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT1) {
        popOperand(&(interpretador->topStackFrame->frame->topOperand));
    } else {
        printf("Erro. Topo da pilha e' do Tipo 2\n");
        exit(1);
    }
	return 0;
}

/*0x58*/
int pop2(Interpretador* interpretador) {
    if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT1 &&
        interpretador->topStackFrame->frame->topOperand->nextOperand->operand.type32_64 == CAT1) {
        popOperand(&(interpretador->topStackFrame->frame->topOperand));
        popOperand(&(interpretador->topStackFrame->frame->topOperand));
    } else {
        popOperand(&(interpretador->topStackFrame->frame->topOperand));
    }
	return 0;
}

/*0x59*/
int dup(Interpretador* interpretador) {
    Operand operand;
    if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT1) {
        operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    } else {
        printf("Erro. Topo da pilha e' do Tipo 2\n");
        exit(1);
    }
	return 0;
}

/*0x5A*/
int dup_x1(Interpretador* interpretador) {
    Operand operand1, operand2;
    if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT1 &&
        interpretador->topStackFrame->frame->topOperand->nextOperand->operand.type32_64 == CAT1) {
        operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
        operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
    } else {
        printf("Erro. Topo da pilha e' do Tipo 2\n");
        exit(1);
    }
	return 0;
}

/*0x5B*/
int dup_x2(Interpretador* interpretador) {
    Operand operand1, operand2, operand3;
    if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT1) { /* Caso 1 */
        if (interpretador->topStackFrame->frame->topOperand->nextOperand->operand.type32_64 == CAT2) { /* dois slots abaixo */
            operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
            operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        } else if (interpretador->topStackFrame->frame->topOperand->nextOperand->nextOperand->operand.type32_64 == CAT1) { /* Caso 2 */
            operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
            operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
            operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor3 */
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand3);
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
            pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        } else {
            printf("Erro. O terceiro valor e' do Tipo 2\n");
            exit(1);
        }
    } else {
        printf("Erro. O primeiro valor e' do Tipo 2\n");
        exit(1);
    }
	return 0;
}

/*0x5C*/
int dup2(Interpretador* interpretador) {
    Operand operand1, operand2;
    if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT1 &&
        interpretador->topStackFrame->frame->topOperand->nextOperand->operand.type32_64 == CAT1) { /* Caso 1 */
        operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o primeiro valor a ser duplicado */
        operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o segundo valor a ser duplicado */
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
    } else if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT2) { /* Caso 2 */
        operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o primeiro valor a ser duplicado */
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
    }
	return 0;
}

/*0x5D*/
int dup2_x1(Interpretador* interpretador) {
    Operand operand1, operand2, operand3;
    if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT1 &&
        interpretador->topStackFrame->frame->topOperand->nextOperand->operand.type32_64 == CAT1) { /* Caso 2 */
        operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
        operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
        operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor3 */
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand3);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
    } else if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT2) { /* Caso 1 */
        operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
        operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
    }
	return 0;
}

/*0x5E*/
int dup2_x2(Interpretador* interpretador) {
    Operand operand1, operand2, operand3, operand4;
    if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT1 &&
        interpretador->topStackFrame->frame->topOperand->nextOperand->operand.type32_64 == CAT1 &&
        interpretador->topStackFrame->frame->topOperand->nextOperand->nextOperand->operand.type32_64 == CAT1 &&
        interpretador->topStackFrame->frame->topOperand->nextOperand->nextOperand->nextOperand->operand.type32_64 == CAT1 ) { /* Caso 1 */
        operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
        operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
        operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor3 */
        operand4 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor4 */
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand4);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand3);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
    } else if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT2) { /* Caso 2 */
        operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
        operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
        operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor3 */
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand3);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
    } else if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT1 &&
        interpretador->topStackFrame->frame->topOperand->nextOperand->operand.type32_64 == CAT1 &&
        interpretador->topStackFrame->frame->topOperand->nextOperand->nextOperand->operand.type32_64 == CAT2) { /* Caso 3 */
        operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
        operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
        operand3 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor3 */
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand3);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
    } else if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT2 &&
        interpretador->topStackFrame->frame->topOperand->nextOperand->operand.type32_64 == CAT2) {
        operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
        operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
        }
	return 0;
}

/*0x5F*/
int _swap(Interpretador* interpretador) {
    Operand operand1, operand2;
    if (interpretador->topStackFrame->frame->topOperand->operand.type32_64 == CAT1 &&
        interpretador->topStackFrame->frame->topOperand->nextOperand->operand.type32_64 == CAT1) {
        operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
        operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand2);
        pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand1);
    } else {
        printf("Erro. Os valores nao sao do Tipo 1\n");
        exit(1);
    }
	return 0;
}
