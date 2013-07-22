#include "ControlTransferInstructions.h"
#include "InstructionManager.h"
#include <stdlib.h>

/*0x99*/
int ifeq(Interpretador* interpretador) {
    Operand operand;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand.operandType.intType == 0) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0x9A*/
int ifne(Interpretador* interpretador) {
    Operand operand;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand.operandType.intType != 0) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0x9B*/
int iflt(Interpretador* interpretador) {
    Operand operand;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand.operandType.intType < 0) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0x9C*/
int ifge(Interpretador* interpretador) {
    Operand operand;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand.operandType.intType >= 0) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0x9D*/
int ifgt(Interpretador* interpretador) {
    Operand operand;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand.operandType.intType > 0) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0x9E*/
int ifle(Interpretador* interpretador) {
    Operand operand;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand.operandType.intType <= 0) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0x9F*/
int if_icmpeq(Interpretador* interpretador) {
    Operand operand1, operand2;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand1.operandType.intType == operand2.operandType.intType) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0xA0*/
int if_icmpne(Interpretador* interpretador) {
    Operand operand1, operand2;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand1.operandType.intType != operand2.operandType.intType) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0xA1*/
int if_icmplt(Interpretador* interpretador) {
    Operand operand1, operand2;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand1.operandType.intType < operand2.operandType.intType) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0xA2*/
int if_icmpge(Interpretador* interpretador) {
    Operand operand1, operand2;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand1.operandType.intType >= operand2.operandType.intType) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0xA3*/
int if_icmpgt(Interpretador* interpretador) {
    Operand operand1, operand2;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand1.operandType.intType > operand2.operandType.intType) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0xA4*/
int if_icmple(Interpretador* interpretador) {
    Operand operand1, operand2;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand1.operandType.intType <= operand2.operandType.intType) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0xA5*/
int if_acmpeq(Interpretador* interpretador) {
    Operand operand1, operand2;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand1.operandType.referenceType == operand2.operandType.referenceType) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0xA6*/
int if_acmpne(Interpretador* interpretador) {
    Operand operand1, operand2;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand2 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor2 */
    operand1 = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor1 */
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand1.operandType.referenceType != operand2.operandType.referenceType) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0xA7*/
int goto_(Interpretador* interpretador) {
    u2 offset;
    u1 branchbyte1, branchbyte2;
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução goto */
    return 0;
}

/*0xA8*/
int jsr(Interpretador* interpretador) {
    Operand operand_result;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    interpretador->topStackFrame->frame->execEnvir->pc++;
    operand_result.type32_64 = CAT1;
    operand_result.operandType.referenceType = interpretador->topStackFrame->frame->execEnvir->pc;
    interpretador->topStackFrame->frame->execEnvir->pc += (offset - 3); /* (offset - 3) para pc voltar a apontar para a instrução jsr */
    return 0;
}

/*0xA9*/
int ret(Interpretador* interpretador) {
    u2 index;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        //interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        //interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    interpretador->topStackFrame->frame->execEnvir->pc = interpretador->topStackFrame->frame->localVarArray[index];
    return 0;
}

/*0xAA*/
int tableswitch(Interpretador* interpretador) {
}

/*0xAB*/
int lookupswitch(Interpretador* interpretador) {
}

/*0xC6*/
int ifnull(Interpretador* interpretador) {
    Operand operand;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor */
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand.operandType.referenceType == NULL) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0xC7*/
int ifnonnull(Interpretador* interpretador) {
    Operand operand;
    u2 offset;
    u1 branchbyte1, branchbyte2;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand)); /* pega o valor */
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 8) | branchbyte2;
    if (operand.operandType.referenceType != NULL) {
        interpretador->topStackFrame->frame->execEnvir->pc += (offset - 2); /* (offset - 2) para pc voltar a apontar para a instrução if */
    } else {
        interpretador->topStackFrame->frame->execEnvir->pc++; /* pc++ para pc apontar para a próxima instrução a ser lida */
    }
    return 0;
}

/*0xC8*/
int goto_w(Interpretador* interpretador) {
    u4 offset;
    u1 branchbyte1, branchbyte2, branchbyte3, branchbyte4;
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte3 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte4 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    offset = (branchbyte1 << 24) | (branchbyte2 << 16) | (branchbyte3 << 8) | branchbyte4;
    interpretador->topStackFrame->frame->execEnvir->pc += (offset - 4); /* (offset - 4) para pc voltar a apontar para a instrução goto_w */
    return 0;
}

/*0xC9*/
int jsr_w(Interpretador* interpretador) {
    Operand operand_result;
    u4 offset;
    u1 branchbyte1, branchbyte2, branchbyte3, branchbyte4;
    branchbyte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte3 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    branchbyte4 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    operand_result.type32_64 = CAT1;
    operand_result.operandType.referenceType = interpretador->topStackFrame->frame->execEnvir->pc;
    offset = (branchbyte1 << 24) | (branchbyte2 << 16) | (branchbyte3 << 8) | branchbyte4;
    interpretador->topStackFrame->frame->execEnvir->pc += (offset - 5); /* (offset - 5) para pc voltar a apontar para a instrução jsr_w */
    return 0;
}

