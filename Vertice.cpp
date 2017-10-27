#include "Vertice.h"



Vertice::Vertice(int a, int b){ 
	num = a; 
	if (b != -1 && b > 0) { updateRelative(b); }
}

Vertice::Vertice(){}

Vertice::~Vertice(){}

void Vertice::updateRelative(int a){

	bool find = false;
	for (size_t i = 0; i < relVertices.size(); i++) {
		if (relVertices.at(i) == a) { find = true; }
	}
	if(!find){ relVertices.push_back(a); }
}

void Vertice::printrel(){

	cout << "Vertice -> " << num << "\t";
	cout << "Vertices Relacionados -> ";

	for (size_t i = 0; i < relVertices.size(); i++) {
		cout << relVertices.at(i) << " ";
	}
	cout << endl;
}
