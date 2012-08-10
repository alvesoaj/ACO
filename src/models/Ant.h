/*
 * Ant.h
 *
 *  Created on: Aug 10, 2012
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
	double getQuality();
	void setQuality(double q);
	int getRouteDistance();
	int getRouteSize();
	void incraseRouteDistance(int val);
	void addToRoute(int point);
	void restartSearch();
	vector<int>* getRoute();
	int getPosition();
	bool checkVisitIn(int pos);
private:
	// Variáveis
	int id;
	int routeDistance;
	double quality;
	vector<int> route;
	vector<bool> tabooList;
};

#endif /* ANT_H_ */
