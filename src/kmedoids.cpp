/*
  Arquivo usado para agrupar os pontos e definir os clusters
  através do k-medoids, variação do k-means
*/

#include <bits/stdc++.h>
#include "../include/agrupamento.h"
#include "../include/kmedoids.h"

using namespace std;

double kmedoids(int pct){ // função que roda o k-medoids
	int n = pontos.size(); // variável que guarda o valor da quantidade de pontos
	int d = pontos[0].data.size(); // variável que guarda o valor da dimensão
	int k = clusters.size(); // variável que guarda o valor da quantidade de grupos
  
  if(pct != -2){ // código utilizado pelo GRASP para sinalizar que não se deve incializar os clusters
    for(int i = 0; i < k; i++){ // para cada cluster
      clusters[i].soma.resize(d); // o vetor de soma do cluster é definido com tamanho d
    }
    vector<bool> usado (n, false); // vetor que representa se determinados pontos foram usados como centros ou não

    for(int i = 0; i < k; i++){ // para cada cluster
      for(int j = 0; j < d; j++){ // para cada dado do cluster
        clusters[i].soma[j] = 0; // o dado do vetor de soma é zerado
      }
      clusters[i].qt = 0; // o valor da quantidade de pontos no cluster é zerado
      while(true){
        int x = rand()%n; // é sorteado um ponto (número de 0 a n - 1)
        if(!usado[x]){ // se tal ponto ainda não foi escolhido
          usado[x] = true; // o ponto é indicado como usado
          clusters[i].data = pontos[x].data; // o centro do cluster recebe os dados do ponto
          break;
        }
      }
    }
    inicio = true; // é indicado que o algoritmo está no seu início
  }
  
	mudanca = true; // a variável mudanca é setada como true
	double dist; // variável que guarda o valor da função objetivo retornado pela função de agrupamento
  int it = 0; // variável que conta o número de iterações

	while(mudanca and it < 20){ // enquanto há mudanças de cluster nos pontos ou o número de iterações é menor que 20
		if(pct == -2) // caso a função tenha sido chamada pelo GRASP na fase de busca local
      it++; // a variável it é incrementada (método para garantir que não haja loops infinitos)
    mudanca = false; // a variável mudanca é setada como false
		dist = agrupamento((inicio ? pct : -1)); // caso o algoritmo esteja no início, é passada como parâmetro a chance de um ponto escolher o segundo cluster mais próximo
		for(int i = 0; i < k; i++){ // para cada cluster
			for(int j = 0; j < d; j++){ // para cada dado do cluster
        if(clusters[i].qt != 0){ // se a quantidade de pontos for diferente de 0 (forma de previnir divisões por 0)
				  clusters[i].data[j] = (double) clusters[i].soma[j]/clusters[i].qt; // o dado do cluster é atualizado como a média dos dados de seus pontos
        }
			}
		}
		inicio = false; // a váriavel início é setada com valor baixo
	}

  if(pct == -1){ // caso a função não tenha sido chamada pelo GRASP
    for(int i = 0; i < n; i++){ // para cada ponto
      cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl; // é printado o ponto e seu respectivo grupo
    }
    cout << "Menor media de distancias: " << dist << endl; // é printado o valor da função objetivo do algoritmo
  }
  return dist; // é retornado o valor da função objetivo do algoritmo
}