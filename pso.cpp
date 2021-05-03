#include <bits/stdc++.h>
#include "agrupamento.h"
#include "pso.h"

using namespace std;

#define w 0.5 // constante de inércia
#define c 2.05 // constantes c1 e c2

struct vCluster{ // estrutura do vetor de velocidade
  vector<double> data;
};

struct particula{ // estrutura de uma partícula
  double melhorFO = INFINITY;
  vector<cluster> clustersP;
  vector<cluster> melhorPos;
  vector<vCluster> velocidade;
};

void pso(){ // função que roda o pso
  int n = pontos.size(); // são definidas as variáveis de tamanho
  int d = pontos[0].data.size();
  int k = clusters.size();
  int p = k*d*10; // a quantidade de partículas é definida
  int melhorPt = 0; // variável que guarda a melhor partícula
  vector<particula> particulas (p); // vetor de partículas

  for(int i = 0; i < p; i++){ // as posições e velocidades das partículas são definidas
    particulas[i].clustersP.resize(k);
    particulas[i].velocidade.resize(k);
    vector<bool> usado (n, false);
    for(int j = 0; j < k; j++){
      while(true){
        int x = rand()%n;
        if(!usado[x]){
          usado[x] = true;
          particulas[i].clustersP[j].data = pontos[x].data;
          break;
        }
      }
      particulas[i].clustersP[j].soma.resize(d, 0);
      particulas[i].clustersP[j].qt = 0;
      particulas[i].velocidade[j].data.resize(d);
      for(int l = 0; l < d; l++){   
        particulas[i].velocidade[j].data[l] = rand()%10;
      }
    }
  }

  for(int i = 0; i < 100; i++){ // critério de parada: número máximo de 100 iterações
    double r1 = (rand()%100 + 1)/100.0; // definição dos valores de r1 e r2
    double r2 = (rand()%100 + 1)/100.0;
    for(int j = 0; j < p; j++){ // é calculada a função objetiva para cada partícula
      clusters = particulas[j].clustersP;
      double fo = agrupamento();
      if(fo < particulas[j].melhorFO){ // se o caso atual da partícula for melhor que a melhor posição
        particulas[j].melhorFO = fo; // tal caso é definido como o melhor
        particulas[j].melhorPos = clusters; //
        if(fo < particulas[melhorPt].melhorFO){ // se tal caso for melhor que o melhor de todas as partículas
          melhorPt = j; // a partícula atual é definida como a melhor
        }
      }

      for(int l = 0; l < k; l++){ // são atualizadas as posições e velocidades
        for(int m = 0; m < d; m++){
          particulas[j].velocidade[l].data[m] *= w;
          double pbest = particulas[j].melhorPos[l].data[m];
          double gbest = particulas[melhorPt].melhorPos[l].data[m];
          double xAt = particulas[j].clustersP[l].data[m];
          particulas[j].velocidade[l].data[m] += c*r1*(pbest - xAt) + c*r2*(gbest - xAt);
          particulas[j].clustersP[l].data[m] += particulas[j].velocidade[l].data[m];
        }
      }
    }
  }

  clusters = particulas[melhorPt].melhorPos;
  agrupamento();
  for(int i = 0; i < n; i++){ // são printados os pontos e seus respectivos grupos
    cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl;
  }
  cout << "Menor media de distancias: " << particulas[melhorPt].melhorFO << endl;
}