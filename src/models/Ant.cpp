/*
 * Ant.cpp
 *
 *  Created on: Aug 10, 2012
 *      Author: aj.alves@zerokol.com
 */

#include "Ant.h"

// Implementação do construtor
Ant::Ant(int id) {
	this->id = id;
	this->routeDistance = 0;
	this->quality = 0;
}

int Ant::getID() {
	return this->id;
}

double Ant::getQuality() {
	return this->quality;
}

void Ant::setQuality(double q) {
	this->quality = q;
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
void Ant::restartSearch() {
	vector<int> newRoute;
	newRoute.push_back(this->route.at(0));
	this->route = newRoute;
	this->routeDistance = 0;
	this->quality = 0;
}

vector<int> Ant::getRoute() {
	return this->route;
}

int Ant::getPosition() {
	return this->route[this->route.size() - 1];
}

bool Ant::checkVisitIn(int pos) {
	for (unsigned int i = 0; i < this->route.size(); i++) {
		if (this->route[i] == pos) {
			return true;
		}
	}
	return false;
}
