#ifndef RLC_STRUCTURES_H
#define RLC_STRUCTURES_H

#include <vector>
#include <string>
#include <stdint.h>

enum rlcMode {X, T, U5, U10, A};
enum typeSdu {Y, D, C};

struct RlcSduS
{
    rlcMode mode = X;
    typeSdu type = Y;
    int pool = 0;
    int sizePdu = 0;
    std::vector<int> sizeSduS;
    std::vector<std::string> data;
};

struct RlcPduS
{
    rlcMode mode = X;
    int sizePdu = 0;
    std::vector<std::string> data;
};

typedef struct pduHeaderU5
{
    uint32_t fi:2;
    uint32_t e:1;
    uint32_t sn:5;
    std::vector<uint32_t> li;
    std::string data;
}pduHeaderU5;

typedef struct pduHeaderU10
{
    uint32_t r1_1:1;
    uint32_t r1_2:1;
    uint32_t r1_3:1;
    uint32_t fi:2;
    uint32_t e:1;
    uint32_t sn:10;
    std::vector<uint32_t> li;
    std::string data;
}pduHeaderU10;

typedef struct pduHeaderAM
{
    uint32_t dc:1;
    uint32_t rf:1;
    uint32_t p:1;
    uint32_t fi:2;
    uint32_t e:1;
    uint32_t sn:10;
}pduHeaderAM;

typedef struct pduStatusHeaderAM
{
    uint32_t dc:1;
    uint32_t cpt:3;
    uint32_t ack_sn:10;
    uint32_t e1:1;
    uint32_t more:1;
}pduStatusHeaderAM;

typedef struct extensionLi
{
    uint32_t e1:1;
    uint32_t li1:11;
    uint32_t e2:1;
    uint32_t li2:11;
}extensionLi;

#endif
