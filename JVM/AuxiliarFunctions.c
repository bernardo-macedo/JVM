#include <math.h>
#include <stdlib.h>
#include "AuxiliarFunctions.h"

float convertU4ToFloat(u4 u4input)
{
	float convertedU4;
	int s;
	int e;
	int m;

	if(u4input == 0x7f800000)
	{
		/*infinito positivo*/
	}
	else if(u4input == 0xff800000)
	{
		/*infinito negativo*/
	}
	else if(((u4input >= 0x7f800001) && (u4input <= 0x7fffffff)) || ((u4input >= 0xff800001) && (u4input <= 0xffffffff)))
	{
		/*nan*/
	}
	else
	{
		s = ((u4input >> 31) == 0) ? 1 : -1;
		e = ((u4input >> 23) & 0xff);
		m = (e == 0) ? (u4input & 0x7fffff) << 1 : (u4input & 0x7fffff) | 0x800000;

		convertedU4 = s*m*(pow(2, (e - 150)));
	}

	return convertedU4;
}

int methodArgsCount(char* descriptor) {
    int argNumber = 0, i = 0;
    char* aux;

    strcpy(aux, descriptor);
    while (aux[i] != ')') {
        if (aux[i] != '(' && aux[i] != '[') {
            argNumber++;
            if (aux[i] == 'L') {
                while (aux[i] != ';') i++;
            }
        }
        i++;
    }
	return argNumber;
}

ClassFile* getClassFileByName(ClassList* init, char* className) {

	u2 classNameIndex;
	char* classNameAux;
	ClassList* cListAux = init;

	while (cListAux != NULL) {
        classNameIndex = cListAux->classFile->constantPool[cListAux->classFile->thisClass].info.ClassInfo.nameIndex;
        classNameAux = cListAux->classFile->constantPool[classNameIndex].info.Utf8Info.bytes;
        if (strcmp(classNameAux, className) == 0)
            return &(cListAux->classFile);
        cListAux = cListAux->nextClass;
	}
	return NULL;
}

MethodInfo* getMethod(ClassFile cFile, char* methodName, char* methodDescriptor) {
    int i;
    char* methodNameAux, methodDescriptorAux;

	for (i = 0; i < cFile.methodsCount; i++) {
	    methodNameAux = cFile.constantPool[cFile.methods[i].nameIndex].info.Utf8Info.bytes;
        methodDescriptorAux = cFile.constantPool[cFile.methods[i].descriptorIndex].info.Utf8Info.bytes;
        if (strcmp(methodNameAux, methodName) == 0 && strcmp(methodDescriptorAux, methodDescriptor) == 0)
            return &(cFile.methods[i]);
	}
	return NULL ;
}

u1* getUTF8(CpInfo *cp, u2 indice) {
	return cp[indice].info.Utf8Info.bytes;
}
