#include <iostream>
#include "Solver.h"
#include "Instance.h"
#include "stdlib.h"
#include "Genetic.h"
#include "Genetic2.h"
#include "Individual.h"
#include <time.h>
using namespace std;
int main(int argc, char *argv[])
{
	Instance *instancia = new Instance(20,6000,5,6000);
	instancia->readFile("instances/SBRP1Bus01.txt");
	Genetic2 *genetic  = new Genetic2(instancia,10,0.7,0.4,5);
	genetic->Evolve();
	Individual *ind = genetic->getBest();
	ind->printX();
	ind->printY();
	ind->printZ();
	delete genetic;
	delete instancia;
	
	return 0;
}
