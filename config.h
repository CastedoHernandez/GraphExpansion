#pragma once
#include <vector>
#include <iostream>


using namespace std;

class config
{
public:
	config();
	config(vector<int>*, vector<int>*, vector<int>*);
	~config();

	void imprimeConfig();

	vector<int> R;	// Vertices recorridos
	vector<int> P;	// Vertices posibles
	vector<int> X;	// Vertices prohibidos
};

