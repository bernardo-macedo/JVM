#include "TypeConversionInstructions.h"

/*0x85*/
int i2l(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.longType = operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x86*/
int i2f(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.floatType = (float) operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x87*/
int i2d(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.doubleType = (double) operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x88*/
int l2i(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.intType = (int) operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x89*/
int l2f(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.floatType = (float) operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x8A*/
int l2d(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.doubleType = (double) operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x8B*/
int f2i(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.intType = (int) operand1.operandType.floatType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x8C*/
int f2l(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.longType = (long long) operand1.operandType.floatType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x8D*/
int f2d(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.doubleType = (double) operand1.operandType.floatType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x8E*/
int d2i(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.intType = (int) operand1.operandType.doubleType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x8F*/
int d2l(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.longType = (long long) operand1.operandType.doubleType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x90*/
int d2f(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.floatType = (float) operand1.operandType.doubleType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x91*/
int i2b(Interpretador* interpretador) {
    Operand operand1, operand_result;
    u1 aux;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    aux = operand1.operandType.intType;
    operand_result.operandType.intType = (int) aux;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x92*/
int i2c(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.intType = (char) operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x93*/
int i2s(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.operandType.intType = (short) operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}
