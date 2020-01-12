#include "Instance.h"

Instance::Instance(int cb, int co, int cw, int ci){
    this->CB = cb;
    this->CO = co;
    this->CW = cw;
    this->CI = ci;
}

void Instance::readFile(char *fileName){
    ifstream arq;
    arq.open(fileName);
    arq>>Kbus;
    arq>>NStations;
	NStations++;
    stations = new float*[NStations];
	stations[0] = new float[2];
	stations[0][0] = 0;
	stations[0][1] = 0;
    for(int i=1; i <NStations; i++){
        stations[i] = new float[2];
        arq>>stations[i][0];
        arq>>stations[i][1];
    }
    arq>>NStudents;
    students = new float*[NStudents];
    for(int i=0; i <NStudents; i++){
        students[i] = new float[2];
        arq>>students[i][0];
        arq>>students[i][1];
    }
    //distance from station to students
    distancesSil = new float*[NStations];
    for(int i=0; i < NStations; i++){
        distancesSil[i] = new float[NStudents];
    }
    for(int i=0; i < NStations; i++){
        for(int j=0; j < NStudents; j++){
            distancesSil[i][j] = dist(stations[i], students[j]);
        }
    }
    distancesStaSta = new float*[NStations];
    for(int i= 0; i<NStations; i++){
        distancesStaSta[i] = new float[NStations];
    }
    for(int i=0; i < NStations; i++){
        for(int j=0; j < NStations; j++){
            distancesStaSta[i][j] = dist(stations[i], stations[j]);
        }
    }
}
int Instance::getSil(int i, int l){
    int val = 0;
    //cout<<"De "<<i<<"  Para: "<<l<<endl
    if (distancesSil[i][l]<800){
        if (i==0){
			val = 0;
		}else{
			val = 1;
		}
    }
    return val;
}
float Instance::dist(float *p1, float *p2){
    return sqrt(pow(p1[0] - p2[0],2) + pow(p1[1] - p2[1],2));
}

int Instance::getCI(){
    return this->CI;

}

int Instance::getKBus(){
    return this->Kbus;
}
int Instance::getNStudents(){
    return this->NStudents;
}
int Instance::getNStations(){
    return this->NStations;
}
float Instance::getDistancesStaSta(int i, int l){
    return this->distancesStaSta[l][i];
}
float Instance::getDistancesStaStu(int i, int l){
    return this->distancesSil[i][l];
}
int Instance::getCB(){
    return this->CB;
}
int Instance::getCO(){
    return this->CO;
}
int Instance::getCW(){
    return this->CW;
}
void Instance::show(){
    cout<<"Kbus: "<<Kbus<<endl;
    cout<<"NStations: "<<NStations<<endl;
    cout<<"NStudents: "<<NStudents<<endl;

}
void Instance::printDistStaStu(){
	for(int i=0; i < NStations; i++){
        for(int j=0; j < NStudents; j++){
            cout<<distancesSil[i][j] << "  ";
        }
		cout<<endl;
    }
}

Instance::~Instance(){

    for(int i =0; i<NStations; i++){
        delete[] stations[i];
    }
    for(int i =0; i<NStudents; i++){
        delete[] students[i];
    }
    for(int i=0; i < NStations; i++){
        delete[] distancesSil[i];
    }
    for(int i =0; i<NStations; i++){
        delete[] distancesStaSta[i];
    }
    delete[] distancesStaSta;
    delete[] distancesSil;
    delete[] stations;
    delete[] students;
}
