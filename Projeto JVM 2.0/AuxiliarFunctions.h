#ifndef FUNCOESGERAIS_H_
#define FUNCOESGERAIS_H_

#include "ClassFile.h"
#include "Controller.h"
#include "Execucao.h"


/** Retorna uma referência a um método a partir de seu name e de seu descriptor.
* \param classFile
* \param methodName Nome do método
* \param descriptor Descritor do método
* \return Referência para um MethodInfo
*/
MethodInfo* getMethodByName(ClassFile classFile, char* methodName, char* descriptor);

/** Retorna o nome da classe a partir de um path.
* \param classNameFiltered Nome da classe sem o path. O resultado desta função será armazenado nesta variável
* \param className Nome da classe ainda com o path e o .class (se tiver)
*/
void getClassNameFiltered(char* classNameFiltered, char* className);

/** Verifica se uma classe já está carregada na memória.
* Pesquisa no constantPool de cada classe da ClassList.
* \return Referência para a classe */
ClassFile* getClassFileName(ClassList* init, char* className);

/** Lê o byte seguinte ao pc e incrementa pc.
* \param StackFrame* Ponteiro para um elemento StackFrame
* \return Byte subsequente a pc
*/
u1 readU1Code(frame*);

/** Lê dois bytes à frente de pc e incrementa pc em dois.
* \param StackFrame* Ponteiro para um elemento StackFrame
* \return Dois bytes subsequentes a pc
*/
u2 readU2Code(frame*);

/** Lê quatro bytes à frente de pc e incrementa pc em quatro.
* \param StackFrame* Ponteiro para um elemento StackFrame
* \return Quatro bytes subsequentes a pc
*/
u4 readU4Code(frame *fr);

/** Conta quantos argumentos são passados no descriptor.
* Varre o descriptor até encontrar um parênteses ')' e vai contando o número de argumentos.
* \param descriptor Descritor
* \return Número de argumentos
*/
int methodArgumentCount(u1* descriptor);

/** Busca o Field a partir do name da classe e do name do Field
* \param className
* \param fieldName
* \return Field
*/
Field* getStaticFieldName(ClassList *init, char* className, char* fieldName);

/** Insere um fieldType no static Field.
* \param ClassList Lista de classes
* \param className Nome da classe
* \param fieldName Nome do Field
* \param operand Valor a ser inserido
*/
void insertStaticFieldValue(ClassList *init, char* className, char* fieldName, OperandType operand);

/** Busca o atributo UTF8 a partir de um índice.
* \param CpInfo
* \param index
* Ponteiro para o atributo
*/
u1* getUtf8(CpInfo* cpInfo, u2 index);

/** Aloca um multiarray
* \param dimensions Número de dimensões do array
* \param sizesArray Array com os sizesArray de cada dimensão
* \return Referência para o array alocado
*/
Array* allocateMultiArray(int dimensions, int* sizesArray);

/** Retorna o número de Fields que o objeto vai ter
* \param Interpretador
* \param ClassFile
* \return Número de fields
*/
int fieldsCount(Interpretador* interpretador, ClassFile classFile);

/** Preenche o array de fields de um objeto com os fields das classes relacionadas a ele.
* \param Interpretador
* \param ClassFile
* \param Field
*/
void fieldsObjectInit(Interpretador *interpretador, ClassFile classFile, Field* fields);

/** Retorna uma referência para um Field a partir de seu name
* \param fieldName Nome do Field
* \param descriptor Descritor do Field
* \param Object
* \return Referência para o Field
*/
Field* getFieldName(char* name, char* descriptor, object* object);

#endif /* FUNCOESGERAIS_H_ */
