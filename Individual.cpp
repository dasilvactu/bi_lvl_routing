#include "Individual.h"

Individual::Individual(int k, int stu, int sta){
    this->Kbus = k;
    this->NStations = sta;
    this->NStudents = stu;
    this->fitnessLVL1 =0;
    this->fitnessLVL2 =0;
    gene = new int[NStations];
    tour = new int*[Kbus];
	sizeTour = new int[Kbus];
    y = new int*[NStations];
    for (int i =0; i<NStations; i++){
        y[i] = new int[Kbus];
    }
    for (int i =0; i<NStations; i++){
        gene[i] = -1;
    }
    for (int i =0; i<NStations; i++){
        for (int k=0;k<Kbus; k++){
                y[i][k] = 0;
        }
    }
    for (int k=0;k<Kbus; k++){
        y[0][k] = 1;
    }
    z = new int**[NStations];
    for (int i =0; i<NStations; i++){
        z[i] = new int*[NStudents];
        for(int l= 0; l < NStudents; l++){
            z[i][l] = new int[Kbus];
        }
    }
    for (int i =0; i<NStations; i++){
        for(int l= 0; l <NStudents; l++){
            for (int k=0;k<Kbus; k++){
                z[i][l][k] = 0;
            }
        }
    }
}

Individual::Individual(Individual * ind){
	this->Kbus = ind->getKBus();
	this->NStations = ind->getNStations();
	this->NStudents = ind->getNStudents();
	this->fitnessLVL1 = ind->getFitness();
	this->fitnessLVL2 = ind->getLVL2();
	this->y = new int*[NStations];
	for (int i = 0; i < NStations; i++) {
		this->y[i] = new int[Kbus];
		for (int k = 0; k < Kbus; k++) {
			this->y[i][k] = ind->getY()[i][k];
		}
	}

	this->z = new int**[NStations];
	for (int i = 0; i < NStations; i++) {
		this->z[i] = new int*[NStudents];
		for (int l = 0; l < NStudents; l++) {
			this->z[i][l] = new int[Kbus];
			for (int k = 0; k < Kbus; k++) {
				this->z[i][l][k] = ind->getZ()[i][l][k];
			}
		}
	}
	this->tour = new int*[Kbus];
	this->sizeTour = new int[Kbus];
    for(int k= 0; k<Kbus; k++){
		this->sizeTour[k] = ind->getSizeTour(k);
        this->tour[k] =  new int[this->sizeTour[k]];
        for(int i=0; i<sizeTour[k]; i++){
            this->tour[k][i] = ind->getTour()[k][i];

        }
    }
    this->gene = new int[NStations];
    for (int i = 0; i < NStations; i++) {
        this->gene[i] = ind->gene[i];
    }
}

void Individual::constructY(){
    for (int i =1; i<NStations; i++){
        int bus = gene[i];
        if (bus!=-1){
            y[i][bus] =1;
        }
    }

}
void Individual::tourConstructZ(){
    for(int pos=0; pos<Kbus; pos++){
        //delete[] tour[pos];
    }
    for(int k= 0; k<Kbus; k++){
        int cont = 0;
        for(int i=1; i<NStations; i++){
            bool tem = false;
            for (int j=0; j<NStudents;j++){
                if(z[i][j][k]==1){
                    tem =true;

                }
            }
            if (tem){
                cont++;
            }
            
        }
        //cout<<"chega: "<<endl;
        
        //cout<<"sai";
        sizeTour[k] = cont;
        //delete[] tour;
        tour[k] = new int[sizeTour[k]];
        int pos = 0;
        for(int i=1; i<NStations; i++){
            bool tem = false;
            for(int j=0; j< NStudents; j++){
                if(z[i][j][k]==1){
                    tem = true;
                }

            }
            if (tem){
                tour[k][pos]= i;
                pos++;
            }
            
        }
    }


}
void Individual::tourConstruct(){

	for(int k= 0; k<Kbus; k++){
		int cont = 0;
        for(int i=1; i<NStations; i++){
            if(y[i][k]==1){
				cont++;

            }
        }
		//cout<<"Cont: "<<cont<<endl;

		sizeTour[k] = cont;
		tour[k] = new int[sizeTour[k]];
		int pos = 0;
		for(int i=1; i<NStations; i++){
            if(y[i][k]==1){
				tour[k][pos]= i;
				pos++;

            }
        }
    }
}

int** Individual::getTour(){
	return tour;
}
float Individual::getFitness(){
    return this->fitnessLVL1;

}
int* Individual::getGene(){
    return this->gene;
}
float Individual::getLVL2(){
    return this->fitnessLVL2;

}
void Individual::setFitnessLVL2(float value){
    this->fitnessLVL2 = value;

}
int Individual::getSizeTour(int value){
	return sizeTour[value];
}
void Individual::evaluate(Instance *instance){
    float part1 = 0;
    int cont = 0;
    for(int i=0; i<NStations; i++){
        for(int l=0; l<NStudents; l++){
            for(int k=0; k<Kbus; k++){
                if(z[i][l][k]==1){
                    cont++;
                }
            }
        }
    }
    //cout<<"cont: "<<cont<<endl;
    part1 = instance->getCI()*cont;
    //cout<<"part1: "<<part1<<endl;
	calcTourCost(instance);
    fitnessLVL1 = part1 - getTourCost();
}

float Individual::calcTourCost(Instance *instance){
    float part2=0;
    for(int k=0; k<Kbus; k++){
        if(sizeTour[k]!=0){
            part2+= instance->getDistancesStaSta(0,tour[k][0]);
            for(int i=0; i<sizeTour[k] -1; i++){
                part2+= instance->getDistancesStaSta(tour[k][i],tour[k][i+1]);
            }
            part2+=instance->getDistancesStaSta(0,tour[k][sizeTour[k]-1]);
            //part2+= instance->getDistancesStaSta(tour[k][sizeTour[k]-1],0);
        }
    }
    xCost = part2*20;
    return xCost;
}
float Individual::calcTourCost(Instance *instance, int k){
    float part2 = 0;
    if(sizeTour[k]!=0){
            part2+= instance->getDistancesStaSta(0,tour[k][0]);
            for(int i=0; i<sizeTour[k] -1; i++){
                part2+= instance->getDistancesStaSta(tour[k][i],tour[k][i+1]);
            }
            part2+=instance->getDistancesStaSta(0,tour[k][sizeTour[k]-1]);
            //part2+= instance->getDistancesStaSta(tour[k][sizeTour[k]-1],0);
    }
    xCost = part2*20;
    return xCost;
}
void Individual::setXCost(float val){
    this->xCost = val;
}
void Individual::swapRoute(int *rotak, int k){
    if(sizeTour[k]!=0){
        for(int i=0; i<sizeTour[k] ; i++){
            this->tour[k][i] = rotak[i];
        }

    }

}
void Individual::swapRoute(vector<int> rotak, int k){
    if(sizeTour[k]!=0){
        for(int i=0; i<sizeTour[k] ; i++){
            this->tour[k][i] = rotak.at(i);
        }

    }

}
float Individual::getTourCost(){
    return xCost;
}
int** Individual::getY(){
    return this->y;
}
int*** Individual::getZ(){
    return this->z;
}

int Individual::getKBus(){
    return this->Kbus;
}
int Individual::getNStudents(){
    return this->NStudents;
}
int Individual::getNStations(){
    return this->NStations;
}
void Individual::printY(){
    cout<<"Y: ";
    for (int k=0;k<Kbus; k++){
        for (int i =0; i<NStations; i++){
            cout<<" "<<y[i][k]<<" ";
        }
        cout<<endl;
    }
}

void Individual::printZ(){
    for (int i =0; i<NStations; i++){
        for(int l= 0; l <NStudents; l++){
            for (int k=0;k<Kbus; k++){
				if (z[i][l][k] ==1){
					cout<<i<<"-"<<l<<"-"<<k<<": "<<z[i][l][k]<<endl;
				}
            }
        }
    }
}
void Individual::printX(){
    for(int k=0;k < Kbus; k++){
        //cout<<"tour "<<k<<endl;
        //cout<<"      ";
		//cout<<"sizeTour: "<<sizeTour[k]<<endl;
        for(int i=0;i<sizeTour[k]; i++){
            cout<<tour[k][i]<<"-";
        }
	cout<<endl;
    }


}

void Individual::printGene(){
    cout<<"Gene: [";
    for (int i =0; i<NStations; i++){
        cout<<this->gene[i]<<" ";
    }
    cout<<"]"<<endl;
}

void Individual::printAll(){
    printGene();
    printY();
    printX();
}
Individual::~Individual(){
    for (int i =0; i<NStations; i++){
        delete[] this->y[i];
    }

    for (int i =0; i<NStations; i++){
        for(int l= 0; l <NStudents; l++){
            delete[] this->z[i][l];
        }
        delete[] this->z[i];
    }
    for(int k=0; k<Kbus; k++){
        delete[] this->tour[k];
    }
    delete[] this->tour;
	delete[] this->sizeTour;
    delete[] this->z;
    delete[] this->y;
    delete[] this->gene;
}
