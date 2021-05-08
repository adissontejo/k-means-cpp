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

void kmeans(){ // função que roda o kmeans básico
	int n = pontos.size(); // variável que guarda o valor da quantiadade de pontos
	int d = pontos[0].data.size(); // variável que guarda o valor da dimensão
	int k = clusters.size(); // variável que guarda a quantidade de grupos
	for(int i = 0; i < k; i++){ // para cada cluster
		clusters[i].soma.resize(d); // o tamanho do vetor soma é definido como o valor da dimensão
		clusters[i].data.resize(d); // o tamanho do vetor data é definido como o valor da dimensão
	}

	for(int i = 0; i < k; i++){ // para cada cluster
		for(int j = 0; j < d; j++){ // para cada dado do cluster
			clusters[i].soma[j] = 0; // o dado de soma é definido como 0
			clusters[i].data[j] = rand()%(MAX - MIN) + MIN; // o dado do centro é definido com um valor aleatório entre MIN e MAX
		}
		clusters[i].qt = 0; // a quantidade de pontos no cluster é definida como 0
	}

	inicio = true; // é indicado que este é o início do algoritmo
	mudanca = true; // a variável global mudanca é definida como true
	double dist; // variável que guarda o valor da função objetivo retornada pela função de agrupamento

	while(mudanca){ // enquanto há mudanças de cluster nos pontos
		mudanca = false; // no início do loop, a variável mudanca é definida como false
		dist = agrupamento(); // é chamada a função de agrupamento e o valor retornado é armazenado
		for(int i = 0; i < k; i++){ // para cada cluster
			for(int j = 0; j < d; j++){ // para cada dado do cluster e do ponto
				if(clusters[i].qt != 0){ // se a quantidade de pontos no cluster for diferente de 0 (maneira de evitar divisões por 0)
					clusters[i].data[j] = (double) clusters[i].soma[j]/clusters[i].qt; // o dado do cluster é definido como a média dos dados de cada ponto neste
				}
			}
		}
		inicio = false; // a váriavel início é setada com valor baixo
	}

	for(int i = 0; i < n; i++){ // para cada ponto
		cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl; // é printado o ponto e seu respectivo grupo
	}
	cout << "Menor media de distancias: " << dist << endl; // é printado o valor da função objetivo
}