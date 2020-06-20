#include <iostream>
#include "Instance.h"
#include "Individual.h"
#include "ILS.h"
#include <time.h>
#include <algorithm>
using namespace std;
int main(int argc, char *argv[])
{
	Instance *instancia = new Instance(20,6000,5,6000);
	instancia->readFile("instances/SBRP1Bus01.txt");
    Individual *ind = new Individual(1,10,17);
    int *aux = new int[10];
    for (int k=0;k<10; k++){
        aux[k] = 0;
    }
    aux[0]=1;
    for (int k=0;k<1;k++){
        ind->getY()[0][k] = 1;
    }
    for(int j = 0; j<4; j++){
        int bus = rand()%1;
        int station = rand()% 10;
        if(aux[station]==0){
            ind->getY()[station][bus] = 1;
            aux[station] = 1;
        }
    }
    delete[] aux;
    ind->tourConstruct();
	ind->printX();
    ILS *ils = new ILS(1);
    ils->run(ind,instancia);
    delete ils;
    delete ind;
	delete instancia;
	
	return 0;
}
