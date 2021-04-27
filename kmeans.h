#ifndef KMEANS_H
#define KMEANS_H

#include <bits/stdc++.h>

using namespace std;

struct ponto{ // estrutura do ponto
	vector<double> data; // dados do ponto
	int grupo = -1; // cluster do ponto
};

extern vector<ponto> pontos;

double kmeans(int n, int d, int k);

#endif