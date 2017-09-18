#include <types.h>
#include "include/rlc_structures.h"

int loadSduFile(std::string filename, RlcSduS *rlcSdu_p);
int savePduFile(std::string filename);
U16 rlcComposer(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p);