#include <bits/stdc++.h>
#include "agrupamento.h"
#include "kmeans.h"

using namespace std;

void kmeans(){
	int n = pontos.size(); // são definidas as variáveis de tamanho
	int d = pontos[0].data.size();
	int k = clusters.size();
	double fo = INFINITY;
	vector<ponto> melhorSolucao; // variável que armazena a melhor solução possível
	for(int i = 0; i < k; i++){
		clusters[i].soma.resize(d);
	}
	for(int cont = 0; cont < 100; cont++){

		vector<bool> usado (n, false); // vetor que representa se determinados pontos foram usados como centros ou não

		for(int i = 0; i < k; i++){ // definição dos clusters
			for(int j = 0; j < d; j++){ // o vetor de soma dos dados dos pontos do cluster é zerado
				clusters[i].soma[j] = 0;
			}
			clusters[i].qt = 0;
			while(true){
				int x = rand()%n; // é gerado um número aleatório de um ponto
				if(!usado[x]){ // se os dados de tal ponto ainda não foram escolhidos como centro:
					usado[x] = true; // tais dados são escolhidos
					clusters[i].data = pontos[x].data; // o centro do cluster recebe os dados do ponto
					break;
				}
			}
		}

		inicio = true;
		mudanca = true;
		double dist;

		while(mudanca){ // enquanto há mudanças de cluster nos pontos
			mudanca = false;
			dist = agrupamento();
			for(int i = 0; i < k; i++){ // os centros dos clusters são atualizados para a média dos dados
				for(int j = 0; j < d; j++){
					clusters[i].data[j] = (double) clusters[i].soma[j]/clusters[i].qt;
				}
			}
			inicio = false; // a váriavel início é setada com valor baixo
		}

		if(dist < fo){ // se a média das distâncias deste caso for menor que a menor registrada
			fo = dist; // esta se torna a menor
			melhorSolucao = pontos;
		}
	}
	for(int i = 0; i < n; i++){
		cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl;
	}
	cout << "Menor media de distancias: " << fo << endl;
}