/*
 * main.cpp
 *
 *  Created on: Aug 10, 2012
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
#include "models/Monitor.h"

// Constantes
#define INVALID -1
// #define CITY_AMOUNT 6
#define CITY_AMOUNT 8
#define POPULATION_SIZE 30
#define PHEROMONE_RATE 0.1
#define ALFA 1
#define BETA 2
#define MAX_INTERATIONS 30
#define EVAPORATION_RATE 0.5
#define POSITIVE_CONTS 0.75

using namespace std;

// Variáveis
vector<Ant*> ants;
double pheromone_cost[CITY_AMOUNT][CITY_AMOUNT];
double pheromone_coverage[CITY_AMOUNT][CITY_AMOUNT];
int distance_links[CITY_AMOUNT][CITY_AMOUNT] = {
		{ INVALID, 1, 1, 1, 1, 1, 1, 1 }, { 1, INVALID, 1, 1, 1, 1, 1, 1 }, {
				1, 1, INVALID, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, INVALID, 1, 1, 1, 1 }, { 1, 1, 1, 1, INVALID, 1, 1, 1 }, {
				1, 1, 1, 1, 1, INVALID, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, INVALID, 1 }, { 1, 1, 1, 1, 1, 1, 1, INVALID } };
int rate[CITY_AMOUNT] = { 2, 8, 4, 6, 3, 4, 6, 1 };
int bestDistance = INVALID;
int worseDistance = INVALID;
double bestSolution = 1000000000.0;
double worseSolution = 0.0;
vector<int> bestRoute;
vector<int> worseRoute;
double average = 0.0;
double variance = 0.0;
double standard_deviation = 0.0;
int greater_distance = INVALID;
Ant reference_ant;

void initialize_ants(vector<Ant*> *vec);
void positioning_ants(vector<Ant*> *vec, bool random);
void seed_initial_pheromone(bool random, double pheromone_rate, int intervals);
void build_solutions(vector<Ant*> *vec);
void check_best_solution(vector<Ant*> *vec);
double calculate_quality(int solution, int best_solution);
int get_random_number(int from, int to);
void pheromone_evaporates();
void update_pheromone(vector<Ant*> *vec);
void print_route(int id, int distance, vector<int> vec);
void print_pheromone();
string number_to_String(double n);
void print_result();
void calculate_metrics(vector<Ant*> *vec);
void get_greater_distance();

int main(int argc, char *argv[]) {
	// Inicializando o gerador de números randômicos com um seed temporal
	srand(time(0));
	// Inicializar o contador de interações
	int interation = 0;
	// Inicializando os objetos formigas
	initialize_ants(&ants);
	// Posicionando as formigas
	positioning_ants(&ants, false);
	// Configurando as concetrações iniciais de feromônio
	seed_initial_pheromone(false, PHEROMONE_RATE, 0);
	// Pegando a maior distância somado com 1
	get_greater_distance();

	while (interation < MAX_INTERATIONS) {
		// Imprimindo a matriz de feromônio
		// print_pheromone();
		build_solutions(&ants);
		check_best_solution(&ants);
		update_pheromone(&ants);
		for (unsigned int i = 0; i < ants.size(); i++) {
			print_route(ants[i]->getID(), ants[i]->getRouteDistance(),
					ants[i]->getRoute());
		}
		interation++;
	}

	// Imprimindo o resultado final
	print_result();

	//cin.get(); // aguarda por um novo caracter para então encerrar a aplicação

	return 0;
}

void initialize_ants(vector<Ant*> *vec) {
	for (int i = 0; i < POPULATION_SIZE; i++) {
		Ant *a = new Ant((i + 1), reference_ant.ALTERNATE);
		vec->push_back(a);
	}
}

void positioning_ants(vector<Ant*> *vec, bool random) {
	for (unsigned int i = 0; i < vec->size(); i++) {
		int random_city = 0;
		if (random) {
			random_city = get_random_number(0, (CITY_AMOUNT - 1));
		}
		vec->at(i)->addToRoute(random_city);
	}
}

void seed_initial_pheromone(bool random, double pheromone_rate, int intervals) {
	double pheromone_seed = pheromone_rate;
	for (int i = 0; i < CITY_AMOUNT; i++) {
		for (int j = 0; j < CITY_AMOUNT; j++) {
			if (i != j) {
				if (random == true && intervals > 0) {
					int rn = get_random_number(1, intervals);
					pheromone_seed = pheromone_rate / rn;
				}
				pheromone_cost[i][j] = pheromone_seed;
				pheromone_coverage[i][j] = pheromone_seed;
			} else {
				pheromone_cost[i][j] = INVALID;
				pheromone_coverage[i][j] = INVALID;
			}
		}
	}
}

void build_solutions(vector<Ant*> *vec) {
	// Para cada formiga
	for (unsigned int i = 0; i < vec->size(); i++) {
		// reiniciando a formiga para a busca
		int trail = reference_ant.IDLE;
		vec->at(i)->restartSearch();

		// Enquanto não passar em todas as cidades
		while (vec->at(i)->getRouteSize() < CITY_AMOUNT) {
			int position = vec->at(i)->getPosition();
			double transition_probability[CITY_AMOUNT];
			double link_rate_sum = 0;

			if (trail == reference_ant.IDLE or vec->at(i)->getTrailMode()
					== reference_ant.RANDOM) {
				int r = get_random_number(1, 100);
				if (r >= 1 and r <= 50) {
					trail = reference_ant.COST;
				} else {
					trail = reference_ant.COVERAGE;
				}
			} else {
				trail = vec->at(i)->getLastTrail() * -1;
			}

			// Somando as taxas de feromonio e heuristica
			for (int j = 0; j < CITY_AMOUNT; j++) {
				// Se a cidade já visitada, não entrar na análise
				if (vec->at(i)->checkVisitIn(j) == false) {
					switch (trail) {
					case reference_ant.COST:
						if (pheromone_cost[position][j] >= 0
								and distance_links[position][j] >= 0) {
							link_rate_sum += pow(pheromone_cost[position][j],
									ALFA) * pow(rate[position], BETA);
						}
						break;
					case reference_ant.COVERAGE:
						if (pheromone_coverage[position][j] >= 0
								and distance_links[position][j] >= 0) {
							link_rate_sum += pow(
									pheromone_coverage[position][j], ALFA)
									* pow(rate[position], BETA);
						}
						break;
					}
				}
			}
			// Calculando a probabilidade de transição
			for (int j = 0; j < CITY_AMOUNT; j++) {
				// Se a cidade já visitada, não entrar na análise
				if (vec->at(i)->checkVisitIn(j) == false) {
					switch (trail) {
					case reference_ant.COST:
						if (pheromone_cost[position][j] >= 0
								and distance_links[position][j] >= 0) {
							transition_probability[j] = (pow(
									pheromone_cost[position][j], ALFA) * pow(
									rate[position], BETA)) / link_rate_sum;
						} else {
							transition_probability[j] = 0;
						}
						break;
					case reference_ant.COVERAGE:
						if (pheromone_coverage[position][j] >= 0
								and distance_links[position][j] >= 0) {
							transition_probability[j] = (pow(
									pheromone_coverage[position][j], ALFA)
									* pow(rate[position], BETA))
									/ link_rate_sum;
						} else {
							transition_probability[j] = 0;
						}
						break;
					}
				} else {
					transition_probability[j] = 0;
				}
			}
			// fazendo a roleta
			double roulette = (double) get_random_number(0, 100) / 100.0;
			double minor = 0;
			double major = 0;
			// Selecionando o próximo nó
			for (unsigned int j = 0; j < sizeof(transition_probability); j++) {
				// Se a cidade já visitada, não entrar na análise
				if (vec->at(i)->checkVisitIn(j) == false) {
					major += transition_probability[j];
					if (roulette >= minor and roulette <= major) {
						vec->at(i)->addToRoute(j);
						vec->at(i)->incraseRouteDistance(
								distance_links[position][j]);
						break;
					} else {
						minor = major;
					}
				}
			}

			if (vec->at(i)->getTrailMode() == reference_ant.ALTERNATE) {
				vec->at(i)->setLastTrail(trail);
			}
		}
	}
}

void check_best_solution(vector<Ant*> *vec) {
	if (vec->size() > 0) {
		if (bestDistance == INVALID and worseDistance == INVALID) {
			bestDistance = vec->at(0)->getRouteDistance();
			bestRoute = vec->at(0)->getRoute();

			worseDistance = vec->at(POPULATION_SIZE - 1)->getRouteDistance();
			worseRoute = vec->at(POPULATION_SIZE - 1)->getRoute();
		}
		for (int i = 0; i < POPULATION_SIZE; i++) {
			if (vec->at(i)->getRouteDistance() < bestDistance) {
				bestDistance = vec->at(i)->getRouteDistance();
				bestRoute = vec->at(i)->getRoute();
			} else if (vec->at(i)->getRouteDistance() > worseDistance) {
				worseDistance = vec->at(i)->getRouteDistance();
				worseRoute = vec->at(i)->getRoute();
			}
		}
		for (int i = 0; i < POPULATION_SIZE; i++) {
			double quality = calculate_quality(vec->at(i)->getRouteDistance(),
					bestDistance);
			if (quality < bestSolution) {
				bestSolution = quality;
			} else if (quality > worseSolution) {
				worseSolution = quality;
			}
			vec->at(i)->setQuality(quality);
		}
	}
}

double calculate_quality(int solution, int best_solution) {
	return (double) (1 * solution) / (double) best_solution;
}

void pheromone_evaporates() {
	for (int i = 0; i < CITY_AMOUNT; i++) {
		for (int j = 0; j < CITY_AMOUNT; j++) {
			if (pheromone_links[i][j] != INVALID) {
				pheromone_links[i][j] = (1 - EVAPORATION_RATE)
						* pheromone_links[i][j];
			}
		}
	}
}

void update_pheromone(vector<Ant*> *vec) {
	pheromone_evaporates();
	for (int i = 0; i < POPULATION_SIZE; i++) {
		double pheromone_to_sum = POSITIVE_CONTS / vec->at(i)->getQuality();
		vector<int> route = vec->at(i)->getRoute();
		for (int j = 0; j < (vec->at(i)->getRouteSize() - 1); j++) {
			int lower = route.at(j);
			int uper = route.at(j + 1);
			if (pheromone_links[lower][uper] != INVALID) {
				pheromone_links[lower][uper] += pheromone_to_sum;
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

void print_route(int id, int distance, vector<int> vec) {
	string temp = "Rota da formiga " + number_to_String(id) + " : ";
	for (unsigned int i = 0; i < vec.size(); i++) {
		temp += number_to_String(vec.at(i));
		if ((i + 1) != vec.size()) {
			temp += ", ";
		}
	}
	temp += ". Tamanho: " + number_to_String(distance) + "\n";
	cout << temp << endl;
}

void print_pheromone() {
	string temp = "Taxas de feromônio:";
	temp += "\n{";
	for (int i = 0; i < CITY_AMOUNT; i++) {
		temp += "{";
		for (int j = 0; j < CITY_AMOUNT; j++) {
			temp += "{" + number_to_String(pheromone_cost[i][j]) + ", "
					+ number_to_String(pheromone_cost[i][j]) + "}";
			if ((j + 1) != CITY_AMOUNT) {
				temp += ", ";
			}
		}
		if ((i + 1) != CITY_AMOUNT) {
			temp += "}, ";
		} else {
			temp += "}";
		}
	}
	temp += "}\n";
	cout << temp << endl;
}

void print_result() {
	cout << "Pior resultado:" << endl;
	cout << "f(x):" << worseSolution << endl;
	print_route(0, worseDistance, worseRoute);

	cout << "Melhor resultado:" << endl;
	cout << "f(x):" << bestSolution << endl;
	print_route(0, bestDistance, bestRoute);

	calculate_metrics(&ants);
	cout << "Média:" << average << endl;
	cout << "Variância:" << variance << endl;
	cout << "Desvio padrão:" << standard_deviation << endl;
}

string number_to_String(double n) {
	stringstream out;
	out << n;
	return out.str();
}

void calculate_metrics(vector<Ant*> *vec) {
	// Calcular a média
	int sum = 0;
	for (unsigned int i = 0; i < POPULATION_SIZE; i++) {
		sum += vec->at(i)->getRouteDistance();
	}
	average = (double) sum / (double) POPULATION_SIZE;
	// Calcuar a variância
	sum = 0;
	for (unsigned int i = 0; i < POPULATION_SIZE; i++) {
		sum += pow(vec->at(i)->getRouteDistance() - average, 2);
	}
	variance = (double) sum / (double) POPULATION_SIZE;
	// Calculando o desvio padrão
	standard_deviation = pow(variance, 0.5);
}

void get_greater_distance() {
	for (int i = 0; i < CITY_AMOUNT; i++) {
		for (int j = 0; j < CITY_AMOUNT; j++) {
			if (distance_links[i][j] > greater_distance) {
				greater_distance = distance_links[i][j];
			}
		}
	}
	greater_distance += 1;
}
