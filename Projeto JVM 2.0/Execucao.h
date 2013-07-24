#ifndef EXECUCAO_H_
#define EXECUCAO_H_

#include "Frame.h"
#include "ClassFile.h"
#include "Instrucoes.h"


/** Inicializa a ClassList com NULL
* \param ClassList* Endereço da lista a ser iniciada
*/
void classListInit(ClassList** listAddress);

/** Adiciona um ClassFile à ClassList.
* \param ClassList** Endereço da lista de classes
* \param ClassFile ClassFile a ser inserido
*/
void classListInsert(ClassList** listAddress, ClassFile classFile);

/** Verifica se uma classe já está carregada na memória.
* Se não estiver, aloca espaço para ela e a  inicializa
* \param Interpretador
* \param className Nome da classe
* \return Referência para o ClassFile
*/
ClassFile* checkClass(Interpretador* interpretador, char* className);

/** Inicializa e executa um método
* \param className Nome da classe
* \param methodName Nome do método
* \param descriptor Descritor do método
* \param Interpretador
* \param numArgs Número de argumentos
*/
void prepareMethod(char* className, char* methodName, char* descriptor, Interpretador *interpretador, int numArgs);

/** Executa o método
* \param Interpretador
*/
void runMethod(Interpretador *interpretador);

#endif /* EXECUCAO_H_ */
