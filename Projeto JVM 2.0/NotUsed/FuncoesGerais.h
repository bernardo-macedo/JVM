/*
 * FuncoesGerais.h
 *
 *  Created on: 15/02/2013
 *      Author: Vitor
 */

#ifndef FUNCOESGERAIS_H_
#define FUNCOESGERAIS_H_

#include "ClassFile.h"
#include "Frame.h"
#include "Execucao.h"

methodInfo* buscaMetodoNome(ClassFile cf, char* nomeMetodo, char* descriptor);

ClassFile* buscaClassFileNome(listaClasses* inicioLista, char* nomeClasse);

u1* buscaUTF8ConstPool(cpInfo* cp, u2 indice);

u1 lerU1Codigo(frame*);

u2 lerU2Codigo(frame*);

u4 lerU4Codigo(frame *fr);

field* buscaStaticFieldNome(listaClasses *inicioLista, char* nomeClasse,
		char* nomeField);

void insereValorStaticField(listaClasses *inicioLista, char* nomeClasse,
		char* nomeField, tipoOperando op);

void limpaPathClasseParaNome(char* nomeClasseSemPath, char* nomeClasse);

int contaArgumentosMetodo(u1* descriptor);

Vetor* alocaMultiArray(int dimenssoes, int* tamanhos);

int contaNumFields(execucao* p, ClassFile cf);

void inicializaFieldsObjeto(execucao *p, ClassFile cf, field* fields);

field* buscaFieldNome(char*, char*, object*);

#endif /* FUNCOESGERAIS_H_ */
