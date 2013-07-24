/*
 * Execucao.h
 *
 *  Created on: 21/02/2013
 *      Author: Vitor
 */

#ifndef EXECUCAO_H_
#define EXECUCAO_H_

#include "Frame.h"
#include "ClassFile.h"
#include "Instrucoes.h"

void inicializaClassFileLista(listaClasses** endInicioLista);

void insereClassFileLista(listaClasses** endInicioLista, ClassFile cf);

ClassFile* verificaClasse(execucao* p, char* nomeClasse);

void preparaExecucaoMetodo(char* nomeClasse, char* nomeMetodo, char* descriptor,
		execucao *p, int numArgs);

void executaMetodo(execucao *p);

#endif /* EXECUCAO_H_ */
