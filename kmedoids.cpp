#include <bits/stdc++.h>
#include "agrupamento.h"

using namespace std;

double kmedoids(int pct){
	int n = pontos.size(); // são definidas as variáveis de tamanho
	int d = pontos[0].data.size();
	int k = clusters.size();
  
  if(pct != -2){ // código utilizado para sinalizar que não se deve incializar os clusters
    for(int i = 0; i < k; i++){
      clusters[i].soma.resize(d);
    }
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
  }
  
	mudanca = true;
	double dist;
  int it = 0;

	while(mudanca and it < 20){ // enquanto há mudanças de cluster nos pontos
		if(pct == -2) // prevenção para evitar loops no grasp
      it++;
    mudanca = false;
		dist = agrupamento((inicio ? pct : -1));
		for(int i = 0; i < k; i++){ // os centros dos clusters são atualizados para a média dos dados
			for(int j = 0; j < d; j++){
        if(clusters[i].qt != 0){
				  clusters[i].data[j] = (double) clusters[i].soma[j]/clusters[i].qt;
        }
			}
		}
		inicio = false; // a váriavel início é setada com valor baixo
	}

  if(pct == -1){
    for(int i = 0; i < n; i++){
      cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl;
    }
    cout << "Menor media de distancias: " << dist << endl;
  }
  return dist;
}