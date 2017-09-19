#ifndef COMPOSER_H
#define COMPOSER_H

#include "rlc_structures.h"

int loadSduFile(std::string filename, RlcSduS *rlcSdu_p);

int savePduFile(std::string filename);
int rlcComposer(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p);

#endif