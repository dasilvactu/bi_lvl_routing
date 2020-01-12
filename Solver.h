#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED
#include <sstream>
#include <iostream>
#include <string>
#include "Individual.h"
#include "Instance.h"
using namespace std;
class Solver{
    Instance *instance;

public:
    Solver(Instance *inst);
    void PopRows(Individual *ind);
};

#endif // SOLVER_H_INCLUDED
