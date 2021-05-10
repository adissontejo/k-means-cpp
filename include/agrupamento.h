/*
	Arquivo header da função de agrupamento
*/

#ifndef AGRUPAMENTO_H
#define AGRUPAMENTO_H

using namespace std;

#include <bits/stdc++.h>

struct ponto{ // estrutura de um ponto
	vector<double> data; // dados do ponto
	int grupo = -1; // cluster do ponto
};

struct cluster{ // estrutura de um cluster
	vector<double> data; // dados do centro do cluster
	vector<double> soma; // soma dos dados dos pontos do cluster
	int qt = 0; // quantidade de pontos no cluster
};

// a variável mudanca definida no arquivo agrupamento.cpp é globalizada
extern bool mudanca;
// a variável inicio definida no arquivo agrupamento.cpp é globalizada
extern bool inicio;

// o vetor de pontos definido no arquivo agrupamento.cpp é globalizado
extern vector<ponto> pontos;
// o vetor de clusters definido no arquivo agrupamento.cpp é globalizado
extern vector<cluster> clusters;

// a função de cálculo de distância é definida
double calc(ponto a, cluster b, bool raiz = false);
double agrupamento(int pct = -1); // a função de agrupamento é definida

#endif