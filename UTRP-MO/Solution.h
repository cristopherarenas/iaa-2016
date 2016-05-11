#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <fstream>
#include "common.h"
#include "Route.h"
#include "ShortestRoute.h"
#include "RouteInfo.h"
#include <vector>

class Solution {
	    
public:
	float fo1,fo2; // stores the result of the objective functions for efficiency
	float quality;
	bool dominated;
	int ranking_pareto;
	vector<bool> stops_used;
	std::vector<Route> routes;
	Solution(void);
	Solution(Problem &p,vector<RouteInfo> &routes_info);
	~Solution(void);
	void set_routes(std::vector<Route> &routes);
	void setQuality(float,float);         //Calcula alterando el valor de fo1 y fo2
	bool check_feasability();
	bool check_connectivity(int size);
	void set_dominated(vector<Solution> &ss);
	float setFO1(ShortestRoute &sr, int** &demand);
	float setFO2(int &size, int** &travel_times);
	
	
	bool print_solution_routes();
    
    bool mutation_mix_routes(Route &r1, Route &r2, int** &travel);
    bool mutation_mix_route(Route &r,int** &travel);
    bool mutation_remove_bs(Route &r,int &size);
    bool mutation_add_bs(Route &r, int** &travel, int &size, vector<BusStop> &bs);
    bool mutation(vector<RouteInfo> &info, int** &travel,int &size,vector<BusStop> &bs);
    
    
};

#endif
