#ifndef INMUNE_H
#define INMUNE_H

#include "Solution.h"
#include "SolutionSet.h"
#include "Route.h"
#include "RouteInfo.h"
#include "ShortestRoute.h"
#include "opciones.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <set>

using namespace std;

class Inmune{
	public:
		Inmune();
		Inmune(Problem &p,Opciones &o,vector<RouteInfo> &routes_info,ShortestRoute &sr);
		~Inmune();
		void print_solutions();
		void print_clones();
		void print_memory();
		void print_solutions(vector<Solution> &s);
		void eliminar_dominados(vector<Solution> &poblacion);
		void actualizar_dominancia(vector<Solution> &poblacion);
		
		void seleccionar_mejores_anticuerpos();
		vector<float> ordenar_afinidad(vector<Solution> &s);
		int get_index_solucion(float valor,vector<Solution> clones);
		
		void clonar_anticuerpos();
		void mutar_clones(Problem &p, vector<RouteInfo> &routes_info, ShortestRoute* &sr);
		void clones_a_poblacion();
		void guardar_mejores_clones();
		void reemplazar_peores_soluciones(Problem &p, vector<RouteInfo> &ri,ShortestRoute &sr);
		
		int pop_size;
		int clon_size;
		int generaciones;
		int prob_mutacion;
		
		float alpha;
		float beta;
		float p_clones;
		float p_reemplazo;
		float p_afinidad_clones;
		
		SolutionSet ss;
		SolutionSet clon;
		SolutionSet memory;
	
};
#endif