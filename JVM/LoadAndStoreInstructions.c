#include "LoadAndStoreInstructions.h"
#include <stdlib.h>

int nop(Interpretador* interpretador) {
    return 0;
}

/*0x01*/
int aconst_null(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.referenceType = NULL;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x02*/
int iconst_m1(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = -1;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x03*/
int iconst_0(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = 0;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x04*/
int iconst_1(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = 1;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x05*/
int iconst_2(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = 2;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x06*/
int iconst_3(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = 3;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x07*/
int iconst_4(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = 4;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x08*/
int iconst_5(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = 5;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x09*/
int lconst_0(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    operand.operandType.longType = 0;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x0A*/
int lconst_1(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    operand.operandType.longType = 1;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x0B*/
int fconst_0(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.floatType = 0.0;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x0C*/
int fconst_1(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.floatType = 1.0;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x0D*/
int fconst_2(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.floatType = 2.0;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x0E*/
int dconst_0(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    operand.operandType.doubleType = 0.0;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x0F*/
int dconst_1(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    operand.operandType.doubleType = 1.0;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x10*/
int bipush(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x11*/
int sipush(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    int byte1, byte2;
    byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    operand.operandType.intType = (byte1 << 8) | byte2;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x12*/
int ldc(Interpretador* interpretador) {
    Operand operand;
    u2 stringIndex;
    operand.type32_64 = CAT1;
    u1 index = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    switch (interpretador->topStackFrame->frame->execEnvir->belongingClass[index].tag) {
        case CONSTANT_Integer:
            operand.operandType.intType = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.IntegerInfo.bytes;
            break;
        case CONSTANT_Float:
            operand.operandType.floatType = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.FloatInfo.bytes;
            break;
        case CONSTANT_String:
            stringIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.StringInfo.stringIndex;
            operand.operandType.referenceType = (char*) interpretador->topStackFrame->frame->execEnvir->belongingClass[stringIndex].info.Utf8Info.bytes;
            break;
        default:
            printf("Indice invalido.\n");
            exit(1);
	}
	pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x13*/
int ldc_w(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    u2 byte1, byte2;
    u2 index;
    u2 stringIndex;
    byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    index = (byte1 << 8) | byte2;
    switch (interpretador->topStackFrame->frame->execEnvir->belongingClass[index].tag) {
        case CONSTANT_Integer:
            operand.operandType.intType = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.IntegerInfo.bytes;
            break;
        case CONSTANT_Float:
            operand.operandType.floatType = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.FloatInfo.bytes;
            break;
        case CONSTANT_String:
            stringIndex = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.StringInfo.stringIndex;
            operand.operandType.referenceType = (char*) interpretador->topStackFrame->frame->execEnvir->belongingClass[stringIndex].info.Utf8Info.bytes;
            break;
        default:
            printf("Indice invalido.\n");
            exit(1);
	}
	pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x14*/
int ldc2_w(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    u2 byte1, byte2;
    u2 index;
    DoubleToInt dToi;
    LongToInt lToi;
    byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    index = (byte1 << 8) | byte2;
    switch (interpretador->topStackFrame->frame->execEnvir->belongingClass[index].tag) {
        case CONSTANT_Double:
            dToi.pairedInt[0] = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.DoubleInfo.highBytes;
            dToi.pairedInt[1] = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.DoubleInfo.lowBytes;
            operand.operandType.doubleType = dToi.d;
            break;
        case CONSTANT_Long:
            lToi.pairedInt[0] = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.LongInfo.highBytes;
            lToi.pairedInt[1] = interpretador->topStackFrame->frame->execEnvir->belongingClass[index].info.LongInfo.lowBytes;
            operand.operandType.longType = lToi.l;
            break;
        default:
            printf("Indice invalido.\n");
            exit(1);
    }
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x15*/
int iload(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    u2 index;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    operand.operandType.intType = interpretador->topStackFrame->frame->localVarArray[index];
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x16*/
int lload(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    u2 index;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    LongToInt lToi;
    lToi.pairedInt[0] = interpretador->topStackFrame->frame->localVarArray[index];
    lToi.pairedInt[1] = interpretador->topStackFrame->frame->localVarArray[index+1];
    operand.operandType.longType = lToi.l;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x17*/
int fload(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    u2 index;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    FloatToInt fToi;
    fToi.i = interpretador->topStackFrame->frame->localVarArray[index];
    operand.operandType.floatType = fToi.f;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x18*/
int dload(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    u2 index;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    DoubleToInt dToi;
    dToi.pairedInt[0] = interpretador->topStackFrame->frame->localVarArray[index];
    dToi.pairedInt[1] = interpretador->topStackFrame->frame->localVarArray[index+1];
    operand.operandType.doubleType = dToi.d;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x19*/
int aload(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    u2 index;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    operand.operandType.referenceType = interpretador->topStackFrame->frame->localVarArray[index];
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x1A*/
int iload_0(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = interpretador->topStackFrame->frame->localVarArray[0];
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x1B*/
int iload_1(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = interpretador->topStackFrame->frame->localVarArray[1];
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x1C*/
int iload_2(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = interpretador->topStackFrame->frame->localVarArray[2];
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x1D*/
int iload_3(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    operand.operandType.intType = interpretador->topStackFrame->frame->localVarArray[3];
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x1E*/
int lload_0(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    LongToInt lToi;
    lToi.pairedInt[0] = interpretador->topStackFrame->frame->localVarArray[0];
    lToi.pairedInt[1] = interpretador->topStackFrame->frame->localVarArray[1];
    operand.operandType.longType = lToi.l;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x1F*/
int lload_1(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    LongToInt lToi;
    lToi.pairedInt[0] = interpretador->topStackFrame->frame->localVarArray[1];
    lToi.pairedInt[1] = interpretador->topStackFrame->frame->localVarArray[2];
    operand.operandType.longType = lToi.l;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x20*/
int lload_2(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    LongToInt lToi;
    lToi.pairedInt[0] = interpretador->topStackFrame->frame->localVarArray[2];
    lToi.pairedInt[1] = interpretador->topStackFrame->frame->localVarArray[3];
    operand.operandType.longType = lToi.l;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x21*/
int lload_3(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    LongToInt lToi;
    lToi.pairedInt[0] = interpretador->topStackFrame->frame->localVarArray[3];
    lToi.pairedInt[1] = interpretador->topStackFrame->frame->localVarArray[4];
    operand.operandType.longType = lToi.l;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x22*/
int fload_0(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    FloatToInt fToi;
    fToi.i = interpretador->topStackFrame->frame->localVarArray[0];
    operand.operandType.floatType = fToi.f;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x23*/
int fload_1(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    FloatToInt fToi;
    fToi.i = interpretador->topStackFrame->frame->localVarArray[1];
    operand.operandType.floatType = fToi.f;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x24*/
int fload_2(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    FloatToInt fToi;
    fToi.i = interpretador->topStackFrame->frame->localVarArray[2];
    operand.operandType.floatType = fToi.f;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x25*/
int fload_3(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    FloatToInt fToi;
    fToi.i = interpretador->topStackFrame->frame->localVarArray[3];
    operand.operandType.floatType = fToi.f;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x26*/
int dload_0(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    DoubleToInt dToi;
    dToi.pairedInt[0] = interpretador->topStackFrame->frame->localVarArray[0];
    dToi.pairedInt[1] = interpretador->topStackFrame->frame->localVarArray[1];
    operand.operandType.doubleType = dToi.d;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x27*/
int dload_1(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    DoubleToInt dToi;
    dToi.pairedInt[0] = interpretador->topStackFrame->frame->localVarArray[1];
    dToi.pairedInt[1] = interpretador->topStackFrame->frame->localVarArray[2];
    operand.operandType.doubleType = dToi.d;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x28*/
int dload_2(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    DoubleToInt dToi;
    dToi.pairedInt[0] = interpretador->topStackFrame->frame->localVarArray[2];
    dToi.pairedInt[1] = interpretador->topStackFrame->frame->localVarArray[3];
    operand.operandType.doubleType = dToi.d;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x29*/
int dload_3(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT2;
    DoubleToInt dToi;
    dToi.pairedInt[0] = interpretador->topStackFrame->frame->localVarArray[3];
    dToi.pairedInt[1] = interpretador->topStackFrame->frame->localVarArray[4];
    operand.operandType.doubleType = dToi.d;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x2A*/
int aload_0(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    VoidToInt vToi;
    vToi.intAddress = interpretador->topStackFrame->frame->localVarArray[0];
    operand.operandType.referenceType = vToi.voidAddress;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x2B*/
int aload_1(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    VoidToInt vToi;
    vToi.intAddress = interpretador->topStackFrame->frame->localVarArray[1];
    operand.operandType.referenceType = vToi.voidAddress;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x2C*/
int aload_2(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    VoidToInt vToi;
    vToi.intAddress = interpretador->topStackFrame->frame->localVarArray[2];
    operand.operandType.referenceType = vToi.voidAddress;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x2D*/
int aload_3(Interpretador* interpretador) {
    Operand operand;
    operand.type32_64 = CAT1;
    VoidToInt vToi;
    vToi.intAddress = interpretador->topStackFrame->frame->localVarArray[3];
    operand.operandType.referenceType = vToi.voidAddress;
    pushOperand(&(interpretador->topStackFrame->frame->topOperand), operand);
    return 0;
}

/*0x36*/
int istore(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    u2 index;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    interpretador->topStackFrame->frame->localVarArray[index] = operand.operandType.intType;
    return 0;
}

/*0x37*/
int lstore(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    u2 index;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    LongToInt lToi;
    lToi.l = operand.operandType.longType;
    interpretador->topStackFrame->frame->localVarArray[index] = lToi.pairedInt[0];
    interpretador->topStackFrame->frame->localVarArray[index+1] = lToi.pairedInt[1];
    return 0;
}

/*0x38*/
int fstore(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    u2 index;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    interpretador->topStackFrame->frame->localVarArray[index] = operand.operandType.intType; // Acessa o valor float como tipo int
    return 0;
}

/*0x39*/
int dstore(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    u2 index;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    DoubleToInt dToi;
    dToi.d = operand.operandType.doubleType;
    interpretador->topStackFrame->frame->localVarArray[index] = dToi.pairedInt[0];
    interpretador->topStackFrame->frame->localVarArray[index+1] = dToi.pairedInt[1];
    return 0;
}

/*0x3A*/
int astore(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    u2 index;
    if(isWide){
        int byte1, byte2;
        byte1 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        byte2 = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
        index = (byte1 << 8) | byte2;
    } else {
        index = *(interpretador->topStackFrame->frame->execEnvir->pc);
        interpretador->topStackFrame->frame->execEnvir->pc++;
    }
    interpretador->topStackFrame->frame->localVarArray[index] = operand.operandType.intType; // Acessa o valor void* como tipo int
    return 0;
}

/*0x3B*/
int istore_0(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[0] = operand.operandType.intType;
    return 0;
}

/*0x3C*/
int istore_1(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[1] = operand.operandType.intType;
    return 0;
}

/*0x3D*/
int istore_2(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[2] = operand.operandType.intType;
    return 0;
}

/*0x3E*/
int istore_3(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[3] = operand.operandType.intType;
    return 0;
}

/*0x3F*/
int lstore_0(Interpretador* interpretador) {
    u1 index = 0;
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    LongToInt lToi;
    lToi.l = operand.operandType.longType;
    interpretador->topStackFrame->frame->localVarArray[index] = lToi.pairedInt[0];
    interpretador->topStackFrame->frame->localVarArray[index+1] = lToi.pairedInt[1];
    return 0;
}

/*0x40*/
int lstore_1(Interpretador* interpretador) {
    u1 index = 1;
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    LongToInt lToi;
    lToi.l = operand.operandType.longType;
    interpretador->topStackFrame->frame->localVarArray[index] = lToi.pairedInt[0];
    interpretador->topStackFrame->frame->localVarArray[index+1] = lToi.pairedInt[1];
    return 0;
}

/*0x41*/
int lstore_2(Interpretador* interpretador) {
    u1 index = 2;
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    LongToInt lToi;
    lToi.l = operand.operandType.longType;
    interpretador->topStackFrame->frame->localVarArray[index] = lToi.pairedInt[0];
    interpretador->topStackFrame->frame->localVarArray[index+1] = lToi.pairedInt[1];
    return 0;
}

/*0x42*/
int lstore_3(Interpretador* interpretador) {
    u1 index = 3;
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    LongToInt lToi;
    lToi.l = operand.operandType.longType;
    interpretador->topStackFrame->frame->localVarArray[index] = lToi.pairedInt[0];
    interpretador->topStackFrame->frame->localVarArray[index+1] = lToi.pairedInt[1];
    return 0;
}

/*0x43*/
int fstore_0(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[0] = operand.operandType.intType;
    return 0;
}

/*0x44*/
int fstore_1(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[1] = operand.operandType.intType;
    return 0;
}

/*0x45*/
int fstore_2(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[2] = operand.operandType.intType;
    return 0;
}

/*0x46*/
int fstore_3(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[3] = operand.operandType.intType;
    return 0;
}

/*0x47*/
int dstore_0(Interpretador* interpretador) {
    u1 index = 0;
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    DoubleToInt dToi;
    dToi.d = operand.operandType.doubleType;
    interpretador->topStackFrame->frame->localVarArray[index] = dToi.pairedInt[0];
    interpretador->topStackFrame->frame->localVarArray[index+1] = dToi.pairedInt[1];
    return 0;
}

/*0x48*/
int dstore_1(Interpretador* interpretador) {
    u1 index = 1;
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    DoubleToInt dToi;
    dToi.d = operand.operandType.doubleType;
    interpretador->topStackFrame->frame->localVarArray[index] = dToi.pairedInt[0];
    interpretador->topStackFrame->frame->localVarArray[index+1] = dToi.pairedInt[1];
    return 0;
}

/*0x49*/
int dstore_2(Interpretador* interpretador) {
    u1 index = 2;
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    DoubleToInt dToi;
    dToi.d = operand.operandType.doubleType;
    interpretador->topStackFrame->frame->localVarArray[index] = dToi.pairedInt[0];
    interpretador->topStackFrame->frame->localVarArray[index+1] = dToi.pairedInt[1];
    return 0;
}

/*0x4A*/
int dstore_3(Interpretador* interpretador) {
    u1 index = 3;
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    DoubleToInt dToi;
    dToi.d = operand.operandType.doubleType;
    interpretador->topStackFrame->frame->localVarArray[index] = dToi.pairedInt[0];
    interpretador->topStackFrame->frame->localVarArray[index+1] = dToi.pairedInt[1];
    return 0;
}

/*0x4B*/
int astore_0(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[0] = operand.operandType.intType; // Acessa o valor void* como tipo int
    return 0;
}

/*0x4C*/
int astore_1(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[1] = operand.operandType.intType; // Acessa o valor void* como tipo int
    return 0;
}

/*0x4D*/
int astore_2(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[2] = operand.operandType.intType; // Acessa o valor void* como tipo int
    return 0;
}

/*0x4E*/
int astore_3(Interpretador* interpretador) {
    Operand operand;
    operand = popOperand(&(interpretador->topStackFrame->frame->topOperand));
    interpretador->topStackFrame->frame->localVarArray[3] = operand.operandType.intType; // Acessa o valor void* como tipo int
    return 0;
}

/*0xC4*/
int wide(Interpretador* interpretador) {
    isWide = 1;
    u1 opcode = *(interpretador->topStackFrame->frame->execEnvir->pc);
    interpretador->topStackFrame->frame->execEnvir->pc++;
    InstructionArray[opcode](interpretador);
    isWide = 0;
    return 0;
}

