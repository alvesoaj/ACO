/*
 * main.cpp
 *
 *  Created on: Aug 11, 2012
 *      Author: aj.alves@zerokol.com
 */

// Importando bibliotecas necessárias
#include <iostream>
#include <vector>
#include "models/Ant.h"

using namespace std;

void initialize_ants(vector<Ant*> *vec, int size);

int main(int argc, char *argv[]) {
	// Variáveis
	int population_size = 3;

	vector<Ant*> ants;
	initialize_ants(&ants, population_size);

	for (unsigned int i = 0; i < ants.size(); i++) {
		cout << "Distancia: " << ants[i]->getRouteDistance() << endl;
		cout << "\n" << endl;
	}

	// cin.ignore(); // ignora o "new line"
	cin.get(); // aguarda por um novo caracter para então encerrar a aplicação

	return 0;
}

void initialize_ants(vector<Ant*> *vec, int size) {
	for (int i = 0; i < size; i++) {
		Ant *a = new Ant(3);
		a->incraseRouteDistance(10 * (i + 1));
		vec->push_back(a);
	}
}
