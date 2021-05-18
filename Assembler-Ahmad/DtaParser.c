
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "Assembler.h"

extern char rawCodeLines[100][100];
extern char binaryDataLines[32][200];


extern int startIndexForDataPart;
extern int endIndexForDataPart;
extern int binDataPointer ;


extern struct _Word arrOfWords[100];
extern int indexOfWordCount;

extern struct _WordArray arr2dOfWords[100];
extern int indexOf2dWordCount;

extern struct _Asciiz arrOfStrings[100];
extern int indexOfStringCount;

extern int numPadding ;
extern int prevInstructionString;

extern int baseDataAddress ;
extern int baseTextAddress ;



/**
 *  Passes each line of the data part to get converted into binary
 *
 */
void convertDataPartToBinary()
{
    for(int i = startIndexForDataPart; i <= endIndexForDataPart; ++i)
        collectVariablesAndValues(rawCodeLines[i]);

}

/**
 *   Collects variables and their values and stores them into appropriate structs
 *
 */
void collectVariablesAndValues(const char* const line)
{

    if(strstr(line, "word") != NULL && strstr(line, ",") == NULL && getOccOfChar2(line)==1 )
    {

        Word* word = (Word*)calloc(1,sizeof(Word));
        word->binValue = (char*)calloc(32,sizeof(char));
        int sizeOfVar = getIndexOf(line, ':');
        word->varName = (char*)calloc(sizeOfVar,sizeof(char));

        for(int i = 0; i< sizeOfVar; i++)
        {
            word->varName[i] = line[i];
        }
        word->varName[sizeOfVar] = '\0';

        int indexOfInt = getIndexOf(line,'.');

        int sizeOfInt = strlen(line) - indexOfInt;

        char charValue[sizeOfInt];
        for (int i = indexOfInt; i<strlen(line); i++)
        {
            charValue[i-indexOfInt] = line[i+1];
        }
        charValue[sizeOfInt-1] = '\0';

        for (int i = 0; i<strlen(charValue); i++)
        {
            charValue[i] = charValue[i+5];
        }



        int intValue;
        sscanf(charValue, "%d", &intValue);

        word->value = intValue;

        word->binValue = convertIntTo32BitBinary(intValue);

        word->lineNum = baseDataAddress;
        word->binAddress = convertIntTo16BitBinary(baseDataAddress);
        baseDataAddress =        baseDataAddress + 4;

        strcpy(binaryDataLines[binDataPointer], word->binValue );
        binDataPointer ++;

        arrOfWords[indexOfWordCount] = (*word);
        indexOfWordCount++;
    }

    if(strstr(line, "word") != NULL && strstr(line, ",") != NULL )
    {


        WordArray* wordArray = (WordArray*)calloc(1,sizeof(WordArray));
        int sizeOfVar = getIndexOf(line, ':');
        wordArray->varName = (char*)calloc(sizeOfVar,sizeof(char)+1);



        for(int i = 0; i< sizeOfVar; i++)
        {

            wordArray->varName[i] = line[i];
        }
        wordArray->varName[sizeOfVar] = '\0';

        char str[100];
        strcpy(str, line);

        int numValues = getOccOfChar(line) +1 ;
        wordArray->numValues = numValues;
        wordArray->value[0] = extractImmediate2(str,1);
        strcpy(str, line);

        for(int i =1; i<numValues; i++)
        {

            wordArray->value[i] = extractImmediate(str,i);
            strcpy(str, line);

        }

        if (prevInstructionString ==  1 && numPadding == 0)
        {
            strcpy(binaryDataLines[binDataPointer],"00000000000000000000000000000000" );
            binDataPointer ++;
            baseDataAddress =        baseDataAddress + 4;
        }

                    wordArray->lineNum = baseDataAddress;

        for(int i = 0; i<numValues; i++)
        {

            wordArray->binValue[i] = convertIntTo32BitBinary(wordArray->value[i]);


            wordArray->binAddress[i] = convertIntTo16BitBinary(baseDataAddress);
            baseDataAddress =        baseDataAddress + 4;

            strcpy(binaryDataLines[binDataPointer], wordArray->binValue[i] );
            binDataPointer ++;
        }

        arr2dOfWords[indexOf2dWordCount] = (*wordArray);
        indexOf2dWordCount++;

        prevInstructionString = 0;
    }

    if(strstr(line, "word") != NULL && getOccOfChar2(line)>1 )
    {

        WordArray* wordArray = (WordArray*)calloc(1,sizeof(WordArray));
        int sizeOfVar = getIndexOf(line, ':');
        wordArray->varName = (char*)calloc(sizeOfVar,sizeof(char));

        for(int i = 0; i< sizeOfVar; i++)
        {
            wordArray->varName[i] = line[i];
        }
        wordArray->varName[sizeOfVar] = '\0';


        int indexOfInt = getIndexOf(line,'.')+7;
        int sizeOfInt = strlen(line) - indexOfInt;
        char charValue[sizeOfInt];
        for (int i = indexOfInt; i<strlen(line); i++)
        {
            charValue[i-indexOfInt] = line[i];
        }

        int intValue;
        sscanf(charValue, "%d", &intValue);

        int sizeOfArray = extractImmediate3(line,2);

        wordArray->numValues = sizeOfArray;

        if (prevInstructionString ==  1 && numPadding == 0)
        {
            strcpy(binaryDataLines[binDataPointer],"00000000000000000000000000000000" );
            binDataPointer ++;
            baseDataAddress =        baseDataAddress + 4;
        }

        wordArray->lineNum = baseDataAddress;
        for(int i = 0 ; i< sizeOfArray; i++)
        {
            wordArray->value[i] = intValue;
            wordArray->binValue[i] = convertIntTo32BitBinary(intValue);
            wordArray->binAddress[i] = convertIntTo16BitBinary(baseDataAddress);
            baseDataAddress =        baseDataAddress + 4;

            strcpy(binaryDataLines[binDataPointer], wordArray->binValue[i] );
            binDataPointer ++;
        }

        arr2dOfWords[indexOf2dWordCount] = (*wordArray);
        indexOf2dWordCount++;

        prevInstructionString = 0;

    }

    if(strstr(line, ".asciiz") != NULL)
    {

        Asciiz* asciiz = (Asciiz*)calloc(1,sizeof(Asciiz));

        int sizeOfVar = getIndexOf(line, ':');
        asciiz->varName = (char*)calloc(sizeOfVar,sizeof(char));
        for(int i = 0; i< sizeOfVar; i++)
        {
            asciiz->varName[i] = line[i];
        }

        int sizeOfVal = strlen(line) - getIndexOf(line, '"') - 2;
        asciiz->value = (char*)calloc(sizeOfVal,sizeof(char));
        char* string = extract_between_quotes(line, sizeOfVal);
        asciiz->value = string;
        asciiz->lineNum = baseDataAddress;
        asciiz->binAddress = convertIntTo16BitBinary(baseDataAddress);
        baseDataAddress = baseDataAddress + 4;

        arrOfStrings[indexOfStringCount] = (*asciiz);
        indexOfStringCount++;


        char* binString = (char*)calloc(32,sizeof(char));
        binString = "";
        int count = 0;

        numPadding = 4- ((strlen(string))%4);
        if (numPadding == 4)
        {
            numPadding = 0;
        }

        for (int i=0; i<strlen(string); i++)
        {


            int c = (int)string[i];
            char* ch = convertIntTo8BitBinary(c);

            binString = append(binString, ch);
            if(count == 3 || (i == (strlen(string)-1)))
            {

                if( i == (strlen(string)-1))
                {
                    for (int j = 0; j< numPadding; j++)
                        binString = append(binString, "00000000");
                }

                strcpy(binaryDataLines[binDataPointer],binString );
                binDataPointer ++;
                count = 0;
                binString = "";
            }
            else
                count++;
        }

        prevInstructionString = 1;

    }

}
