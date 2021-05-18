#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void readFileIntoArrayAndClean(char* inputFile);
void findStartIndex(char * part);
void findEndIndex(char * part);
void readFileIntoArray(char * inputFile);
void cleanTextPart();
void writeArraysIntoFile(char * outputFile);
void writeLabelDataIntoFile(char * outputFile);

#endif // FILEIO_H_INCLUDED
