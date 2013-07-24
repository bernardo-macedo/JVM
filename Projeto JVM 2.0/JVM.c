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
#include "AuxiliarFunctions.h"
#include "Instrucoes.h"


int main(int argc, char* argv[]) {

	if (argc == 2) {

		char className[30];
		Interpretador *interpretador;

		interpretador = malloc(sizeof(Interpretador));

		strcpy(className, argv[1]);

		stackFrameInit(&(interpretador->topFrame));
		classListInit(&(interpretador->topClass));

		prepareMethod(className, "main", "([Ljava/lang/String;)V", interpretador,
				0);

		runMethod(interpretador);

	} else {
		printf("ERRO! Possíveis causas:\n");
		printf("\t1. Mais de um argumento de linha de comando foi passado\n");
		printf("\t2. Nao foi passado um argumento de linha de comando\n");
	}

	return 0;
}
