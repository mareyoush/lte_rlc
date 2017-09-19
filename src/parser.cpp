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
    pdu->data = "";
    int pduSize = 0;
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
    // Get first line length
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

    // ------------------- Transparent mode --------------------------
    if ((*c) == 'T'){
        c++;
        for (; (*c) != '\0'; c++){
            if (!isspace(*c)){
                printf("Bad file format\n");
                return EBAD_FORMAT;
            }
        }
        printf("Transparent mode\n");
        pdu->mode = T;  
    }
    // ----------------------Transparent mode-------------------------

    // -----------------AMD PDU --------------------------------------
    if ((*c) == 'A'){   // acknowledgment mode - only file size needed
        c++;
        if (!isspace(*c)){
            printf("Bad file format\n");
            return EBAD_FORMAT;
        }
        while (isspace(*c)) // skip whitespaces
            c++;
        char *currentPos = c;
        for (; (*c) != '\0'; c++){
            if (!isdigit(*c)){
                printf("Bad file format\n");
                return EBAD_FORMAT;
            }
        }
        pduSize = atoi(currentPos);
        if (pduSize <= 0){
            printf("Bad PDU size\n");
            return EBAD_PDU_SIZE;
        }
        printf("Acknowledgment mode, size:%d\n", pduSize);
        pdu->mode = A;  
    }
    // -------------------------------AMD PDU-----------------------------

    // ------------- UMD PDU ----------------------------------
    if ( (*c) == 'U'){  // unacknowledgment mode 
        c++;
        if ( (*c) != '5' && (*c) != '1'){
            printf("Bad file format\n");
            return EBAD_FORMAT;
        }

        // ------ U5 mode -- only file size needed ------
        if ((*c) == '5'){   
            c++;
            if (!isspace(*c)){
                printf("Bad file format\n");
                return EBAD_FORMAT;
            }
            while (isspace(*c)) // skip whitespaces
                c++;

            char *currentPos = c;
            for (; (*c) != '\0'; c++){
                if (!isdigit(*c)){
                    printf("Bad file format\n");
                    return EBAD_FORMAT;
                }
            }
            pduSize = atoi(currentPos);
            if (pduSize <= 0){
                printf("Bad PDU size\n");
                return EBAD_PDU_SIZE;
            }
            printf("U5 mode, size:%d\n", pduSize);
            pdu->mode = U5;
        }
        // ---------------------U5------------------------

        // ----- U10 mode -- only file size needed --------
        if ( (*c) == '1'){  
            c++;
            if((*c) != '0'){
                printf("Bad file format\n");
                return EBAD_FORMAT;
            }
            c++;
            if (!isspace(*c)){
                printf("Bad file format\n");
                return EBAD_FORMAT;
            }
            while (isspace(*c)) // skip whitespaces
                c++;
            char *currentPos = c;
            for (; (*c) != '\0'; c++){
                if (!isdigit(*c)){
                    printf("Bad file format\n");
                    return EBAD_FORMAT;
                }
            }
            pduSize = atoi(currentPos);
            if (pduSize <= 0){
                printf("Bad PDU size\n");
                return EBAD_PDU_SIZE;
            }
            printf("U10 mode, size:%d\n", pduSize);
            pdu->mode = U10;  
        } 
        // ---------------------U10--------------------
    }
    // ------------------ UMD PDU ----------------------
    
    
    // Start reading data from second line
    c = buffer + firstLineLen + 1;
    while ( (*c) != '\0'){
        if (ishex(*c)){
            pdu->data += *c;
        }
        else if (isspace(*c))
            ;
        else{
            printf("Invalid character in data:%c\n", *c);
            return EBAD_FORMAT;
        }
        c++;
    }
    printf("Data: %s\n", pdu->data.c_str());
    printf("%lu bytes\n", strlen(pdu->data.c_str()) / 2);
    return 0;
}

int ishex(char c){
    if( isdigit(c)
        || c == 'a' || c == 'A' 
        || c == 'b' || c == 'B'
        || c == 'c' || c == 'C'
        || c == 'd' || c == 'D'
        || c == 'e' || c == 'E'
        || c == 'f' || c == 'F')
        return 1;
    return 0;
}