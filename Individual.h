#ifndef INDIVIDUAL_H_INCLUDED
#define INDIVIDUAL_H_INCLUDED
#include <iostream>
#include <vector>
#include "Instance.h"
using namespace std;
class Individual{
	int **tour; // tour[k][i] tour for k-bus
	int *sizeTour; // size of tours
    int **y; // y[i][k] bus k in station i
    int *gene; // gene[i] bus in station i
    int ***z; // z[i][l][k] student l pick bus k in stop i
    int Kbus;
    int NStudents;
    int NStations;
    float xCost;
    float fitnessLVL1;
    float fitnessLVL2;
public:
    Individual(int k, int stu, int sta);
    Individual(Individual *ind);
    ~Individual();
    void tourConstruct();
    void tourConstructZ();
    void constructY();
    float getFitness();
    float calcTourCost(Instance *instance);
    float calcTourCost(Instance *instance, int k);
    float getLVL2();
    void setFitnessLVL2(float value);
    void evaluate(Instance *instance);
	void swapRoute(int *rotak, int k);
	void swapRoute(vector<int> rotak, int k);
	float getTourCost();
    void printY();
    void printZ();
    void printX();
	int** getTour();
    int** getY();
    int*** getZ();
    int* getGene();
    void setXCost(float val);
    int getKBus();
    int getNStudents();
    int getNStations();
	int getSizeTour(int value);
};


#endif // INDIVIDUAL_H_INCLUDED
