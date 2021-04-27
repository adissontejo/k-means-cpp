#include <bits/stdc++.h>
#include "kmeans.h"

using namespace std;

vector<ponto> pontos;
struct cluster{ // estrutura do cluster
	vector<double> data; // dados do centro do cluster
	vector<double> soma; // soma dos dados dos pontos do cluster
	int qt = 0; // quantidade de pontos no cluster
};

double calc(ponto a, cluster b){ // função que calcula a distância euclidiana
  double total = 0;
  for(int i = 0; i < a.data.size(); i++){
  	total += pow(a.data[i] - b.data[i], 2);
	}
	return total;
}

double kmeans(int n, int d, int k){ // função que roda o k-means

	bool mudanca = true; // se houve mudança de grupos nos pontos ou não
	bool inicio = true; // se é o primeiro agrupamento realizado ou não
  double media = 0; // variável que guarda a média das distâncias entre pontos seus centros
	vector<cluster> clusters (k); // vetor dos clusters
	vector<bool> usado (n, false); // vetor que representa se determinados pontos foram usados como centros ou não

	for(int i = 0; i < k; i++){ // definição dos clusters
		clusters[i].soma.resize(d, 0); // o vetor de soma dos dados dos pontos do cluster é zerado
		clusters[i].qt = 0;
		while(true){
			int n = rand()%pontos.size(); // É gerado um número aleatório de um ponto
			if(!usado[i]){ // se os dados de tal ponto ainda não foram escolhidos como centro:
				usado[i] = true; // tais dados são escolhidos
				clusters[i].data = pontos[n].data; // o centro do cluster recebe os dados do ponto
				break;
			}
		}
	}

	while(mudanca){ // enquanto há mudanças de cluster nos pontos
		mudanca = false;
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
		for(int i = 0; i < k; i++){ // os centros dos clusters são atualizados para a média dos dados
			for(int j = 0; j < d; j++){
				clusters[i].data[j] = (double) clusters[i].soma[j]/clusters[i].qt;
			}
		}
		inicio = false; // a váriavel início é setada com valor baixo
	}
	for(int i = 0; i < n; i++){
		media += (double) calc(pontos[i], clusters[pontos[i].grupo])/n; // é calculada a média das distâncias
	}
	return media;
}