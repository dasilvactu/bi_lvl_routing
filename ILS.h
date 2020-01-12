#ifndef ILS_H_INCLUDED
#define ILS_H_INCLUDED
#include "Instance.h"
#include "Individual.h"
#include <algorithm>
#include <vector>
using namespace std;
class ILS{
    int iterations;
public:
    ILS(int it);
    void run(Individual *ind, Instance *instance);
};

#endif // ILS_H_INCLUDED
