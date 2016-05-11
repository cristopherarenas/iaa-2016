#include "Route.h"

using namespace std;

Route::Route(void) {};

Route::Route(Problem &p, RouteInfo &ri, vector<bool> &check_bus){
	this->tipo_ruta = ri.tipo_ruta;
	int longitud = ri.min_length+rand()%(ri.max_length-ri.min_length);
	this->bus_stops.reserve(longitud);
	int random_bs = rand()%(p.get_bus_stops().size());
	
	
	vector<int> neighbors;
	int counter_bus = 0; 
	
	
	for(int i=0;i<longitud;i++){
		this->bus_stops.push_back(p.get_bus_stops()[random_bs]);
		check_bus[random_bs] = true;
		counter_bus++;
		for(int j=0;j<p.get_size();j++){
			if (!check_bus[j] && p.get_travel_times()[random_bs][j]>0){
				neighbors.push_back(j);
			}
			
		}
		if(neighbors.size()>0){
			random_bs = neighbors[rand()%(neighbors.size())];
			neighbors.clear();
		}
		else{
			for(int j=0;j<p.get_size();j++){
				if (p.get_travel_times()[random_bs][j]>0){
					neighbors.push_back(j);
				}
			}
			random_bs = neighbors[rand()%(neighbors.size())];
			neighbors.clear();
		}
	}
}

void Route::define_bus_type(int tipo) 
{
	this->tipo_ruta = tipo;
}

void Route::set_bus_stops(std::vector<BusStop> &bus_stops)
{
	this->bus_stops = bus_stops;
}

void Route::add_bus_stops(std::vector<BusStop> &bus_stops){
	
	for(int i = 0;i < bus_stops.size(); i++){
		this->bus_stops.push_back(bus_stops[i]);
		}
	} 

void Route::add_distinct_bus_stops(std::vector<BusStop>& bus_stops){

	int flag = 0;
	for (int i = 0; i < bus_stops.size();i++){
		flag = 0;
		for(int j = 0;j<this->bus_stops.size();j++){
			if(this->bus_stops[j] == bus_stops[i]){
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			this->bus_stops.push_back(bus_stops[i]);
		}
	}
}

void Route::print_route(){
	for( int i = 0; i < this->bus_stops.size(); i++){
		std::cout << this->bus_stops[i].idi+1;
		if(i < this->bus_stops.size()-1){
			std::cout << ", ";
			}
		}
		std::cout << std::endl;
	}
	
bool Route::check_cycles_and_backtracks()
{
	for (int i = 0; i < this->bus_stops.size()-1; ++i)
	{
		//std::cout << this->bus_stops[i].id << std::endl;
		//std::cout << "	vs" << std::endl;
		for (int j = i+1; j < this->bus_stops.size(); ++j)
		{
			//std::cout << this->bus_stops[j].id << std::endl;
			if (this->bus_stops[i] == this->bus_stops[j])
				return true;
		}
	}
    return false;
};


bool Route::check_edge(int id_a, int id_b){
    for(std::vector<BusStop>::iterator it = bus_stops.begin() ; it != bus_stops.end() - 1 ; ++it   ){
        if( (*it).idi == id_a && (*(it+1)).idi == id_b ){
            return true;
        }

        if( (*it).idi == id_b && (*(it+1)).idi == id_a ){
            return true;
        }
    }
    return false;
}

bool Route::find_node(int id_a){
    for(std::vector<BusStop>::iterator it = bus_stops.begin() ; it != bus_stops.end()  ; ++it   ){
        if( (*it).idi == id_a){
            return true;
        }
    }
    return false;
}

bool Route::find_nodes(int id_a, int id_b){
    return find_node(id_a) && find_node(id_b);
}

