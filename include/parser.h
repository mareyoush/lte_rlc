#ifndef PARSER_H
#define PARSER_H
#include "rlc_structures.h"
#include <stdint.h>

#define EFILE_EMPTY 1
#define EBAD_FORMAT 2
#define EBAD_PDU_SIZE 3
#define EBAD_DATA_LENGTH 4

uint16_t check_pdu_file(FILE *file, struct RlcPduS *pdu);
uint16_t rlcParser(RlcPduS *rlcPdu_p, RlcSduS *rlcSdu_p);
uint16_t parseU5(RlcPduS *pdu, RlcSduS *sdu);
uint16_t parseU10(RlcPduS *pdu, RlcSduS *sdu);
uint16_t parseT(RlcPduS *pdu, RlcSduS *sdu);
uint16_t parseA(RlcPduS *pdu, RlcSduS *sdu);
int ishex(char c);
#endif