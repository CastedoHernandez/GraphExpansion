#include "Grafo.h"

Grafo::Grafo(string nameFile){

	/// Variables
	string line;	// Linea del fichero
	ifstream file;	// Fichero de lectura
	
	/// Ejecucion
	file.open(nameFile);	// Apertura del fichero

	if (file.is_open()) {	// Chequeo de la correcta apertura
		cout << "\nCreating Grafo..." << endl;	// Comando para usuario
		while (getline(file, line)) {			// Asignacion de linea de fichero -> linea
			if(!line.empty())	handlerInput(line);		// Si linea no se encuentra vacia
		}												// llamar al manejador ( = handlerInput )
		file.close();							// Cierre del fichero
		cout << "Grafo finished" << endl;		// Comando para usuario
	}
	else { cout << "No se ha podido abrir el fichero: " << nameFile << endl; }	// Error en apertura del fichero

}

Grafo::~Grafo(){}


void Grafo::handlerInput(string s) {

	size_t foundB;
	size_t foundA;

	char i = s.at(0);

	int aristas = -1;
	int vertices = -1;

	int actVertice;
	int relVertice;

	switch (i) {
	case 'p':
		foundA = 0;
		foundB = 0;

		for (unsigned j = 0; j < 4; j++) {
			foundA = s.find(" ", foundB + 1);

			string saux = s.substr(foundB + 1, foundA - (foundB + 1));
			int iaux = atoi(saux.c_str());

			if (j == 2) { vertices = iaux; }
			else if (j == 3) { aristas = iaux; }
			foundB = foundA;
		}

		setParametros(vertices, aristas);
		addVertice(1, -1);

		break;

	case 'e':
		foundA = 0;
		foundB = 0;

		for (unsigned j = 0; j < 3; j++) {

			foundA = s.find(" ", foundB + 1);

			string saux = s.substr(foundB + 1, foundA - (foundB + 1));

			int iaux = atoi(saux.c_str());

			if (j == 1) { actVertice = iaux; }
			else if (j == 2) { relVertice = iaux; }
			foundB = foundA;
		}

		addVertice(actVertice, relVertice);
		break;

	default:
		break;
	}
}



void Grafo::setParametros(int a, int b){

	a = vertices;
	b = aristas;

}

void Grafo::addVertice(int num, int rel) {

	bool find = false;

	for (size_t i = 0; i < red.size(); i++) {
		if (red.at(i).getNum() == num) {
			red.at(i).updateRelative(rel);
			find = true;
		}	

		// Doblamos las relaciones antes del 1 -> 2
		// ahora de 1 -> 2 y de 2 -> 1
		if (red.at(i).getNum() == rel) {
			red.at(i).updateRelative(num);
		}
		/////
	}

	if (!find) {
		Vertice newV(num, rel);
		red.push_back(newV);
	}
}

void Grafo::printGrafo(){
	/// Imprime por consola cada uno de los vertices de la red
	/// además de los vertices con los que se encuentran unidos
	/// mediante aristas

	cout << "\n\n ----- GRAFO INFO ----- " << endl;
	
	for (size_t i = 0; i < red.size(); i++) {
		red.at(i).printrel();
	}
}