#include <iostream>
#include "Solver.h"
#include "Instance.h"
#include "stdlib.h"
#include "Genetic.h"
#include "Individual.h"
#include <time.h>
using namespace std;
int main(int argc, char *argv[])
{
	Instance *instancia = new Instance(20,6000,5,6000);
	instancia->readFile("instances/SBRP1Bus01.txt");
	//instancia->printDistStaStu();
	//cin.get();
	Solver *solver = new Solver(instancia);
	Individual *ind = new Individual(instancia->getKBus(), instancia->getNStudents(), instancia->getNStations());
	ind->getY()[0][0] = 1;
	ind->getY()[1][0] = 1;
	ind->getY()[2][0] = 1;
	ind->getY()[3][0] = 1;
	ind->getY()[4][0] = 1;
	ind->getY()[5][0] = 1;
	ind->getY()[6][0] = 1;
	ind->getY()[7][0] = 1;
	ind->getY()[8][0] = 1;
	ind->getY()[9][0] = 1;
	ind->getY()[10][0] = 0;
	ind->printY();
	solver->PopRows(ind);

	cout<<endl<<"tour"<<endl;
	ind->tourConstruct();
	ind->printX();
	ind->printZ();
	ILS *ils = new ILS(10);
	ils->run(ind,instancia);
	ind->evaluate(instancia);
	ind->tourConstructZ();
	cout<<endl<<endl;
	cout<<endl<<"tour"<<endl;
	ind->printX();
	ind->printZ();
	ind->calcTourCost(instancia);
	//ind->evaluate(instancia);
	cout<<"\nTourCost: "<<ind->getTourCost()<<endl;
	cout<<"\nFitness: "<<ind->getFitness()<<endl;
    	
    
	delete ils;
	delete ind;
	delete instancia;
	delete solver;
	
	
	return 0;
}
