#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>

enum rlcMode {T, U5, U10, A};
enum typeSdu {D, C};

struct RlcSduS
{
    rlcMode mode;
    typeSdu type;
    int pool;
    int sizePdu;
    int seqNum;
    std::vector<int> sizeSduS;
    std::vector<std::string> data;
};

struct RlcPduS
{
    rlcMode mode;
    int sizePdu;
    std::vector<std::string> data;
};


int main()
{
    return 0;
}

