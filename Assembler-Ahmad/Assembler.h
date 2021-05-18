#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct _RegData{
char* regName;
uint8_t regValue;
char* binValue;
};

typedef struct _RegData RegData;

RegData SearchRegData(char* name);

struct _InstructionData{
char* instructionName;
char* op;
char* shift;
char* func;

};
typedef struct _InstructionData InstructionData;

InstructionData searchInstructionData(char* name);

struct _Label{
char* labName;
int lineNum;
};
typedef struct _Label Label;

struct _Asciiz{
char* varName;
char* value;
char* binAddress;
int lineNum;
};

typedef struct _Asciiz Asciiz;

struct _Word{
char* varName;
int32_t value;
char* binValue;
char* binAddress;
int lineNum;
};
typedef struct _Word Word;

struct _WordArray{
char* varName;
int32_t value[50];
char* binValue[50];
char* binAddress[50];
int numValues;
int lineNum;
};
typedef struct _WordArray WordArray;


void run (char * inputFile, char * outFile);

#endif // ASSEMBLER_H_INCLUDED
