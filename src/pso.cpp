#include <bits/stdc++.h>
#include "../include/agrupamento.h"
#include "../include/pso.h"

using namespace std;

#define w 0.5 // constante de inércia
#define c 2.05 // constantes c1 e c2

struct vCluster{ // estrutura do vetor de velocidade
  vector<double> data;
};

struct particula{ // estrutura de uma partícula
  double melhorFO = INFINITY;
  vector<cluster> melhorPos;
  vector<cluster> clustersP;
  vector<vCluster> velocidade;
};

void pso(){ // função que roda o pso
  int n = pontos.size(); // são definidas as variáveis de tamanho
  int d = pontos[0].data.size();
  int k = clusters.size();
  int p = k*d*10; // a quantidade de partículas é definida
  int melhorPt = 0; // variável que guarda a melhor partícula
  clock_t tIni = clock();
  vector<cluster> melhorGrupoDeCluster;
  double melhorFuncaoObjetivo = INFINITY;
  vector<particula> particulas (p); // vetor de partículas
  for(int i = 0; i < p; i++){
    particulas[i].clustersP.resize(k);
    particulas[i].velocidade.resize(k);
    for(int j = 0; j < k; j++){
      particulas[i].velocidade[j].data.resize(d);
    }
  }

  while(clock() - tIni < 10*CLOCKS_PER_SEC){ // enquanto o tempo de 10s não for atingido, o pso é rodado várias vezes
    for(int i = 0; i < p; i++){ // as posições e velocidades das partículas são definidas
      particulas[i].melhorFO = INFINITY;
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
        for(int l = 0; l < d; l++){   
          particulas[i].velocidade[j].data[l] = rand()%10;
        }
      }
    }

    int qt = 0; // variável que conta há quantas iterações não há melhora
    bool melhora; // variável que indica se houve melhora ou não

    while(clock() - tIni < 10*CLOCKS_PER_SEC and qt < 20){ // critério de parada: número máximo de 20 iterações sem melhora e tempo máximo de 10s
      double r1 = (rand()%100 + 1)/100.0; // definição dos valores de r1 e r2
      double r2 = (rand()%100 + 1)/100.0;
      melhora = false;
      for(int i = 0; i < p; i++){ // é calculada a função objetivo para cada partícula
        clusters = particulas[i].clustersP;
        double fo = agrupamento();
        if(fo < particulas[i].melhorFO){ // se o caso atual da partícula for melhor que a melhor posição
          particulas[i].melhorFO = fo; // tal caso é definido como o melhor
          particulas[i].melhorPos = clusters; //
          if(fo < particulas[melhorPt].melhorFO){ // se tal caso for melhor que o melhor de todas as partículas
            melhorPt = i; // a partícula atual é definida como a melhor
            melhora = true;
          }
        }

        for(int j = 0; j < k; j++){ // são atualizadas as posições e velocidades
          for(int l = 0; l < d; l++){
            particulas[i].velocidade[j].data[l] *= w;
            double pbest = particulas[i].melhorPos[j].data[l];
            double gbest = particulas[melhorPt].melhorPos[j].data[l];
            double xAt = particulas[i].clustersP[j].data[l];
            particulas[i].velocidade[j].data[l] += c*r1*(pbest - xAt) + c*r2*(gbest - xAt);
            particulas[i].clustersP[j].data[l] += particulas[i].velocidade[j].data[l];
          }
        }
      }
      if(melhora){
        qt = 0;
      }else{
        qt++;
      }
    }
    if(particulas[melhorPt].melhorFO < melhorFuncaoObjetivo){
      melhorFuncaoObjetivo = particulas[melhorPt].melhorFO;
      melhorGrupoDeCluster = particulas[melhorPt].clustersP;
    }
    melhorPt = 0;
  }
  clusters = melhorGrupoDeCluster;
  agrupamento();
  for(int i = 0; i < n; i++){ // são printados os pontos e seus respectivos grupos
    cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl;
  }
  cout << "Menor media de distancias: " << melhorFuncaoObjetivo << endl;
}