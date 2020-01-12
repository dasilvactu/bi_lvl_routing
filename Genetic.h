#ifndef GENETIC_H_INCLUDED
#define GENETIC_H_INCLUDED
#include "Individual.h"
#include "Instance.h"
#include "Solver.h"
#include "ILS.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;
class Genetic{
    float NCross;
    float NMut;
    int PopSize;
    int MaxIt;
    int nc;
    int nm;
    int tot;
    int Nils;
    Individual **population;
    Instance *instance;
public:
    Genetic(Instance *instance,int popsize, float ncross, float nmut,  int maxit);
    ~Genetic();
    void InitPOP();
    void InitPOP2();
    void OnePointCX(Individual *p1, Individual *p2, Individual *f1, Individual *f2);
    void OnePointCX2(Individual *p1, Individual *p2, Individual *f1, Individual *f2);
    void TwoPointCX(Individual *p1, Individual *p2, Individual *f1, Individual *f2);
    void TwoPointCX2(Individual *p1, Individual *p2, Individual *f1, Individual *f2);
    void Mutation(Individual *p1, Individual *f1);
    void Mutation2(Individual *p1, Individual *f1);
    void Evolve();
    int Tournament();
    Individual* getBest();




};

#endif // GENETIC_H_INCLUDED
