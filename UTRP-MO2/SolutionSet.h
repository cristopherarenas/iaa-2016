#ifndef SOLUTION_SET_H
#define SOLUTION_SET_H

#include <vector>

#include "Solution.h"
#include "Problem.h"
#include "RouteInfo.h"
#include "ShortestRoute.h"

class SolutionSet { 
  int id;

public:
	std::vector <Solution> solutions;	
	~SolutionSet(void);
	SolutionSet(void);
	SolutionSet(int size);
	//SolutionSet(Problem &p,vector<RouteInfo> &ri,int &pop_size);
	SolutionSet(Problem &p,vector<RouteInfo> &ri,int &pop_size, ShortestRoute &sro, float &alpha, float &beta);
	bool print_solution_set();
	vector<Solution> get_solution_ranking(int rank);
};

#endif
