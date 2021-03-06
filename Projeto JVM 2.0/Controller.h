#ifndef FRAME_H_
#define FRAME_H_

#define TIPO1 1
#define TIPO2 0

#include "DebugFuncs.h"
#include "ClassFile.h"


/** Poss�veis tipos de um Operando.
*/
typedef union OperandType {
	int intType;
	long long longType;
	float floatType;
	double doubleType;
	void* referenceType;
} OperandType;

/** Pilha de operandos.
* Cont�m uma vari�vel que indica o tipo do operando, uma que indica se � Tipo 1 ou Tipo 2
* e um ponteiro para o pr�ximo operando da pilha.
*/
typedef struct OperandStack {
	OperandType operand;
	int type32_64;
	struct OperandStack *nextOperand;
} OperandStack;

/** O Frame � composto de um array de vari�veis locais, uma pilha de operandos
* e um ambiente de execu��o dos m�todos.
* A se��o de ambiente de execu��o compreende as vari�veis *constantPool, *currOpcode e *pc.
* Cont�m um ponteiro para a classe � qual o m�todo pertence,
* um ponteiro para o opcode da instru��o sendo lida
* e um program counter, que indica o endere�o da instru��o sendo lida
*/
typedef struct Frame {
	Operand *localVarArray;
	OperandStack *topOperand;
	CpInfo *constantPool;
	u1* currOpcode;
	u1 *pc;
} Frame;

/** O StackFrame � a pilha de frames da JVM.
* ou seja, a Stack.
*/
typedef struct StackFrame {
	Frame frame;
	struct StackFrame *nextFrame;
} StackFrame;

/** Poss�veis tipos de um Field.
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
* Cont�m o nome, o descritor e o tipo do field.
*/
typedef struct Field {
	char* name;
	char* descriptor;
	FieldType fieldType;
} Field;

/** Estrutura que define um objeto.
* Cont�m a quantidade de campos e os campos.
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

/** O ClassList � uma lista de classes j� carregadas.
* � tarefa do interpretador, quando for necess�rio, buscar nesta lista se uma classe j� foi carregada
* e carreg�-la caso n�o tenha sido.
*/
typedef struct ClassList {
	ClassFile classFile;
	int staticFieldsCount;
	Field* staticFields;
	ObjectList* objectsList;
	struct ClassList *nextClass;
} ClassList;

/** O Interpretador possui uma refer�ncia para o frame mais recente da pilha de frames
* e para a classe mais recente da lista de classes
*/
typedef struct Interpretador {
	StackFrame* topStackFrame;
	ClassList* topClass;
} Interpretador;

/** Estrutura que modela o array que ser� usado nas instru��es de objetos
*/
typedef struct Array {
	int size, type;
	OperandType* array;
} Array;

/* ******************** Fun��es ******************** */

/** Fun��o que verifica se a pilha de operandos est� vazia.
* \param OperandStack* Ponteiro para a pilha de operandos
* \return 1 se a pilha estiver vazia, 0 se n�o estiver
*/
int emptyStack(OperandStack *topoPilha);

/** Fun��o que coloca um operand na pilha de operandos.
* \param OperandStack** Endere�o da pilha de operandos
* \param Operand Operando a ser empilhado
*/
void pushOperand(OperandStack **topAddress, Operand operand, int type32_64);

/** Fun��o que remove um operand da pilha de operandos.
* \param OperandStack** Endere�o da pilha de operandos
* \return Operando que foi desempilhado
*/
Operand popOperand(OperandStack **topAddress);

/** Fun��o que inicializa a pilha de operandos.
* \param OperandStack** Endere�o da pilha de operandos
*/
void stackInit(OperandStack **stackAddress);

/** Fun��o que verifica se a pilha de frames est� vazia.
* \param StackFrame* Ponteiro para a pilha de frames
* \return 1 se a pilha estiver vazia, 0 se n�o estiver
*/
void emptyStackFrame(StackFrame *topStackFrame);

/** Fun��o que inicializa a pilha de frames.
* \param Endere�o da pilha de frames
*/
void stackFrameInit(StackFrame **topFrameAddress);

/** Fun��o que cria um novo frame na pilha de frames
* \param StackFrame** Endere�o da pilha de frames
*/
void pushFrame(StackFrame **topFrameAddress);

/** Fun��o que remove um frame da pilha de frames
* \param StackFrame** Endere�o da pilha de frames
*/
void popFrame(StackFrame **topFrameAddress);

/** Fun��o que inicializa um frame
* \param ClassList* Lista de classes
* \param ClassFile
* \param StackFrame* Pilha de frames
* \param char* Nome do m�todo
* \param char* Descri��o do m�todo
*/
void frameInit(ClassList *init, ClassFile classFile, StackFrame *StackFrame, char* methodName, char* descriptor);

#endif /* PILHAOPERANDOS_H_ */
