#ifndef RLC_STRUCTURES_H
#define RLC_STRUCTURES_H
<<<<<<< HEAD
#include <vector>
#include <string>

enum rlcMode {T, U5, U10, A};
enum typeSdu {D, C};
=======

#include <string>
#include <vector>
enum rlcMode {X, T, U5, U10, A};
enum typeSdu {Y, D, C};
>>>>>>> composer

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
    std::string data;
};
#endif
