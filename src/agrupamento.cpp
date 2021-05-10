/*
	Arquivo usado como base para todos os outros, pois este separa 
	os pontos nos clusters pré-definidos de acordo com a distância
	dos pontos aos centros dos clusters
*/

#include <bits/stdc++.h>
#include "../include/agrupamento.h"

using namespace std;

vector<ponto> pontos; // vetor global dos pontos que serão lidos na entrada
vector<cluster> clusters; // vetor global dos clusters/centros

// variáveis globais utilizadas pelo k-means e k-medoids
bool mudanca; // indica se houve mudança de grupo em algum ponto
bool inicio = true; // indica se o algoritmo está no início

// calcula a distância euclidiana entre um ponto e um centro
double calc(ponto a, cluster b, bool raiz){
  double total = 0; // valor total da distância
  for(int i = 0; i < a.data.size(); i++){ // para cada dado do ponto
  	// é adicionado ao total o quadrado da subtração dos dados
		total += pow(a.data[i] - b.data[i], 2);
	}
	if(raiz){ // caso tenha sido requisitada a raíz do total para print
		return sqrt(total);
	}
	return total; // é retornada a distância (ao quadrado) para comparação
}

// define os grupos dos pontos e retorna a função
// objetivo de um agrupamento específico
double agrupamento(int pct){ 
  int n = pontos.size();         // quantidade de pontos
  int d = pontos[0].data.size(); // dimensão
  int k = clusters.size();       // quantidade de grupos
  
	for(int i = 0; i < n; i++){   //para cada ponto
		int centro = -1;   // índice do centro mais próximo
		int centro2 = -1;  // índice do segundo centro mais próximo
		double menor = INFINITY;         // menor distância
		double segundoMenor = INFINITY;  // segunda menor distância

		for(int j = 0; j < k; j++){ // para cada cluster existente
			// é calculada a distância ponto-centro
			double dist = calc(pontos[i], clusters[j]);
			// se a distância recém calculada for menor que a menor até então:
			if(dist < menor){
				// a distância antiga é registrada como a segunda menor
				centro2 = centro;
				// o centro antigo é registrado como o segundo mais próximo
				segundoMenor = menor;
				menor = dist; // tal distância é registrada como a menor
				centro = j;   // tal centro é registrado como o mais próximo

				// se não, e se a distância recém calculada
				// for menor que a segunda menor distância
			}else if(dist < segundoMenor){
				segundoMenor = dist; // tal distância é definida como a segunda menor
				centro2 = j; // tal centro é definido como o segundo mais próximo
			}
		}

		 // se a porcentagem de chance de escolher o segundo centro mais próximo
		 // for maior que 0 (recurso usado pelo grasp)
		if(pct > 0){ 
			int r = rand()%100; // é sorteado um número
			if(r < pct){ // se este número estiver dentro da porcentagem
				centro = centro2; // o segundo centro mais próximo é escolhido
			}
		}

		int antigo = pontos[i].grupo; // antigo centro mais próximo do ponto
		
		// se esta não for a primeira iteração
		// e o centro antigo for diferente do atual
		if(!inicio and antigo != centro){
			for(int j = 0; j < d; j++){ // para cada dado do ponto e do cluster
				// o valor de soma do cluster antigo é atualizado
				clusters[antigo].soma[j] -= pontos[i].data[j]; 
			}

			clusters[antigo].qt--; // a quantidade de pontos é diminuida
		}

		// se este for o primeiro agrupamento ou
		// o cluster antigo for diferente do atual
		if(inicio or antigo != centro){
			for(int j = 0; j < d; j++){ // para cada dado do ponto e do cluster
				// o valor de soma do cluster atual é atualizado
				clusters[centro].soma[j] += pontos[i].data[j];
			}

			clusters[centro].qt++; // a quantidade de pontos é aumentada
			pontos[i].grupo = centro; // o cluster do ponto é atualizado
			mudanca = true; // é registrado que houve mudanças na etapa atual
		}
	}
  double fo = 0; // valor da função objetivo
  for(int i = 0; i < n; i++){ // para cada ponto
		// é adicionada a distância ponto-cluster no valor da função objetivo
    fo += calc(pontos[i], clusters[pontos[i].grupo])/((double) n);
  }
  return fo; // é retornado o valor da função objetivo
}
