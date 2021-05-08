#include <bits/stdc++.h>
#include "../include/agrupamento.h"
#include "../include/kmeans.h"

using namespace std;

#define MIN 0
#define MAX 100000

void kmeans(){
	int n = pontos.size(); // são definidas as variáveis de tamanho
	int d = pontos[0].data.size();
	int k = clusters.size();
	for(int i = 0; i < k; i++){
		clusters[i].soma.resize(d);
		clusters[i].data.resize(d);
	}

	for(int i = 0; i < k; i++){ // definição dos clusters
		for(int j = 0; j < d; j++){ // o vetor de soma dos dados dos pontos do cluster é zerado
			clusters[i].soma[j] = 0;
			clusters[i].data[j] = rand()%(MAX - MIN) + MIN;
		}
		clusters[i].qt = 0;
	}

	inicio = true;
	mudanca = true;
	double dist;

	while(mudanca){ // enquanto há mudanças de cluster nos pontos
		mudanca = false;
		dist = agrupamento();
		for(int i = 0; i < k; i++){ // os centros dos clusters são atualizados para a média dos dados
			for(int j = 0; j < d; j++){
				if(clusters[i].qt != 0){
					clusters[i].data[j] = (double) clusters[i].soma[j]/clusters[i].qt;
				}
			}
		}
		inicio = false; // a váriavel início é setada com valor baixo
	}

	for(int i = 0; i < n; i++){
		cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl;
	}
	cout << "Menor media de distancias: " << dist << endl;
}