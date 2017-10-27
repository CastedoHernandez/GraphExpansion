#include "Solucion.h"



Solucion::Solucion(Grafo *a) {

	graph = a->red; 
	sizeGraph = (int)a->red.size();	// Inicializacion tamanio
	typeSolucion = 100;	// Solucion no definida, solo para imprimir
	iteraciones = 0;	// Inicializacion valor de nodos expandidos

	for (size_t it = 0; it < graph.size(); it++) {
		P.push_back(graph.at(it).num);	// Aniadir todas las posibilidades
	}
	R.clear();	// Vaciar vector de prohibidos
	X.clear();	// Vaciar vector de recorridos

	config aux(&R, &P, &X);	// Inicializar primer estado
	exp.push_back(aux);
}

Solucion::~Solucion(){}

void Solucion::Bron(){
	
	typeSolucion = 0;
	config Padre;

	clock_t begin, end;
	begin = clock();	// Comienza a contar el tiempo

	do{ 
		iteraciones++;	// Aumentar en 1 el numero de nodos expandidos
		Padre = exp.at(exp.size() - 1);
		vector<int> X = Padre.X;
		vector<config> aux; // Para poderlo ordenar

		/// Expansion
		for (size_t i = 0; i < Padre.P.size(); i++) {
			config Hijo;
			vector<int> iP, fP;

			int num = Padre.P.at(i);
			vector<int> posib = graph.at(num - 1).relVertices;

			Hijo.R = Padre.R;
			Hijo.R.push_back(num);

			if (Hijo.R.size() > clique.size()) {
				clique = Hijo.R;
			}

			Hijo.X = vectorCom(&X, &posib);
			fP = vectorDif(&Padre.P, &Hijo.R);
			iP = vectorDif(&fP, &Hijo.X);
			Hijo.P = vectorCom(&iP, &posib);

			if(!Hijo.P.empty())		aux.push_back(Hijo);

			X.push_back(num);
		}

		exp.pop_back();

		for (size_t j = 0; j < aux.size(); j++) {
			exp.push_back(aux.at(aux.size() - 1 - j));
		}

	} while (!exp.empty());

	end = clock();
	tiempo = double(end - begin) / CLOCKS_PER_SEC;

}

void Solucion::BronPoda(){

	typeSolucion = 1;
	config Padre;

	clock_t begin, end;
	begin = clock();	// Comienza a contar el tiempo

	do {
		iteraciones++;	// Aumentar en 1 el numero de nodos expandidos
		Padre = exp.at(exp.size() - 1);
		vector<int> X = Padre.X;
		vector<config> aux; // Para poderlo ordenar

		/// Expansion
		for (size_t i = 0; i < Padre.P.size(); i++) {
	
			config Hijo;
			vector<int> iP, fP;

			int num = Padre.P.at(i);
			vector<int> posib = graph.at(num - 1).relVertices;

			Hijo.R = Padre.R;
			Hijo.R.push_back(num);

			Hijo.X = vectorCom(&X, &posib);
			fP = vectorDif(&Padre.P, &Hijo.R);
			iP = vectorDif(&fP, &Hijo.X);
			Hijo.P = vectorCom(&iP, &posib);

			if (Hijo.R.size() + Hijo.P.size() > clique.size()) {

				if (Hijo.R.size() > clique.size())
					clique = Hijo.R;
				
				if (!Hijo.P.empty()) 
					aux.push_back(Hijo);

				X.push_back(num);
			}
		}

		exp.pop_back();

		for (size_t j = 0; j < aux.size(); j++) {
			exp.push_back(aux.at(aux.size() - 1 - j));
		}

	} while (!exp.empty());

	end = clock();
	tiempo = double(end - begin) / CLOCKS_PER_SEC;

}


void Solucion::BronMaxVec() {

	/// Tiempo
	clock_t begin, end;	// Declaración de comienzo y fin;
	begin = clock();	// Comienza a contar el tiempo


						/// Variables
	typeSolucion = 2;	// Tipo de solucion
	config Padre;		// Declaracion del vertice a expandir

						/// Bucle de expansion
	do {
		iteraciones++;	// Aumentar en 1 el numero de nodos expandidos
		Padre = exp.at(exp.size() - 1);	// Asignacion del ultimo nodo del vector de expansion

		vector<int> X = Padre.X;	 // Asignacion de vertices prohibidos
		vector<config> aux;			 // Para poderlo ordenar

		cout << "PADRE " << endl;
		Padre.imprimeConfig();

		/// Expansion
		for (size_t i = 0; i < Padre.P.size(); i++) {
			config Hijo;
			vector<int> iP, fP;

			int num = Padre.P.at(i);
			vector<int> posib = graph.at(num - 1).relVertices;

			Hijo.R = Padre.R;
			Hijo.R.push_back(num);

			if (Hijo.R.size() > clique.size()) {
				clique = Hijo.R;
			}

			Hijo.X = vectorCom(&X, &posib);
			fP = vectorDif(&Padre.P, &Hijo.R);
			iP = vectorDif(&fP, &Hijo.X);
			Hijo.P = vectorCom(&iP, &posib);

			if (!Hijo.P.empty()) {
				aux.push_back(Hijo);
			}
			X.push_back(num);

			cout << "HIJO " << endl;
			Hijo.imprimeConfig();
		}
		system("PAUSE");

		exp.pop_back();	// Eliminacion del vertice expandido

						// Ordenar vector de expansion mas vecinos
		if (!aux.empty()) {		// Si tiene vecinos
			int posMax = 0;		// Inicializacion posicion con mas vecinos
			int sizeMax = aux.at(0).P.size();	// Tamaño maximo el primero
			for (size_t it = 0; it < aux.size() - 1; it++) {	// Recorrer todos los hijos
				if (sizeMax < aux.at(it + 1).P.size()) {		// Si el tamaño es mayor 
					sizeMax = aux.at(it + 1).P.size();	// Actualizacion tamanio maximo
					posMax = it;		// Actualizacion de la posicion
				}
			}

			config maxAux = aux.at(posMax);
			aux.at(posMax) = aux.at(aux.size() - 1);
			aux.pop_back();
			aux.push_back(maxAux);
		}

		for (size_t j = 0; j < aux.size(); j++) {
			exp.push_back(aux.at(j));
		}

	} while (!exp.empty());

	end = clock();
	tiempo = double(end - begin) / CLOCKS_PER_SEC;
}


void Solucion::BronMinVec() {

	typeSolucion = 3;
	config Padre;

	clock_t begin, end;
	begin = clock();	// Comienza a contar el tiempo
	
	do {
		iteraciones++;	// Aumentar en 1 el numero de nodos expandidos
		Padre = exp.at(exp.size() - 1);
		vector<int> X = Padre.X;
		vector<config> aux; // Para poderlo ordenar

		/// Expansion
		for (size_t i = 0; i < Padre.P.size(); i++) {

			config Hijo;
			vector<int> iP, fP;

			int num = Padre.P.at(i);
			vector<int> posib = graph.at(num - 1).relVertices;

			Hijo.R = Padre.R;
			Hijo.R.push_back(num);

			if (Hijo.R.size() > clique.size()) {
				clique = Hijo.R;
			}

			Hijo.X = vectorCom(&X, &posib);
			fP = vectorDif(&Padre.P, &Hijo.R);
			iP = vectorDif(&fP, &Hijo.X);
			Hijo.P = vectorCom(&iP, &posib);

			if (!Hijo.P.empty())		aux.push_back(Hijo);

			X.push_back(num);
		}

		exp.pop_back();

		// Ordenar vector de expansion mas vecinos
		if (!aux.empty()) {		// Si tiene vecinos
			int posMin = 0;		// Inicializacion posicion con mas vecinos
			int sizeMin = aux.at(0).P.size();	// Tamaño maximo el primero
			for (size_t it = 0; it < aux.size() - 1; it++) {	// Recorrer todos los hijos
				if (sizeMin > aux.at(it + 1).P.size()) {			// Si el tamaño es mayor 
					sizeMin = aux.at(it + 1).P.size();
					posMin = it;				// Actualizacion de la posicion
				}
			}

			config maxAux = aux.at(posMin);
			aux.at(posMin) = aux.at(aux.size() - 1);
			aux.pop_back();
			aux.push_back(maxAux);
		}

		for (size_t j = 0; j < aux.size(); j++) {
			exp.push_back(aux.at(j));
		}
	} while (!exp.empty());

	end = clock();
	tiempo = double(end - begin) / CLOCKS_PER_SEC;
}


void Solucion::BronPivot() {

	/// Tiempo
	clock_t begin, end;	// Declaración de comienzo y fin;
	begin = clock();	// Comienza a contar el tiempo


	/// Variables
	typeSolucion = 4;	// Tipo de solucion
	config Padre;		// Declaracion del vertice a expandir

	/// Bucle de expansion
	do {
		iteraciones++;	// Aumentar en 1 el numero de nodos expandidos
		Padre = exp.at(exp.size() - 1);	// Asignacion del ultimo nodo del vector de expansion

		vector<int> X = Padre.X;	 // Asignacion de vertices prohibidos
		vector<config> aux;			 // Para poderlo ordenar

		int posMaxP = 0;
		int sizeMaxP = 0;	// Tamaño maximo el primero
		for (size_t it = 0; it < Padre.P.size(); it++) {
			int num = Padre.P.at(it);
			int tam = graph.at(num - 1).relVertices.size();
			if (tam > sizeMaxP) {
				sizeMaxP = tam;
				posMaxP = it;
			}
		}

		if (!Padre.P.empty()) {
			int numero = Padre.P.at(posMaxP);
			Padre.P.at(posMaxP) = Padre.P.at(0);
			Padre.P.at(0) = numero;
		}
		
		vector<int> pivot;	// control de expansion

		/// Expansion
		for (size_t i = 0; i < Padre.P.size(); i++) {
			config Hijo;
			vector<int> iP, fP;

			int num = Padre.P.at(i);
			if (i == 0 || !findNumber(&pivot, num)) {
				vector<int> posib = graph.at(num - 1).relVertices;

				Hijo.R = Padre.R;
				Hijo.R.push_back(num);

				if (Hijo.R.size() > clique.size()) {
					clique = Hijo.R;
				}

				Hijo.X = vectorCom(&X, &posib);
				fP = vectorDif(&Padre.P, &Hijo.R);
				iP = vectorDif(&fP, &Hijo.X);
				Hijo.P = vectorCom(&iP, &posib);

				if (i == 0) {		// Creacion del vector de pivot
					pivot = Hijo.P;
					pivot.insert(pivot.end(), Hijo.X.begin(), Hijo.X.end());
				}

				if (!Hijo.P.empty()) {
					aux.push_back(Hijo);
				}
				X.push_back(num);
			}
		}

		exp.pop_back();	// Eliminacion del vertice expandido

						// Ordenar vector de expansion mas vecinos
		if (!aux.empty()) {		// Si tiene vecinos
			int posMax = 0;		// Inicializacion posicion con mas vecinos
			int sizeMax = aux.at(0).P.size();	// Tamaño maximo el primero
			for (size_t it = 0; it < aux.size() - 1; it++) {	// Recorrer todos los hijos
				if (sizeMax < aux.at(it + 1).P.size()) {		// Si el tamaño es mayor 
					sizeMax = aux.at(it + 1).P.size();	// Actualizacion tamanio maximo
					posMax = it;		// Actualizacion de la posicion
				}
			}

			config maxAux = aux.at(posMax);
			aux.at(posMax) = aux.at(aux.size() - 1);
			aux.pop_back();
			aux.push_back(maxAux);
		}

		for (size_t j = 0; j < aux.size(); j++) {
			exp.push_back(aux.at(j));
		}

	} while (!exp.empty());

	end = clock();
	tiempo = double(end - begin) / CLOCKS_PER_SEC;
}



void Solucion::Amplitud(){
	/// Resolucion en amplitud la busqueda del numero de clique de un 
	/// grafo dado. La expansión de los diferentes notdos es realizada mediante
	/// la tecnica de amplitud. 

	/// Variables 
	typeSolucion = 5;	// Tipo de solucion
	config Padre;		// Declaracion del nodo padre

	/// Tiempo
	clock_t begin, end;	// Declaracion de comienzo y fin 
	begin = clock();	// Comienza a contar el tiempo

	/// Bucle de expansion
	do {
		iteraciones++;		// Aumentar en 1 el numero de nodos expandidos
		Padre = exp.at(0);	// Asignacion del nodo a expandir
		vector<int> X = Padre.X;	// Nodos prohibidos
		vector<config> aux; // Para poderlo ordenar

		/// Expansion
		for (size_t i = 0; i < Padre.P.size(); i++) {

			config Hijo;
			vector<int> iP, fP;

			int num = Padre.P.at(i);
			vector<int> posib = graph.at(num - 1).relVertices;

			Hijo.R = Padre.R;
			Hijo.R.push_back(num);

			if (Hijo.R.size() > clique.size()) 
				clique = Hijo.R;

			Hijo.X = vectorCom(&X, &posib);	// Determinar vecotres prohibidos 

			fP = vectorDif(&Padre.P, &Hijo.R);	// Determinacion de vectores
			iP = vectorDif(&fP, &Hijo.X);		// que se podrian expandir
			Hijo.P = vectorCom(&iP, &posib);	// en funcion del nodo actual

			if (!Hijo.P.empty())	// Si el nodo actual tiene posibilidades de expansion		
				aux.push_back(Hijo);	// Aniadir al vector de nodos a expandir

			X.push_back(num);	// Añadir el numero del vertice a la lista de vertices prohibidos

		}

		exp.pop_back();

		for (size_t j = 0; j < aux.size(); j++) {
			exp.push_back(aux.at(j));
		}
	} while (!exp.empty());

	end = clock();
	tiempo = double(end - begin) / CLOCKS_PER_SEC;

}


vector<int> Solucion::vectorCom(vector<int>*a, vector<int>*b) {
	/// Compara dos vectores, a y b, de numeros enteros devolviendo
	/// en otro vector el conjunto de enteros comunes a ambos vectores
	
	vector<int> pos;	// Container para numeros diferentes

	for (size_t i = 0; i < a->size(); i++) {	// Recorre primer vector
		for (size_t j = 0; j < b->size(); j++) {	// REcorre segundo vector
			if (a->at(i) == b->at(j)) {		// Mismo numero en los dos vecotes
				pos.push_back(a->at(i));	// Se almacena valor en container pos
				break;						// No hace falsa seguir recorriendo el vector
			}
		}
	}

	return pos;	// Se devuelve el contenedor
}



vector<int> Solucion::vectorDif(vector<int>*a, vector<int>*b){
	/// Compara dos vectores, a y b, de numeros enteros devolviendo
	/// en otro vector el conjunto de enteros no comunes a ambos vectores

	vector<int> pos;	// Container para numeros diferentes
	
	for (size_t i = 0; i < a->size(); i++) {	// Recorre primer vector
		bool found = false;		// Inicializacion de variable found (= encontrado),
								// ya que es un numero nuevo a buscar en el
								// otro vector.

		for (size_t j = 0; j < b->size(); j++) {	// Se recorre el segundo vector
			if (a->at(i) == b->at(j)) {	// Mismo numero en ambos vectores
				found = true;			// Variable found a true
				break;					// No hace falta seguir recorriendo el vector				
			}
		}
		if (!found) { pos.push_back(a->at(i));}	// Si no se encuentra añadir al container pos
	}

	return pos;	// Se devuelve el contenedor
}

bool Solucion::findNumber(const vector<int> *a, int b) {
	/// Dado un vector de enteros y un entero, comprueba 
	/// que el entero se encuentre en el vector, devoviendo 
	/// true cuando esta y false cuando no. 

	/// Recorrer vector
	for (auto it = a->begin(); it != a->end(); it++) {
		if (*it == b) { return true; };	// Devolver true, no hace falta
	}									// seguir recorriendo el vector

	return false;	
}


void Solucion::imprimirInfo(){
	/// Imprime la solucion obtenida mediante el metodo aplicado corresponeidnte con
	/// la variable, typeSolucion. Imprime: el numero de clique, los vertices que forman el numero
	/// de clique, el numero de nodos totales expandidos y el tiempo de ejecucion.

	cout << endl;

	/// Tipo de solucion
	if (typeSolucion == 0) { cout << "\t -------- INFO - Solucion por profundidad -------- \n"; }
	else if (typeSolucion == 1) { cout << "\t -------- INFO - Solucion por profundidad, poda -------- \n"; }
	else if (typeSolucion == 2) { cout << "\t -------- INFO - Solucion por profundidad, mas hijos -------- \n"; }
	else if (typeSolucion == 3) { cout << "\t -------- INFO - Solucion por profundidad, menos hijos -------- \n"; }
	else if (typeSolucion == 3) { cout << "\t -------- INFO - Solucion por profundidad, pivot -------- \n"; }
	else if (typeSolucion == 5) { cout << "\t -------- INFO - Solucion por amplitud -------- \n"; }
	else { cout << "\t -------- INFO - Solucion NO DEFINIDA -------- \n"; }
	
	/// Informacion de la solucion
	cout << "\tNumero de clique es: " << clique.size() << endl;
	cout << "\tVertices: ";
	for (auto it = clique.begin(); it != clique.end(); it++) {
		cout << *it << " ";
	}

	cout << endl;
	cout << "\tNumero de nodos: " << iteraciones << endl;
	cout << "\tTiempo de ejecucion: " << tiempo << endl;
	cout << endl;

}

