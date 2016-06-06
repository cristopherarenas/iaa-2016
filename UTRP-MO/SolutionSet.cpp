#include "SolutionSet.h"


SolutionSet::SolutionSet(void){
	
}

SolutionSet::~SolutionSet(){
}

SolutionSet::SolutionSet(int size){
	vector<Solution> sol;
	sol.reserve(size);
	this->solutions=sol;
}

SolutionSet::SolutionSet(Problem &p, vector<RouteInfo> &ri,int &pop_size) 
{
	vector<Solution> sol;
	sol.reserve(p.get_size());
	this->solutions=sol;
	
	bool sol_conexa = false;
	//generar conjunto de rutas factible	
	for(int i=0;i<pop_size;i++){
		do{
			//cout << "intentando generar solucion";
			Solution *s = new Solution(p,ri);
			sol_conexa = s->check_connectivity(p.get_size()) && s->check_feasability();
			//cout << s->check_connectivity(p.get_size()) << " " << s->check_feasability() << endl;
			if(sol_conexa){
				this->solutions.push_back(*s);
				//cout << "es conexa" << endl;
			}
			delete s;
		}while(!sol_conexa);	
		cout << "solution " << (i+1) << endl;
	}
	
}

vector<Solution> SolutionSet::get_solution_ranking(int rank){
	vector<Solution> result;
	result.reserve(this->solutions.size());
	
	for(int i=0;i<this->solutions.size();i++){
		if(this->solutions[i].ranking_pareto == rank){
			result.push_back(this->solutions[i]);
		}
	}
	return result;
	
}


bool SolutionSet::print_solution_set(){
	std::string filename;
	filename = "Results/Pareto.txt";
	std::ofstream paret(filename.c_str());

	for (std::vector<Solution>::iterator it =  this->solutions.begin(); it!= this->solutions.end(); ++it)
	{
		paret << it->fo1;
		paret << "\t";
		paret << it->fo2;
		paret << std::endl;
    }
    paret.close();
};
