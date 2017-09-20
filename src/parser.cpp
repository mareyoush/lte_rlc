#include "rlc_structures.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstdio>

std::string hexToBin(std::string hex)
{
    std::string output = "";
    for(int i = 0; (unsigned)i < hex.length(); ++i)
    {
        switch(hex[i])
	{
   	    case '0': output.append("0000"); break;
	    case '1': output.append("0001"); break;
	    case '2': output.append("0010"); break;
	    case '3': output.append("0011"); break;
	    case '4': output.append("0100"); break;
	    case '5': output.append("0101"); break;
	    case '6': output.append("0110"); break;
	    case '7': output.append("0111"); break;
	    case '8': output.append("1000"); break;
	    case '9': output.append("1001"); break;
	    case 'a': output.append("1010"); break;
	    case 'b': output.append("1011"); break;
	    case 'c': output.append("1100"); break;
	    case 'd': output.append("1101"); break;
	    case 'e': output.append("1110"); break;
	    case 'f': output.append("1111"); break;
       }
    }
    return output;
}



// Checks file with PDU - returns 0 on success
// Author - Adam Wroblak
uint16_t check_pdu_file(FILE *file, struct RlcPduS *pdu)
{
    unsigned int pduSize = 0;
    // Get the file size and read it into a memory buffer
	fseek(file, 0L, SEEK_END);  
	size_t fsize = ftell(file); 
    fseek(file, 0L, SEEK_SET);  
    
    if (fsize == 0){    // file is empty
        printf("empty file\n");
        return EFILE_EMPTY;
    }

    char *buffer = (char*) malloc(fsize * sizeof(char) + 1);
    fread(buffer, fsize, 1, file);
    buffer[fsize] = '\0';

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
    while (isspace(*c)) // skip whitespaces
        c++;
    
    if ( (*c) != 'A' && (*c) != 'U' && (*c) != 'T' ){
        printf("Bad file format: first line must be mode [size]\n");
        free(buffer);
        free(firstLineBuff);
        return EBAD_FORMAT;
    }

    // ------------------- Transparent mode --------------------------
    if ((*c) == 'T'){
        c++;
        for (; (*c) != '\0'; c++){
            if (!isspace(*c)){
                printf("Bad file format: no characters allowed after 'T' in first line\n");
                free(buffer);
                free(firstLineBuff);
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
            printf("Bad file format: space required after 'A'\n");
            free(buffer);
            free(firstLineBuff);
            return EBAD_FORMAT;
        }
        while (isspace(*c)) // skip whitespaces
            c++;
        char *currentPos = c;
        for (; (*c) != '\0'; c++){
            if (!isdigit(*c)){
                printf("Bad file format: only digits allowed after 'A'\n");
                free(buffer);
                free(firstLineBuff);
                return EBAD_FORMAT;
            }
        }
        pduSize = atoi(currentPos);
        if (pduSize <= 0){
            printf("Bad PDU size\n");
            free(buffer);
            free(firstLineBuff);
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
            printf("Bad file format: only '5' or '1' after 'U' allowed\n");
            free(buffer);
            free(firstLineBuff);
            return EBAD_FORMAT;
        }

        // ------ U5 mode -- only file size needed ------
        if ((*c) == '5'){   
            c++;
            if (!isspace(*c)){
                printf("Bad file format: space required after 'U5'\n");
                free(buffer);
                free(firstLineBuff);
                return EBAD_FORMAT;
            }
            while (isspace(*c)) // skip whitespaces
                c++;

            char *currentPos = c;
            for (; (*c) != '\0'; c++){
                if (!isdigit(*c)){
                    printf("Bad file format: only digits allowed after 'U5'l\n");
                    free(buffer);
                    free(firstLineBuff);
                    return EBAD_FORMAT;
                }
            }
            pduSize = atoi(currentPos);
            if (pduSize <= 0){
                printf("Bad PDU size\n");
                free(buffer);
                free(firstLineBuff);
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
                printf("Bad file format: only '0' allowed after 'U1'\n");
                free(buffer);
                free(firstLineBuff);
                return EBAD_FORMAT;
            }
            c++;
            if (!isspace(*c)){
                printf("Bad file format: space required after 'U10'\n");
                free(buffer);
                free(firstLineBuff);
                return EBAD_FORMAT;
            }
            while (isspace(*c)) // skip whitespaces
                c++;
            char *currentPos = c;
            for (; (*c) != '\0'; c++){
                if (!isdigit(*c)){
                    printf("Bad file format: only digits allowed after 'U10'\n");
                    free(buffer);
                    free(firstLineBuff);
                    return EBAD_FORMAT;
                }
            }
            pduSize = atoi(currentPos);
            if (pduSize <= 0){
                printf("Bad PDU size\n");
                free(buffer);
                free(firstLineBuff);
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
    std::string data = "";
    while ( (*c) != '\0'){
        if (ishex(*c)){
            data += *c;
        }
        else if (isspace(*c))
            ;
        else{
            printf("Invalid character in data:%c\n", *c);
            free(buffer);
            free(firstLineBuff);
            return EBAD_FORMAT;
        }
        c++;
    }
    // Check if data size is given in bytes
    // (no half bytes!)
    if (  (strlen(data.c_str()) % 2) != 0 ){
        printf("Bad data length: only even number of hex digits allowed\n");
        free(buffer);
        free(firstLineBuff);
        return EBAD_DATA_LENGTH;
    } 

    pdu->sizePdu = pduSize;
    // in transparent mode size is not specified
    if (pdu->mode == T){
        pdu->sizePdu = strlen(data.c_str()) / 2;
    }

    std::string pduString = "";
    
    while (!data.empty()){
        for (int i = 0; i < pdu->sizePdu * 2 && !data.empty(); i++){
            pduString += data[0];
            data.erase(0,1);
        }
        pdu->data.push_back(pduString);
        pduString = "";
    }
    // conversion test	
    printf("bin: %s", hexToBin(pdu->data[0]).c_str());
    
    free(buffer);
    free(firstLineBuff);
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

uint16_t rlcParser(RlcPduS *rlcPdu_p, RlcSduS *rlcSdu_p){
    uint16_t ret = 0;
    switch (rlcPdu_p->mode){
        case T:
        {
            ret = parseT(rlcPdu_p, rlcSdu_p);
        }
        case A:
        {
            ret = parseA(rlcPdu_p, rlcSdu_p);
        }
        case U5:
        {
            ret = parseU5(rlcPdu_p, rlcSdu_p);
        }
        case U10:
        {
            ret = parseU10(rlcPdu_p, rlcSdu_p);
        }
    } 
    return ret;
}

uint16_t parseU5(RlcPduS *pdu, RlcSduS *sdu)
{
    
    return 0;
}
uint16_t parseU10(RlcPduS *pdu, RlcSduS *sdu)
{
    return 0;
}
uint16_t parseT(RlcPduS *pdu, RlcSduS *sdu)
{
    return 0;
}
uint16_t parseA(RlcPduS *pdu, RlcSduS *sdu)
{
    for (unsigned int i = 0; i < pdu->data.size(); i++){
        // extract one data pdu from structure
        const char *data = pdu->data[i].c_str();
        printf("data %d:\n%s\n", i, data);
        char stringHeader[5];
        //char *data_p = NULL; // beginning of data part will be stored here, if PDU will be data PDU
        // copy header to sepparate variable
        memcpy(stringHeader, data, 4);
        stringHeader[4] = '\0';
        printf("header: %s ", stringHeader);
        long int intHeader = strtol(stringHeader, NULL, BASE_16);

        // check header insides
        int dc = ((intHeader & BIT16) != 0);

        // --------------- RLC control PDU ------------------------
        if (dc == 0){
            printf("Control PDU\n");

        }
        // --------------- RLC control PDU ------------------------
        
        // --------------- RLC data PDU ---------------------------
        else{
            printf("Data PDU\n");
            int rf = ((intHeader & BIT15) != 0);
            int p  = ((intHeader & BIT14) != 0);
            int fi = ((intHeader & (BIT13 | BIT12)) >> 11);
            int e  = ((intHeader & BIT11) != 0);
            int sn = (intHeader & FIRST_10_BITS);
            printf("dc=%d, rf=%d, p=%d, fi=%d, e=%d, sn=%d\n", dc, rf, p, fi, e, sn);
            
            // ---------------- extension flag set-------------------
            if (e){
                
            }
            // ---------------- extension flag set -----------------

            // ---------------- exntension flag not set ------------
            else{
                //char *c = &data[4]; // this is where header ends
                //printf("data part: %s\n", c);
            }
            // ---------------- exntension flag not set ------------
        }
        // ------------- RLC data PDU -----------------------------


    }
    return 0;
}
