
#include "Assembler.h"
#include "FileIO.h"
#include "TxtParser.h"
#include "Printer.h"
#include "DtaParser.h"

char rawCodeLines[100][100];
int totalLinesOfRawCode;

char binaryDataLines[32][200];
int binTextPointer = 0;

char binaryTextLines[32][200];
int binDataPointer = 0;

struct _Word arrOfWords[100];
int indexOfWordCount = 0;

struct _WordArray arr2dOfWords[100];
int indexOf2dWordCount = 0;

struct _Asciiz arrOfStrings[100];
int indexOfStringCount = 0;

struct _Label arrOfLabels[100];
int indexOfLabelCount = 0;

int baseDataAddress = 8192;
int baseTextAddress = 0;

int currentTextLine = 0;
int currentInstLine = 0;


int startIndexForTextPart;
int endIndexForTextPart;

int startIndexForDataPart;
int endIndexForDataPart;



int numPadding = 0;
int prevInstructionString = 0;

// MIPS 32 Register Data
static RegData reg[32] =
{
    {"$zero",0,"00000"},{"$at",1,"00001"},{"$v0",2,"00010"},{"$v1",3,"00011"},{"$a0",4,"00100"},{"$a1",5,"00101"},
    {"$a2",6,"00110"},{"$a3",7,"00111"},{"$t0",8,"01000"},{"$t1",9,"01001"},{"$t2",10,"01010"},{"$t3",11,"01011"},
    {"$t4",12,"01100"},{"$t5",13,"01101"},{"$t6",14,"01110"},{"$t7",15,"01111"},{"$s0",16,"10000"},{"$s1",17,"10001"},
    {"$s2",18,"10010"},{"$s3",19,"10011"},{"$s4",20,"10100"},{"$s5",21,"10101"},{"$s6",22,"10110"},{"$s7",23,"10111"},
    {"$t8",24,"11000"},{"$t9",25,"11001"},{"$k0",26,"11010"},{"$k1",27,"11011"},{"$gp",28,"11100"},{"$sp",29,"11101"},
    {"$fp",30,"11110"},{"$ra",31,"11111"}
};

// MIPS 32 Instruction Data
static InstructionData data[24] =
{
    {"addi","001000",NULL,NULL},{"addu","000000","00000","100001"},{"addiu","001001",NULL,NULL},
    {"mul","011100","00000","000010"},{"lui","001111",NULL,"NULL"},{"add","000000","00000","100000"},
    {"nor","000000","00000","100111"},{"lw","100011",NULL,NULL},{"sub","000000","00000","100010"},
    {"mult","000000","00000","011000"},{"slti","001010",NULL,NULL},{"slt","000000","00000","101010"},
    {"beq","000100",NULL,NULL},{"bne","000101",NULL,NULL},{"sra","000000",NULL,"000011"},{"sll","000000",NULL,"000000"},
    {"move","000000","00000","100001"},{"li","001001",NULL,NULL},{"la","001000", NULL, NULL},
    {"bgtz","000111",NULL,NULL},{"blez","000110",NULL,NULL},{"j","000010",NULL,NULL},{"srav","000000","00000","000111"},
    {"sw","101011",NULL,NULL}
};



/**
 *   Runs the program to convert the assembly code.
 *
 *   Post: Binary Code is Printed to the output file.
 *
 */
void run(char * inputFile, char * outFile)
{
    // Start Of FileIO Functions
    readFileIntoArrayAndClean(inputFile);

    // End Of FileIO Functions


    // DataParser Function
    convertDataPartToBinary();

    // Text Parser Function
    convertTextPartToBinary();

    // FileIO Function
    writeArraysIntoFile(outFile);

    clearMemory();
}

/**
 *   Runs the program to convert the assembly code.
 *
 *   Post: Symbol Information is printed to the output file.
 *
 */
void run_2(char * inputFile, char * outFile)
{
    // Start Of FileIO Functions
    readFileIntoArrayAndClean(inputFile);

    // End Of FileIO Functions


    // DataParser Function
    convertDataPartToBinary();

    // Text Parser Function
    convertTextPartToBinary();

    writeLabelDataIntoFile(outFile);

    clearMemory();

}


void clearMemory(){


        for(int i = 0; i < indexOfWordCount ; i++)
    {
        free(arrOfWords[i].varName);
        free(arrOfWords[i].binValue);
        free(arrOfWords[i].binAddress);
    }

    int index1 = indexOf2dWordCount;

    for(int i = 0; i < index1 ; i++)
    {
        free(arr2dOfWords[i].varName);
        }

    for(int i = 0; i < indexOfStringCount ; i++)
    {
        free(arrOfStrings[i].varName);
         free(arrOfStrings[i].value);
         free(arrOfStrings[i].binAddress);
    }


    for (int i = 0; i< indexOfLabelCount; i++){
    free(arrOfLabels[i].labName);
    }



}

/**
 *   Searches the RegisterData and returns a match.
 *
 */
RegData SearchRegData(char* name)
{
    for (int i = 0; i<32; i++)
    {
        if(strcmp(reg[i].regName, name) == 0)
        {
            return reg[i];
        }
    }
    return (RegData)
    {
        NULL,0,NULL
    };
}

/**
 *   Searches the Instruction Data and returns a match.
 *
 */
InstructionData searchInstructionData(char* name)
{
    for (int i = 0 ; i<24; i++)
    {
        if (strcmp(data[i].instructionName,name)==0)
        {
            return data[i];
        }
    }
    return (InstructionData)
    {
        NULL,NULL,NULL
    };
}

/**
 *   Searches the WordData and returns the words binary address.
 *
 */
char* searchWordData(char* name)
{

    for (int i = 0 ; i<indexOfWordCount; i++)
    {
        if (strcmp(arrOfWords[i].varName,name)==0)
        {
            return arrOfWords[i].binAddress;
        }
    }

    for (int i = 0 ; i<indexOf2dWordCount; i++)
    {
        if (strcmp(arr2dOfWords[i].varName,name)==0)
        {
            return arr2dOfWords[i].binAddress[0];
        }
    }

    for (int i = 0 ; i<indexOfStringCount; i++)
    {
        if (strcmp(arrOfStrings[i].varName,name)==0)
        {
            return arrOfStrings[i].binAddress;
        }
    }

    return "XXXXXXXXXXXXXXXX";


}


/**
 *   Searches the Label Data and returns its line Number
 *
 */
int SearchLabels(char* name)
{
    for (int i = 0; i<indexOfLabelCount; i++)
    {
        if(strcmp(arrOfLabels[i].labName, name) == 0)
        {
            return arrOfLabels[i].lineNum;
        }
    }
    return 0;
}









