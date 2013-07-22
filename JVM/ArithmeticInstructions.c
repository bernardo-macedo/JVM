#include "ArithmeticInstructions.h"

/*0x60*/
int iadd(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = operand2.operandType.intType + operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x61*/
int ladd(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = operand2.operandType.longType + operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x62*/
int fadd(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.floatType = operand2.operandType.floatType + operand1.operandType.floatType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x63*/
int dadd(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.doubleType = operand2.operandType.doubleType + operand1.operandType.doubleType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x64*/
int isub(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = operand2.operandType.intType - operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x65*/
int lsub(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = operand2.operandType.longType - operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x66*/
int fsub(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.floatType = operand2.operandType.floatType - operand1.operandType.floatType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x67*/
int dsub(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.doubleType = operand2.operandType.doubleType - operand1.operandType.doubleType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x68*/
int imul(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = operand2.operandType.intType * operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x69*/
int lmul(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = operand2.operandType.longType * operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x6A*/
int fmul(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.floatType = operand2.operandType.floatType * operand1.operandType.floatType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x6B*/
int dmul(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.doubleType = operand2.operandType.doubleType * operand1.operandType.doubleType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x6C*/
int idiv(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = operand2.operandType.intType / operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x6D*/
int ldiv_(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = operand2.operandType.longType / operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x6E*/
int fdiv(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.floatType = operand2.operandType.floatType / operand1.operandType.floatType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x6F*/
int ddiv(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.doubleType = operand2.operandType.doubleType / operand1.operandType.doubleType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x70*/
int irem(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = operand2.operandType.intType % operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x71*/
int lrem(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = operand2.operandType.longType % operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x72*/
int frem(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.floatType = (float) fmod(operand2.operandType.floatType, operand1.operandType.floatType);
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x73*/
int drem_(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.doubleType = fmod(operand2.operandType.doubleType, operand1.operandType.doubleType);
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x74*/
int ineg(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = 0 - operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x75*/
int lneg(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = 0 - operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x76*/
int fneg(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.type32_64 = CAT1;
    operand_result.operandType.floatType = 0 - operand1.operandType.floatType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x77*/
int dneg(Interpretador* interpretador) {
    Operand operand1, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    operand_result.type32_64 = CAT2;
    operand_result.operandType.doubleType = 0 - operand1.operandType.doubleType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x78*/
int ishl(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand1.operandType.intType = operand1.operandType.intType & 0x1F; /* pega os 5 bits mais baixos de value2 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = operand2.operandType.intType << operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x79*/
int ishr(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand1.operandType.intType = operand1.operandType.intType & 0x1F; /* pega os 5 bits mais baixos de value2 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = operand2.operandType.intType >> operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x7A*/
int iushr(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand1.operandType.intType = operand1.operandType.intType & 0x1F; /* pega os 5 bits mais baixos de value2 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = operand2.operandType.intType >> operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x7B*/
int lshl(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand1.operandType.longType = operand1.operandType.longType & 0x11F; /* pega os 6 bits mais baixos de value2 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = operand2.operandType.longType << operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x7C*/
int lshr(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand1.operandType.longType = operand1.operandType.longType & 0x11F; /* pega os 6 bits mais baixos de value2 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = operand2.operandType.longType >> operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x7D*/
int lushr(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand1.operandType.longType = operand1.operandType.longType & 0x11F; /* pega os 6 bits mais baixos de value2 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = operand2.operandType.longType >> operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x7E*/
int iand(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = operand2.operandType.intType & operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x7F*/
int land(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = operand2.operandType.longType & operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x80*/
int ior(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = operand2.operandType.intType | operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x81*/
int lor(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = operand2.operandType.longType | operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x82*/
int ixor(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
    operand_result.operandType.intType = operand2.operandType.intType ^ operand1.operandType.intType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x83*/
int lxor(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT2;
    operand_result.operandType.longType = operand2.operandType.longType ^ operand1.operandType.longType;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x84*/
int iinc(Interpretador* interpretador) {
    u2 index;
    u2 constant;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        constant = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        constant = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    interpretador->topStackFrame->frame->localVarArray[index] += (int) constant;
	return 0;
}

/*0x94*/
int lcmp(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
	if (operand2.operandType.longType > operand1.operandType.longType) {
		operand_result.operandType.intType = 1;
	} else if (operand2.operandType.longType == operand1.operandType.longType) {
		operand_result.operandType.intType = 0;
	} else {
		operand_result.operandType.intType = -1;
	}
	pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x95*/
int fcmpl(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
	if (operand2.operandType.floatType > operand1.operandType.floatType) {
		operand_result.operandType.intType = 1;
	} else if (operand2.operandType.floatType == operand1.operandType.floatType) {
		operand_result.operandType.intType = 0;
	} else if (operand2.operandType.floatType < operand1.operandType.floatType) {
		operand_result.operandType.intType = -1;
	} else {
        operand_result.operandType.intType = -1;
	}
	pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x96*/
int fcmpg(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
	if (operand2.operandType.floatType > operand1.operandType.floatType) {
		operand_result.operandType.intType = 1;
	} else if (operand2.operandType.floatType == operand1.operandType.floatType) {
		operand_result.operandType.intType = 0;
	} else if (operand2.operandType.floatType < operand1.operandType.floatType) {
		operand_result.operandType.intType = -1;
	} else {
        operand_result.operandType.intType = 1;
	}
	pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x97*/
int dcmpl(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
	if (operand2.operandType.doubleType > operand1.operandType.doubleType) {
		operand_result.operandType.intType = 1;
	} else if (operand2.operandType.doubleType == operand1.operandType.doubleType) {
		operand_result.operandType.intType = 0;
	} else if (operand2.operandType.doubleType < operand1.operandType.doubleType) {
		operand_result.operandType.intType = -1;
	} else {
        operand_result.operandType.intType = -1;
	}
	pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}

/*0x98*/
int dcmpg(Interpretador* interpretador) {
    Operand operand1, operand2, operand_result;
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand1 = value2 */
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* operand2 = value1 */
    operand_result.type32_64 = CAT1;
	if (operand2.operandType.doubleType > operand1.operandType.doubleType) {
		operand_result.operandType.intType = 1;
	} else if (operand2.operandType.doubleType == operand1.operandType.doubleType) {
		operand_result.operandType.intType = 0;
	} else if (operand2.operandType.doubleType < operand1.operandType.doubleType) {
		operand_result.operandType.intType = -1;
	} else {
        operand_result.operandType.intType = 1;
	}
	pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand_result);
	return 0;
}
