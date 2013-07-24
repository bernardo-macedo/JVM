/*
 * Instrucoes.h
 *
 *  Created on: 08/02/2013
 *      Author: Vitor
 */

#ifndef INSTRUCOES_H_
#define INSTRUCOES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Frame.h"
#include "Execucao.h"
#include "ClassLoader.h"
#include "AuxiliarFunctions.h"
#include "ClassFile.h"

int nop(Interpretador *interpretador); // 0x00
int aconst_null(Interpretador *interpretador); // 0x01
int iconst_m1(Interpretador *interpretador); //0x2
int iconst_0(Interpretador *interpretador); // 0x3
int iconst_1(Interpretador *interpretador); // 0x4
int iconst_2(Interpretador *interpretador); // 0x5
int iconst_3(Interpretador *interpretador); // 0x6
int iconst_4(Interpretador *interpretador); // 0x7
int iconst_5(Interpretador *interpretador); // 0x8
int lconst_0(Interpretador *interpretador); // 0x9
int lconst_1(Interpretador *interpretador); // 0xA
int fconst_0(Interpretador *interpretador); // 0xB
int fconst_1(Interpretador *interpretador); // 0xC
int fconst_2(Interpretador *interpretador); // 0xD
int dconst_0(Interpretador *interpretador); // 0xE
int dconst_1(Interpretador *interpretador); // 0xF

// push ------------------------------------------------------------
int bipush(Interpretador *interpretador); // 0x10
int sipush(Interpretador *interpretador); // 0x11

int ldc(Interpretador *interpretador); // 0x12
int ldc_w(Interpretador *interpretador); // 0x13
int ldc2_w(Interpretador *interpretador); // 0x14

// load ------------------------------------------------------------
int iload(Interpretador *interpretador); //0x15
int lload(Interpretador *interpretador); //0x16
int fload(Interpretador *interpretador); //0x17
int dload(Interpretador *interpretador); //0x18
int aload(Interpretador *interpretador); //0x19
int iload_0(Interpretador *interpretador); //0x1A
int iload_1(Interpretador *interpretador); // 0X1B
int iload_2(Interpretador *interpretador); // 0X1C
int iload_3(Interpretador *interpretador); // 0X1D
int lload_0(Interpretador *interpretador); // 0x1E
int lload_1(Interpretador *interpretador); // 0x1F
int lload_2(Interpretador *interpretador); // 0x20
int lload_3(Interpretador *interpretador); // 0x21
int fload_0(Interpretador *interpretador); // 0x22
int fload_1(Interpretador *interpretador); // 0x23
int fload_2(Interpretador *interpretador); // 0x24
int fload_3(Interpretador *interpretador); // 0x25
int dload_0(Interpretador *interpretador); // 0x26
int dload_1(Interpretador *interpretador); // 0x27
int dload_2(Interpretador *interpretador); // 0x28
int dload_3(Interpretador *interpretador); // 0x29
int aload_0(Interpretador *interpretador); // 0x2A
int aload_1(Interpretador *interpretador); // 0x2B
int aload_2(Interpretador *interpretador); // 0x2C
int aload_3(Interpretador *interpretador); // 0x2D

//Aload ---------------------------------------------------------------
int iaload(Interpretador *interpretador); // 0x2E , 0X33 , 0X34 , 0X35
int laload(Interpretador *interpretador); // 0X2F
int faload(Interpretador *interpretador); // 0X 30
int daload(Interpretador *interpretador); // 0X31
int aaload(Interpretador *interpretador); // 0X32

// store ------------------------------------------------------------

int store(Interpretador *interpretador); // 0x36 , 0x37 , 0x38, 0x39 , 0x3A
int store_0(Interpretador *interpretador); //0x3B , 0X3F , 0X43 , 0X47 , 0X4B
int store_1(Interpretador *interpretador); //0X3C , 0X40 , 0X44 , 0X48 , 0X4C
int store_2(Interpretador *interpretador); //0X3D , 0X41 , 0X45 , 0X49 , 0X4D
int store_3(Interpretador *interpretador); //0X3E , 0X42 , 0X46 , 0X4A , 0X4E

//Astore -----------------------------------------------------------

int iastore(Interpretador *interpretador); //0x4f , 0x54 , 0x55 , 0x56
int lastore(Interpretador *interpretador); //0x50
int fastore(Interpretador *interpretador); //0x51
int dastore(Interpretador *interpretador); //0x52
int aastore(Interpretador *interpretador); //0x53
//pop ---------------------------------------------------------------
int pop(Interpretador *interpretador); //0x57
int pop2(Interpretador *interpretador); //0x58
// dup --------------------------------------------------------------
int dup(Interpretador *interpretador); // 0x59
int dup_x1(Interpretador *interpretador); // 0x5A
int dup_x2(Interpretador *interpretador); // 0x5B
int dup2(Interpretador *interpretador); // 0x5C
int dup2_x1(Interpretador *interpretador); // 0x5D
int dup2_x2(Interpretador *interpretador); // 0x5E
// swap ----------------------------------------------------------
int swap(Interpretador *interpretador);  //0x5F
// add ------------------------------------------------------------

int iadd(Interpretador *interpretador);  //0x60
int ladd(Interpretador *interpretador);  //0x61
int fadd(Interpretador *interpretador);  //0x62
int dadd(Interpretador *interpretador);  //0x63
// sub ------------------------------------------------------------

int isub(Interpretador *interpretador);  //0x64
int lsub(Interpretador *interpretador);  //0x65
int fsub(Interpretador *interpretador);  //0x66
int dsub(Interpretador *interpretador);  //0x67

// mul ------------------------------------------------------------
int imul(Interpretador *interpretador);  //0x68
int lmul(Interpretador *interpretador);  //0x69
int fmul(Interpretador *interpretador);  //0x6A
int dmul(Interpretador *interpretador);  //0x6B

// div-------------------------------------------------------------
int idiv(Interpretador *interpretador);  //0x6C
int ldiv_(Interpretador *interpretador);  //0x6D
int fdiv(Interpretador *interpretador);  //0x6E
int ddiv(Interpretador *interpretador);  //0x6F

// rem -----------------------------------------------------------
int irem(Interpretador *interpretador);  //0x70
int lrem(Interpretador *interpretador);  //0x71
int frem(Interpretador *interpretador);  //0x72
int drem_(Interpretador *interpretador);  //0x73

// neg -----------------------------------------------------------
int ineg(Interpretador *interpretador);  //0x74
int lneg(Interpretador *interpretador);  //0x75
int fneg(Interpretador *interpretador);  //0x76
int dneg(Interpretador *interpretador);  //0x77

// shl -----------------------------------------------------------
int ishl(Interpretador *interpretador);  //0x78
int lshl(Interpretador *interpretador);  //0x79

// shr -----------------------------------------------------------
int ishr(Interpretador *interpretador);  //0x7A
int lshr(Interpretador *interpretador);  //0x7B
//ushift -----------------------------------------------------------
int iushr(Interpretador *interpretador); //0x7C
int lushr(Interpretador *interpretador); //0x7D

//Bitwise ---------------------------------------------------------
int iand(Interpretador *interpretador);  //0x7E
int land(Interpretador *interpretador);  //0x7F
int ior(Interpretador *interpretador);  //0x80
int lor(Interpretador *interpretador);  //0x81
int ixor(Interpretador *interpretador);  //0x82
int lxor(Interpretador *interpretador);  //0x83
int iinc(Interpretador *interpretador); // 0x84

//x2y -------------------------------------------------------------
int i2l(Interpretador *interpretador);  //0x85
int i2f(Interpretador *interpretador);  //0x86
int i2d(Interpretador *interpretador);  //0x87

int l2i(Interpretador *interpretador);  //0x88
int l2f(Interpretador *interpretador);  //0x89
int l2d(Interpretador *interpretador);  //0x8A

int f2i(Interpretador *interpretador);  //0x8B
int f2l(Interpretador *interpretador);  //0x8C
int f2d(Interpretador *interpretador);  //0x8D

int d2i(Interpretador *interpretador);  //0x8E
int d2l(Interpretador *interpretador);  //0x8F
int d2f(Interpretador *interpretador);  //0x90

int i2c(Interpretador *interpretador);  //0x91, 0x92
int i2s(Interpretador *interpretador);  //0x93
//XcmpY ------------------------------------------------------------------
int lcmp(Interpretador *interpretador);  //0x94
int fcmpl(Interpretador *interpretador);  //0x95
int fcmpg(Interpretador *interpretador);  //0x96
int dcmpl(Interpretador *interpretador);  //0x97
int dcmpg(Interpretador *interpretador);  //0x98
// IF --------------------------------------------------------------------
int ifeq(Interpretador *interpretador);  //0x99
int ifne(Interpretador *interpretador);  //0x9A
int iflt(Interpretador *interpretador);  //0x9B
int ifge(Interpretador *interpretador);  //0x9C
int ifgt(Interpretador *interpretador);  //0x9D
int ifle(Interpretador *interpretador);  //0x9E
int if_icmpeq(Interpretador *interpretador);  //0x9F
int if_icmpne(Interpretador *interpretador);  //0xA0
int if_icmplt(Interpretador *interpretador);  //0xA1
int if_icmpge(Interpretador *interpretador);  //0xA2
int if_icmpgt(Interpretador *interpretador);  //0xA3
int if_icmple(Interpretador *interpretador);  //0xA4
int if_acmpeq(Interpretador *interpretador);  //0xA5
int if_acmpne(Interpretador *interpretador);  //0xA6

// controle ---------------------------------------------------------
int goto_(Interpretador *interpretador); // 0xA7
int jsr(Interpretador *interpretador); // 0xA8
int ret(Interpretador *interpretador); // 0xA9
//Switch -------------------------------------------------------------

int tableswitch(Interpretador *interpretador); //0xAA
int lookupswitch(Interpretador *interpretador); //0xAB
// retornos ------------------------------------------------------
int ireturn(Interpretador *interpretador);  //0xAC
int lreturn(Interpretador *interpretador);  //0xAD
int freturn(Interpretador *interpretador);  //0xAE
int dreturn(Interpretador *interpretador);  //0xAF
int areturn(Interpretador *interpretador);  //0xB0
int return_(Interpretador *interpretador);  //0xB1

// static --------------------------------------------------------
int getstatic(Interpretador *interpretador); // 0xB2
int putstatic(Interpretador *interpretador); // 0xB3
// Field ------------------------------------------------------------
int getfield(Interpretador *interpretador); // 0xB4
int putfield(Interpretador *interpretador); //0xB5
// invokes -------------------------------------------------------
int invokevirtual(Interpretador *interpretador); // 0xB6
int invokespecial(Interpretador *interpretador); // 0xB7
int invokestatic(Interpretador *interpretador); // 0xB8

//Objetos --------------------------------------------------------
int new_(Interpretador *interpretador); //0xBB
//Array ------------------------------------------------------------
int newarray(Interpretador *interpretador); //0xBC
int anewarray(Interpretador *interpretador); //0xBD
int arraylength(Interpretador *interpretador); // 0xBE
//Array -------------------------------------------------------------
int multianewarray(Interpretador *interpretador); // 0xC5
//if_null------------------------------------------------------------
int ifnull(Interpretador *interpretador); //0xC6
int ifnonnull(Interpretador *interpretador); //0xc7
//controle_wide----------------------------------------------------------
int goto_w(Interpretador *interpretador); //0xC8
int jsr_w(Interpretador *interpretador); //0xC9

int (*vetInstr[])(Interpretador *interpretador);

#endif /* INSTRUCOES_H_ */
