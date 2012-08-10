/*
 * main.cpp
 *
 *  Created on: Aug 11, 2012
 *      Author: aj.alves@zerokol.com
 */

#include <iostream>
#include "models/Ant.h"

using namespace std;

int main(int argc, char *argv[]) {
	Ant a(2);

	cout << "Distancia: " << a.getRouteDistance() << endl;
	cout << "\n" << endl;

	cin.ignore(); // ignores the newline
	cin.get(); // waits for character

	return 0;
}
