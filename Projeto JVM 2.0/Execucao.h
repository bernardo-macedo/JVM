#ifndef EXECUCAO_H_
#define EXECUCAO_H_

#include "Frame.h"
#include "ClassFile.h"
#include "Instrucoes.h"


/** Inicializa a ClassList com NULL
* \param ClassList* Endere�o da lista a ser iniciada
*/
void classListInit(ClassList** listAddress);

/** Adiciona um ClassFile � ClassList.
* \param ClassList** Endere�o da lista de classes
* \param ClassFile ClassFile a ser inserido
*/
void classListInsert(ClassList** listAddress, ClassFile classFile);

/** Verifica se uma classe j� est� carregada na mem�ria.
* Se n�o estiver, aloca espa�o para ela e a  inicializa
* \param Interpretador
* \param className Nome da classe
* \return Refer�ncia para o ClassFile
*/
ClassFile* checkClass(Interpretador* interpretador, char* className);

/** Inicializa e executa um m�todo
* \param className Nome da classe
* \param methodName Nome do m�todo
* \param descriptor Descritor do m�todo
* \param Interpretador
* \param numArgs N�mero de argumentos
*/
void prepareMethod(char* className, char* methodName, char* descriptor, Interpretador *interpretador, int numArgs);

/** Executa o m�todo
* \param Interpretador
*/
void runMethod(Interpretador *interpretador);

#endif /* EXECUCAO_H_ */
