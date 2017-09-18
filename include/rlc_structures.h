#ifndef RLC_STRUCTURES_H
#define RLC_STRUCTURES_H
#include <vector>
#include <string>

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
#endif