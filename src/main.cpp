#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include "composer.h"


int main()
{
    RlcSduS *rlcSdu_p = new RlcSduS();
    loadSduFile("example1.txt", rlcSdu_p);
    return 0;
}

