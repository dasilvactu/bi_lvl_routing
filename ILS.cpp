#include "ILS.h"
ILS::ILS(int it){
    iterations = it;
}

bool sortInd(Individual* a, Individual* b) {
	return a->getTourCost() <b->getTourCost();
}

int* insertValue (int* originalArray, int positionToInsertAt,int originalPosition, int ValueToInsert, int sizeOfOriginalArray){
	vector<int> newArray;
	for(int i = 0; i<sizeOfOriginalArray;i++){
		if(originalArray[i]!=ValueToInsert){
			newArray.push_back(originalArray[i]);
		}
		
	}
	newArray.insert(newArray.begin()+positionToInsertAt,ValueToInsert);
	int * retorno = new int[sizeOfOriginalArray];
	for(int i = 0; i<sizeOfOriginalArray; i++){
		retorno[i] = newArray[i];
	} 
	newArray.clear();
	return retorno;
}

void ILS::perturbation(int qtd, int n,int k, Individual *current){
	for(int j=0;j<qtd; j++){
		int a = rand()%n;
		int b = rand()%n;
		int val = current->getTour()[k][a];
		current->getTour()[k][a] = current->getTour()[k][b];
		current->getTour()[k][b] = val;
		//cout<<"entrou ILS"<<endl;
	}
}

void ILS::localSearch(Individual **localSearch,Individual *current, int n, int k,Instance *instance){
	int position = rand()%n; // position removed
	int value = current->getTour()[k][position];
	for(int j= 0; j< n; j++){
		localSearch[j] = new Individual(current);
		int* newTour = insertValue(localSearch[j]->getTour()[k],j,position,value,n);
		localSearch[j]->swapRoute(newTour,k);
		delete newTour;
	}
}

void ILS::run(Individual *ind, Instance *instance){
    //cout<<"Ind cost: "<<ind->calcTourCost(instance) <<" Route:";
	//cout<<"Entrou"<<endl;
   // ind->printY();
	//ind->printX();
   // cout<<endl;

    //cout<<"entrou ILS"<<endl;
    for (int k=0;k<ind->getKBus(); k++){

        //cout<<"k: "<<k<<endl;
        int n = ind->getSizeTour(k);
		if (n!=0){
			//cout<<"N: "<<n<<endl;
			for(int it=0;it<iterations; it++){
				Individual *current = new Individual(ind);
				//cout<<"IT: "<<it<<endl;
				int x = rand()%n; //qtd swaps
				perturbation(x,n,k,current);				

				//local search k removes and insertions
				Individual **individuals = new Individual*[n];
				localSearch(individuals,current,n,k,instance);
				sort(individuals, individuals + n, sortInd);
				if(individuals[0]->getTourCost()<ind->getTourCost()){
					ind->swapRoute(individuals[0]->getTour()[k],k);
					ind->setXCost(individuals[0]->getTourCost());
					//localSearch[0]->printX();
					//cout<<"dps troca:"<<endl;
					//ind->printX();
				}
				for(int z= 0; z<n ; z++){
					delete individuals[z];
				}
				delete [] individuals;
				delete current;

			}
		}
    }

    //cout<<"Best cost: "<<ind->calcTourCost(instance) <<" Route:";
    //cout<<"Saiu:'"<<endl;
	//ind->printY();
	//ind->printX();
    //cout<<endl;

}
