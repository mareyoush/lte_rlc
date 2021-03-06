#ifndef COMPOSER_H
#define COMPOSER_H

#include "rlc_structures.h"

std::string decToBin(int dec, int bitsNumber);
int loadSduFile(std::string filename, RlcSduS *rlcSdu_p);
int savePduFile(std::string filename, RlcPduS *rlcPdu_p);
uint16_t rlcComposer(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p);
uint16_t composerTM(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p);
uint16_t composerUM(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p);
uint16_t composerAM(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p);
void log(std::string prompt);

#endif