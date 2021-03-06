#include "Problem.h"


Problem::Problem(void) {};
Problem::~Problem(void) {};
int** Problem::get_demand(void) { return this->demand;}; // calculates the total demand adding all demands

void Problem::set_size(int size)
{
	this->size = size;
}

void Problem::set_demand(int **&demand)
{
	this->demand = demand;
}

void Problem::set_travel_times(int **&travel_times)
{
	this->travel_times = travel_times;
}

void Problem::set_bus_stops(std::vector<BusStop> &bus_stops)
{
	this->bus_stops = bus_stops;
}

void Problem::set_name(std::string name)
{
	std::vector<std::string> x = split(name, '/');
	this->name = x[x.size()-1];
}

void Problem::show_bus_stops(void)
{
	for (std::vector<BusStop>::iterator it =  this->bus_stops.begin(); it!= this->bus_stops.end(); ++it)
	{
		std::cout << "BusStop:" << it->idi+1 << " (" << it->x << ", " << it->y << ")" << std::endl;
    }
}

void Problem::show_demand(void)
{
	::show_matrix(this->demand, this->size);
}

void Problem::show_travel_times(void)
{
	::show_matrix(this->travel_times, this->size);
}

std::string Problem::get_name(void){
	return this->name;
}

std::vector<BusStop> Problem::get_bus_stops(void){
	return this->bus_stops;
}

int Problem::get_size(void){
	return this->size;
}

int** Problem::get_travel_times(void){
	return this->travel_times;
}

float Problem::get_lbfo1(void){
	return this->lb_fo1;
}

float Problem::get_lbfo2(void){
	return this->lb_fo2;
}

void Problem::set_lbfo1(float &val){
	this->lb_fo1 = val;
}

void Problem::set_lbfo2(float &val){
	this->lb_fo2 = val;
}
