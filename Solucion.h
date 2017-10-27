#pragma once
#include <vector>
#include "Vertice.h"
#include "Grafo.h"
#include "config.h"
#include <ctime>

using namespace std;

class Solucion {

public:
	Solucion(Grafo *);
	~Solucion();

	/// Algortimos de solucion
	void Bron();		
	void BronPoda();
	void BronMaxVec();
	void BronMinVec();
	void BronPivot();
	void Amplitud();

	/// Funciones complementarias de los algortimos
	vector<int> vectorCom(vector<int>*, vector<int>*);
	vector<int> vectorDif(vector<int>*, vector<int>*);
	bool findNumber(const vector<int> *a, int b);

	void imprimirInfo();	// Imprimir informacion de la solucion

private:

	int iteraciones;	// Numero nodos expandidos
	int typeSolucion;	// Tipo de busqueda
	double tiempo;		// Tiempo de ejecucion 

	vector<config> exp;		// Vector de situaciones ( =cconfig )
	vector<int> clique;		// Vertices del clique
	vector<Vertice> graph;	// Copia del grafo

	int sizeGraph;	// Numero total de vertices ( = grapfh.size())

	/// Vectores de inicializacion
	vector<int> R;	// Vertices recorridos
	vector<int> P;	// Vertices posibles a recorrer
	vector<int> X;	// Vertices prohibidos

};

