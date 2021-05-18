#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Assembler.h"

extern char rawCodeLines[100][100];
extern char binaryDataLines[32][200];
extern char binaryTextLines[32][200];
extern struct _Label arrOfLabels[100];
extern struct _Word arrOfWords[100];
extern struct _WordArray arr2dOfWords[100];
extern struct _Asciiz arrOfStrings[100];


extern int startIndexForTextPart;
extern int endIndexForTextPart;
extern int startIndexForDataPart;
extern int endIndexForDataPart;
extern int totalLinesOfRawCode;
extern int binTextPointer ;
extern int binDataPointer ;
extern int indexOfLabelCount;
extern int indexOfWordCount;
extern int indexOf2dWordCount;
extern int indexOfStringCount;


/**
 *   Calls functions necessary to read input file into array
 *
 */

void  readFileIntoArrayAndClean(char* inputFile){
    readFileIntoArray(inputFile);
    findStartIndex("data");
    findStartIndex("text");
    findEndIndex("data");
    findEndIndex("text");
    cleanTextPart();
}

/**
 *   Reads the input file into an array.
 *
 */
void readFileIntoArray(char * inputFile)
{

    FILE *plist = NULL;
    int i = 0;


    plist = fopen(inputFile, "r");
    while(fgets(rawCodeLines[i], 1000, plist))
    {
        /* get rid of ending \n from fgets */
        rawCodeLines[i][strlen(rawCodeLines[i]) - 1] = '\0';
        i++;
    }

    totalLinesOfRawCode = i;


}

/**
 *   Finds the start index of the given part of the assembly code
 *
 */
void findStartIndex(char * part)
{

    for(int i = 0; i < totalLinesOfRawCode; ++i)
    {
        if(strstr(rawCodeLines [i], part) != NULL)
        {

            if (strcmp(part,"text")==0)
            {
                startIndexForTextPart = i+1;
            }
            else
            {
                startIndexForDataPart = i+1
                                        ;
            }

        }
    }
}

/**
 *   Finds the end index of the given part of the assembly code
 *
 */
void findEndIndex(char * part)
{

    if(strcmp(part,"text")==0)
    {
        endIndexForTextPart = totalLinesOfRawCode - 1;
    }
    if (strcmp(part,"data")==0 && startIndexForDataPart
            != 0)
    {
        endIndexForDataPart = startIndexForTextPart - 3;
    }

}




/**
 *   Cleans the assembly code from comments
 *
 */
void cleanTextPart()
{
    char *ptr;
    for(int i = startIndexForTextPart; i < endIndexForTextPart; ++i)
        if(strstr(rawCodeLines [i], "#") != NULL)
        {
            ptr = strchr(rawCodeLines [i], '#');
            if (ptr != NULL)
            {
                *ptr = '\0';
            }
        }

}

/**
 *   Writes the converted binary data into the output file
 *
 */
void writeArraysIntoFile(char * outputFile)
{

    FILE *plist = NULL;
    int i = 0;


    plist = fopen(outputFile, "w");

    for(int i = 0; i < binTextPointer; ++i)
        fprintf(plist,"%s\n", binaryTextLines[i]);

    if(binDataPointer > 0)
    {
        fprintf(plist,"\n");
    }

    for(int i = 0; i < binDataPointer; ++i)
        fprintf(plist,"%s\n", binaryDataLines[i]);

    fclose (plist);
}


/**
 *   Writes the symbol data into the output file.
 *
 */
void writeLabelDataIntoFile(char * outputFile){

    FILE *plist = NULL;
    int i = 0;


    plist = fopen(outputFile, "w");

    for(int i = 0; i < indexOfWordCount ; i++)
    {
        fprintf(plist,"0x%08x",arrOfWords[i].lineNum);
        fprintf(plist,"%s","    ");
        fprintf(plist,arrOfWords[i].varName);
        fprintf(plist,"\n");
    }

    int index1 = indexOf2dWordCount;

    for(int i = 0; i < index1 ; i++)
    {

        fprintf(plist,"0x%08x",arr2dOfWords[i].lineNum);
        fprintf(plist,"%s","    ");
        fprintf(plist,arr2dOfWords[i].varName);
        fprintf(plist,"\n");
        }

    for(int i = 0; i < indexOfStringCount ; i++)
    {
        fprintf(plist,"0x%08x",arrOfStrings[i].lineNum);
        fprintf(plist,"%s","    ");
        fprintf(plist,arrOfStrings[i].varName);
        fprintf(plist,"\n");
    }


    for (int i = 0; i< indexOfLabelCount; i++){
       fprintf(plist,"0x%08x",arrOfLabels[i].lineNum);
       fprintf(plist,"%s","    ");
       fprintf(plist,"%s",arrOfLabels[i].labName);
       fprintf(plist,"\n");
    }
     fclose (plist);

}
