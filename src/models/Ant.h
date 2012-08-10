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
	Ant(int id, int len);
	// Métodos
	int getID();
	void setLenght(int len);
	int getLenght();
	int getRouteDistance();
	void incraseRouteDistance(int val);
	void addToRoute(int point);
	vector<int>* getRoute();
	int getPosition();
private:
	// Variáveis
	int id;
	int lenght;
	int routeDistance;
	vector<int> route;
	vector<bool> tabooList;
};

#endif /* ANT_H_ */
