/*
 * Ant.h
 *
 *  Created on: Aug 11, 2012
 *      Author: aj.alves@zerokol.com
 */

#ifndef ANT_H_
#define ANT_H_

#include <vector>
using std::vector;

class Ant {
public:
	Ant(int len);
	void setLenght(int len);
	int getLenght();
	double getRouteDistance();
private:
	int lenght;
	double routeDistance;
	vector<double> route;
	vector<bool> tabuList;
};

#endif /* ANT_H_ */
