#ifndef PARSER_H
#define PARSER_H
#include "rlc_structures.h"
#include <stdint.h>
#include <string>

#define BASE_16 16
#define EFILE_EMPTY 1
#define EBAD_FORMAT 2
#define EBAD_PDU_SIZE 3
#define EBAD_DATA_LENGTH 4

<<<<<<< HEAD
#define BIT1  0x0001
#define BIT2  0x0002
#define BIT3  0x0004
#define BIT4  0x0008
#define BIT5  0x0010
#define BIT6  0x0020
#define BIT7  0x0040
#define BIT8  0x0080
#define BIT9  0x0100
#define BIT10 0x0200
#define BIT11 0x0400
#define BIT12 0x0800
#define BIT13 0x1000
#define BIT14 0x2000
#define BIT15 0x4000
#define BIT16 0x8000
#define FIRST_10_BITS 0x03ff

=======
std::string hexToBin(std::string hex);
>>>>>>> ec86212ea872e35525bed03f91e4b30642ee234f
uint16_t check_pdu_file(FILE *file, struct RlcPduS *pdu);
uint16_t rlcParser(RlcPduS *rlcPdu_p, RlcSduS *rlcSdu_p);
uint16_t parseU5(RlcPduS *pdu, RlcSduS *sdu);
uint16_t parseU10(RlcPduS *pdu, RlcSduS *sdu);
uint16_t parseT(RlcPduS *pdu, RlcSduS *sdu);
uint16_t parseA(RlcPduS *pdu, RlcSduS *sdu);
int ishex(char c);
#endif
