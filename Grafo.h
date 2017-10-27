#pragma once

#include <string>
#include <fstream>

#include "Vertice.h"


using namespace std;

class Grafo {

public:
	Grafo(string);
	~Grafo();

	void printGrafo();	

	vector<Vertice> red;	// Grafo entero donde posicion en el vector
							// se corresponde con el numero del vertice

private:

	// Funciones para la inicializacion
	void handlerInput(string);
	void setParametros(int, int);
	void addVertice(int, int);

	int vertices = -1;	// Numero de vertices
	int aristas = -1;	// Numero aristas 
};

 