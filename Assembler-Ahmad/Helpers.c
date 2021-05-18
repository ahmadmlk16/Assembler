#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Assembler.h"

/**
 *   The Following Functions are helpers used in the made Assembler code.
 *
 */



char const flip[] = "10";

/**
 *   Joins to given string into one
 *
 */
append(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/**
 *   Removes black spaces from a given string
 *
 */
char* removeSpaces(char* input)
{
    int i,j;
    char *output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)
    {
        if (input[i]!=' ')
            output[j]=input[i];
        else
            j--;
    }
    output[j]=0;
    return output;
}

/**
 *   Extracts the string between quotation marks
 *
 */
extract_between_quotes(char* s, int size)
{
    char * dest = (char*)calloc(size+1,sizeof(char));

    int start = getIndexOf(s,'"')+1;


    for(int i = start; i< strlen(s)-1; i++)
    {
        dest[i-start] = s[i];
    }

    dest[size] = '\0';
    return dest;

}


/**
 *   Extracts the label from a given line
 *
 */
char* extractLabel(char* str, int skip)
{

    char delim[] = ",";
    char *ptr = strtok(str, delim);
    for (int i = 0; i< skip ; i++)
    {
        ptr = strtok(NULL, delim);
    }
    return ptr;

}

/**
 *   Extracts the label from a given jump line
 *
 */
char* extractJump(char* str, int skip)
{

    char delim[] = "j";
    char *ptr = strtok(str, delim);
    for (int i = 0; i< skip ; i++)
    {
        ptr = strtok(NULL, delim);
    }
    return ptr;

}

/**
 *   Extracts the immediate from a given line seperated by ","
 *
 */
int extractImmediate(char* str, int skip)
{

    char delim[] = ",";
    char *ptr = strtok(str, delim);
    for (int i = 0; i< skip ; i++)
    {
        ptr = strtok(NULL, delim);
    }
    int x;
    sscanf(ptr, "%d", &x);
    return x;

}

/**
 *   Extracts the immediate from a given line seperated by "d"
 *
 */
int extractImmediate2(char* str, int skip)
{

    char delim[] = "d";
    char *ptr = strtok(str, delim);
    for (int i = 0; i< skip ; i++)
    {
        ptr = strtok(NULL, delim);
    }
    int x;
    sscanf(ptr, "%d", &x);
    return x;

}

/**
 *   Extracts the immediate from a given line seperated by ":"
 *
 */
int extractImmediate3(char* str, int skip)
{

    char delim[] = ":";
    char *ptr = strtok(str, delim);
    for (int i = 0; i< skip ; i++)
    {
        ptr = strtok(NULL, delim);
    }
    int x;
    sscanf(ptr, "%d", &x);
    return x;

}



/**
 *   Converts given int into a 5 bit binary string
 *
 */
convertIntTo5BitBinary(int n)
{
    int neg = 0;
    if(n < 0)
    {
        neg = 1;
        n = n*-1;
    }
    int binaryNum[5];
    // counter for binary array
    int i = 4;
    while (n > 0)
    {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i--;
    }
    for (int j = i; j>=0; j--)
    {
        binaryNum[j] = 0;
    }
    if (neg == 1)
    {
        for (int k = 0 ; k<6 ; k++)
        {
            if (binaryNum[k] == 0)
                binaryNum[k] = 1;
            else
                binaryNum[k] = 0;
        }
    }
    char str[5];
    i=0;
    int index = 0;
    for (i=0; i<6; i++)
        index += sprintf(&str[index], "%d", binaryNum[i]);
    char out[6] = "0";
    if (neg == 1)
    {
        int index = 5;
        strcat(out, str);
        while(index >= 0)
        {
            out[index] = flip[out[index] -'0'];
            if(out[index] == '1')
                break;
            index--;
        }

    }
    int     slen = 0;
    char *string = malloc((6) * sizeof(char));

    if(neg == 1)
    {
        for (i = 0; i < 5; i++)
        {
            string[i] = out[(i+1)];
        }
    }
    else
    {
        for (i = 0; i < 5; i++)
        {
            string[i] = str[i];
        }
    }
    string[5] = '\0';

    return string;

}


/**
 *   Converts given int into a 8 bit binary string
 *
 */
convertIntTo8BitBinary(int n)
{
    int neg = 0;
    if(n < 0)
    {
        neg = 1;
        n = n*-1;
    }
    int binaryNum[8];
    // counter for binary array
    int i = 7;
    while (n > 0)
    {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i--;
    }
    for (int j = i; j>=0; j--)
    {
        binaryNum[j] = 0;
    }
    if (neg == 1)
    {
        for (int k = 0 ; k<9 ; k++)
        {
            if (binaryNum[k] == 0)
                binaryNum[k] = 1;
            else
                binaryNum[k] = 0;
        }
    }
    char str[8];
    i=0;
    int index = 0;
    for (i=0; i<9; i++)
        index += sprintf(&str[index], "%d", binaryNum[i]);
    char out[9] = "0";
    if (neg == 1)
    {
        int index = 8;
        strcat(out, str);
        while(index >= 0)
        {
            out[index] = flip[out[index] -'0'];
            if(out[index] == '1')
                break;
            index--;
        }

    }
    int     slen = 0;
    char *string = malloc((9) * sizeof(char));

    if(neg == 1)
    {
        for (i = 0; i < 8; i++)
        {
            string[i] = out[(i+1)];
        }
    }
    else
    {
        for (i = 0; i < 8; i++)
        {
            string[i] = str[i];
        }
    }
    string[8] = '\0';

    return string;

}

/**
 *   Converts given int into a 16 bit binary string
 *
 */
convertIntTo16BitBinary(int n)
{
    int neg = 0;
    if(n < 0)
    {
        neg = 1;
        n = n*-1;
    }
    int binaryNum[16];
    // counter for binary array
    int i = 15;
    while (n > 0)
    {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i--;
    }
    for (int j = i; j>=0; j--)
    {
        binaryNum[j] = 0;
    }
    if (neg == 1)
    {
        for (int k = 0 ; k<17 ; k++)
        {
            if (binaryNum[k] == 0)
                binaryNum[k] = 1;
            else
                binaryNum[k] = 0;
        }
    }
    char str[16];
    i=0;
    int index = 0;
    for (i=0; i<17; i++)
        index += sprintf(&str[index], "%d", binaryNum[i]);
    char out[17] = "0";
    if (neg == 1)
    {
        int index = 16;
        strcat(out, str);
        while(index >= 0)
        {
            out[index] = flip[out[index] -'0'];
            if(out[index] == '1')
                break;
            index--;
        }

    }
    int     slen = 0;
    char *string = malloc((17) * sizeof(char));

    if(neg == 1)
    {
        for (i = 0; i < 16; i++)
        {
            string[i] = out[(i+1)];
        }
    }
    else
    {
        for (i = 0; i < 16; i++)
        {
            string[i] = str[i];
        }
    }
    string[16] = '\0';

    return string;

}

/**
 *   Converts given int into a 26 bit binary string
 *
 */
convertIntTo26BitBinary(int n)
{
    int neg = 0;
    if(n < 0)
    {
        neg = 1;
        n = n*-1;
    }
    int binaryNum[26];
    // counter for binary array
    int i = 25;
    while (n > 0)
    {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i--;
    }
    for (int j = i; j>=0; j--)
    {
        binaryNum[j] = 0;
    }
    if (neg == 1)
    {
        for (int k = 0 ; k<27 ; k++)
        {
            if (binaryNum[k] == 0)
                binaryNum[k] = 1;
            else
                binaryNum[k] = 0;
        }
    }
    char str[26];
    i=0;
    int index = 0;
    for (i=0; i<27; i++)
        index += sprintf(&str[index], "%d", binaryNum[i]);
    char out[27] = "0";
    if (neg == 1)
    {
        int index = 26;
        strcat(out, str);
        while(index >= 0)
        {
            out[index] = flip[out[index] -'0'];
            if(out[index] == '1')
                break;
            index--;
        }

    }
    int     slen = 0;
    char *string = malloc((27) * sizeof(char));

    if(neg == 1)
    {
        for (i = 0; i < 26; i++)
        {
            string[i] = out[(i+1)];
        }
    }
    else
    {
        for (i = 0; i < 26; i++)
        {
            string[i] = str[i];
        }
    }
    string[26] = '\0';

    return string;
}

/**
 *   Converts given int into a 32 bit binary string
 *
 */
convertIntTo32BitBinary(int n)
{
    int neg = 0;
    if(n < 0)
    {
        neg = 1;
        n = n*-1;
    }
    int binaryNum[32];
    // counter for binary array
    int i = 31;
    while (n > 0)
    {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i--;
    }
    for (int j = i; j>=0; j--)
    {
        binaryNum[j] = 0;
    }
    if (neg == 1)
    {
        for (int k = 0 ; k<33 ; k++)
        {
            if (binaryNum[k] == 0)
                binaryNum[k] = 1;
            else
                binaryNum[k] = 0;
        }
    }
    char str[32];
    i=0;
    int index = 0;
    for (i=0; i<33; i++)
        index += sprintf(&str[index], "%d", binaryNum[i]);
    char out[33] = "0";
    if (neg == 1)
    {
        int index = 32;
        strcat(out, str);
        while(index >= 0)
        {
            out[index] = flip[out[index] -'0'];
            if(out[index] == '1')
                break;
            index--;
        }

    }
    int     slen = 0;
    char *string = malloc((33) * sizeof(char));

    if(neg == 1)
    {
        for (i = 0; i < 32; i++)
        {
            string[i] = out[(i+1)];
        }
    }
    else
    {
        for (i = 0; i < 32; i++)
        {
            string[i] = str[i];
        }
    }
    string[32] = '\0';

    return string;
}

/**
 *   Gets the first index of the given character and returns as int
 *
 */

int getIndexOf(const char* const line, char * symbol)
{
    char *e;
    int index;
    e = strchr(line, symbol);
    index = (int)(e - line);
    return index;
}

/**
 *   Gets the number of Occurences of ","
 *
 */
int getOccOfChar(const char* const line)
{

    int count=0;
    for(int i=0; line[i]; i++)
    {
        if(line[i]== ',')
        {
            count++;
        }
    }
    return count;

}

/**
 *   Gets the number of Occurences of ":"
 *
 */
int getOccOfChar2(const char* const line)
{

    int count=0;
    for(int i=0; line[i]; i++)
    {
        if(line[i]== ':')
        {
            count++;
        }
    }
    return count;

}


