/*
  Arquivo usado para agrupar os pontos e definir os clusters
  através do k-medoids, variação do k-means
*/

#include <bits/stdc++.h>
#include "../include/agrupamento.h"
#include "../include/kmedoids.h"

using namespace std;

double kmedoids(int pct){ // função que roda o k-medoids
	int n = pontos.size(); // quantidade de pontos
	int d = pontos[0].data.size(); // dimensão
	int k = clusters.size(); // quantidade de grupos
  
  // código utilizado pelo GRASP para sinalizar
  // que não se deve incializar os clusters
  if(pct != -2){
    for(int i = 0; i < k; i++){ // para cada cluster
      // o vetor de soma do cluster é definido com tamanho d
      clusters[i].soma.resize(d);
    }

    // vetor que representa se determinados pontos
    // foram usados como centros ou não
    vector<bool> usado (n, false);

    for(int i = 0; i < k; i++){ // para cada cluster
      for(int j = 0; j < d; j++){ // para cada dado do cluster
        clusters[i].soma[j] = 0; // o dado do vetor de soma é zerado
      }

      // o valor da quantidade de pontos no cluster é zerado
      clusters[i].qt = 0;

      while(true){
        int x = rand()%n; // é sorteado um ponto (número de 0 a n - 1)
        if(!usado[x]){ // se tal ponto ainda não foi escolhido
          usado[x] = true; // o ponto é indicado como usado
          // o centro do cluster recebe os dados do ponto
          clusters[i].data = pontos[x].data;
          break;
        }
      }
    }
    inicio = true; // é indicado que o algoritmo está no seu início
  }
  
	mudanca = true; // a variável mudanca é setada como true
	double dist; // valor da função objetivo retornado pela função de agrupamento
  int it = 0; // variável que conta o número de iterações

  // enquanto há mudanças de cluster nos pontos
  // ou o número de iterações é menor que 20 (GRASP)
	while(mudanca and it < 20){
    // caso a função tenha sido chamada pelo GRASP na fase de busca local
		if(pct == -2){
      // a variável it é incrementada
      // (método para garantir que não haja loops infinitos)
      it++;
    }
    
    mudanca = false; // a variável mudanca é setada como false

    // caso o algoritmo esteja no início, é passada como parâmetro 
    // a chance de um ponto escolher o segundo cluster mais próximo
		dist = agrupamento((inicio ? pct : -1));

		for(int i = 0; i < k; i++){ // para cada cluster
			for(int j = 0; j < d; j++){ // para cada dado do cluster
        // se a quantidade de pontos for diferente de 0
        // (forma de previnir divisões por 0)
        if(clusters[i].qt != 0){
          // o dado do cluster é atualizado como a média dos dados de seus pontos
				  clusters[i].data[j] = (double) clusters[i].soma[j]/clusters[i].qt;
        }
			}
		}

		inicio = false; // a váriavel início é setada com valor baixo
	}

  if(pct == -1){ // caso a função não tenha sido chamada pelo GRASP
    for(int i = 0; i < n; i++){ // para cada ponto
      // é printado o ponto e seu respectivo grupo
      cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl;
    }
    // é printada a função objetivo do algoritmo
    cout << "Menor soma de distancias: " << dist << endl;
  }

  return dist; // é retornado o valor da função objetivo do algoritmo
}