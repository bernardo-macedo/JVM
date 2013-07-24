#ifndef FRAME_H_
#define FRAME_H_

#define TIPO1 1
#define TIPO2 0

#include "DebugFuncs.h"
#include "ClassFile.h"


/** Possíveis tipos de um Operando.
*/
typedef union OperandType {
	int intType;
	long long longType;
	float floatType;
	double doubleType;
	void* referenceType;
} OperandType;

/** Pilha de operandos.
* Contém uma variável que indica o tipo do operando, uma que indica se é Tipo 1 ou Tipo 2
* e um ponteiro para o próximo operando da pilha.
*/
typedef struct OperandStack {
	OperandType operand;
	int type32_64;
	struct OperandStack *nextOperand;
} OperandStack;

/** O Frame é composto de um array de variáveis locais, uma pilha de operandos
* e um ambiente de execução dos métodos.
* A seção de ambiente de execução compreende as variáveis *constantPool, *currOpcode e *pc.
* Contém um ponteiro para a classe à qual o método pertence,
* um ponteiro para o opcode da instrução sendo lida
* e um program counter, que indica o endereço da instrução sendo lida
*/
typedef struct Frame {
	Operand *localVarArray;
	OperandStack *topOperand;
	CpInfo *constantPool;
	u1* currOpcode;
	u1 *pc;
} Frame;

/** O StackFrame é a pilha de frames da JVM.
* ou seja, a Stack.
*/
typedef struct StackFrame {
	Frame frame;
	struct StackFrame *nextFrame;
} StackFrame;

/** Possíveis tipos de um Field.
*/
typedef union FieldType {
	int intType;
	short shortType;
	float floatType;
	long long longType;
	double doubleType;
	char charType;
	void* referenceType;
} FieldType;

/** Estrutura que define um field.
* Contém o nome, o descritor e o tipo do field.
*/
typedef struct Field {
	char* name;
	char* descriptor;
	FieldType fieldType;
} Field;

/** Estrutura que define um objeto.
* Contém a quantidade de campos e os campos.
*/
typedef struct Object {
	int fieldsCount;
	Field* fields;
} Object;

/** Estrutura que define uma lista de objetos
*/
typedef struct ObjectList {
	Object object;
	struct ObjectList *nextObject;
} ObjectList;

/** O ClassList é uma lista de classes já carregadas.
* É tarefa do interpretador, quando for necessário, buscar nesta lista se uma classe já foi carregada
* e carregá-la caso não tenha sido.
*/
typedef struct ClassList {
	ClassFile classFile;
	int staticFieldsCount;
	Field* staticFields;
	ObjectList* objectsList;
	struct ClassList *nextClass;
} ClassList;

/** O Interpretador possui uma referência para o frame mais recente da pilha de frames
* e para a classe mais recente da lista de classes
*/
typedef struct Interpretador {
	StackFrame* topStackFrame;
	ClassList* topClass;
} Interpretador;

/** Estrutura que modela o array que será usado nas instruções de objetos
*/
typedef struct Array {
	int size, type;
	OperandType* array;
} Array;

/* ******************** Funções ******************** */

/** Função que verifica se a pilha de operandos está vazia.
* \param OperandStack* Ponteiro para a pilha de operandos
* \return 1 se a pilha estiver vazia, 0 se não estiver
*/
int emptyStack(OperandStack *topoPilha);

/** Função que coloca um operand na pilha de operandos.
* \param OperandStack** Endereço da pilha de operandos
* \param Operand Operando a ser empilhado
*/
void pushOperand(OperandStack **topAddress, Operand operand, int type32_64);

/** Função que remove um operand da pilha de operandos.
* \param OperandStack** Endereço da pilha de operandos
* \return Operando que foi desempilhado
*/
Operand popOperand(OperandStack **topAddress);

/** Função que inicializa a pilha de operandos.
* \param OperandStack** Endereço da pilha de operandos
*/
void stackInit(OperandStack **stackAddress);

/** Função que verifica se a pilha de frames está vazia.
* \param StackFrame* Ponteiro para a pilha de frames
* \return 1 se a pilha estiver vazia, 0 se não estiver
*/
void emptyStackFrame(StackFrame *topStackFrame);

/** Função que inicializa a pilha de frames.
* \param Endereço da pilha de frames
*/
void stackFrameInit(StackFrame **topFrameAddress);

/** Função que cria um novo frame na pilha de frames
* \param StackFrame** Endereço da pilha de frames
*/
void pushFrame(StackFrame **topFrameAddress);

/** Função que remove um frame da pilha de frames
* \param StackFrame** Endereço da pilha de frames
*/
void popFrame(StackFrame **topFrameAddress);

/** Função que inicializa um frame
* \param ClassList* Lista de classes
* \param ClassFile
* \param StackFrame* Pilha de frames
* \param char* Nome do método
* \param char* Descrição do método
*/
void frameInit(ClassList *init, ClassFile classFile, StackFrame *StackFrame, char* methodName, char* descriptor);

#endif /* PILHAOPERANDOS_H_ */
