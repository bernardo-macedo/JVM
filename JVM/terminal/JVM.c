/**
*  Implementa��o da JVM vers�o 1.2
*  Alunos:
*    Bernardo Mac�do - 10/0008224
*    Renata Cristina - 10/0020089
*    Lu�sa Behrens - 10/0016286
*  Instru��es:
*    Ap�s a compila��o, executar a JVM com os seguintes parametros
*       <nome_do_arquivo_da_jvm> <opcao_imprimir_arquivo_class> <arquivo.class>
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ClassLoader.h"
#include "ClassStructure.h"
#include "InstructionManager.h"
#include "Controller.h"

int main(int argc, char *argv[])
{
	char classpath[100];
	Interpretador* interpretador;

	interpretador = malloc(sizeof(Interpretador));
	frameStackInit(&(interpretador->topStackFrame));
	initClassList(&(interpretador->initClass));
    /*
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
	strcpy(classpath, argv[2]);

    methodInit(classpath, "main", "([Ljava/lang/String;)V", interpretador, 0, atoi(argv[1]));
    */
    printf("COMECOU\n");
    methodInit("testeLogArit.class", "main", "([Ljava/lang/String;)V", interpretador, 0, 0);
	//initiateExecution(classpath, "main", "([Ljava/lang/String;)V", (argc - 3), atoi(argv[1]));

	return 0;
}
