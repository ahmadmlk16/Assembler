#ifndef TXTPARSER_H_INCLUDED
#define TXTPARSER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void convertTextPartToBinary();
void gatherLabelData(const char* const line);
void collectLabel(char* line);
void convertTextLineToBinary(const char* const line);

#endif // TXTPARSER_H_INCLUDED
