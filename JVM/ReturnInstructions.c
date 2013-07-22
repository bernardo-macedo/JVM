#include "ReturnInstructions.h"

/*0xAC*/
int ireturn(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    popFrame(&(interpretador->topStackFrame));
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
	return 1;
}

/*0xAD*/
int lreturn(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    popFrame(&(interpretador->topStackFrame));
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
	return 1;
}

/*0xAE*/
int freturn(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    popFrame(&(interpretador->topStackFrame));
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
	return 1;
}

/*0xAF*/
int dreturn(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    popFrame(&(interpretador->topStackFrame));
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
	return 1;
}

/*0xB0*/
int areturn(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    popFrame(&(interpretador->topStackFrame));
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
	return 1;
}

/*0xB1*/
int return_(Interpretador* interpretador) {
    popFrame(&(interpretador->topStackFrame));
    return 1;
}

