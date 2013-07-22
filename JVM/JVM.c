/**
*  Implementação da JVM versão 1.2
*  Alunos:
*    Bernardo Macêdo - 10/0008224
*    Renata Cristina - 10/0020089
*    Luísa Behrens - 10/?
*  Instruções:
*    Após a compilação, executar a JVM com os seguintes parametros
*       <nome_do_arquivo_da_jvm> <opcao_imprimir_arquivo_class> <arquivo.class>
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ClassLoader.h"
#include "ClassStructure.h"
#include "InstructionManager.h"
#include "Controller.h"

int main(int argc, char *argv[])
{
	//char *classpath;
	Interpretador* interpretador;

	interpretador = malloc(sizeof(Interpretador));
	frameStackInit(&(interpretador->topStackFrame));
	initClassList(&(interpretador->initClass));

	if(argc < 3)
	{
		printf("ERRO: formato de entrada invalido.Use:\nnome_programa opcao_imprimir arquivo.class\n\nA opcao_imprimir pode ser 0 caso nao queira imrpimir o ClassFile ou 1 caso queira");
		exit(1);
	}
	if((atoi(argv[1]) != 0) && (atoi(argv[1]) != 1))
	{
		printf("ERRO: opcao_imprimir errada. Use 0 (para NAO imprimir) ou 1 (para imprimir)");
		exit(1);
	}
	//strcpy(classpath, argv[2]);
    methodInit(argv[2], "main", "([Ljava/lang/String;)V", interpretador, 0, atoi(argv[1]));

	//initiateExecution(classpath, "main", "([Ljava/lang/String;)V", (argc - 3), atoi(argv[1]));

	return 0;
}
