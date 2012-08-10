/*
 * Ant.h
 *
 *  Created on: Aug 11, 2012
 *      Author: aj.alves@zerokol.com
 */

#ifndef ANT_H_
#define ANT_H_

// Importando bibliotecas necessárias
#include <vector>
using std::vector;

class Ant {
public:
	// Construtor
	Ant(int len);
	// Metodos
	void setLenght(int len);
	int getLenght();
	double getRouteDistance();
	void incraseRouteDistance(double val);
private:
	// variáveis
	int lenght;
	double routeDistance;
	vector<double> route;
	vector<bool> tabuList;
};

#endif /* ANT_H_ */
