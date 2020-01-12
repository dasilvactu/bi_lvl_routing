#include "Genetic2.h"

Genetic2::Genetic2(Instance *instance,int popsize, float ncross, float nmut,  int maxit){
    this->NCross = ncross;
    this->NMut = nmut;
    this->PopSize = popsize;
    this->MaxIt = maxit;
    this->nc = (int)(popsize*ncross);
    this->nm = (int)(popsize*nmut);
    this->Nils = 50;
    if (this->nc%2){
        this->nc++;
    }
    this->tot = popsize+nc+nm;
	if (tot%2) {
			tot ++;
	}
	//cout<<tot<<" - "<<nc<<" - "<<nm<<endl;
    this->population = new Individual*[this->tot];
	this->instance = instance;
}


void Genetic2::InitPOP2(){
    int kbus = instance->getKBus();
    int stations = instance->getNStations();
    int students = instance->getNStudents();
    //cout<<kbus<<" - "<<stations<<" - "<<students<<endl<<endl;
    //int insertions = rand() % stations;
    int insertions = 3;
    for(int i=0;i<PopSize; i++){
        population[i] = new Individual(kbus, students, stations);
        for(int j = 0; j<insertions; j++){
            int bus = rand()%kbus;
            int station = rand()% (stations -1) +1;
            population[i]->getGene()[station] = bus;            
        }

        population[i]->constructY();
    }

}
void Genetic2::OnePointCX2(Individual *p1, Individual *p2, Individual *f1, Individual *f2){
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
    f1->constructY();
    f2->constructY();
}
void Genetic2::TwoPointCX2(Individual *p1, Individual *p2, Individual *f1, Individual *f2){
    int range = p1->getNStations();
    int kmax = p1->getKBus();
    int cut1 = rand() % range;
    int cut2 = rand() % range;
    int aux = min(cut1,cut2);
    if(cut2==aux){
        cut2 = cut1;
        cut1 = aux;
    }
    
    for(int i = 0; i<range; i++){
        if(i>cut1 && i<cut2){
            f1->getGene()[i] = p2->getGene()[i];
            f2->getGene()[i] = p1->getGene()[i];
        }else{
            f1->getGene()[i] = p1->getGene()[i];
            f2->getGene()[i] = p2->getGene()[i];
        }
    }
    f1->constructY();
    f2->constructY();
    
}
void Genetic2::Mutation2(Individual *p1, Individual *f1){
    int jmax = p1->getNStations();
    int kmax = p1->getKBus();
    int bus = rand() % (kmax +1) -1;
    int station = rand() % (jmax-1) +1;
    f1->getGene()[station] = bus;
    f1->constructY();
    
}
int Genetic2::Tournament(){
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
Individual* Genetic2::getBest(){
    return this->population[0];
}
void Genetic2::Evolve(){
    Solver *solver = new Solver(instance);
    InitPOP2();
    for(int i=0; i<PopSize; i++){
        solver->PopRows(population[i]);
        population[i]->tourConstruct();
		
        ILS *ils = new ILS(50);
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
			TwoPointCX2(population[a],population[b],population[i],population[i+1]);
			population[i]->tourConstructZ();
			population[i+1]->tourConstructZ();
            solver->PopRows(population[i]);
            solver->PopRows(population[i+1]);
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
            Mutation2(population[a],population[i]);
			population[i]->tourConstructZ();
			//population[a]->printY();
			//population[i]->printY();
			//cout<<endl<<endl;
            solver->PopRows(population[i]);
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
}
Genetic2::~Genetic2(){
    for(int i=0; i <PopSize; i++){
			delete this->population[i];
		
    }
    delete[] this->population;

}