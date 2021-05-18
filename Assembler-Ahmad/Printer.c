#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Assembler.h"

extern int totalLinesOfRawCode;
extern char rawCodeLines[100][100];

extern int binTextPointer;
extern char binaryTextLines[32][200];

extern char binaryDataLines[32][200];
extern int binDataPointer;

extern int startIndexForDataPart;
extern int endIndexForDataPart;

extern int startIndexForTextPart;
extern int endIndexForTextPart;

extern int indexOfWordCount;

extern struct _Word arrOfWords[100];
extern int indexOfWordCount;

extern struct _WordArray arr2dOfWords[100];
extern int indexOf2dWordCount ;

extern  struct _Asciiz arrOfStrings[100];
extern int indexOfStringCount ;

extern struct _Label arrOfLabels[100];
extern int indexOfLabelCount;


/**
 *   Prints the assembly code array taken from the input file
 *
 */
void printTheRawDataArray()
{
    for(int i = 0; i < totalLinesOfRawCode; ++i)
        printf("%s\n", rawCodeLines[i]);
}

/**
 *   Prints the text part represented in binary
 *
 */
void printTextBinaryDataArray()
{
    for(int i = 0; i < binTextPointer; ++i)
        printf("%s\n", binaryTextLines[i]);
}

/**
 *   Prints the data part represented in binary
 *
 */
void printDataBinaryDataArray()
{
    if(binDataPointer > 0)
    {
        printf("\n");
    }
    for(int i = 0; i < binDataPointer; ++i)
        printf("%s\n", binaryDataLines[i]);
}

/**
 *   Prints stats for the file read
 *
 */
void printStats()
{
    printf("Total Lines Of Raw Code: %d \n", totalLinesOfRawCode);
    printf("Data Part Start Index: %d \n", startIndexForDataPart);
    printf("Data Part End Index: %d \n", endIndexForDataPart);
    printf("Text Part Start Index: %d \n", startIndexForTextPart);
    printf("Text Part End Index: %d \n", endIndexForTextPart);

}

/**
 *   Prints the words gathered from the input file
 *
 */
void printWordArray()
{

    for(int i = 0; i < indexOfWordCount ; i++)
    {
        printf("Word: ");
        printf(arrOfWords[i].varName);
        printf(" %d ",arrOfWords[i].value);
        printf(arrOfWords[i].binValue);
        printf("\n");
    }
}

/**
 *   Prints the word arrays gathered from the input file
 *
 */
void printWord2DArray()
{
    int index1 = indexOf2dWordCount;

    for(int i = 0; i < index1 ; i++)
    {

        printf("Word: ");
        printf(arr2dOfWords[i].varName);
        printf("\n");

        int index2 = arr2dOfWords[i].numValues;
        for (int j =0 ; j< index2; j++)
        {
            printf(" %d ",arr2dOfWords[i].value[j]);
            printf(arr2dOfWords[i].binValue[j]);
            printf("\n");
        }
    }
}
