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
	// Constantes
	const int ALTERNATE = 0;
	const int RANDOM = 1;
	const int COST = 100;
	const int COVERAGE = -100;

	// Construtor
	Ant();
	Ant(int id, int trail);
	// Métodos
	int getID();
	double getQuality();
	void setQuality(double q);
	int getTrailMode();
	void setTrailMode(int tm);
	int getLastTrail();
	void setLastTrail(int lt);
	int getRouteDistance();
	int getRouteSize();
	void incraseRouteDistance(int val);
	void addToRoute(int point);
	void restartSearch();
	vector<int> getRoute();
	int getPosition();
	bool checkVisitIn(int pos);

private:
	// Variáveis
	int id;
	int routeDistance;
	double quality;
	int trailMode;
	int lastTrail;
	vector<int> route;
};

#endif /* ANT_H_ */
