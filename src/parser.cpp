#include "rlc_structures.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EFILE_EMPTY 1
#define EBAD_FORMAT 2
#define EBAD_PDU_SIZE 3

int check_pdu_file(FILE *file, struct RlcPduS *pdu)
{
    // Get the file size and read it into a memory buffer
	fseek(file, 0L, SEEK_END);  
	size_t fsize = ftell(file); 
    fseek(file, 0L, SEEK_SET);  
    
    if (fsize == 0){    // file is empty
        printf("empty file\n");
        return EFILE_EMPTY;
    }

    char *buffer = (char*) malloc(fsize * sizeof(char));
    fread(buffer, fsize, 1, file);

    int firstLineLen = 0;  
    char *c = &buffer[0];
    while ( (*c) != '\n' && (*c) != EOF){
        c++;
        firstLineLen++;
    }
    
    
    char *firstLineBuff = (char*) malloc(firstLineLen * sizeof(char) + 1);
    memcpy(firstLineBuff, buffer, firstLineLen);
    firstLineBuff[firstLineLen] = '\0';

    
    c = &firstLineBuff[0];
    while (isspace(*c)) // remove whitespaces
        c++;
    
    if ( (*c) != 'A' && (*c) != 'U' && (*c) != 'T' ){
        printf("Bad file format\n");
        return EBAD_FORMAT;
    }

    if ((*c) == 'T'){
        c++;
        for (; (*c) != '\0'; c++){
            if (!isspace(*c)){
                printf("Bad file format\n");
                return EBAD_FORMAT;
            }
        }
        printf("Transparent mode\n");     
    }

    if ((*c) == 'A'){   // acknowledgment mode - only file size needed
        c++;
        if (!isspace(*c)){
            printf("Bad file format\n");
            return EBAD_FORMAT;
        }
        while (isspace(*c)) // remove whitespaces
            c++;
        char *currentPos = c;
        for (; (*c) != '\0'; c++){
            if (!isdigit(*c)){
                printf("Bad file format\n");
                return EBAD_FORMAT;
            }
        }
        int pduSize = atoi(currentPos);
        if (pduSize <= 0){
            printf("Bad PDU size\n");
            return EBAD_PDU_SIZE;
        }
        printf("Acknowledgment mode, size:%d\n", pduSize);     
    }

    if ( (*c) == 'U'){  // unacknowledgment mode 
        c++;
        if ( (*c) != '5' && (*c) != '1'){
            printf("Bad file format\n");
            return EBAD_FORMAT;
        }

        if ((*c) == '5'){   // U5 mode -- only file size needed

        }
    }
    
    return 0;
}