#include "config.h"





config::config()
{
}

config::config(vector<int>*a, vector<int>*b, vector<int>*c){
	
	R = *a;
	P = *b;
	X = *c;

}


config::~config(){
}

void config::imprimeConfig() {

	cout << "R -> ";
	for (auto it = R.begin(); it != R.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
	cout << "P -> ";
	for (auto it = P.begin(); it != P.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
	cout << "X -> ";
	for (auto it = X.begin(); it != X.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}