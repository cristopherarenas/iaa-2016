#include "BusStop.h"

/*
BusStop::BusStop(int idi, float x, float y) {
	this->x = x;
	this->y = y;
	this->idi=idi;
	
	
};
*/

BusStop::BusStop(int idi, float x, float y, int **&travel, int &size) {
	this->x = x;
	this->y = y;
	this->idi=idi;
	
	vector<int> n;
	n.reserve(1);
	
	for(unsigned int j=0; j<size;j++){
		if(travel[idi][j] != -1){
			n.push_back(j);
		} 
	}
	this->neighbors = n;
};

bool BusStop::operator==(const BusStop& compare) 
{ 
	return compare.idi == this->idi; 
}

