#include <iostream>
#include <fstream>
#include <string>
#include "Grafo.h"
#include "Solucion.h"


using namespace std;



int main() {

	Grafo a("c-fat200-1.clq");
	a.printGrafo();
	cout << endl;

	cout << "-------------------------------------------------------\n";
	
	Solucion b(&a);
	b.Bron();
	b.imprimirInfo();

	Solucion c(&a);
	c.BronPivot();
	c.imprimirInfo();

	
	Solucion d(&a);
	d.BronMinVec();
	d.imprimirInfo();

	Solucion e(&a);
	e.BronPoda();
	e.imprimirInfo();
	
	cout << endl;
	system("PAUSE");
}

