/*
 * Monitor.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: zerokol
 */

#include "Monitor.h"

Monitor::Monitor() {
	// TODO Auto-generated constructor stub
}

double Monitor::getCost(vector<int>* route) {
	return route->size();
}

double Monitor::getCoverage(double cost) {
	return this->a * pow(cost, 2) + this->b * pow(cost, 1) + c;
}
