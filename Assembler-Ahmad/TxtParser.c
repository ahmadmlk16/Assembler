#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "Assembler.h"

extern int startIndexForTextPart;
extern int endIndexForTextPart;

extern char rawCodeLines[100][100];
extern int currentInstLine;
extern int currentTextLine;

extern struct _Label arrOfLabels[100];
extern int indexOfLabelCount ;

extern char binaryTextLines[32][200];
extern int binDataPointer;
extern int binTextPointer;


/**
 *   Passes each line of text data to first extract all labels
 *   Then passes each line of text data to be converted
 *
 */
void convertTextPartToBinary(){

    for(int i = startIndexForTextPart; i <= endIndexForTextPart; ++i)
    {
        gatherLabelData(rawCodeLines[i]);
    }
    currentInstLine = 0;
    currentTextLine = 0;
    for(int i = startIndexForTextPart; i <= endIndexForTextPart; ++i)
    {
        convertTextLineToBinary( rawCodeLines[i]);
    }

}

/**
 *   Passes each given line to gather label data is present
 *
 */
void gatherLabelData(const char* const line)
{

    if ((strstr(line, ",") != NULL) || (strstr(line, "syscall") != NULL) || (strstr(line, "nop") != NULL)
            || (strstr(line, "j ") != NULL) )
    {
        currentInstLine++;
        currentTextLine++;
    }
    if (strstr(line, ":") != NULL )
    {

        collectLabel(line);
        currentTextLine++;
    }


}

/**
 *  Collects the label data from the given line and stores it into the appropriate struct.
 *
 */
void collectLabel(char* line)
{
    Label* label = (Label*)calloc(1,sizeof(Label));


    char delim[] = ":";
    char *temp =  (char*)calloc(1,sizeof(char));


    strcpy(temp, line);

    char *ptr = strtok(temp, delim);

    label->labName = ptr;
    label->lineNum = currentInstLine;


    arrOfLabels[indexOfLabelCount] = (*label);
    indexOfLabelCount++;

}

/**
 *   converts the given text line into binary and passes it to its appropriate function.
 *
 */

void convertTextLineToBinary(const char* const line)
{
    if (strstr(line, "lw ") != NULL  && strstr(line, "(") != NULL )
    {

        convertRtOffsetRs(line, "lw");
        currentInstLine++;
        currentTextLine++;
    }

    if (strstr(line, "sw ") != NULL )
    {

        convertRtOffsetRs(line, "sw");
        currentInstLine++;
        currentTextLine++;
    }

    if (strstr(line, "lui ") != NULL )
    {

        convertRtImm16ORLabel(line,"lui");
        currentInstLine++;
        currentTextLine++;
    }

    if (strstr(line, "add ") != NULL )
    {

        convertRdRsRt(line,"add");
        currentInstLine++;
        currentTextLine++;

    }

    if (strstr(line, "addi ") != NULL )
    {

        convertRtRsImm16(line, "addi");
        currentInstLine++;
        currentTextLine++;
    }

    if (strstr(line, "addu ") != NULL )
    {

        convertRdRsRt(line, "addu");
        currentInstLine++;
        currentTextLine++;
    }

    if (strstr(line, "addiu ") != NULL )
    {

        convertRtRsImm16(line, "addiu");
        currentInstLine++;
        currentTextLine++;
    }

    if (strstr(line, "mul ") != NULL )
    {

        convertRdRsRt(line, "mul");
        currentInstLine++;
        currentTextLine++;
    }

    if (strstr(line, "mult ") != NULL )
    {

        convertRsRt(line,"mult");
        currentInstLine++;
        currentTextLine++;
    }

    if (strstr(line, "nop") != NULL )
    {

        strcpy(binaryTextLines[binTextPointer], "00000000000000000000000000000000" );
        binTextPointer ++;
        currentInstLine++;
        currentTextLine++;

    }

    if (strstr(line, "nor ") != NULL )
    {

        convertRdRsRt(line, "nor");
        currentInstLine++;
        currentTextLine++;
    }

    if (strstr(line, "sll ") != NULL )
    {

        convertRdRtSa(line, "sll");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "slt ") != NULL )
    {

        convertRdRsRt(line,"slt");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "slti ") != NULL )
    {


        convertRtRsImm16(line, "slti");
        currentTextLine++;
        currentInstLine++;

    }

    if (strstr(line, "sra ") != NULL )
    {

        convertRdRtSa(line, "sra");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "srav ") != NULL )
    {

        convertRdRtRs(line, "srav");
        currentTextLine++;
        currentInstLine++;

    }

    if (strstr(line, "sub ") != NULL )
    {

        convertRdRsRt(line, "sub");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "beq ") != NULL )
    {

        convertRsRtOffset(line, "beq");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "blez ") != NULL )
    {

        convertRsOffset(line, "blez");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "bgtz ") != NULL )
    {

        convertRsOffset(line, "bgtz");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "bne ") != NULL )
    {

        convertRsRtOffset(line, "bne");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "j ") != NULL )
    {

        convertTarget(line, "j");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "syscall") != NULL )
    {

        strcpy(binaryTextLines[binTextPointer], "00000000000000000000000000001100" );
        binTextPointer ++;
        currentTextLine++;
    }

    if (strstr(line, "move ") != NULL )
    {

        convertRdRs(line, "move");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "blt ") != NULL )
    {

        convertRdRsOffSetForBlt(line,"blt");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "la ") != NULL )
    {

        convertRtImm16ORLabel(line,"la");
        currentTextLine++;
        currentInstLine++;

    }

    if (strstr(line, "li ") != NULL )
    {

        convertRtImm16ORLabel(line, "li");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, "lw ") != NULL && strstr(line, "(") == NULL)
    {

        convertRtImm16ORLabel(line, "lw");
        currentTextLine++;
        currentInstLine++;
    }

    if (strstr(line, ":") != NULL )
    {
        currentTextLine++;
    }

}



/**
 *   ALL the following Functions Convert a Given sytax of assembly code into binary and append that assembly code into an array.
 *
 */

void convertRdRsRt(const char* const line, char * name)
{
    char * binLine;
    InstructionData iData = searchInstructionData(name);
    RegData rData;


    char * temp =  "";
    char  RD[6];
    char  RS[6];
    char  RT[6];

    char  str[150];
    strcpy(str, line);

    int index = getIndexOf(line,'$');

    if(str[index+1]== 'z')
    {
        RD[0] = str[index];
        index++;
        RD[1] = str[index];
        index++;
        RD[2] = str[index];
        index++;
        RD[3] = str[index];
        index++;
        RD[4] = str[index];
        index++;
        RD[5] = '\0';
        index += 2;
    }
    else
    {
        RD[0] = str[index];
        index++;
        RD[1] = str[index];
        index++;
        RD[2] = str[index];
        index++;
        RD[3] = '\0';
        index += 2;
    }

    if(str[index+1]== 'z')
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = str[index];
        index++;
        RS[4] = str[index];
        index++;
        RS[5] = '\0';
        index += 2;
    }
    else
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = '\0';
        index += 2;
    }

    if(str[index+1]== 'z')
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = str[index];
        index++;
        RT[4] = str[index];
        index++;
        RT[5] = '\0';
        index += 2;
    }
    else
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = '\0';
        index += 2;
    }

    rData = SearchRegData(RS);
    char * binRS = rData.binValue;

    rData = SearchRegData(RT);
    char * binRT = rData.binValue;

    rData = SearchRegData(RD);
    char * binRD = rData.binValue;

    binLine = append(temp, iData.op);
    binLine = append(binLine, binRS);
    binLine = append(binLine, binRT);
    binLine = append(binLine, binRD);
    binLine = append(binLine, iData.shift);
    binLine = append(binLine, iData.func);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;
}

void convertRtRsImm16(const char* const line, char * name)
{
    char * binLine;
    InstructionData iData = searchInstructionData(name);
    RegData rData;


    char * temp =  "";
    char  RT[6];
    char  RS[6];

    char  str[150];
    int imm;
    strcpy(str, line);

    int index = getIndexOf(line,'$');

    if(str[index+1]== 'z')
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = str[index];
        index++;
        RT[4] = str[index];
        index++;
        RT[5] = '\0';
        index += 2;
    }
    else
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = '\0';
        index += 2;
    }

    if(str[index+1]== 'z')
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = str[index];
        index++;
        RS[4] = str[index];
        index++;
        RS[5] = '\0';
        index += 2;
    }
    else
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = '\0';
        index += 2;
    }

    rData = SearchRegData(RS);
    char * binRS = rData.binValue;

    rData = SearchRegData(RT);
    char * binRT = rData.binValue;

    imm = extractImmediate(line,2);


    char * binImm = convertIntTo16BitBinary(imm);


    binLine = append(temp, iData.op);
    binLine = append(binLine, binRS);
    binLine = append(binLine, binRT);
    binLine = append(binLine, binImm);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;
}

void convertRsRt(const char* const line, char * name)
{
    char * binLine;
    InstructionData iData = searchInstructionData(name);
    RegData rData;


    char * temp =  "";

    char  RS[6];
    char  RT[6];

    char  str[150];
    strcpy(str, line);

    int index = getIndexOf(line,'$');

    if(str[index+1]== 'z')
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = str[index];
        index++;
        RS[4] = str[index];
        index++;
        RS[5] = '\0';
        index += 2;
    }
    else
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = '\0';
        index += 2;
    }

    if(str[index+1]== 'z')
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = str[index];
        index++;
        RT[4] = str[index];
        index++;
        RT[5] = '\0';
        index += 2;
    }
    else
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = '\0';
        index += 2;
    }

    rData = SearchRegData(RS);
    char * binRS = rData.binValue;

    rData = SearchRegData(RT);
    char * binRT = rData.binValue;

    binLine = append(temp, iData.op);
    binLine = append(binLine, binRS);
    binLine = append(binLine, binRT);
    binLine = append(binLine, "00000");
    binLine = append(binLine, iData.shift);
    binLine = append(binLine, iData.func);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;
}

void convertRdRs(const char* const line, char * name)
{
    char * binLine;
    InstructionData iData = searchInstructionData(name);
    RegData rData;


    char * temp =  "";

    char  RD[6];
    char  RS[6];

    char  str[150];
    strcpy(str, line);

    int index = getIndexOf(line,'$');

    if(str[index+1]== 'z')
    {
        RD[0] = str[index];
        index++;
        RD[1] = str[index];
        index++;
        RD[2] = str[index];
        index++;
        RD[3] = str[index];
        index++;
        RD[4] = str[index];
        index++;
        RD[5] = '\0';
        index += 2;
    }
    else
    {
        RD[0] = str[index];
        index++;
        RD[1] = str[index];
        index++;
        RD[2] = str[index];
        index++;
        RD[3] = '\0';
        index += 2;
    }

    if(str[index+1]== 'z')
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = str[index];
        index++;
        RS[4] = str[index];
        index++;
        RS[5] = '\0';
        index += 2;
    }
    else
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = '\0';
        index += 2;
    }

    rData = SearchRegData(RD);
    char * binRD = rData.binValue;

    rData = SearchRegData(RS);
    char * binRS = rData.binValue;

    binLine = append(temp, iData.op);
    binLine = append(binLine, "00000");
    binLine = append(binLine, binRS);
    binLine = append(binLine, binRD);
    binLine = append(binLine, iData.shift);
    binLine = append(binLine, iData.func);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;
}

void convertRtImm16ORLabel(const char* const line, char * name)
{
    char * binLine;
    InstructionData iData = searchInstructionData(name);
    RegData rData;


    char * temp =  "";
    char  RT[6];


    char  str[150];

    strcpy(str, line);

    int index = getIndexOf(line,'$');

    if(str[index+1]== 'z')
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = str[index];
        index++;
        RT[4] = str[index];
        index++;
        RT[5] = '\0';
        index += 2;
    }
    else
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = '\0';
        index += 2;
    }

    rData = SearchRegData(RT);

    char * binRT = rData.binValue;

    int imm;
    char* label;
    char * binImm;

    if(name == "la" || name == "lw")
    {
        label = extractLabel(line, 1);
        label = removeSpaces(label);
        binImm = searchWordData(label);


    }
    else
    {
        imm = extractImmediate(line,1);
        binImm = convertIntTo16BitBinary(imm);
    }




    binLine = append(temp, iData.op);
    binLine = append(binLine, "00000");
    binLine = append(binLine, binRT);
    binLine = append(binLine, binImm);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;
}

void convertRtOffsetRs(const char* const line, char * name)
{
    char * binLine;
    InstructionData iData = searchInstructionData(name);
    RegData rData;


    char * temp =  "";
    char  RT[6];
    char  RS[6];

    char  str[150];
    int imm;
    strcpy(str, line);

    int index = getIndexOf(str,'$');

    if(str[index+1]== 'z')
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = str[index];
        index++;
        RT[4] = str[index];
        index++;
        RT[5] = '\0';
        index += 2;
    }
    else
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = '\0';
        index += 2;
    }

    int rSIndex = getIndexOf(str,'(');
    rSIndex++;
    if(str[rSIndex+1]== 'z')
    {
        RS[0] = str[rSIndex];
        rSIndex++;
        RS[1] = str[rSIndex];
        rSIndex++;
        RS[2] = str[rSIndex];
        rSIndex++;
        RS[3] = str[rSIndex];
        rSIndex++;
        RS[4] = str[rSIndex];
        rSIndex++;
        RS[5] = '\0';
    }
    else
    {
        RS[0] = str[rSIndex];
        rSIndex++;
        RS[1] = str[rSIndex];
        rSIndex++;
        RS[2] = str[rSIndex];
        rSIndex++;
        RS[3] = '\0';
    }

    rData = SearchRegData(RS);
    char * binRS = rData.binValue;

    rData = SearchRegData(RT);
    char * binRT = rData.binValue;

    imm = extractImmediate(str,1);


    char * binImm = convertIntTo16BitBinary(imm);


    binLine = append(temp, iData.op);
    binLine = append(binLine, binRS);
    binLine = append(binLine, binRT);
    binLine = append(binLine, binImm);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;
}

void convertRsRtOffset(const char* const line, char * name)
{

    char * binLine;
    InstructionData iData = searchInstructionData(name);
    RegData rData;


    char * temp =  "";
    char  RT[6];
    char  RS[6];

    char  str[150];
    int imm;
    strcpy(str, line);

    int index = getIndexOf(line,'$');

    if(str[index+1]== 'z')
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = str[index];
        index++;
        RS[4] = str[index];
        index++;
        RS[5] = '\0';
        index += 2;
    }
    else
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = '\0';
        index += 2;
    }

    if(str[index+1]== 'z')
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = str[index];
        index++;
        RT[4] = str[index];
        index++;
        RT[5] = '\0';
        index += 2;
    }
    else
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = '\0';
        index += 2;
    }

    rData = SearchRegData(RS);
    char * binRS = rData.binValue;

    rData = SearchRegData(RT);
    char * binRT = rData.binValue;


    char*  offset = extractLabel(line, 2);
    offset = removeSpaces(offset);

    int labelLineNum = SearchLabels(offset);

    int binNum;
    if((labelLineNum - currentInstLine)>0)
        binNum = labelLineNum - currentInstLine - 1 ;

    else
        binNum  = labelLineNum - currentInstLine -1 ;//////FIX


    char * binImm = convertIntTo16BitBinary(binNum);


    binLine = append(temp, iData.op);
    binLine = append(binLine, binRS);
    binLine = append(binLine, binRT);
    binLine = append(binLine, binImm);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;

}

void convertRdRtSa(const char* const line, char * name)
{

    char * binLine;
    InstructionData iData = searchInstructionData(name);
    RegData rData;


    char * temp =  "";
    char  RD[6];
    char  RT[6];

    char  str[150];
    int imm;
    strcpy(str, line);

    int index = getIndexOf(line,'$');

    if(str[index+1]== 'z')
    {
        RD[0] = str[index];
        index++;
        RD[1] = str[index];
        index++;
        RD[2] = str[index];
        index++;
        RD[3] = str[index];
        index++;
        RD[4] = str[index];
        index++;
        RD[5] = '\0';
        index += 2;
    }
    else
    {
        RD[0] = str[index];
        index++;
        RD[1] = str[index];
        index++;
        RD[2] = str[index];
        index++;
        RD[3] = '\0';
        index += 2;
    }

    if(str[index+1]== 'z')
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = str[index];
        index++;
        RT[4] = str[index];
        index++;
        RT[5] = '\0';
        index += 2;
    }
    else
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = '\0';
        index += 2;
    }

    rData = SearchRegData(RD);
    char * binRD = rData.binValue;

    rData = SearchRegData(RT);
    char * binRT = rData.binValue;


    int sa = extractImmediate(str,2);

    char * binImm = convertIntTo5BitBinary(sa);


    binLine = append(temp, iData.op);
    binLine = append(binLine, "00000");
    binLine = append(binLine, binRT);
    binLine = append(binLine, binRD);
    binLine = append(binLine, binImm);
    binLine = append(binLine, iData.func);

    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;

}

void convertRsOffset(const char* const line, char * name)
{
    char * binLine;
    InstructionData iData = searchInstructionData(name);
    RegData rData;


    char * temp =  "";

    char  RS[6];

    char  str[150];
    int imm;
    strcpy(str, line);

    int index = getIndexOf(line,'$');

    if(str[index+1]== 'z')
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = str[index];
        index++;
        RS[4] = str[index];
        index++;
        RS[5] = '\0';
        index += 2;
    }
    else
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = '\0';
        index += 2;
    }



    rData = SearchRegData(RS);
    char * binRS = rData.binValue;



    char*  offset = extractLabel(line, 1);
    offset = removeSpaces(offset);

    int labelLineNum = SearchLabels(offset);

    int binNum;
    if((labelLineNum - currentInstLine)>0)
        binNum = labelLineNum - currentInstLine - 1 ;

    else
        binNum  = labelLineNum - currentInstLine -1 ;//////FIX


    char * binImm = convertIntTo16BitBinary(binNum);



    binLine = append(temp, iData.op);
    binLine = append(binLine, binRS);
    binLine = append(binLine, "00000");
    binLine = append(binLine, binImm);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;
}
convertTarget(const char* const line, char * name)
{
    char * binLine;
    InstructionData iData = searchInstructionData(name);



    char * temp =  "";


    char  str[150];
    int imm;
    strcpy(str, line);





    char*  offset = extractJump(line, 1);
    offset = removeSpaces(offset);

    int labelLineNum = SearchLabels(offset);

    char * binImm = convertIntTo26BitBinary(labelLineNum);

    binLine = append(temp, iData.op);
    binLine = append(binLine, binImm);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;
}

void convertRdRtRs(const char* const line, char * name)
{
    char * binLine;
    InstructionData iData = searchInstructionData(name);
    RegData rData;


    char * temp =  "";
    char  RD[6];
    char  RT[6];
    char  RS[6];

    char  str[150];
    strcpy(str, line);

    int index = getIndexOf(line,'$');

    if(str[index+1]== 'z')
    {
        RD[0] = str[index];
        index++;
        RD[1] = str[index];
        index++;
        RD[2] = str[index];
        index++;
        RD[3] = str[index];
        index++;
        RD[4] = str[index];
        index++;
        RD[5] = '\0';
        index += 2;
    }
    else
    {
        RD[0] = str[index];
        index++;
        RD[1] = str[index];
        index++;
        RD[2] = str[index];
        index++;
        RD[3] = '\0';
        index += 2;
    }

    if(str[index+1]== 'z')
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = str[index];
        index++;
        RT[4] = str[index];
        index++;
        RT[5] = '\0';
        index += 2;
    }
    else
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = '\0';
        index += 2;
    }

    if(str[index+1]== 'z')
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = str[index];
        index++;
        RS[4] = str[index];
        index++;
        RS[5] = '\0';
        index += 2;
    }
    else
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = '\0';
        index += 2;
    }

    rData = SearchRegData(RS);
    char * binRS = rData.binValue;

    rData = SearchRegData(RT);
    char * binRT = rData.binValue;

    rData = SearchRegData(RD);
    char * binRD = rData.binValue;

    binLine = append(temp, iData.op);
    binLine = append(binLine, binRS);
    binLine = append(binLine, binRT);
    binLine = append(binLine, binRD);
    binLine = append(binLine, iData.shift);
    binLine = append(binLine, iData.func);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;
}

void convertRdRsOffSetForBlt(const char* const line, char * name)
{

    char * binLine;
    InstructionData iData = searchInstructionData("slt");
    RegData rData;


    char * temp =  "";
    char  RD[6];
    char  RS[6];
    char  RT[6];

    char  str[150];
    strcpy(str, line);

    int index = getIndexOf(line,'$');

    if(str[index+1]== 'z')
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = str[index];
        index++;
        RS[4] = str[index];
        index++;
        RS[5] = '\0';
        index += 2;
    }
    else
    {
        RS[0] = str[index];
        index++;
        RS[1] = str[index];
        index++;
        RS[2] = str[index];
        index++;
        RS[3] = '\0';
        index += 2;
    }

    if(str[index+1]== 'z')
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = str[index];
        index++;
        RT[4] = str[index];
        index++;
        RT[5] = '\0';
        index += 2;
    }
    else
    {
        RT[0] = str[index];
        index++;
        RT[1] = str[index];
        index++;
        RT[2] = str[index];
        index++;
        RT[3] = '\0';
        index += 2;
    }

    RD[0] = '$';
    RD[1] = 'a';
    RD[2] = 't';
    RD[3] = '\0';


    rData = SearchRegData(RS);
    char * binRS = rData.binValue;

    rData = SearchRegData(RT);
    char * binRT = rData.binValue;

    rData = SearchRegData(RD);
    char * binRD = rData.binValue;

    binLine = append(temp, iData.op);
    binLine = append(binLine, binRS);
    binLine = append(binLine, binRT);
    binLine = append(binLine, binRD);
    binLine = append(binLine, iData.shift);
    binLine = append(binLine, iData.func);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;


    currentTextLine++;






    binLine = "";
    iData = searchInstructionData("bne");


    temp =  "";
    int imm;
    strcpy(str, line);

    RT[0] = '$';
    RT[1] = 'a';
    RT[2] = 't';
    RT[3] = '\0';

    RS[0] = '$';
    RS[1] = 'z';
    RS[2] = 'e';
    RS[3] = 'r';
    RS[4] = 'o';
    RS[5] = '\0';


    rData = SearchRegData(RS);
    binRS = rData.binValue;

    rData = SearchRegData(RT);
    binRT = rData.binValue;


    char*  offset = extractLabel(line, 2);
    offset = removeSpaces(offset);

    int labelLineNum = SearchLabels(offset);

    int binNum;
    if((labelLineNum - currentInstLine)>0)
        binNum = labelLineNum - currentInstLine - 1 ;

    else
        binNum  = labelLineNum - currentInstLine -1 ;//////FIX


    char * binImm = convertIntTo16BitBinary(binNum);


    binLine = append(temp, iData.op);
    binLine = append(binLine, binRT);
    binLine = append(binLine, binRS);
    binLine = append(binLine, binImm);


    strcpy(binaryTextLines[binTextPointer],binLine );
    binTextPointer ++;



}

