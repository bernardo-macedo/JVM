/*
 * FuncoesGerais.c
 *
 *  Created on: 15/02/2013
 *      Author: Vitor
 */

#include "FuncoesGerais.h"
#include "ClassFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que retorna a referência descrição de um método (methodInfo) dado um nome e um descritor
// É retornada a referência pois podemos validar se não encontrou um método
// simplesmente comparando com NULL
methodInfo* buscaMetodoNome(ClassFile cf, char* nomeMetodo, char* descriptor) {

	int i;

	for (i = 0; i < cf.methods_count; i++) {
		if (strcmp(
				(char*) buscaUTF8ConstPool(cf.constant_pool,
						cf.methods[i].nameIndex), nomeMetodo) == 0
				&& strcmp(
						(char*) buscaUTF8ConstPool(cf.constant_pool,
								cf.methods[i].descriptorIndex), descriptor)
						== 0) {
			return &(cf.methods[i]);
		}
	}

	return NULL ;

}

// Função que dada uma path para uma classe, filtra-a para ter somente seu nome
void limpaPathClasseParaNome(char* nomeClasseSemPath, char* nomeClasse) {

	int i;
	int j = 0;

	i = strlen(nomeClasse) - 1;

	// Pulamos o ".class" com o bloco abaixo, se estiver lá
	if (strstr(nomeClasse, ".class") != NULL ) {
		while (nomeClasse[i] != '.') {
			i--;
		}
		i--;
	}

	// Agora, pulamos até encontrarmos o primeiro divisor, se tiver algum
	// ou até o começo da String
	while (nomeClasse[i] != '\\' && nomeClasse[i] != '/'
			&& &(nomeClasse[i]) != nomeClasse) {
		i--;
	}
	if (nomeClasse[i] == '\\' || nomeClasse[i] == '/') {
		i++;
	}

	// Agora passamos o nome da classe para o nomeClasseSemPath
	while (nomeClasse[i] != '.' && nomeClasse[i] != '\0') {
		nomeClasseSemPath[j] = nomeClasse[i];
		i++;
		j++;
	}
	nomeClasseSemPath[j] = '\0';

}

// Função que verifica se uma determinada classe já está carregada
// A busca é feita pela constant pool de cada classe,
// vendo cada membro this_class.
ClassFile* buscaClassFileNome(listaClasses* inicioLista, char* nomeClasse) {

	listaClasses* p1;
	u2 indiceClassInfo;

	p1 = inicioLista;

	while (p1 != NULL ) {

		indiceClassInfo = p1->cf.this_class;

		if (strcmp(
				buscaUTF8ConstPool(p1->cf.constant_pool,
						p1->cf.constant_pool[indiceClassInfo].info.classInfo.nameIndex),
				nomeClasse) == 0) {
			return &(p1->cf);
		}
		p1 = p1->proxClasse;
	}

	return NULL ;

}

//retorna um byte referente ao pc da frame dada
//le o byte do pc da frame e incrementa o pc
u1 lerU1Codigo(frame *fr) {
	u1 retorno;
	retorno = *(fr->pc);
	fr->pc++;
	return retorno;
}

//retorna os dois bytes referentes ao pc da frame dada
//le os proximos dois bytes do pc da frame e incrementa em 2 o pc
u2 lerU2Codigo(frame *fr) {
	u2 retorno;

	retorno = *(fr->pc);
	fr->pc++;

	retorno = retorno << 8 | *(fr->pc);
	fr->pc++;

	return retorno;

}

u4 lerU4Codigo(frame *fr) {
	u4 retorno;
	retorno = *(fr->pc);
	fr->pc++;
	retorno = retorno << 8 | *(fr->pc);
	fr->pc++;
	retorno = retorno << 8 | *(fr->pc);
	fr->pc++;
	retorno = retorno << 8 | *(fr->pc);
	fr->pc++;
	return retorno;
}
//dado o descritor do metodo conta-se quantos argumentos sao passados para ele
//É feita uma varredura no descritor e ao chegar na ')' encerra a varredura
//Duarante a varredura um contador conta os argumentos que forem aparecendo
int contaArgumentosMetodo(u1* descriptor) {

	u1* varredor;
	int i = 0;
	int numArgs = 0;

	varredor = descriptor;

	// Varre o descritor até achar o ')', que indica final dos parametros.
	while (varredor[i] != ')') {
		if (varredor[i] != '(' && varredor[i] != '[') {
			numArgs++;
			if (varredor[i] == 'L') {
				while (varredor[i] != ';') {
					i++;
				}
			}
		}

		i++;

	}

	return numArgs;

}

// Função que retorna o field estático dados o nome da classe e o nome do field
field* buscaStaticFieldNome(listaClasses* inicioLista, char* nomeClasse,
		char* nomeField) {

	u2 indiceClassInfo;
	listaClasses *p1;
	int i;

	p1 = inicioLista;

	while (p1 != NULL ) {

		indiceClassInfo = p1->cf.this_class;

		if (strcmp(nomeClasse,
				buscaUTF8ConstPool(p1->cf.constant_pool,
						p1->cf.constant_pool[indiceClassInfo].info.classInfo.nameIndex))
				== 0) {
			for (i = 0; i < p1->numStaticFields; i++) {
				if (strcmp(nomeField, p1->staticFields[i].nome) == 0) {
					return (&p1->staticFields[i]);
				}
			}

			// Não há como ter duas classes com o mesmo nome, então
			// se o nome bateu, mas em nenhum dos fields foi encontrado
			// o esperado, então welp, retorne NULL.
			return NULL ;
		}

		p1 = p1->proxClasse;
	}

	return NULL ;
}

void insereValorStaticField(listaClasses* inicioLista, char* nomeClasse,
		char* nomeField, tipoOperando op) {

	u2 indiceClassInfo;
	listaClasses *p1;
	int i;

	p1 = inicioLista;

	while (p1 != NULL ) {

		indiceClassInfo = p1->cf.this_class;

		if (strcmp(nomeClasse,
				buscaUTF8ConstPool(p1->cf.constant_pool,
						p1->cf.constant_pool[indiceClassInfo].info.classInfo.nameIndex))
				== 0) {
			for (i = 0; i < p1->numStaticFields; i++) {
				if (strcmp(nomeField, p1->staticFields[i].nome) == 0) {
					// Como o long long cobre o tamanho da union, uso ele para passar o valor
					p1->staticFields[i].valor.tipoLong = op.tipoLong;
					return;
				}
			}

			// Não há como ter duas classes com o mesmo nome, então
			// se o nome bateu, mas em nenhum dos fields foi encontrado
			// o esperado, então welp, retorne.
			return;
		}

		p1 = p1->proxClasse;
	}

}

// Função que retorna um atributo UTF8 dado um índice válido
u1* buscaUTF8ConstPool(cpInfo *cp, u2 indice) {

	return cp[indice].info.UTF8Info.bytes;

}

Vetor* alocaMultiArray(int dimenssoes, int* tamanhos) {
	Vetor *aux, *aux2;
	int i;
	int *auxTamanhos;
	if (dimenssoes == 1) { // função recursiva , critério de parada
		aux = malloc(sizeof(Vetor)); // aloca para a parada
		aux->size = tamanhos[0];
		aux->type = T_INT;
		aux->array = calloc(tamanhos[0], sizeof(tipoOperando));
	} else {
		aux = malloc(sizeof(Vetor)); //garante a alocação do vetor
		aux->size = tamanhos[0];
		aux->type = T_INT;
		aux->array = calloc(tamanhos[0], sizeof(tipoOperando));
		//---------------------------------------------------
		auxTamanhos = calloc(dimenssoes - 1, sizeof(int)); // montando o vetor de tamanho para o proximo nivel de recursão
		for (i = 1; i < dimenssoes; ++i) { // o proximo nível recebe uma posição a menos
			auxTamanhos[i - 1] = tamanhos[i];
		}
		//---------------------------------------------------
		for (i = 0; i < tamanhos[0]; ++i) {
			aux2 = alocaMultiArray(dimenssoes - 1, auxTamanhos);
			aux->array[i].tipoReferencia = aux2;
		}
	}
	return aux;
}

// Retorna o número de fields que o objeto sendo alocado terá
int contaNumFields(execucao *p, ClassFile cf) {

	int i;
	ClassFile* cfAux;
	u2 indiceNomeSuperClasse;
	char nomeSuperClasse[100];
	int numFields = 0;

	cfAux = &cf;

	for (i = 0; i < cfAux->fields_count; i++) {
		// Temos que ter certeza que os campos estáticos não são adicionados
		// ao número de campos do objeto
		if ((cfAux->fields[i].accessFlags & ACC_STATIC) == 0) {
			numFields++;
		}
	}

	// Esse loop varre as super classes contando os fields
	// que são public ou protected mas não são static
	while (cfAux->super_class != 0) {

		indiceNomeSuperClasse =
				cfAux->constant_pool[cfAux->super_class].info.classInfo.nameIndex;

		strcpy(nomeSuperClasse,
				buscaUTF8ConstPool(cfAux->constant_pool,
						indiceNomeSuperClasse));

		cfAux = verificaClasse(p, nomeSuperClasse);

		for (i = 0; i < cfAux->fields_count; i++) {
			// Adicionamos se o campo for public ou protected e não é static
			if (((cfAux->fields[i].accessFlags & ACC_STATIC) == 0)) {
				numFields++;
			}
		}

	}

	return numFields;

}

// Função que preenche o array de fields do objeto com os fields de todas
// as classes ligadas a ele (classe + super classes) e inicializa o valor com 0
void inicializaFieldsObjeto(execucao *p, ClassFile cf, field* fields) {

	int i;
	int j = 0; // Contador dos fields do objeto
	ClassFile* cfAux;
	u2 indiceNomeSuperClasse;
	u2 indiceDescritorField;
	u2 indiceNomeField;
	char* descritor;
	char* nomeField;
	char nomeSuperClasse[100];

	cfAux = &cf;

	// Esse loop inicializa os fields não estáticos da classe base
	for (i = 0; i < cfAux->fields_count; i++) {

		indiceDescritorField = cfAux->fields[i].descriptorIndex;
		descritor = buscaUTF8ConstPool(cfAux->constant_pool,
				indiceDescritorField);

		indiceNomeField = cfAux->fields[i].nameIndex;
		nomeField = buscaUTF8ConstPool(cfAux->constant_pool, indiceNomeField);

		if ((cfAux->fields[i].accessFlags & ACC_STATIC) == 0) {
			fields[j].descritor = descritor;
			fields[j].nome = nomeField;
			fields[j].valor.tipoLong = 0;//Inicializo long com 0, pois ocupa todos os 64 bits da union
			j++;
		}
	}

	// Esse loop varre as super classes inicializando os fields
	// que são public ou protected mas não são static
	while (cfAux->super_class != 0) {

		indiceNomeSuperClasse =
				cfAux->constant_pool[cfAux->super_class].info.classInfo.nameIndex;

		strcpy(nomeSuperClasse,
				buscaUTF8ConstPool(cfAux->constant_pool,
						indiceNomeSuperClasse));

		cfAux = verificaClasse(p, nomeSuperClasse);

		if (cfAux != NULL ) {
			for (i = 0; i < cfAux->fields_count; i++) {

				indiceDescritorField = cfAux->fields[i].descriptorIndex;
				descritor = buscaUTF8ConstPool(cfAux->constant_pool,
						indiceDescritorField);

				indiceNomeField = cfAux->fields[i].nameIndex;
				nomeField = buscaUTF8ConstPool(cfAux->constant_pool,
						indiceNomeField);

				// Inicializamos se o campo for public ou protected e não é static
				if (((cfAux->fields[i].accessFlags & ACC_STATIC) == 0)) {
					fields[j].descritor = descritor;
					fields[j].nome = nomeField;
					fields[j].valor.tipoLong = 0;
					j++;
				}
			}
		} else {
			printf(
					"ERRO em inicializaFieldsObjeto: super classe nao encontrada\n");
			exit(1);
		}
	}

}

field* buscaFieldNome(char* nome, char* descritor, object* obj) {
	field* campo;
	int i;
	for (i = 0; i < obj->fieldsCount; ++i) {
		if ((strcmp(nome, (obj->fields[i].nome)) == 0)
				&& (strcmp(descritor, (obj->fields->descritor)) == 0)) {
			campo = &(obj->fields[i]);
			return campo;
		}
	}
	campo = NULL;
	return campo;
}
