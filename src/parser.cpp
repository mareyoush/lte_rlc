#include "rlc_structures.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <bitset>

std::string hexToBin(std::string hex)
{
    std::string output = "";
    for(unsigned int i = 0; i < hex.length(); ++i)
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
	    case 'a': case 'A': output.append("1010"); break;
	    case 'b': case 'B': output.append("1011"); break;
	    case 'c': case 'C': output.append("1100"); break;
	    case 'd': case 'D': output.append("1101"); break;
	    case 'e': case 'E': output.append("1110"); break;
	    case 'f': case 'F': output.append("1111"); break;
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

    char *buffer = new char[fsize + 1];
    fread(buffer, fsize, 1, file);
    buffer[fsize] = '\0';

    int firstLineLen = 0;  
    char *c = &buffer[0];
    // Get first line length
    while ( (*c) != '\n' && (*c) != EOF){
        c++;
        firstLineLen++;
    }
       
    char *firstLineBuff = new char[firstLineLen + 1];
    memcpy(firstLineBuff, buffer, firstLineLen);
    firstLineBuff[firstLineLen] = '\0';

    c = &firstLineBuff[0];
    while (isspace(*c)) // skip whitespaces
        c++;
    
    if ( (*c) != 'A' && (*c) != 'U' && (*c) != 'T' ){
        printf("Bad file format: first line must be mode [size]\n");
        delete[] buffer;
        delete[] firstLineBuff;
        return EBAD_FORMAT;
    }

    // ------------------- Transparent mode --------------------------
    if ((*c) == 'T'){
        c++;
        for (; (*c) != '\0'; c++){
            if (!isspace(*c)){
                printf("Bad file format: no characters allowed after 'T' in first line\n");
                delete[] buffer;
                delete[] firstLineBuff;
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
            delete[] buffer;
            delete[] firstLineBuff;
            return EBAD_FORMAT;
        }
        while (isspace(*c)) // skip whitespaces
            c++;
        char *currentPos = c;
        for (; (*c) != '\0'; c++){
            if (!isdigit(*c)){
                printf("Bad file format: only digits allowed after 'A'\n");
                delete[] buffer;
                delete[] firstLineBuff;
                return EBAD_FORMAT;
            }
        }
        pduSize = atoi(currentPos);
        if (pduSize <= 0){
            printf("Bad PDU size\n");
            delete[] buffer;
            delete[] firstLineBuff;
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
            delete[] buffer;
            delete[] firstLineBuff;
            return EBAD_FORMAT;
        }

        // ------ U5 mode -- only file size needed ------
        if ((*c) == '5'){   
            c++;
            if (!isspace(*c)){
                printf("Bad file format: space required after 'U5'\n");
                delete[] buffer;
                delete[] firstLineBuff;
                return EBAD_FORMAT;
            }
            while (isspace(*c)) // skip whitespaces
                c++;

            char *currentPos = c;
            for (; (*c) != '\0'; c++){
                if (!isdigit(*c)){
                    printf("Bad file format: only digits allowed after 'U5'l\n");
                    delete[] buffer;
                    delete[] firstLineBuff;
                    return EBAD_FORMAT;
                }
            }
            pduSize = atoi(currentPos);
            if (pduSize <= 0){
                printf("Bad PDU size\n");
                delete[] buffer;
                delete[] firstLineBuff;
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
                delete[] buffer;
                delete[] firstLineBuff;
                return EBAD_FORMAT;
            }
            c++;
            if (!isspace(*c)){
                printf("Bad file format: space required after 'U10'\n");
                delete[] buffer;
                delete[] firstLineBuff;
                return EBAD_FORMAT;
            }
            while (isspace(*c)) // skip whitespaces
                c++;
            char *currentPos = c;
            for (; (*c) != '\0'; c++){
                if (!isdigit(*c)){
                    printf("Bad file format: only digits allowed after 'U10'\n");
                    delete[] buffer;
                    delete[] firstLineBuff;
                    return EBAD_FORMAT;
                }
            }
            pduSize = atoi(currentPos);
            if (pduSize <= 0){
                printf("Bad PDU size\n");
                delete[] buffer;
                delete[] firstLineBuff;
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
            delete[] buffer;
            delete[] firstLineBuff;
            return EBAD_FORMAT;
        }
        c++;
    }
    // Check if data size is given in bytes
    // (no half bytes!)
    if (  (strlen(data.c_str()) % 2) != 0 ){
        printf("Bad data length: only even number of hex digits allowed\n");
        delete[] buffer;
        delete[] firstLineBuff;
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
    
    delete[] buffer;
    delete[] firstLineBuff;
    return 0;
}
// Author: Adam Wroblak
int ishex(char c){
    return ( isdigit(c)
        || c == 'a' || c == 'A' 
        || c == 'b' || c == 'B'
        || c == 'c' || c == 'C'
        || c == 'd' || c == 'D'
        || c == 'e' || c == 'E'
        || c == 'f' || c == 'F');
}

uint16_t rlcParser(RlcPduS *rlcPdu_p, RlcSduS *rlcSdu_p){
    uint16_t ret = 0;
    switch (rlcPdu_p->mode){
        case T:
        {
            ret = parseT(rlcPdu_p, rlcSdu_p);
            break;
        }
        case A:
        {
            ret = parseA(rlcPdu_p, rlcSdu_p);
            break;
        }
        case U5:
        {
            ret = parseU5(rlcPdu_p, rlcSdu_p);
            break;
        }
        case U10:
        {
            ret = parseU10(rlcPdu_p, rlcSdu_p);
            break;
        }
    } 
    return ret;
}

uint16_t parseU5(RlcPduS *pdu, RlcSduS *sdu)
{
    for (unsigned int i = 0; i < pdu->data.size(); ++i){
    
        std::string headerStr = hexToBin(pdu->data[i].substr(0,2));

        pduHeaderU5 pduh;
	pduh.fi = std::bitset<32>(headerStr.substr(0,2)).to_ulong();
	pduh.e = std::bitset<32>(headerStr.substr(2,1)).to_ulong();
	pduh.sn = std::bitset<32>(headerStr.substr(3,5)).to_ulong();

	printf("FI: %u, E: %u, SN: %u", pduh.fi, pduh.e, pduh.sn);

	//parse li
    }

    return 0;
}
uint16_t parseU10(RlcPduS *pdu, RlcSduS *sdu)
{	
    for (unsigned int i = 0; i < pdu->data.size(); ++i){
        
        std::string headerStr = hexToBin(pdu->data[i].substr(0,4));

	pduHeaderU10 pduh;
	pduh.r1_1 = std::bitset<32>(headerStr.substr(0,1)).to_ulong();
	pduh.r1_2 = std::bitset<32>(headerStr.substr(1,1)).to_ulong();
	pduh.r1_3 = std::bitset<32>(headerStr.substr(2,1)).to_ulong();
	pduh.fi = std::bitset<32>(headerStr.substr(3,2)).to_ulong();
	pduh.e = std::bitset<32>(headerStr.substr(5,1)).to_ulong();
	pduh.sn = std::bitset<32>(headerStr.substr(6,10)).to_ulong();

	printf("R1: %u, R1: %u, R1: %u, FI: %u, E: %u, SN: %u\n", pduh.r1_1, pduh.r1_2, pduh.r1_3, pduh.fi, pduh.e, pduh.sn);
	
	//parse li
    }
    return 0;
}
uint16_t parseT(RlcPduS *pdu, RlcSduS *sdu)
{
    return 0;
}

// Author : Adam Wroblak
uint16_t parseA(RlcPduS *pdu, RlcSduS *sdu)
{
    uint16_t ret = 0;
    std::vector<pduAMDInfo> pduS;
    for (unsigned int i = 0; i < pdu->data.size(); i++){
        struct pduAMDInfo info;

        // by default header is 2 bytes (4 hex digits)
        int headerOffset = 4;

        // extract one data pdu from structure
        const char *data = pdu->data[i].c_str();
        printf("PDU %d: ", i);
        char *stringHeader = new char[headerOffset + 1];
        // copy header to sepparate variable
        memcpy(stringHeader, data, headerOffset);
        stringHeader[4] = '\0';
        printf("header: %s ", stringHeader);
        long int intHeader = strtol(stringHeader, NULL, BASE_16);
        delete[] stringHeader;

        // check header insides
        info.dc = ((intHeader & BIT16) != 0);

        // --------------- RLC control PDU ------------------------
        if (info.dc == 0){
            printf("Control PDU\n");
            ret = readControlAMDPDU(pdu->data[i], &info);
            //pduS.push_back(info);
        }
        // --------------- RLC control PDU ------------------------
        
        // --------------- RLC data PDU ---------------------------
        else{
            
            printf("Data PDU\n");
            info.dc = 1;
            info.rf = ((intHeader & BIT15) != 0);
            info.p  = ((intHeader & BIT14) != 0);
            info.fi = ((intHeader & (BIT13 | BIT12)) >> 11);
            info.e  = ((intHeader & BIT11) != 0);
            info.sn = (intHeader & FIRST_10_BITS);
            
            // ---------------- extension flag set-------------------
            if (info.e){
                // I should think of setting the beggining of 
                // extension part in other places in case when
                // in future LSF SO could occur
                std::string extensionPart(&data[headerOffset]); 
                
                int extensionRead = readExtension(extensionPart, &info.li);  
                info.data = std::string(&data[headerOffset + extensionRead * 2]);
                pduS.push_back(info);          
            }
            // ---------------- extension flag set -----------------

            // ---------------- exntension flag not set ------------
            else{
                info.data = std::string(&data[headerOffset]);
                printf("data part(one SDU): %s\n", info.data.c_str());
                pduS.push_back(info);
            }
            // ---------------- exntension flag not set ------------
        }
        // ------------- RLC data PDU -----------------------------

    }

    // chop into SDUs
    if (!pduS.empty()){
        for (unsigned int i = 0; i < pduS.size(); i++){
            printf("PDU %u dc=%d, rf=%d, p=%d, fi=%d, e=%d, sn=%d\n"
            ,i , pduS[i].dc, pduS[i].rf, pduS[i].p, pduS[i].fi, pduS[i].e, pduS[i].sn);
            printf("DATA: %s li: ", pduS[i].data.c_str());
            for (unsigned int j = 0; j < pduS[i].li.size(); j++){
                printf("%lu ", pduS[i].li[j]);
            }
            printf("\n");
        }
    }
    return ret;
}

// Author: Adam Wroblak
// returns bytes read from Extension part
// Lengths will be stored in int vector
// extensionPart is part of PDU from where 
// extension part beggins
int readExtension(std::string extensionPart, std::vector<long int> *liVec)
{
    std::string binExtensionPart = hexToBin(extensionPart);

    // eFlag tells if extension part ends or not
    // 0 - ends, 1 - doesn't end 
    std::string eFlag = "1"; // for first iteration of loop

    // I need to count number of bits read
    // for checking if padding is present
    int bitsRead = 0;  
    while (eFlag == "1"){   // while there is next length indicator to get                
        // Check if extension flag is set
        // and remove it
        eFlag = binExtensionPart.substr(0, 1);
        binExtensionPart.erase(0,1);
        bitsRead += 1;

        // Get LI 
        std::string lengthIndicator = binExtensionPart.substr(0, 11);
        binExtensionPart.erase(0,11);
        bitsRead += 11;

        long int li = strtoul(lengthIndicator.c_str(), NULL, BASE_2);
        liVec->push_back(li);
    }

    // check if padding is present
    while ( (bitsRead % 8) != 0 ){
        binExtensionPart.erase(0,1);
        bitsRead++;
    }
    return bitsRead / 8;
}


// Author: Adam Wroblak
// struct will be filled depending on contents in the data string
uint16_t readControlAMDPDU(std::string pdu, struct pduAMDInfo *info)
{
    std::string binPdu = hexToBin(pdu);
    std::string strDc = binPdu.substr(0, 1);
    std::string strCpt = binPdu.substr(1,3);
    std::string strAckSn = binPdu.substr(4, 10);
    std::string strE1 = binPdu.substr(14, 1);
    printf("dc: %s cpt: %s ack_sn: %s e1: %s\n", strDc.c_str(), strCpt.c_str(), strAckSn.c_str(), strE1.c_str());

    // if NACK set follows
    if (strE1[0] == '1'){

    }

    return 0;
}
