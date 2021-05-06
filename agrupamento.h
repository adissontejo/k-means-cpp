#ifndef AGRUPAMENTO_H
#define AGRUPAMENTO_H

using namespace std;

#include <bits/stdc++.h>

struct ponto{ // estrutura do ponto
	vector<double> data; // dados do ponto
	int grupo = -1; // cluster do ponto
};

struct cluster{ // estrutura do cluster
	vector<double> data; // dados do centro do cluster
	vector<double> soma; // soma dos dados dos pontos do cluster
	int qt = 0; // quantidade de pontos no cluster
};

extern bool mudanca;
extern bool inicio;

extern vector<ponto> pontos;
extern vector<cluster> clusters;

double agrupamento(int pct = -1);

#endif