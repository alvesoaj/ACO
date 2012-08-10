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
int Ant::getRouteDistance() {
	return this->routeDistance;
}

int Ant::getRouteSize() {
	return this->route.size();
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

int Ant::getPosition() {
	return this->route[this->route.size() - 1];
}

bool Ant::checkVisitIn(int pos) {
	for (int i = 0; i < this->route.size(); i++) {
		if (this->route[i] == pos) {
			return true;
		}
	}
	return false;
}
