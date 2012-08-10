/*
 * Ant.cpp
 *
 *  Created on: Aug 11, 2012
 *      Author: aj.alves@zerokol.com
 */

#include "Ant.h"

// Implementação do construtor
Ant::Ant(int id, int len) {
	this->id = id;
	this->lenght = len;
	this->routeDistance = 0;
}

int Ant::getID() {
	return this->id;
}

// Implementação dos métodos
void Ant::setLenght(int len) {
	this->lenght = len;
}

int Ant::getLenght() {
	return this->lenght;
}

int Ant::getRouteDistance() {
	return this->routeDistance;
}

void Ant::incraseRouteDistance(int val) {
	this->routeDistance += val;
}

void Ant::addToRoute(int point) {
	this->route.push_back(point);
}

vector<int>* Ant::getRoute() {
	return &this->route;
}

int Ant::getPosition(){
	return this->route[this->route.size() - 1];
}
