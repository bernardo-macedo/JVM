#ifndef FUNCOESGERAIS_H_
#define FUNCOESGERAIS_H_

#include "ClassFile.h"
#include "Controller.h"
#include "Execucao.h"


/** Retorna uma refer�ncia a um m�todo a partir de seu name e de seu descriptor.
* \param classFile
* \param methodName Nome do m�todo
* \param descriptor Descritor do m�todo
* \return Refer�ncia para um MethodInfo
*/
MethodInfo* getMethodByName(ClassFile classFile, char* methodName, char* descriptor);

/** Retorna o nome da classe a partir de um path.
* \param classNameFiltered Nome da classe sem o path. O resultado desta fun��o ser� armazenado nesta vari�vel
* \param className Nome da classe ainda com o path e o .class (se tiver)
*/
void getClassNameFiltered(char* classNameFiltered, char* className);

/** Verifica se uma classe j� est� carregada na mem�ria.
* Pesquisa no constantPool de cada classe da ClassList.
* \return Refer�ncia para a classe */
ClassFile* getClassFileName(ClassList* init, char* className);

/** L� o byte seguinte ao pc e incrementa pc.
* \param StackFrame* Ponteiro para um elemento StackFrame
* \return Byte subsequente a pc
*/
u1 readU1Code(frame*);

/** L� dois bytes � frente de pc e incrementa pc em dois.
* \param StackFrame* Ponteiro para um elemento StackFrame
* \return Dois bytes subsequentes a pc
*/
u2 readU2Code(frame*);

/** L� quatro bytes � frente de pc e incrementa pc em quatro.
* \param StackFrame* Ponteiro para um elemento StackFrame
* \return Quatro bytes subsequentes a pc
*/
u4 readU4Code(frame *fr);

/** Conta quantos argumentos s�o passados no descriptor.
* Varre o descriptor at� encontrar um par�nteses ')' e vai contando o n�mero de argumentos.
* \param descriptor Descritor
* \return N�mero de argumentos
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

/** Busca o atributo UTF8 a partir de um �ndice.
* \param CpInfo
* \param index
* Ponteiro para o atributo
*/
u1* getUtf8(CpInfo* cpInfo, u2 index);

/** Aloca um multiarray
* \param dimensions N�mero de dimens�es do array
* \param sizesArray Array com os sizesArray de cada dimens�o
* \return Refer�ncia para o array alocado
*/
Array* allocateMultiArray(int dimensions, int* sizesArray);

/** Retorna o n�mero de Fields que o objeto vai ter
* \param Interpretador
* \param ClassFile
* \return N�mero de fields
*/
int fieldsCount(Interpretador* interpretador, ClassFile classFile);

/** Preenche o array de fields de um objeto com os fields das classes relacionadas a ele.
* \param Interpretador
* \param ClassFile
* \param Field
*/
void fieldsObjectInit(Interpretador *interpretador, ClassFile classFile, Field* fields);

/** Retorna uma refer�ncia para um Field a partir de seu name
* \param fieldName Nome do Field
* \param descriptor Descritor do Field
* \param Object
* \return Refer�ncia para o Field
*/
Field* getFieldName(char* name, char* descriptor, object* object);

#endif /* FUNCOESGERAIS_H_ */
