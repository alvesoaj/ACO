/*
 * Monitor.h
 *
 *  Created on: Sep 13, 2012
 *      Author: zerokol
 */

#ifndef MONITOR_H_
#define MONITOR_H_

// Importando bibliotecas necessárias
#include <math.h>
#include <vector>
using std::vector;

class Monitor {
private:
	int a = 1;
	int b = 2;
	int c = 0;
public:
	Monitor();

	double getCost(vector<int>* route);
	double getCoverage(double cost);
};

#endif /* MONITOR_H_ */
