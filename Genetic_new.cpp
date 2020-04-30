#include "Genetic.h"


Genetic::Genetic(Instance *instance,int popsize, float ncross, float nmut,  int maxit){
    this->Nils = 10;
    this->NCross = ncross;
    this->NMut = nmut;
    this->PopSize = popsize;
    this->MaxIt = maxit;
    this->nc = (int)(popsize*ncross);
    if (this->nc%2){
        this->nc++;
    }
    this->nm = (int)(popsize*nmut);
    this->tot = popsize+nc+nm;
	if (tot%2) {
			tot ++;
	}
	//cout<<tot<<" - "<<nc<<" - "<<nm<<endl;
    this->population = new Individual*[this->tot];
	this->instance = instance;
}

void Genetic::InitPOP(){
    int kbus = instance->getKBus();
    int stations = instance->getNStations();
    int students = instance->getNStudents();
    //cout<<kbus<<" - "<<stations<<" - "<<students<<endl<<endl;
    int insertions = 3;
    for(int i=0;i<PopSize; i++){
        int *aux = new int[stations];
        for (int k=0;k<stations; k++){
            aux[k] = 0;
        }
        aux[0]=1;
        population[i] = new Individual(kbus, students, stations);
		for (int k=0;k<kbus;k++){
			population[i]->getY()[0][k] = 1;
		}
        for(int j = 0; j<insertions; j++){
            int bus = rand()%kbus;
            int station = rand()% stations;
            if(aux[station]==0){
                population[i]->getY()[station][bus] = 1;
                aux[station] = 1;
            }
        }
        delete[] aux;
    }


}
void Genetic::OnePointCX(Individual *p1, Individual *p2, Individual *f1, Individual *f2){
    int range = p1->getNStations();
    int kmax = p1->getKBus();
    int cut = rand() % range;
//    cout<<"Cut: "<<cut<<endl;
    for(int k=0; k<kmax; k++){
        for(int i = 0; i<range; i++){
            if(i<cut){
                f1->getY()[i][k] = p1->getY()[i][k];
                f2->getY()[i][k] = p2->getY()[i][k];
            }else{
                f1->getY()[i][k] = p2->getY()[i][k];
                f2->getY()[i][k] = p1->getY()[i][k];
            }
        }
    }
}
void Genetic::TwoPointCX(Individual *p1, Individual *p2, Individual *f1, Individual *f2){
    int range = p1->getNStations();
    int kmax = p1->getKBus();
    int cut1 = rand() % range;
    int cut2 = rand() % range;
    int aux = min(cut1,cut2);
    if(cut2==aux){
        cut2 = cut1;
        cut1 = aux;
    }
//    cout<<"Cuts: "<<cut1<<"-"<<cut2<<endl;
    for(int k=0; k<kmax; k++){
        for(int i = 0; i<range; i++){
            if(i>cut1 && i<cut2){
                f1->getY()[i][k] = p2->getY()[i][k];
                f2->getY()[i][k] = p1->getY()[i][k];
            }else{
                f1->getY()[i][k] = p1->getY()[i][k];
                f2->getY()[i][k] = p2->getY()[i][k];
            }
        }
    }
}
void Genetic::Mutation(Individual *p1, Individual *f1){
    //for(int i=0;i<p1->getNStations(); i++){
     //   for (int k=0; k< p1->getKBus(); k++){
      //      f1->getY()[i][k] = p1->getY()[i][k];
        //}
    //}
    int jmax = p1->getNStations();
    int kmax = p1->getKBus();
    int bus = rand() % (kmax);
    int station = rand() % (jmax-1) +1;
//    cout<<"Station: "<<station<<" - Bus: "<<bus<<endl;
    for(int k=0; k<kmax; k++){
        f1->getY()[station][k] = 0;
    }
    f1->getY()[station][bus] = 1;
}
int Genetic::Tournament(){
    int a = rand() % PopSize;
    int b = rand() % PopSize;
    return min(a, b);
}

bool sortIndividual(Individual* a, Individual* b) {
	return a->getFitness() >b->getFitness();
}
bool sortIndividualLVL2(Individual* a, Individual* b) {
	return a->getLVL2() <b->getLVL2();
}
Individual* Genetic::getBest(){
    return this->population[0];

}
void Genetic::Evolve(){
    Solver *solver = new Solver(instance);
    InitPOP();
    for(int i=0; i<PopSize; i++){
        solver->PopRows(population[i]);
        population[i]->tourConstructZ();
		
        ILS *ils = new ILS(this->Nils);
		ils->run(population[i],instance);
		
		population[i]->evaluate(instance);
		delete ils;
    }
    for(int it=0;it<MaxIt; it++){
	//operators
//        cout<<"Evolution"<<endl;
        for (int i = PopSize; i < PopSize+nc; i+=2) {//CrossOver
            int a = Tournament(), b = Tournament();
            population[i] = new Individual(population[a]);
            population[i + 1] = new Individual(population[b]);
			TwoPointCX(population[a],population[b],population[i],population[i+1]);
            solver->PopRows(population[i]);
            solver->PopRows(population[i+1]);
            population[i]->tourConstructZ();
            population[i+1]->tourConstructZ();
            ILS *ils = new ILS(this->Nils);
            ils->run(population[i],instance);
            population[i]->evaluate(instance);
            delete ils;
            ILS *ils2 = new ILS(this->Nils);
            ils2->run(population[i+1],instance);
            population[i+1]->evaluate(instance);
            delete ils2;

        }
	    for (int i = PopSize+nc; i < tot; i++) {//Mutation
            int a = Tournament();
            population[i] = new Individual(population[a]);
            Mutation(population[a],population[i]);
			//population[a]->printY();
			//population[i]->printY();
			//cout<<endl<<endl;
            solver->PopRows(population[i]);
            population[i]->tourConstructZ();
            ILS *ils = new ILS(this->Nils);
            ils->run(population[i],instance);
            population[i]->evaluate(instance);
            delete ils;

        }
        sort(population, population + tot, sortIndividual);

        for(int i = PopSize; i < tot; i++){
                delete population[i];
        }
        //cout<<"IT: "<<it<<" - Value: "<<population[0]->getFitness()<<endl;
    }
	//cout<<"BEST: "<<population[0]->getFitness()<<endl;
	delete solver;
	//return population[0];
}
Genetic::~Genetic(){
    for(int i=0; i <PopSize; i++){
			delete this->population[i];
		
    }
    delete[] this->population;

}
