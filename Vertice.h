#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Vertice
{
public:
	Vertice(int,int);
	Vertice();
	~Vertice();

	int getNum() { return num; }
	void updateRelative(int);

	void printrel();

//private:
	int num;
	int prof;
	bool expandido = false;
	vector<int> relVertices;
	vector<int> restVertices;
	vector<int> family;
};

