#include "Solver.h"
#include <ilcplex/ilocplex.h>
using namespace std;
typedef IloArray<IloNumVarArray> NumVarMatrix;
typedef IloArray<NumVarMatrix>   NumVar3Matrix;


Solver::Solver(Instance *inst){
    this->instance = inst;
}

void Solver::PopRows(Individual *ind){
    try {
        //cout<<"Entrou Solver:"<<endl<<endl;
        IloEnv env;
        IloModel model(env);
        IloNum bus = instance->getKBus();
        IloNum stations = instance->getNStations();
        IloNum students = instance->getNStudents();
		NumVar3Matrix z(env,stations);
        char nomez[50];
        //create decision variables for model
        for(int i = 0; i<stations; i++){
			z[i] = NumVarMatrix(env,students);
            for(int l = 0; l<students; l++){
				z[i][l] = IloNumVarArray(env, bus);
                for(int k =0; k<bus; k++){
                    sprintf(nomez,"z(%d,%d,%d)",i,l,k);
                    z[i][l][k] = IloNumVar(env,0,1,ILOINT,nomez);
                }
            }
        }
		
		 IloExpr obj1(env);

        //objective funcion
		
		for (int i = 0; i< stations; i++){
			for (int l=0; l< students ; l++){
				for ( int k=0; k< bus; k++){
					//cout<< instance->getCW()<<" - " <<instance->getDistancesStaStu(i,l) << " - "<<instance->getCO()<<endl;
					obj1+=(instance->getCW()*instance->getDistancesStaStu(i,l) - instance->getCO())*z[i][l][k];
				}
			}
			
		}
        
        
        model.add(IloMinimize(env, obj1+ students*instance->getCO()));
        //add constraints to model

        for (int k = 0; k<bus; k++){
	    IloExpr expr(env);
            for(int i=0; i<stations; i++){

                for (int l=0; l<students; l++){
                    expr+=z[i][l][k];
                }

            }
	    model.add(expr<=instance->getCB());
		expr.clear();
        }

        for (int l = 0; l<students; l++){
            IloExpr expr1(env);
            for(int i=0; i<stations; i++){
                for (int k=0; k<bus; k++){
                    expr1+=z[i][l][k];
                }
            }
            model.add(expr1<=1);
			expr1.clear();
        }

        for (int i = 0; i<stations; i++){
            for(int l=0; l<students; l++){
                IloExpr expr2(env);
                for (int k=0; k<bus; k++){
                    expr2+=z[i][l][k];
                }
                model.add(expr2<= instance->getSil(i,l));
				expr2.clear();
            }

        }
        for (int i = 0; i<stations; i++){
            for(int l=0; l<students; l++){
                for (int k=0; k<bus; k++){
                    model.add(z[i][l][k]<= ind->getY()[i][k]);
                }
            }
        }
       
        obj1.clear();
        IloCplex cplex(model);
        cplex.setOut(env.getNullStream());
		//cplex.exportModel("modelo.lp");
        cplex.solve();
        //cout<<" Status: "<< cplex.getStatus()<<endl;
        //cout<<" Custo Soluçao:"<< cplex.getObjValue()<<endl;
        for (int i =0; i<instance->getNStations(); i++){
            for(int l= 0; l <instance->getNStudents(); l++){
                for (int k=0;k<instance->getKBus(); k++){
                    ind->getZ()[i][l][k] = int(cplex.getValue(z[i][l][k]));
                    //cout<<i<<"-"<<l<<"-"<<k<<": "<<cplex.getValue(z[i][l][k])<<endl;
                }
            }
        }
        ind->setFitnessLVL2(float(cplex.getObjValue()));
//        cout<<"Função Objetivo: "<<cplex.getObjValue()<<endl;
//        cout<<"Função Objetivo Cast: "<<float(cplex.getObjValue())<<endl;
		env.end();

    } catch (IloException& e) {
        cerr << "Concert exception caught: " << e << endl;
     }
     catch (...) {
        cerr << "Unknown exception caught" << endl;
     }

}
