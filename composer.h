#include <types.h>

int loadSduFile(std::string filename);
int savePduFile(std::string filename);
U16 rlcComposer(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p);