#include <bits/stdc++.h>
#include "../include/agrupamento.h"
#include "../include/kmeans.h"
#include "../include/kmedoids.h"
#include "../include/genetico.h"
#include "../include/pso.h"
#include "../include/grasp1.h"
#include "../include/grasp2.h"

using namespace std;

int main(int argc, char **argv){ // função main que recebe argc e argv como parâmetros
	ios_base::sync_with_stdio(false); cin.tie(0);
	srand (time(NULL));
	
	if(argc < 2){ // caso a quantidade de argumentos seja maior que 2
		cout << "   *** Usage: " << argv[0] << " KMO|PSO|GEN|GRP1|GRP2\n"; // é printada a forma de uso do comando
		exit(0); // o programa é finalizado
	}

	int n, d, k; // quantidade de pontos, dimensão e quantidade de clusters
	cin >> n >> d; // são lidas a quantidade de pontos e a dimensão
	
	pontos.resize(n); // vetor dos pontos é definido com tamanho n

	for(int i = 0; i < n; i++){ // para cada ponto
		// é definido o tamanho do vetor de dados do ponto
		pontos[i].data.resize(d - 1);
		int id;
		cin >> id;
		for(int j = 0; j < d - 1; j++){ // para cada dado do ponto
			cin >> pontos[i].data[j]; // é lido o dado do ponto
		}
	}

	if(argc < 3){ // se a quantidade de argumentos for menor que 3
		k = 3;	// a quantidade de grupos é definida como padrão (3)
	}else{ // se não
		k = atoi(argv[2]); // a quantidade de grupos é definida com o valor do terceiro argumento
	}

	clusters.resize(k); // o vetor de clusters é definido com tamanho k

	if(strcmp(argv[1], "GEN") == 0){ //  caso o segundo argumento seja GEN
		genetico(); // é chamado o algoritmo genético
	}else if(strcmp(argv[1], "PSO") == 0){ // se não, caso o segundo argumento seja PSO
		pso(); // é chamado o algoritmo PSO
	}else if(strcmp(argv[1], "GRP1") == 0){ // se não, caso o segundo argumento seja GRP1
		grasp1(); // é chamado o algoritmo GRASP 1
	}else if(strcmp(argv[1], "GRP2") == 0){ // se não, caso o segundo argumento seja GRP2
		grasp2(); // é chamado o algoritmo GRASP 2
	}else if(strcmp(argv[1], "KMD") == 0){
		kmedoids();
	}else{ // se não
		kmeans(); // é chamado o algoritmo k-means
	}

  return 0;
}

