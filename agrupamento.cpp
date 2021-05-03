#include <bits/stdc++.h>
#include "agrupamento.h"

using namespace std;

vector<ponto> pontos;
vector<cluster> clusters;

bool mudanca, inicio = true;

double calc(ponto a, cluster b){ // função que calcula a distância euclidiana
  double total = 0;
  for(int i = 0; i < a.data.size(); i++){
  	total += pow(a.data[i] - b.data[i], 2);
	}
	return total;
}

double agrupamento(){ // função base que define os grupos dos pontos e retorna a função objetiva de um agrupamento específico
  int n = pontos.size();
  int d = pontos[0].data.size();
  int k = clusters.size();
  for(int i = 0; i < n; i++){  // É calculada a distância de cada ponto para cada centro
		int centro = -1; // variável que guarda o índice do centro mais próximo
		double menor = INFINITY; // variável que guarda o valor da menor distância
		for(int j = 0; j < k; j++){
			double dist = calc(pontos[i], clusters[j]);
			if(dist < menor){ // se a distância recém calculada for menor que a menor distância até então:
				menor = dist; // tal distância é registrada como a menor
				centro = j; // tal centro é registrado como o mais próximo
			}
		}
		int antigo = pontos[i].grupo; // variável que armazena o antigo centro mais próximo do ponto
		if(!inicio and antigo != centro){ //se este não for o primeiro agrupamento e o centro antigo for diferente do atual
			for(int j = 0; j < d; j++){ //os valores de soma do cluster antigo são atualizados
				clusters[antigo].soma[j] -= pontos[i].data[j];
			}
			clusters[antigo].qt--; // a quantidade de pontos é diminuida
		}
		if(inicio or antigo != centro){ // se este for o primeiro agrupamento ou o cluster antigo for diferente do atual
			for(int j = 0; j < d; j++){ // os valores de soma do cluster atual são atualizados
				clusters[centro].soma[j] += pontos[i].data[j];
			}
			clusters[centro].qt++; // a quantidade de pontos é aumentada
			pontos[i].grupo = centro; // o cluster do ponto é atualizado
			mudanca = true; // é registrado que houve mudanças na atual etapa
		}
	}
  double fo = 0;
  for(int i = 0; i < n; i++){
    fo += calc(pontos[i], clusters[pontos[i].grupo])/((double) n);
  }
  return fo;
}
