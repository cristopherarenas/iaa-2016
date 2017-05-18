#ifndef BUS_STOP_H
#define BUS_STOP_H

#include <iostream>
#include "common.h"

using namespace std;

class BusStop
{
    
public:
    int idi;
    float x,y;
    vector<int> neighbors;
	
	BusStop(int idi, float x, float y,int **&travel, int &size);
    //BusStop(int idi, float x, float y);
    bool operator==(const BusStop& compare);

};


#endif
