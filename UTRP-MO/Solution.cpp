#include "Solution.h"
#include "Route.h"
#include "ShortestRoute.h"

Solution::Solution(void) 
{
	this->dominated = false;
	this->ranking_pareto = 1;
}

Solution::Solution(Problem &p, vector<RouteInfo> &routes_info)
{
	//crear nueva solucion factible
	this->dominated = false;
	this->ranking_pareto = 1;
	
	vector<bool> check_bus;
	check_bus.reserve(p.get_bus_stops().size());
	for(int i=0;i<p.get_bus_stops().size();i++){
		check_bus.push_back(false);
	}
		
	for(int i=0;i<routes_info.size();i++){
		for(int j=0;j<routes_info[i].quantity;j++){
			//crear rutas entre una longitud minima y maxima
			Route r = Route(p,routes_info[i],check_bus);
			this->routes.push_back(r);
		}
	}
	
}

Solution::~Solution()
{
	
}

void Solution::set_routes(std::vector<Route> &routes)
{
	this->routes = routes;
}

//Calcula alterando el valor de fo1 y fo2
void Solution::setQuality(float alpha, float beta)
{
	float aptitud;
	aptitud = alpha*this->fo1+beta*this->fo2;
	this->quality=aptitud;
}
         
bool Solution::check_feasability(){
	bool check = true;
	for(int i=0;i<this->routes.size();i++){
		check = check && !this->routes[i].check_cycles_and_backtracks();
	}
	return check;
	
};

float Solution::setFO1(ShortestRoute &sr, int** &demand){
    float numerador=0.0;
    float denominador=0.0;
    float transferencias=0.0;

    for (int i = 0; i < (sr.getSize()-1); i++)
    {
        for (int j = i+1; j < sr.getSize(); j++)
	{
		//std::cout<<"Transferencias ("<<i+1<<","<<j+1<<"):"<< sr->getTransfers(i,j,this->routes)<<std::endl;
		//getchar();
                numerador+=demand[i][j]*(sr.distance(i,j) + 5*sr.getTransfers(i,j,this->routes));
                denominador+=demand[i][j];

        }
    }    
    //std::cout << "\nFO:" << numerador/denominador << "\n";
    //cout << "numerador " << numerador << endl;
    //cout << "denominador " << denominador << endl;
    //cout << "division" << numerador/denominador << endl;
    this->fo1 = (numerador/denominador);
    return (numerador/denominador);
    //this->fo1 = (numerador/denominador);
    //return (numerador/denominador);
};

float Solution::setFO2(int &size, int** &travel_times) {
	float time=0.0;
	int it_ruta;
	
	//iteracion sobre todas las rutas
	for(it_ruta=0;it_ruta<this->routes.size();it_ruta++) {
		for(int i=0;i<size;i++) {
			for(int j=i;j<size;j++) {
				if(this->routes[it_ruta].check_edge(i,j)) {
					time+=travel_times[i][j];
					//cout << travel_times[i][j] << "+";
				}
			}
		}
	}
	//cout << endl;

	
	this->fo2=time;
	return time;
}

bool Solution::check_connectivity(int size){

	Route *set = new Route();
	set->set_bus_stops(this->routes[0].bus_stops);
	
	int i, flag = 0, added_sum = 1, added_sum_old = 0;
	int added [this->routes.size()];
	std::fill_n(added,this->routes.size(),0);
	added [0] = 1;
	
	while(added_sum_old < added_sum){
		added_sum_old = added_sum;
		for (i = 1; i < this->routes.size() ; i++){
			//std::cout << "revisando ruta: " << i << std::endl;
			flag = 0;
			if(added[i] == 0){
				for (int j= 0; j < this->routes[i].bus_stops.size();j++){
					for (int k = 0; k < set->bus_stops.size(); k++){
						//std::cout << "comparando paradas " << this->routes[i].bus_stops[j].id << " y " << set->bus_stops[k].id << std::endl;
						if(this->routes[i].bus_stops[j] == set->bus_stops[k]){
							set->add_distinct_bus_stops(this->routes[i].bus_stops);
							added [i] = 1;
							added_sum +=1;
							flag = 1;
							break;
						}
					}
					if(flag == 1){
						break;
					}
				}
			}
		}
	}

	// std::cout << "p->size: " << size << std::endl;
	// std::cout << "set size: " << set->bus_stops.size() << std::endl;
	// std::cout << "Connected Bus Stops: " << std::endl;
	// set->print_route();
	if(size == set->bus_stops.size()){
		return true;
	}

	return false;
};

bool Solution::print_solution_routes(){
	std::string filename;
	filename = "Results/SolutionRoutes.txt";
	std::ofstream sol(filename.c_str());

	for (int i = 0; i < this->routes.size() ; i++){
		for( int j = 0; j < this->routes[i].bus_stops.size(); j++){
			sol << this->routes[i].bus_stops[j].idi+1;
			if(j < this->routes[i].bus_stops.size()-1){
				sol << ", ";
			}
		}
		sol << std::endl;
	}  
  	sol.close();
};

bool Solution::mutation_add_bs(Route &r, int** &travel, int &size, vector<BusStop> &bs){
	//agregar una parada al final
	//r.print_route();
	bool change = false;
	//vector<BusStop> nbs;
	//nbs.reserve(r.bus_stops.size()+1);
	for(int i=0;i<size;i++){
		//la nueva parada de bus seleccioada debe cumplir con dos condiciones:
		//1. No debe pertenecer a la ruta (ciclos)
		//2. Debe tener conexion directa con la ultima parada de la ruta
		if(travel[r.bus_stops[r.bus_stops.size()-1].idi][i]!=-1){
			if(!r.find_node(i)){
				r.bus_stops.push_back(bs[i]);
				//la parada cambia
				//change = true;
				//break;
			}
		}
		if(change){
			break;
		}
	}
	
	return change;
}

bool Solution::mutation_remove_bs(Route &r,int &size){
	r.bus_stops.erase(r.bus_stops.end()-1);
	return check_connectivity(size);
}

bool Solution::mutation_mix_routes(Route &r1, Route &r2, int** &travel){
	cout << "r1 ";
	r1.print_route();
	cout << "r2 ";
	r2.print_route();
	int random_bs = 0;
	if(r1.bus_stops.size() > r2.bus_stops.size()){
		random_bs = rand()%(r2.bus_stops.size()-1);
	}
	else{
		random_bs = rand()%(r1.bus_stops.size()-1);
	}
	
	vector<BusStop> bs1,bs2;
	bs1.reserve(r2.bus_stops.size());
	bs2.reserve(r1.bus_stops.size());
	
	if((travel[r1.bus_stops[random_bs].idi][r2.bus_stops[random_bs].idi+1]=!-1) 
	&& (travel[r2.bus_stops[random_bs].idi][r1.bus_stops[random_bs].idi+1]=!-1)){
		for(int i=0;i<=random_bs;i++){
			bs1.push_back(r1.bus_stops[i]);
			bs2.push_back(r2.bus_stops[i]);
		}
		
		for(int i=random_bs+1;i<r1.bus_stops.size();i++){
			bs2.push_back(r1.bus_stops[i]);
		}
		
		for(int i=random_bs+1;i<r2.bus_stops.size();i++){
			bs1.push_back(r2.bus_stops[i]);
		}
	}
	else{
		return false;
	}
	cout << endl;
	cout << "r1 ";
	r1.print_route();
	cout << "r2 ";
	r2.print_route();
	return r1.check_cycles_and_backtracks() && r2.check_cycles_and_backtracks();	
}

bool Solution::mutation_mix_route(Route &r,int** &travel){
	int end_bs = r.bus_stops.size()-1;
	bool change = false;
	if(travel[r.bus_stops[0].idi][r.bus_stops[end_bs].idi] != -1){
		//cout << "true" << endl;
		vector<BusStop> bs;
		bs.reserve(r.bus_stops.size());
		
		int random_point = 1+rand()%(r.bus_stops.size()-2);
		//cout << "random point " << random_point << endl;
		for(int i=random_point;i<r.bus_stops.size();i++){
			bs.push_back(r.bus_stops[i]);
		}
		for(int i=0;i<random_point;i++){
			bs.push_back(r.bus_stops[i]);
		}
		//cout << "r ";
		//r.print_route();
		
		r.set_bus_stops(bs);
		//cout << "nr ";
		//r.print_route();
		change = true;
	}
	return change;	
}

//add a new bus stop in a random route if possible
/*
bool Solution::mutation(vector<RouteInfo> &info, int** &travel,int &size,vector<BusStop> &bs){
	int route_selected = rand()%this->routes.size();
	bool change = false;
	Route r = this->routes[route_selected];
	//si la ruta seleccionada aleatoriamente tiene el maximo de paraderos permitidos, se borra una parada
	if(this->routes[route_selected].bus_stops.size()>info[this->routes[route_selected].tipo_ruta].min_length){
		//borrar ultima parada
		cout << "ruta" << endl;
		this->routes[route_selected].print_route();
		cout << "ruta size " <<  this->routes[route_selected].bus_stops.size() << endl;
		cout << "borrando parada" << endl;
		this->routes[route_selected].bus_stops.erase(this->routes[route_selected].bus_stops.end()-1);
		this->routes[route_selected].print_route();
		cout << "ruta size " <<  this->routes[route_selected].bus_stops.size() << endl;
		cout << "verificando conectividad " << this->check_connectivity(size) << endl;
		while(!check_connectivity(size)){
			cout << "restaurar ruta" << endl;
			this->routes[route_selected] = r;
			this->routes[route_selected].print_route();
			cout << "ruta size " <<  this->routes[route_selected].bus_stops.size() << endl;
			cout << "escogiendo nueva ruta" << endl;
			route_selected = rand()%this->routes.size();
			r = this->routes[route_selected];
			r.print_route();
			cout << "ruta size " <<  this->routes[route_selected].bus_stops.size() << endl;
			this->routes[route_selected].bus_stops.erase(this->routes[route_selected].bus_stops.end()-1);
			cout << "ruta size " <<  this->routes[route_selected].bus_stops.size() << endl;
			cout << "verificando conectividad " << this->check_connectivity(size) << endl;
		}
		cout << "s" << endl;
		this->routes[route_selected].print_route();
		change = true;
	}
	//en cualquier otro caso se agrega una parada
	else{
		//agregar una parada al final
		//cout << "agregando parada" << endl;
		//int bs_selected = rand()%this->routes[route_selected].bus_stops.size();
		//this->routes[route_selected].print_route();
		//cout << this->routes[route_selected].bus_stops[this->routes[route_selected].bus_stops.size()-1].idi << endl;
		
		for(int i=0;i<size;i++){
			//la nueva parada de bus seleccioada debe cumplir con dos condiciones:
			//1. No debe pertenecer a la ruta (ciclos)
			//2. Debe tener conexion directa con la ultima parada de la ruta
			if(travel[this->routes[route_selected].bus_stops[this->routes[route_selected].bus_stops.size()-1].idi][i]!=-1){
				if(!this->routes[route_selected].find_node(i+1)){
					for(int j=0;j<bs.size();j++){
						if(bs[j].idi == i+1){
							this->routes[route_selected].bus_stops.push_back(bs[j]);
							change = true;
							break;
						}
					}
				}
			}
			if(change){
				break;
			}
			//cout << travel[this->routes[route_selected].bus_stops[this->routes[route_selected].bus_stops.size()-1].idi][i] << " " ;
		}
		//cout << endl;
		
	}
	return change;
	
}*/

bool Solution::mutation(vector<RouteInfo> &info, int** &travel,int &size,vector<BusStop> &bs){
	//int route_selected = rand()%this->routes.size();
	for(int route_selected=0;route_selected<this->routes.size();route_selected++){
		bool change = false;
		Route r = this->routes[route_selected];
		int intentos = 0;
		
		do{
			if(this->routes[route_selected].bus_stops.size()==info[this->routes[route_selected].tipo_ruta].max_length){
				int op_mutacion = (100*rand())%2;
				if(op_mutacion == 0){
					change = mutation_remove_bs(this->routes[route_selected],size);
				}
				else if(op_mutacion == 1){
					change = mutation_mix_route(this->routes[route_selected],travel);
				}
				
				
			}
			else if(this->routes[route_selected].bus_stops.size()==info[this->routes[route_selected].tipo_ruta].min_length){
				int op_mutacion = (100*rand())%2;
				if(op_mutacion == 0){
					change = mutation_add_bs(this->routes[route_selected],travel,size,bs);
				}
				else if(op_mutacion == 1){
					change = mutation_mix_route(this->routes[route_selected],travel);
				}
			}
			else{
				int op_mutacion = (100*rand())%3;
				if(op_mutacion == 0){
					change = mutation_remove_bs(this->routes[route_selected],size);
				}
				else if(op_mutacion == 1){
					change = mutation_add_bs(this->routes[route_selected],travel,size,bs);
				}
				else if (op_mutacion == 2){
					change = mutation_mix_route(this->routes[route_selected],travel);
				}			
			}
			
			if(!change){
				this->routes[route_selected] = r;
				route_selected = rand()%this->routes.size();
				r = this->routes[route_selected];
			}
			intentos++;
			
		}while(intentos <20 && !change);
	}
	return true;
	//cout << "intentos " << intentos << " change " << change << endl;
}

void Solution::set_dominated(vector<Solution> &ss){
	this->dominated=false;
	for(int i=0;i<ss.size();i++)
	{
		if((this->fo1>=ss[i].fo1 && this->fo2>ss[i].fo2)||(this->fo1>ss[i].fo1 && this->fo2>=ss[i].fo2))
		{
			this->dominated =  true;
			this->ranking_pareto++;
		}
	}
}
