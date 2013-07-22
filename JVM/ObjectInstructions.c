#include "ObjectInstructions.h"

/*0x2E*/
int iaload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    operand_result.operandType.intType = *(operand2.operandType.referenceType[operand1.operandType.intType]);
    operand_result.type32_64 = CAT1;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
    return 0;
}

/*0x2F*/
int laload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    operand_result.operandType.longType = *(operand2.operandType.referenceType[operand1.operandType.intType]);
    operand_result.type32_64 = CAT2;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
    return 0;
}

/*0x30*/
int faload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    operand_result.operandType.floatType = *(operand2.operandType.referenceType[operand1.operandType.intType]);
    operand_result.type32_64 = CAT1;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
    return 0;
}

/*0x31*/
int daload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    operand_result.operandType.doubleType = *(operand2.operandType.referenceType[operand1.operandType.intType]);
    operand_result.type32_64 = CAT2;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
    return 0;
}

/*0x32*/
int aaload(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o index */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o arrayref */
    operand_result.operandType.referenceType = *(operand2.operandType.referenceType[operand1.operandType.intType]);
    operand_result.type32_64 = CAT1;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
    return 0;
}

/*0x33*/
int baload(Interpretador* interpretador) {
}

/*0x34*/
int caload(Interpretador* interpretador) {
}

/*0x35*/
int saload(Interpretador* interpretador) {
}

/*0x4F*/
int iastore(Interpretador* interpretador) {
}

/*0x50*/
int lastore(Interpretador* interpretador) {
}

/*0x51*/
int fastore(Interpretador* interpretador) {
}

/*0x52*/
int dastore(Interpretador* interpretador) {
}

/*0x53*/
int aastore(Interpretador* interpretador) {
}

/*0x54*/
int bastore(Interpretador* interpretador) {
}

/*0x55*/
int castore(Interpretador* interpretador) {
}

/*0x56*/
int sastore(Interpretador* interpretador) {
}

/*0xB2*/
int getstatic(Interpretador* interpretador) {
}

/*0xB3*/
int putstatic(Interpretador* interpretador) {
}

/*0xB4*/
int getfield(Interpretador* interpretador) {
}

/*0xB5*/
int putfield(Interpretador* interpretador) {
}

/*0xBB*/
int new(Interpretador* interpretador) {
}

/*0xBC*/
int newarray(Interpretador* interpretador) {
}

/*0xBD*/
int anewarray(Interpretador* interpretador) {
}

/*0xBE*/
int arraylength(Interpretador* interpretador) {
}

/*0xC0*/
int checkcast(Interpretador* interpretador) {
}

/*0xC1*/
int instanceof(Interpretador* interpretador) {
}

/*0xC5*/
int multianewarray(Interpretador* interpretador) {
}


#endif
