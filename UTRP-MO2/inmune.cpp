#include "inmune.h"

using namespace std;

Inmune::Inmune(){
	
}

Inmune::Inmune(Problem &p,Opciones &o,vector<RouteInfo> &routes_info,ShortestRoute &sr){
		this->pop_size = o.get_popsize();
		this->clon_size = o.get_clonsize();
		this->generaciones = o.get_generaciones();
		this->prob_mutacion = o.get_probmutacion();
		
		
		this->alpha = o.get_alpha(); 
		this->beta = o.get_beta();
		this->p_afinidad_clones = o.get_afinidad();
		this->p_clones = o.get_porcentajeclones();
		this->p_reemplazo = o.get_porcentajereemplazo();
		
		if(this->alpha>1){
			int random_number = 100*rand()%11;
			if(random_number<0){
				random_number = random_number*-1;
			}
			int a = random_number*10;
			int b = 100-random_number*10;
			this->alpha = a/100.0;
			this->beta = b/100.0;
			cout << "iniciando con alpha=" << this->alpha << " beta=" << this->beta << endl;
		}
		
		//obtencion de conjuto de soluciones factible
		//this->ss = SolutionSet(p, routes_info,this->pop_size);
		this->ss = SolutionSet(p, routes_info,this->pop_size,sr,this->alpha,this->beta);
		
		/*
		int** demand = p.get_demand();
		int** travel = p.get_travel_times();
		int size = p.get_size();
		

		
		//calculo de fo
		for(int i=0;i<this->ss.solutions.size();i++){
			this->ss.solutions[i].setFO1(sr,demand);
			this->ss.solutions[i].setFO2(size,travel);
			this->ss.solutions[i].setQuality(this->alpha,this->beta);
			//cout << "fo2 " << this->ss.solutions[i].fo2 << " fo1 " << this->ss.solutions[i].fo1 << " apt " << this->ss.solutions[i].quality << endl; 
		}
		*/
		int clon_size = o.get_clonsize();
		
		this->clon = SolutionSet(clon_size);
		this->memory = SolutionSet(clon_size);
};

Inmune::~Inmune(){

};

void Inmune::print_solutions(){
	for(int i=0;i<this->ss.solutions.size();i++){
		cout << "r " << ss.solutions[i].ranking_pareto << ": fo2 " << this->ss.solutions[i].fo2 << " fo1 " << this->ss.solutions[i].fo1 << " apt " << this->ss.solutions[i].quality << endl; 
	}
}

void Inmune::print_clones(){
	for(int i=0;i<this->clon.solutions.size();i++){
		cout << "r " << clon.solutions[i].ranking_pareto << ": fo2 " << this->clon.solutions[i].fo2 << " fo1 " << this->clon.solutions[i].fo1 << " apt " << this->clon.solutions[i].quality << endl; 
	}
}

void Inmune::print_memory(){
	for(int i=0;i<this->memory.solutions.size();i++){
		cout << "r " << memory.solutions[i].ranking_pareto << ": fo2 " << this->memory.solutions[i].fo2 << " fo1 " << this->memory.solutions[i].fo1 << " apt " << this->memory.solutions[i].quality << endl; 
	}
}

void Inmune::print_solutions(vector<Solution> &s){
	for(int i=0;i<s.size();i++){
		cout << "r " << s[i].ranking_pareto << ": fo2 " << s[i].fo2 << " fo1 " << s[i].fo1 << " apt " << s[i].quality << endl; 
	}
}

void Inmune::eliminar_dominados(vector<Solution> &poblacion)
{
	int size = poblacion.size();
	//revisar si son dominados con respecto a otras soluciones
	for(int i=0;i<poblacion.size();i++)
	{
		poblacion[i].set_dominated(poblacion);
	}
	
	//se eliminan las soluciones dominadas
	for(int i=size-1;i>=0;i--)
	{
		//eliminacion desde el final del vector hasta el principio
		if(poblacion[i].dominated)
		{
			poblacion.erase(poblacion.begin()+i);
		}
	}
}

void Inmune::actualizar_dominancia(vector<Solution> &poblacion)
{
	int size = poblacion.size();
	//revisar si son dominados con respecto a otras soluciones
	for(int i=0;i<poblacion.size();i++)
	{
		poblacion[i].set_dominated(poblacion);
	}
}

void Inmune::seleccionar_mejores_anticuerpos()
{	
	//se elige un porcentaje de los mejores individuos
	int seleccion = (this->ss.solutions.size()*this->p_afinidad_clones + 0.5f);
	this->clon.solutions.clear();
	this->clon.solutions.reserve(seleccion);
	vector<float> afinidades = ordenar_afinidad(this->ss.solutions);
	
	for(int i=0;i<seleccion;i++)
	{
		int index = get_index_solucion(afinidades[i],this->ss.solutions);
		if(index!=-1){
			this->clon.solutions.push_back(this->ss.solutions[index]);
		}
	}
}

vector<float> Inmune::ordenar_afinidad(vector<Solution> &s)
{
	set<float> afinidades_unicas;
	vector<float> afinidades;
	for(int i=0;i<s.size();i++)
	{
		afinidades_unicas.insert(s[i].quality);
	}
	
	for(set<float>::iterator it=afinidades_unicas.begin();it!=afinidades_unicas.end();it++){
		afinidades.push_back(*it);
	}
	
	
	return afinidades;
}

int Inmune::cantidad_mutaciones(float valor, float menor_x, float mayor_x, int menor_y, int mayor_y){
	float result = menor_y+((mayor_y-menor_y)/(mayor_x-menor_x))*(valor-menor_x);
	return (int)(result+0.5f);
}

int Inmune::get_index_solucion(float valor,vector<Solution> clones)
{
	int index = -1;
	for(int i=0;i<clones.size();i++)
	{
		if(clones[i].quality==valor)
		{
			index = i;
		}
	}
	return index;
}

void Inmune::clonar_anticuerpos()
{
	int random;
	int size = this->clon.solutions.size();
	for(int i=0;i<this->clon_size-size;i++)
	{
		random = rand()%size;
		//cout << "i " << i << " random " << random << endl;
		this->clon.solutions.push_back(this->clon.solutions[random]);
	}
	
}

void Inmune::mutar_clones(Problem &p, vector<RouteInfo> &routes_info, ShortestRoute* &sr){
	int** demand = p.get_demand();
	int** travel_times = p.get_travel_times();
	vector<BusStop> bus_stops = p.get_bus_stops();
	int size = p.get_size();
	vector<float> afinidades = ordenar_afinidad(this->clon.solutions);
	float lbfo1 = p.get_lbfo1();
	float lbfo2 = p.get_lbfo2();
	
	
	for(int i=0;i<this->clon.solutions.size();i++){
		//cout << "solution " << i << endl;
		
		int cant = cantidad_mutaciones(this->clon.solutions[i].quality,afinidades[0],afinidades[afinidades.size()-1],1,this->clon.solutions[i].routes.size());
		for(int j=0;j<cant;j++){
			if(this->clon.solutions[i].mutation(routes_info,travel_times,size,bus_stops)){
				//cout << "fo1 " << this->clon.solutions[i].fo1 << " fo2 " << this->clon.solutions[i].fo2 << " apt " << this->clon.solutions[i].quality << endl;
				this->clon.solutions[i].setFO1(*sr,demand);
				this->clon.solutions[i].setFO2(size,travel_times);
				//this->clon.solutions[i].setQuality(this->alpha,this->beta);
				this->clon.solutions[i].setQuality(this->alpha,this->beta,lbfo1,lbfo2);
				//cout << "fo1 " << this->clon.solutions[i].fo1 << " fo2 " << this->clon.solutions[i].fo2 << " apt " << this->clon.solutions[i].quality << endl;
			}
			else{
				cout << i << " false" << endl;
			}		
		}
	}
}

void Inmune::clones_a_poblacion(){
	//cout << "Clones a poblacion" << endl;
	//cout << "Poblacion size " << this->ss.solutions.size() <<  endl;
	
	//obtener un conjunto con todos los rankings de pareto
	set<int> rankings;
	for(int i=0;i<this->clon.solutions.size();i++){
		rankings.insert(this->clon.solutions[i].ranking_pareto);
	}
	
	vector<int> rankings_p;
	for (set<int>::iterator it=rankings.begin(); it!=rankings.end();it++){
		//cout << "ranking pareto " << *it << endl;
		vector<Solution> s = this->clon.get_solution_ranking(*it);
		for(int j=0;j<s.size();j++){
			this->ss.solutions.push_back(s[j]);
		}
		s.clear();
		//cout << "Poblacion size " << this->ss.solutions.size() <<  endl;
		if(this->ss.solutions.size() > this->pop_size){
			break;
			//cout << "break" << endl;
		}
	}
}

bool Inmune::find_solution(Solution &s,vector<Solution> &sols){
	for(int i=0;i<sols.size();i++){
		if(s.fo1 == sols[i].fo1 && s.fo2==sols[i].fo2 && s.quality == sols[i].quality){
			return true;
		}
	}
	return false;
}

void Inmune::guardar_mejores_clones(){
	//cout << "Guardar mejores clones" << endl;
	
	int seleccion = (this->clon_size*this->p_clones + 0.5f);
	//obtener soluciones dominadas
	vector<Solution> mejores = this->clon.get_solution_ranking(1);
	
	/*
	for(int i=0;i<mejores.size();i++){
		cout << "mejor i fo1 " << mejores[i].fo2 << " fo1 " << mejores[i].fo1 << " apt " << mejores[i].quality << endl;
	}
	
	cout << "Mejores size " << mejores.size() << endl;
	*/
	//print_solutions(mejores);
	
	int counter = 0;
	int i = 0;
	vector<float> afinidades = ordenar_afinidad(mejores);
	
	/*
	for(int i=0;i<afinidades.size();i++){
		cout << "afinidad i " << i << " " << afinidades[i] << endl;
	}
	*/
	
	while(counter < seleccion && i<afinidades.size()){
		int index = get_index_solucion(afinidades[i],mejores);
		//buscar si solucion ya esta en conjunto de memoria
		
		if(index!=-1){
			if(!find_solution(mejores[index],this->memory.solutions)){
				this->memory.solutions.push_back(mejores[index]);
			}
			counter++;
		}
		i++;
	}
	mejores.clear();
	
	//cout << "memoria size " <<  this->memory.solutions.size() << endl;
}

void Inmune::reemplazar_peores_soluciones(Problem &p, vector<RouteInfo> &ri, ShortestRoute &sr){
	//cout << "Reemplazar peores soluciones" << endl;
	//cout << "obtener mejores afinidades de poblacion" << endl;
	
	//variable temporal para guardar mejores soluciones
	vector<Solution> mejores;
	mejores.reserve(this->pop_size);
	
	//obtener las mejores afinidades
	vector<float> afinidades = ordenar_afinidad(this->ss.solutions);
	int seleccion = (this->pop_size*(1-this->p_reemplazo) + 0.5f);
	int counter = 0;
	int i = 0;
	while(counter < seleccion && i < afinidades.size()){
		int index = get_index_solucion(afinidades[i],this->ss.solutions);
		if(index!=-1){
			mejores.push_back(this->ss.solutions[index]);
			counter++;
		}
		i++;
	}
	
	//cout << "mejores size " << mejores.size() << endl;
	this->ss.solutions.clear();
	this->ss.solutions = mejores;
	mejores.clear();
	
	//cout << "poblacion size " << this->ss.solutions.size() << endl;
	//cout << "Agregar soluciones aleatorias" << endl;
	
	//generar soluciones aleatorias para agregar a la poblacion
	int** demand = p.get_demand();
	int** travel = p.get_travel_times();
	int size = p.get_size();
	
	int cant_reemplazo = this->pop_size*this->p_reemplazo;
	bool sol_conexa = false;
	for(int i=0;i<cant_reemplazo;i++){
		do{
			//Solution *s = new Solution(p,ri);
			Solution *s = new Solution(p,ri,sr,this->alpha,this->beta);
			sol_conexa = s->check_connectivity(p.get_size()) && s->check_feasability();
			if(sol_conexa){
				//s->setFO1(sr,demand);
				//s->setFO2(size,travel);
				//s->setQuality(this->alpha,this->beta);
				this->ss.solutions.push_back(*s);
				//cout << "sol aleatoria " << i << ": " << s->fo1 << " " << s->fo2 << " " << s->quality << endl;
			}
			delete s;
		}while(!sol_conexa);
	}
	//cout << "poblacion size " << this->ss.solutions.size() << endl;
	
}

void Inmune::cambiar_alpha_beta(){
	int random_number = 100*rand()%11;
	if(random_number<0){
		random_number = random_number*-1;
	}
	int a = random_number*10;
	int b = 100-random_number*10;
	this->alpha = a/100.0;
	this->beta = b/100.0;
	cout << "cambio, alpha=" << this->alpha << " beta=" << this->beta << endl;
}
