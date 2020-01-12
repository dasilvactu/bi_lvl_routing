#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;
class Instance{
    int Kbus;
    int NStudents;
    int NStations;
    float **stations;
    float **students;
    float **distancesSil;
    float **distancesStaSta;
    int CB;
    int CO;
    int CW;
    int CI;
public:
    Instance(int cb, int co, int cw, int ci);
    ~Instance();
    void readFile(char *fileName);
    float dist(float *p1, float *p2);
    int getSil(int i, int l);
    int getKBus();
    int getNStudents();
    int getNStations();
    float getDistancesStaStu(int i, int l);
    float getDistancesStaSta(int i, int l);
	void printDistStaStu();
    int getCB();
    int getCO();
    int getCW();
    int getCI();
    void show();
};

#endif // INSTANCE_H_INCLUDED
