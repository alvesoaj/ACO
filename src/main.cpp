/*
 * main.cpp
 *
 *  Created on: Aug 11, 2012
 *      Author: aj.alves@zerokol.com
 */

// Importando bibliotecas necessárias
#include <iostream>
#include <vector> // Para fácil uso de vetores
#include <string> // Para trabalhar fácil com strings
#include <sstream> // Para trabalhar fácil com strings
#include <math.h> // Para ajudar em calculos matemáticos
#include <ctime>  // Para usar o time() e fornecer um bom seed para o random
#include <cstdlib> // Para gerar numeros randômicos
#include "models/Ant.h"

// Constantes
#define NULL -1
#define CITY_AMOUNT 6
#define POPULATION_SIZE 3
#define PHEROMONE_RATE 0.1
#define ALFA 1
#define BETA 1
#define MAX_INTERATIONS 1

// Variáveis
vector<Ant*> ants;
double pheromone_links[CITY_AMOUNT][CITY_AMOUNT];
int distance_links[CITY_AMOUNT][CITY_AMOUNT] = { { NULL, 7, 4, 3, 11, 1 }, { 7,
		NULL, 2, 8, 10, 8 }, { 4, 2, NULL, 9, 9, 3 }, { 3, 8, 9, NULL, 5, 4 },
		{ 11, 10, 9, 1, NULL, 3 }, { 1, 8, 3, 4, 3, NULL } };

using namespace std;

void initialize_ants(vector<Ant*> *vec);
void positioning_ants(vector<Ant*> *vec);
void seed_initial_pheromone();
void build_solutions(vector<Ant*> *vec);
int get_random_number(int from, int to);
void print_route(int id, vector<int> *vec);
string number_to_String(double n);

int main(int argc, char *argv[]) {
	// Inicializando o gerador de números randômicos com um seed temporal
	srand(time(0));
	// Inicializar o contador de interações
	int interation = 0;
	// Inicializando os objetos formigas
	initialize_ants(&ants);
	// Posicionando as formigas aleatoriamente
	positioning_ants(&ants);
	// Configurando as concetrações iniciais de feromônio
	seed_initial_pheromone();

	while (interation < MAX_INTERATIONS) {
		build_solutions(&ants);
		interation++;
	}

	for (unsigned int i = 0; i < ants.size(); i++) {
		print_route(ants[i]->getID(), ants[i]->getRoute());
	}

	//cin.get(); // aguarda por um novo caracter para então encerrar a aplicação

	return 0;
}

void initialize_ants(vector<Ant*> *vec) {
	for (int i = 0; i < POPULATION_SIZE; i++) {
		Ant *a = new Ant((i + 1), CITY_AMOUNT);
		vec->push_back(a);
	}
}

void positioning_ants(vector<Ant*> *vec) {
	for (unsigned int i = 0; i < vec->size(); i++) {
		int random_city = get_random_number(0, (CITY_AMOUNT - 1));
		vec->at(i)->addToRoute(random_city);
	}
}

void seed_initial_pheromone() {
	for (int i = 0; i < CITY_AMOUNT; i++) {
		for (int j = 0; j < CITY_AMOUNT; j++) {
			if (i != j) {
				pheromone_links[i][j] = PHEROMONE_RATE;
			} else {
				pheromone_links[i][j] = NULL;
			}
		}
	}
}

void build_solutions(vector<Ant*> *vec) {
	// Para cada formiga
	for (unsigned int i = 0; i < vec->size(); i++) {
		for(int p = 0; p < CITY_AMOUNT; p++){
			int position = vec->at(i)->getPosition();
			double transition_probability[CITY_AMOUNT];
			double link_rate_sum = 0;
			// Somando as taxas de feromonio e heuristica
			for (int j = 0; j < CITY_AMOUNT; j++) {
				if (pheromone_links[position][j] >= 0
						and distance_links[position][j] >= 0) {
					link_rate_sum += pow(pheromone_links[position][j], ALFA) * pow(
							distance_links[position][j], BETA);
				}
			}
			// Calculando a probabilidade de transição
			for (int j = 0; j < CITY_AMOUNT; j++) {
				if (pheromone_links[position][j] >= 0
						and distance_links[position][j] >= 0) {
					transition_probability[j] = (pow(pheromone_links[position][j],
							ALFA) * pow(distance_links[position][j], BETA))
							/ link_rate_sum;
				}else{
					transition_probability[j] = 0;
				}
			}
			// fazendo a roleta
			double roulette = (double)get_random_number(0, 10000) / 10000.0;
			double minor = 0;
			double major = 0;
			// Selecionando o próximo nó
			cout << roulette << endl;
			for (int j = 0; j < sizeof(transition_probability); j++) {
				major += transition_probability[j];
				if(roulette >= minor and roulette <= major){
					vec->at(i)->addToRoute(j);
					break;
				}else{
					minor = major;
				}
			}
		}
	}
}

int get_random_number(int from, int to) {
	if (from < to) {
		return (rand() % to) + from;
	} else {
		return 0;
	}
}

void print_route(int id, vector<int> *vec) {
	string temp = "Rota da formiga " + number_to_String(id) + " : ";
	for (unsigned int i = 0; i < vec->size(); i++) {
		temp += number_to_String(vec->at(i));
		if ((i + 1) != vec->size()) {
			temp += ", ";
		}
	}
	temp += ".\n";
	cout << temp << endl;
}

string number_to_String(double n) {
	stringstream out;
	out << n;
	return out.str();
}
