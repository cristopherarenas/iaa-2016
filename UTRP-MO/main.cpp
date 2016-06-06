#include <iostream>
#include <vector>

#include <getopt.h>
#include <cstdlib>
#include <ctime>

#include "common.h"
#include "DataHandler.h"
#include "Problem.h"
#include "Solution.h"
#include "BusStop.h"
#include "Route.h"
#include "RouteInfo.h"
#include "ShortestRoute.h"
#include "SolutionSet.h"
#include "Utils.h"
#include "inmune.h"
#include "opciones.h"

#define POP_SIZE 50
#define ALPHA 0.4
#define BETA 0.6
#define CLON_SIZE 75
#define PROBMUTACION 0.1
#define AFINIDAD 1
#define GENERACIONES 10
#define CLONES 0.5
#define REEMPLAZO 0.3


using namespace std;

void intro(void)
{
	std::string s = 	"____ __________________________________  _____   ________   		\n"
						"|    |   \\__    ___/\\______   \\______   \\/     \\  \\_____  \\ \n"
						"|    |   / |    |    |       _/|     ___/  \\ /  \\  /   |   \\ 	\n"
						"|    |  /  |    |    |    |   \\|    |  /    Y    \\/    |    \\	\n"
						"|______/   |____|    |____|_  /|____|  \\____|__  /\\_______  /	\n"
						"                            \\/                 \\/         \\/ 	\n";

	s += ">>> UTRP Multi Objective C++ Approach by UTFSM Students :D <<< ";
	std::cout << s << std::endl;
}

void usage(void)
{
	std::string s = 	"Usage: ./utrpmo -i INSTANCE_PREFIX -s SEED -r ROUTE_INFO -p POP_SIZE -c CLON_SIZE -g GENERACIONES -a PORC_CLONES -b PORC_REEMPLAZO -f ALPHA\n"
						"For example: ./utrpmo -i instances/Mandl -s 12345 -r \"10:2:7;12:3:8\" \n";

	std::cout << s << std::endl;
}

int main(int argc, char **argv)
{
	//srand(time(NULL));
	time_t inicio;
	time_t fin;
	time_t fin_sol;
	double segundos;
	time(&inicio);
	
	intro();

	int size;
    char c;

    int opt_seed = -1;
    std::string opt_route_type;
    std::string opt_instance_prefix;
    std::vector<RouteInfo> routes_info;
	int popsize = 0;
	int clonsize = 0;
	int iteraciones = 0;
	int porc_clones = 0;
	int porc_reemplazo = 0;
	int afinidad = 0;
	int p_fo = 0;
	
    while ((c = getopt(argc, argv, "i:s:r:p:c:g:a:b:d:f:")) != -1)
    switch (c)
    {
    	case 'i':
    		opt_instance_prefix = optarg;
    		break;
	    case 's':
	        opt_seed = atoi(optarg);
	        break;
   	    case 'r':
   	    {
	        opt_route_type = optarg;
			std::vector<std::string> x = split(opt_route_type, ';');
			for (int i = 0; i < x.size(); ++i)
			{
				std::vector<std::string> y = split(x[i], ':');
				RouteInfo rt (i,atoi(y[0].c_str()), atoi(y[1].c_str()), atoi(y[2].c_str()));
				routes_info.push_back(rt);
			}
	        break;
	    }
	    case 'p':
			popsize = atoi(optarg);
			break;
	    case 'c':
			clonsize = atoi(optarg);
			break;
	    case 'g':
			iteraciones = atoi(optarg);
			break;
	    case 'a':
			porc_clones = atoi(optarg);
			break;
	    case 'b':
			porc_reemplazo = atoi(optarg);
			break;
		case 'd':
			afinidad = atoi(optarg);
			break;
		case 'f':
			p_fo = atoi(optarg);
			break;
	    case '?':
	        if (optopt == 's' || optopt == 'r' || optopt == 'i')
            	fprintf (stderr, "Option -%c requires an argument.\n", optopt);
	        else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
	        else
                fprintf (stderr,
		                "Unknown option character `\\x%x'.\n",
                        optopt);
            usage();
	        return 1;
	    default:
                usage();
	            abort();
    }

    if (opt_seed == -1)
    {
            fprintf (stderr, "You need to specify option `-s'.\n");
            usage();
            return 1;
    }
    if (opt_route_type.empty())
    {
            fprintf (stderr, "You need to specify option `-r'.\n");
            usage();
            return 1;
    }
    if (opt_instance_prefix.empty())
    {
            fprintf (stderr, "You need to specify option `-i'.\n");
            usage();
            return 1;
    }

    std::cout << "The passed parameters are:" << std::endl;
    for (int i = 0; i < routes_info.size(); ++i)
    {
    	std::cout << "\t" << routes_info[i].tipo_ruta <<  ":";
		std::cout << routes_info[i].quantity << ":" << routes_info[i].min_length << ":" << routes_info[i].max_length << std::endl;
    }
	


	// PARSE DATA
	DataHandler *dh = new DataHandler();

	std::vector<coordinate_t> coords;
	std::string ip = opt_instance_prefix;
	if (dh->read_coords(ip + "Coords.txt", coords) == -1) abort();
	int **demand;
	if (dh->read_demand(ip + "Demand.txt", demand, size) == -1) abort();
	int **travel_times;
	if (dh->read_travel_times(ip + "TravelTimes.txt", travel_times, size) == -1) abort();


	
	std::vector<BusStop> bus_stops;
	// Initialize BusStops
	int i=0;
	for (std::vector<coordinate_t>::iterator it =  coords.begin(); it!= coords.end(); ++it)
	{
		bus_stops.push_back(BusStop(i, it->x, it->y));
		i++;
    }

	// Initialize problem
	Problem *p = new Problem();
	p->set_name(opt_instance_prefix);
	p->set_size(size);
	p->set_demand(demand);
	p->set_travel_times(travel_times);
	p->set_bus_stops(bus_stops);	

	// Show parsed data (optional)
	/*if (DEBUG)
	/{
		p->show_bus_stops();
		std::cout << "..." << std::endl;
		p->show_demand();
		std::cout << "..." << std::endl;
		p->show_travel_times();	
	}
	*/	
	//parametros del algoritmo
	Opciones* o = new Opciones();
	
	o->set_popsize(popsize);
	o->set_alpha((p_fo)/100.0);
	o->set_beta((100-p_fo)/100.0);
	o->set_clonsize(clonsize);
	o->set_probmutacion(0.1);
	o->set_afinidad(afinidad/100.0);
	o->set_generaciones(iteraciones);
	o->set_porcentajeclones(porc_clones/100.0);
	o->set_porcentajereemplazo(porc_reemplazo/100.0);
	o->set_size(size);

	ShortestRoute *sr = new ShortestRoute(size);
	sr->calcDistNoRoutes(travel_times);
	
	//se le entrega la semmilla al random
	srand(opt_seed);
	

	
	//inicializacion del algoritmo
	Inmune *algoritmo = new Inmune(*p,*o,routes_info,*sr);
	time(&fin_sol);

	int generacion = 1;
	
	vector<float> hiper;
	hiper.reserve(algoritmo->generaciones);
	
	while(generacion <= algoritmo->generaciones){
		cout << "generacion " << generacion << endl;
		//eliminar soluciones dominadas
		//cout << "eliminar soluciones dominadas" << endl;
		algoritmo->eliminar_dominados(algoritmo->ss.solutions);
			
		//seleccionar mejores soluciones
		//cout << "seleccionar mejores anticuerpos" << endl;
		algoritmo->seleccionar_mejores_anticuerpos();
				
		//cout << "clonar anticuerpos"  << endl;
		algoritmo->clonar_anticuerpos();
		
		algoritmo->mutar_clones(*p,routes_info,sr);
		algoritmo->actualizar_dominancia(algoritmo->clon.solutions);
		
		//copiar todos los clones al conjunto de poblacion 
		algoritmo->clones_a_poblacion();
		
		//copiar un porcentaje de mejores clones al conjunto de memoria
		algoritmo->guardar_mejores_clones();
		//algoritmo->actualizar_dominancia(algoritmo->memory.solutions);
		algoritmo->eliminar_dominados(algoritmo->memory.solutions);
				
		//reemplazar las peores soluciones de la poblacion con soluciones aleatorias
		algoritmo->reemplazar_peores_soluciones(*p, routes_info,*sr);
			
		//se guardan los optimos de pareto para las generaciones multiplos de 500
		
		if(generacion%500==0){
		
			stringstream sstr,sstr7;
			sstr << "results/" << opt_seed << "_pareto_" << generacion << "_alpha_" << p_fo << "_beta_" << (100-p_fo) << "_af_" << afinidad << "_cl_" << porc_clones << "_re_" << porc_reemplazo << ".txt";
			sstr7 << "results/" << opt_seed << "_pareto2_" << generacion << "_alpha_" << p_fo << "_beta_" << (100-p_fo) << "_af_" << afinidad << "_cl_" << porc_clones << "_re_" << porc_reemplazo << ".txt";
			string nombre = sstr.str();
			string nombre7 = sstr7.str();
			ofstream archivo(nombre.c_str());
			ofstream archivo7(nombre7.c_str());
			for(int k=0;k<algoritmo->memory.solutions.size();k++)
			{
				archivo << algoritmo->memory.solutions[k].fo1 << " " << algoritmo->memory.solutions[k].fo2 << " " << algoritmo->memory.solutions[k].quality << endl;
				archivo7 << algoritmo->memory.solutions[k].fo1 << " " << algoritmo->memory.solutions[k].fo2 << " " << algoritmo->memory.solutions[k].quality << endl;
				
				for (int i = 0; i < algoritmo->memory.solutions[k].routes.size() ; i++){
					
					for( int j = 0; j < algoritmo->memory.solutions[k].routes[i].bus_stops.size(); j++){
						archivo << algoritmo->memory.solutions[k].routes[i].bus_stops[j].idi+1;
						
						if(j < algoritmo->memory.solutions[k].routes[i].bus_stops.size()-1){
							archivo << ", ";
						}
					}
					archivo << endl;
				}  
								
			}
			archivo.close();
			archivo7.close();
			
			//se guardan los optimos de pareto para la generacion
			stringstream sstr2;
			sstr2 << "results/" << opt_seed << "_solucion_" << generacion << "_alpha_" << p_fo << "_beta_" << (100-p_fo) << "_af_" << afinidad << "_cl_" << porc_clones << "_re_" << porc_reemplazo << ".txt";
			nombre = sstr2.str();
			
			ofstream archivo2(nombre.c_str());
			
			for(int i=0;i<algoritmo->ss.solutions.size();i++)
			{
				archivo2 << algoritmo->ss.solutions[i].fo1 << " " << algoritmo->ss.solutions[i].fo2 << " " << algoritmo->ss.solutions[i].quality << endl;
					
			}
			archivo2.close();

			//se guardan los optimos de pareto para la generacion
			stringstream sstr3;
			sstr3 << "results/" << opt_seed << "_clones_" << generacion << "_alpha_" << p_fo << "_beta_" << (100-p_fo) << "_af_" << afinidad << "_cl_" << porc_clones << "_re_" << porc_reemplazo << ".txt";
			nombre = sstr3.str();
			
			ofstream archivo3(nombre.c_str());
			
			for(int i=0;i<algoritmo->clon.solutions.size();i++)
			{
				archivo3 << algoritmo->clon.solutions[i].fo1 << " " << algoritmo->clon.solutions[i].fo2 << " " << algoritmo->clon.solutions[i].quality << endl;
					
			}
			archivo3.close();
			
		}		
		
		//se calcula el hipervolumen para la generacion actual
		SolutionSet* sset = new SolutionSet(size);
		sset->solutions = algoritmo->memory.solutions;
		
		for(int i=0;i<algoritmo->memory.solutions.size();i++){
			sset->solutions.push_back(algoritmo->memory.solutions[i]);
		}
		
		float hypervolume = hv(sset, p);
		cout << "hypervolumen: " << hypervolume << endl;	
		hiper.push_back(hypervolume);
		delete sset;
		//siguiente generacion
		generacion++;
	}
	
	//guardar hipervolumen
	stringstream sstr4;
	sstr4 << "results/" << opt_seed << "_hypervolumen" << "_alpha_" << p_fo << "_beta_" << (100-p_fo) << "_af_" << afinidad << "_cl_" << porc_clones << "_re_" << porc_reemplazo << ".txt";
	string nombre = sstr4.str();
	
	ofstream archivo4(nombre.c_str());
	
	for(int i=0;i<hiper.size();i++)
	{
		archivo4 << hiper[i] << endl;
			
	}
	archivo4.close();
	
	//guardar hipervolumen
	stringstream sstr6;
	sstr6 << "results/hypervolumen" << "_alpha_" << p_fo << "_beta_" << (100-p_fo) << ".txt";
	nombre = sstr6.str();
	
	ofstream archivo6(nombre.c_str(), ios::out | ios::app);
	
	archivo6 << opt_seed << ": af:" << afinidad << " cl:" << porc_clones << " re:" << porc_reemplazo << " " << hiper[hiper.size()-1] << endl;
	
	archivo6.close();
	
	delete p;
	delete sr;
	
	// De-Allocate memory to prevent memory leak
	for (int i = 0; i < size; ++i)
	{
		delete [] demand[i];
		delete [] travel_times[i];
	}
	delete [] demand;
	delete [] travel_times;
	

	stringstream sstr5;
	sstr5 << "results/" << opt_seed << "_time" << "_alpha_" << p_fo << "_beta_" << (100-p_fo) << "_af_" << afinidad << "_cl_" << porc_clones << "_re_" << porc_reemplazo << ".txt";
	string nombre5 = sstr5.str();
	ofstream archivo5(nombre5.c_str());
	
	segundos = difftime(fin_sol,inicio);
	archivo5 << "Generar soluciones factibles iniciales: " << segundos << " segundos" << endl;
	time(&fin);
	segundos = difftime(fin,fin_sol);
	
	archivo5 << "Iteraciones: " << segundos << " segundos" << endl;
	
	segundos = difftime(fin,inicio);
	archivo5 << "Total: " << segundos << " segundos" << endl;
	archivo5.close();
	
	return 0;
}
