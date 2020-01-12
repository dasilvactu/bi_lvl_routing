#include <iostream>
#include "Solver.h"
#include "Instance.h"
#include "stdlib.h"
#include "Genetic2.h"
#include <time.h>
#include "Individual.h"
using namespace std;
#define IT 15

int main(int argc, char *argv[])
{
    Individual *best = new Individual(1,17,10);	
    float* vetor = new float[IT];
    for(int i=0; i<IT; i++){
//        srand (atoi(argv[1]));
        srand (i+1);
        char* arquivo = argv[1];
        //cout<<arquivo<<endl;
        Instance *instancia = new Instance(20,6000,5,6000);
        instancia->readFile(arquivo);
        //instancia->show();
        Genetic2 *genetic  = new Genetic2(instancia,50,0.7,0.4,90);
        genetic->Evolve();
		Individual *current= new Individual(genetic->getBest());
		if (current->getFitness()>best->getFitness()){
			delete best;
			best = new Individual(current);
		}
		vetor[i] = current->getFitness();
        delete current;
	    delete genetic;
	    delete instancia;
    }
	best->printX();
	best->printY();
	best->printZ();
    float soma = 0;
    for(int i=0;i<IT; i++){
        soma+=vetor[i];
		cout<<vetor[i]<<endl;
    }
    cout<<endl<<soma/IT<<endl;
    delete best;
    delete[] vetor;
    return 0;
}
