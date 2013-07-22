#ifndef CONTROLLER_H
#define CONTROLLER_H
#define CAT1 1
#define CAT2 2

#include "ClassStructure.h"

/** Se��o de ambiente de execu��o.
* Cont�m um ponteiro para a classe � qual o m�todo pertence,
* um ponteiro para o opcode da instru��o sendo lida
* e um program counter, que indica o endere�o da instru��o sendo lida
*/
typedef struct ExecEnvirSection {
    CpInfo *belongingClass;
    u1 *currOpcode;
    u1 *pc;
} ExecEnvirSection;

/** Estrutura de um Operando.
* Cont�m um inteiro que indica se � Tipo 1 ou Tipo 2 e o tipo do operando.
*/
typedef struct Operand {
    int type32_64; /*1: operandos do tipo 1 | 2: operandos do tipo 2*/
    union OperandType {
        int intType;
        long long longType;
        float floatType;
        double doubleType;
        void* referenceType;
    } operandType;
} Operand;

/** Pilha de operandos.
* Cont�m o tipo do operando, definido por uma union e um int que indica se � do Tipo 1 ou 2,
* e um ponteiro para o pr�ximo operando da pilha.
*/
typedef struct OperandStack {
    Operand operand;
    struct OperandStack *nextOperand;
} OperandStack;

/** O Frame � composto de um array de vari�veis locais, uma pilha de operandos
* e um ambiente de execu��o dos m�todos.
*/
typedef struct Frame {
    int *localVarArray;    // array de variaveis locais de 32 bits por slot
    ExecEnvirSection *execEnvir;
    OperandStack *topOperand;
} Frame;

/** O StackFrame � a pilha de frames da JVM.
* ou seja, a Stack.
*/
typedef struct StackFrame {
    Frame *frame;
    struct StackFrame *nextFrame;
} StackFrame;

/** Estrutura que define um campo.
* Cont�m o nome, o descritor e o tipo do field.
*/
typedef struct Field {
	char* name;
	char* descriptor;
    union FieldType {
        int intType;
        short shortType;
        float floatType;
        long long longType;
        double doubleType;
        char charType;
        void* referenceType;
    } fieldType;
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
typedef struct ObjectsList {
	Object object;
	struct ObjectList *nextObject;
} ObjectsList;

/** O ClassList � uma lista de classes j� carregadas.
* � tarefa do interpretador, quando for necess�rio, buscar nesta lista se uma classe j� foi carregada
* e carreg�-la caso n�o tenha sido.
*/
typedef struct ClassList {
    ClassFile *classFile;
    int staticFieldsCount;
    Field *staticFields;
    ObjectsList *objectsList;
    struct ClassList *nextClass;
} ClassList;

/** O Interpretador possui uma referencia para o Frame mais recente da pilha de frames
* e para a classe mais recente da lista de classes
*/
typedef struct Interpretador {
    StackFrame *topStackFrame;
    ClassList *initClass;
} Interpretador;

/* ******************** Fun��es ******************** */

/** Fun��o que verifica se a pilha de operandos est� vazia.
* \param OperandStack* Ponteiro para a pilha de operandos
* \return 1 se a pilha estiver vazia, 0 se n�o estiver
*/
int emptyStack(OperandStack*);

/** Fun��o que verifica o n�mero de slots (32 bits) ocupados pelos primeiros argumentos.
* \param OperandStack* Ponteiro para a pilha de operandos
* \param int N�mero de argumentos a serem verificados
* \return int N�mero de slots ocupados pelos argumentos
*/
int countSlots(OperandStack* topOperand, int argNumber);

/** Fun��o que coloca um operando na pilha de operandos.
* \param OperandStack** Endere�o da pilha de operandos
* \param Operand Operando a ser empilhado
*/
void pushOperand(OperandStack**, Operand);

/** Fun��o que inicializa a pilha de operandos.
* \param OperandStack** Endere�o da pilha de operandos
*/
void stackInit(OperandStack**);

/** Fun��o que remove um operando da pilha de operandos.
* \param OperandStack** Endere�o da pilha de operandos
* \return Operando que foi desempilhado
*/
Operand popOperand(OperandStack**);

/** Fun��o que verifica se a pilha de frames est� vazia.
* \param StackFrame* Ponteiro para a pilha de frames
* \return 1 se a pilha estiver vazia, 0 se n�o estiver
*/
int emptyStackFrame(StackFrame*);

/** Fun��o que inicializa a pilha de frames.
* \param Endere�o da pilha de frames
*/
void frameStackInit(StackFrame**);

/** Fun��o que cria um novo frame na pilha de frames
* \param StackFrame** Endere�o da pilha de frames
*/
void pushFrame(StackFrame**);

/** Fun��o que remove um frame da pilha de frames
* \param StackFrame** Endere�o da pilha de frames
*/
void popFrame(StackFrame**);

/** Fun��o que inicializa um frame
* \param ClassList* Lista de classes
* \param ClassFile
* \param StackFrame* Pilha de frames
* \param char* Nome do m�todo
* \param char* Descri��o do m�todo
*/
void frameInit(ClassList*, ClassFile, StackFrame*, char*, char*);

/** Fun��o de inicializa��o da lista de classes carregadas */
void initClassList(ClassList**);

/** Fun��o que inicializa o vetor de campos est�ticos de um elemento ClassList */
void initStaticFields(ClassList*, ClassFile);

/** Fun��o de inser��o de elemento na lista de classes carregadas */
void appendClassList(ClassList**, ClassFile);

/** Fun��o que carrega a classe em mem�ria, se ela n�o estiver j� carregada */
ClassFile* loadClass(Interpretador*, char*);

/** Fun��o de inicializa��o da main, passando o que foi lido da linha de comando */
void mainInit(char* className, Interpretador* interpretador, int, char**);

/** Fun��o de inicializa��o dos demais m�todos */
void methodInit(char*, char*, char*, Interpretador*, int, int);

/** Fun��o de execu��o de um m�todo */
void methodExec(Interpretador*);

#endif
