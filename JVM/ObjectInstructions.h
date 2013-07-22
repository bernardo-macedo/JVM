#ifndef OBJECTINSTRUCTIONS_H
#define OBJECTINSTRUCTIONS_H

#include "Controller.h"

int iaload(Interpretador*); /*0x2E*/
int laload(Interpretador*); /*0x2F*/
int faload(Interpretador*); /*0x30*/
int daload(Interpretador*); /*0x31*/
int aaload(Interpretador*); /*0x32*/

int baload(Interpretador*); /*0x33*/
int caload(Interpretador*); /*0x34*/
int saload(Interpretador*); /*0x35*/

int iastore(Interpretador*); /*0x4F*/
int lastore(Interpretador*); /*0x50*/
int fastore(Interpretador*); /*0x51*/
int dastore(Interpretador*); /*0x52*/
int aastore(Interpretador*); /*0x53*/

int bastore(Interpretador*); /*0x54*/
int castore(Interpretador*); /*0x55*/
int sastore(Interpretador*); /*0x56*/

int getstatic(Interpretador*); /*0xB2*/
int putstatic(Interpretador*); /*0xB3*/

int getfield(Interpretador*); /*0xB4*/
int putfield(Interpretador*); /*0xB5*/

int new(Interpretador*); /*0xBB*/

int newarray(Interpretador*); /*0xBC*/
int anewarray(Interpretador*); /*0xBD*/

int arraylength(Interpretador*); /*0xBE*/

int checkcast(Interpretador*); /*0xC0*/
int instanceof(Interpretador*); /*0xC1*/

int multianewarray(Interpretador*); /*0xC5*/


#endif
