/*
 * Ant.cpp
 *
 *  Created on: Aug 11, 2012
 *      Author: aj.alves@zerokol.com
 */

#include "Ant.h"

Ant::Ant(int len) {
	this->lenght = len;
	this->routeDistance = 0.0;
	this->route.resize(len);
	this->tabuList.resize(len);
}

void Ant::setLenght(int len) {
	this->lenght = len;
}

int Ant::getLenght() {
	return this->lenght;
}

double Ant::getRouteDistance() {
	return this->routeDistance;
}
