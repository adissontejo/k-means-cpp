/*
	Arquivo usado para agrupar os pontos e definir os clusters
	através do k-means básico
*/

#include <bits/stdc++.h>
#include "../include/agrupamento.h"
#include "../include/kmeans.h"

using namespace std;

#define MIN 0 // valor mínimo de um dado
#define MAX 100000 // valor máximo de um dado

double kmeans(int pct){ // função que roda o kmeans básico
	int n = pontos.size(); // quantiadade de pontos
	int d = pontos[0].data.size(); // dimensão
	int k = clusters.size(); // quantidade de grupos

	if(pct != -2){
		for(int i = 0; i < k; i++){ // para cada cluster
			// o tamanho do vetor soma é definido como o valor da dimensão
			clusters[i].soma.resize(d);
			// o tamanho do vetor data é definido como o valor da dimensão
			clusters[i].data.resize(d);
		}

		for(int i = 0; i < k; i++){ // para cada cluster
			for(int j = 0; j < d; j++){ // para cada dado do cluster
				clusters[i].soma[j] = 0; // o dado de soma é definido como 0
				// o dado do centro é definido com um valor aleatório entre MIN e MAX
				clusters[i].data[j] = rand()%(MAX - MIN) + MIN;
			}
			clusters[i].qt = 0; // a quantidade de pontos no cluster é definida como 0
		}

		inicio = true; // é indicado que este é o início do algoritmo
	}

	mudanca = true; // a variável global mudanca é definida como true
	double dist; // valor da função objetivo retornada pela função de agrupamento
	int it = 0;

	while(mudanca and it < 20){ // enquanto há mudanças de cluster nos pontos
		if(pct == -2){
			it++;
		}
		// no início do loop, a variável mudanca é definida como false
		mudanca = false;
		// é chamada a função de agrupamento e o valor retornado é armazenado
		dist = agrupamento((inicio ? pct : -1));

		for(int i = 0; i < k; i++){ // para cada cluster
			for(int j = 0; j < d; j++){ // para cada dado do cluster e do ponto
				// se a quantidade de pontos no cluster  for diferente
				// de 0 (maneira de evitar divisões por 0)
				if(clusters[i].qt != 0){
					// o dado do cluster é definido como a média
					// dos dados de cada ponto neste
					clusters[i].data[j] = (double) clusters[i].soma[j]/clusters[i].qt;
				}
			}
		}

		inicio = false; // a váriavel início é setada com valor baixo
	}

	if(pct == -1){
		for(int i = 0; i < n; i++){ // para cada ponto
			// é printado o ponto e seu respectivo grupo
			cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl;
		}
		// é printada a função objetivo do algoritmo
		cout << "Menor soma de distancias: " << dist << endl;
	}

	return dist;
}