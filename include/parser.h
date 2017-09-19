#ifndef PARSER_H
#define PARSER_H
#include "rlc_structures.h"

#define EFILE_EMPTY 1
#define EBAD_FORMAT 2
#define EBAD_PDU_SIZE 3
#define EBAD_DATA_LENGTH 4

int check_pdu_file(FILE *file, struct RlcPduS *pdu);
int ishex(char c);
#endif