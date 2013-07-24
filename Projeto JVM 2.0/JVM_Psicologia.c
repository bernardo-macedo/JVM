/*
 * Arquivo inicial da JVM.
 *
 * Começa a ler o arquivo .class, faz a tarefa do ClassLoader
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ClassFile.h"
#include "DebugFuncs.h"
#include "ClassLoader.h"
#include "Frame.h"
#include "FuncoesGerais.h"
#include "Instrucoes.h"

int main(int argc, char* argv[]) {

	if (argc == 2) {

		char nomeClasse[30];
		execucao *p;

		p = malloc(sizeof(execucao));

		strcpy(nomeClasse, argv[1]);

		inicializaPilhaFrames(&(p->frameAtual));
		inicializaClassFileLista(&(p->pInicioLista));

		preparaExecucaoMetodo(nomeClasse, "main", "([Ljava/lang/String;)V", p,
				0);

		executaMetodo(p);

	} else {
		printf("ERRO! Possíveis causas:\n");
		printf("\t1. Mais de um argumento de linha de comando foi passado\n");
		printf("\t2. Nao foi passado um argumento de linha de comando\n");
	}

	return 0;
}
