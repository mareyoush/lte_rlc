#include "rlc_structures.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EFILE_EMPTY 1

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
    
    return 0;
}