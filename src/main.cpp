#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include "composer.h"


int main()
{
    RlcSduS *rlcSdu_p = new RlcSduS();
    RlcPduS *rlcPdu_p = new RlcPduS();
    loadSduFile("example1.txt", rlcSdu_p);
    rlcComposer(rlcSdu_p, rlcPdu_p);
    return 0;
}

