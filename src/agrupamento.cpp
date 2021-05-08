/*
	Arquivo usado como base para todos os outros, pois este separa 
	os pontos nos clusters pré-definidos de acordo com a distância
	dos pontos aos centros dos clusters
*/

#include <bits/stdc++.h>
#include "../include/agrupamento.h"

using namespace std;

vector<ponto> pontos; // vetor global que guarda todos os pontos que serão lidos na entrada
vector<cluster> clusters; // vetor global que guarda todos os clusters/centros

bool mudanca, inicio = true; // variáveis globais usadas pelo k-means e k-medoids que informam respectivamente se houve mudança de grupos nos pontos e se é a primeira iteração do algoritmo

double calc(ponto a, cluster b){ // função que calcula a distância euclidiana entre um ponto e um cluster
  double total = 0; // variável que guarda o valor total da distância
  for(int i = 0; i < a.data.size(); i++){ // para cada dado do ponto
  	total += pow(a.data[i] - b.data[i], 2); // é adicionado ao total o quadrado da subtração dos dados
	}
	return total; // é retornada a distância (ao quadrado) para comparação
}

double agrupamento(int pct){ // função base que define os grupos dos pontos e retorna a função objetiva de um agrupamento específico
  int n = pontos.size(); // variável que guarda o valor da quantidade de pontos
  int d = pontos[0].data.size(); // variável que guarda o valor da dimensão
  int k = clusters.size(); // variável que guarda o valor da quantidade de grupos
  for(int i = 0; i < n; i++){  // é calculada a distância de cada ponto para cada centro
		int centro = -1; // variável que guarda o índice do centro mais próximo
		int centro2 = -1; // variável que guarda o valor do segundo centro mais próximo
		double menor = INFINITY; // variável que guarda o valor da menor distância
		double segundoMenor = INFINITY; // variável que guarda o valor da segunda menor distância
		for(int j = 0; j < k; j++){ // para cada cluster existente
			double dist = calc(pontos[i], clusters[j]); // é calculada a distância ponto-centro
			if(dist < menor){ // se a distância recém calculada for menor que a menor distância até então:
				centro2 = centro; // a distância antiga é registrada como a segunda menor
				segundoMenor = menor; // o centro antigo é registrado como o segundo mais próximo
				menor = dist; // tal distância é registrada como a menor
				centro = j; // tal centro é registrado como o mais próximo
			}else if(dist < segundoMenor){ // se não, e se a distância recém calculada for menor que a segunda menor distância
				segundoMenor = dist; // tal distância é definida como a segunda menor
				centro2 = j; // tal centro é definido como o segundo mais próximo
			}
		}
		if(pct > 0){ // se a porcentagem de escolher o segundo centro mais próximo for maior que 0 (recurso usado pelo grasp)
			int r = rand()%100; // é sorteado um número
			if(r < pct){ // se este número estiver dentro da porcentagem
				centro = centro2; // o segundo centro mais próximo é escolhido
			}
		}
		int antigo = pontos[i].grupo; // variável que armazena o antigo centro mais próximo do ponto
		if(!inicio and antigo != centro){ //se este não for o primeiro agrupamento e o centro antigo for diferente do atual
			for(int j = 0; j < d; j++){ // para cada dado do ponto e do cluster
				clusters[antigo].soma[j] -= pontos[i].data[j]; // o valor de soma do cluster antigo é atualizado 
			}
			clusters[antigo].qt--; // a quantidade de pontos é diminuida
		}
		if(inicio or antigo != centro){ // se este for o primeiro agrupamento ou o cluster antigo for diferente do atual
			for(int j = 0; j < d; j++){ // para cada dado do ponto e do cluster
				clusters[centro].soma[j] += pontos[i].data[j]; // o valor de soma do cluster atual é atualizado
			}
			clusters[centro].qt++; // a quantidade de pontos é aumentada
			pontos[i].grupo = centro; // o cluster do ponto é atualizado
			mudanca = true; // é registrado que houve mudanças na etapa atual
		}
	}
  double fo = 0; // variável que guarda o valor da função objetivo
  for(int i = 0; i < n; i++){ // para cada ponto
    fo += calc(pontos[i], clusters[pontos[i].grupo])/((double) n); // é adicionada a distância ponto-cluster no valor da função objetivo
  }
  return fo; // é retornado o valor da função objetivo
}
