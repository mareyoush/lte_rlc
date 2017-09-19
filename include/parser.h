#ifndef PARSER_H
#define PARSER_H
#include "rlc_structures.h"
int check_pdu_file(FILE *file, struct RlcPduS *pdu);
int ishex(char c);
#endif