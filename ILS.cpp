#include "ILS.h"
ILS::ILS(int it){
    iterations = it;
}

bool sortInd(Individual* a, Individual* b) {
	return a->getTourCost() <b->getTourCost();
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
				//perturbation x swap
				//cout<<"x: "<<x<<endl;
				for(int j=0;j<x; j++){
					int a = rand()%n;
					int b = rand()%n;
					int val = current->getTour()[k][a];
					current->getTour()[k][a] = current->getTour()[k][b];
					current->getTour()[k][b] = val;
					//cout<<"entrou ILS"<<endl;
				}

				//local search k removes and insertions
				Individual **localSearch = new Individual*[n];
				for(int j= 0; j< n; j++){
					localSearch[j] = new Individual(current);
					int position = rand()%n; // position removed
					vector<int> tour;
					for (int t= 0; t<n;t++){
						if (t==j){
							tour.push_back(localSearch[j]->getTour()[k][position]);
						}
						if (t!=position){
							tour.push_back(localSearch[j]->getTour()[k][t]);
						}
					}
					//cout<<"Tour: ";
					//for (int t= 0; t<n;t++){
						//cout<<tour.at(t)<<" - ";
					//}
					//cout<<endl;
					localSearch[j]->swapRoute(tour,k);
					tour.clear();
					//swap(localSearch[j]->getTour()[k][j],localSearch[j]->getTour()[k][position]);
					float val = localSearch[j]->calcTourCost(instance,k);
					
					//cout<<"ind "<< j<< "  cost: "<<val <<" Route:";
					//localSearch[j]->printX();
					//cout<<endl;
				}
				sort(localSearch, localSearch + n, sortInd);
				if(localSearch[0]->getTourCost()<ind->getTourCost()){

					//localSearch[0]->printX();
					//cout<<"trocou:"<<endl;
					//ind->printX();
					ind->swapRoute(localSearch[0]->getTour()[k],k);
					ind->setXCost(localSearch[0]->getTourCost());
					//localSearch[0]->printX();
					//cout<<"dps troca:"<<endl;
					//ind->printX();
				}
				for(int z= 0; z<n ; z++){
					delete localSearch[z];
				}
				delete [] localSearch;
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
