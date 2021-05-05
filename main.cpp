#include <bits/stdc++.h>
#include "agrupamento.h"
#include "kmeans.h"
#include "genetico.h"
#include "pso.h"

using namespace std;

int main(int argc, char **argv){
	ios_base::sync_with_stdio(false); cin.tie(0);
	srand (time(NULL));
	
	if(argc < 2){
		cout << "   *** Usage: " << argv[0] << " KMO|PSO|GEN\n";
		exit(0); 
	}

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
	clusters.resize(k);

	if(strcmp(argv[1], "GEN") == 0){ // é escolhido o algoritmo de acordo com o argv
		genetico();
	}else if(strcmp(argv[1], "PSO") == 0){
		pso();
	}else{
		kmeans();
	}

  return 0;
}

