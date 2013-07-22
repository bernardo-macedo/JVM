#ifndef TYPECONVERSIONINSTRUCTIONS_H
#define TYPECONVERSIONINSTRUCTIONS_H

/** Converte o primeiro valor da pilha de int para long */
int i2l(Interpretador*); /*0x85*/

/** Converte o primeiro valor da pilha de int para float */
int i2f(Interpretador*); /*0x86*/

/** Converte o primeiro valor da pilha de int para double */
int i2d(Interpretador*); /*0x87*/

/** Converte o primeiro valor da pilha de long para int */
int l2i(Interpretador*); /*0x88*/

/** Converte o primeiro valor da pilha de long para float */
int l2f(Interpretador*); /*0x89*/

/** Converte o primeiro valor da pilha de long para double */
int l2d(Interpretador*); /*0x8A*/

/** Converte o primeiro valor da pilha de float para int */
int f2i(Interpretador*); /*0x8B*/

/** Converte o primeiro valor da pilha de float para long */
int f2l(Interpretador*); /*0x8C*/

/** Converte o primeiro valor da pilha de float para double */
int f2d(Interpretador*); /*0x8D*/

/** Converte o primeiro valor da pilha de double para int */
int d2i(Interpretador*); /*0x8E*/

/** Converte o primeiro valor da pilha de double para long */
int d2l(Interpretador*); /*0x8F*/

/** Converte o primeiro valor da pilha de double para float */
int d2f(Interpretador*); /*0x90*/

/** Converte o primeiro valor da pilha de int para byte */
int i2b(Interpretador*); /*0x91*/

/** Converte o primeiro valor da pilha de int para char */
int i2c(Interpretador*); /*0x92*/

/** Converte o primeiro valor da pilha de int para short */
int i2s(Interpretador*); /*0x93*/

#endif
