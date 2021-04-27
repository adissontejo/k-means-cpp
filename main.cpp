#include <bits/stdc++.h>
#include "kmeans.h"

using namespace std;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	srand (time(NULL));

	int n, d, k; // quantidade de pontos, dimensão e quantidade de clusters
	cin >> n >> d; // são lidas a quantidade de pontos, a dimensão e a quantidade de clusters
	
	pontos.resize(n); // vetor dos pontos é definido com tamanho n

	for(int i = 0; i < n; i++){ // são lidos n pontos com d dados cada
		pontos[i].data.resize(d); // é definido o tamanho do vetor de dados do ponto
		for(int j = 0; j < d; j++){
			cin >> pontos[i].data[j];
		}
	}

	cin >> k; // é lida a quantidade de clusters

	double menor = INFINITY; // vetor que guarda a menor média das dinstâncias entre ponto e centro
	vector<ponto> melhor; // vetor que guarda o melhor cenário de divisão do k-means

	for(int i = 0; i < 100; i++){ // o k-means é executado 100 vezes e permanece o melhor cenário
		double media = kmeans(n, d, k); // É chamada a função que roda o algoritmo k-means
		if(media < menor){ // se a média das distâncias for menor que a até então menor média
			menor = media; // tal média se torna a menor média
			melhor = pontos; // tal cenário se torna o melhor cenário
		}
	}

	vector<int> qt (k, 0);

	for(int i = 0; i < n; i++){ // são printados os pontos e seus respectivos clusters
		cout << "Ponto " << i << " >> Cluster " << melhor[i].grupo << endl;
		qt[melhor[i].grupo]++;
	}
	cout << endl;
	for(int i = 0; i < k; i++){ // são printados os clusters e suas quantidades de pontos
		cout << "Cluster " << i << " >> " << qt[i] << " Pontos\n";
	}

  return 0;
}

