
/*
  Arquivo usado para agrupar os pontos utilizando
  o algoritmo de Otimização por Enxame de Partículas
  (PSO)
*/

#include <bits/stdc++.h>
#include "../include/agrupamento.h"
#include "../include/pso.h"

using namespace std;

#define w 0.5 // constante de inércia
#define c 2.05 // valor que representa as constantes c1 e c2

struct vCluster{ // estrutura de uma velocidade
  vector<double> data; // dados da velocidade
};

struct particula{ // estrutura de uma partícula
  // melhor caso local da partícula
  double melhorFO = INFINITY;
  // melhor posição da partícula
  vector<cluster> melhorPos;
  // posição atual da partícula
  vector<cluster> clustersP;
  // velocidades da partícula
  vector<vCluster> velocidade;
};

void pso(){ // função que roda o PSO
  int n = pontos.size(); // quantidade de pontos
  int d = pontos[0].data.size(); // dimensão
  int k = clusters.size(); // quantidade de grupos
  int p = k*d*10; // a quantidade de partículas é definida

  clock_t tIni = clock(); // instante de tempo em que a função foi iniciada
  // melhor solução de todas as iterações do PSO
  vector<cluster> melhorGrupoDeCluster;
  // valor da melhor função objetivo de todas as iterações
  double melhorFuncaoObjetivo = INFINITY;
  vector<particula> particulas (p); // o vetor de partículas é definido
  
  for(int i = 0; i < p; i++){  // para cada partícula
    // o vetor de clusters (posição) é definido com tamanho k
    particulas[i].clustersP.resize(k);
    // o vetor de velocidades é definido com tamanho k
    particulas[i].velocidade.resize(k);
    for(int j = 0; j < k; j++){ // para cada velocidade
      // o vetor de dados da velocidade é definido com tamanho d
      particulas[i].velocidade[j].data.resize(d);
    }
  }

  // enquanto o tempo de 10s não for atingido, o PSO é rodado várias vezes
  while(clock() - tIni < 10*CLOCKS_PER_SEC){
    // variável que guarda a melhor partícula da rodada
    int melhorPt = 0;

    for(int i = 0; i < p; i++){ // para cada partícula
      // o valor da melhor função objetivo de cada
      // partícula é definida com valor infinito
      particulas[i].melhorFO = INFINITY;
      // vetor que indica se os diferentes pontos foram escolhidos 
      // para terem seus dados como os dados dos clusters ou não
      vector<bool> usado (n, false);

      for(int j = 0; j < k; j++){ // para cada cluster e cada velocidade
        while(true){
          int x = rand()%n; // é sorteado um ponto (número de 0 a n - 1)
          if(!usado[x]){ // se o ponto sorteado não foi utilizado ainda
            usado[x] = true; // o ponto sorteado é marcado como utilizado
            // os dados do cluster são definidos com 
            // os valores dos dados do ponto sorteado
            particulas[i].clustersP[j].data = pontos[x].data;
            break; // o loop é quebrado
          }
        }

        // o vetor de soma do cluster é zerado
        particulas[i].clustersP[j].soma.resize(d, 0);
        // a quantidade de pontos no cluster é zerada
        particulas[i].clustersP[j].qt = 0;

        // para cada dado da velocidade
        for(int l = 0; l < d; l++){ 
          // a velocidade é definida com um valor aleatório
          particulas[i].velocidade[j].data[l] = rand()%10;
        }
      }
    }

    int qt = 0; // variável que conta há quantas iterações não há melhora

    // critério de parada: número máximo de 20 
    // iterações sem melhora e tempo máximo de 10s
    while(clock() - tIni < 10*CLOCKS_PER_SEC and qt < 20){
      double r1 = (rand()%100 + 1)/100.0; // o valor de r1 é sorteado
      double r2 = (rand()%100 + 1)/100.0; // o valor de r2 é sorteado

      bool melhora = false; // variável que indica se houve melhora ou não

      for(int i = 0; i < p; i++){ // para cada partícula
        // o vetor global de clusters é definido 
        // como o vetor de clusters da partícula
        clusters = particulas[i].clustersP;
        // a função agrupamento é chamada e seu valor de retorno é armazenado
        double fo = agrupamento();

        // se a posição atual da partícula for 
        // melhor que a melhor posição local
        if(fo < particulas[i].melhorFO){
          // o valor da função objetivo recém-calculado
          // é definido como o melhor local
          particulas[i].melhorFO = fo;
          // tal posição é definida como a melhor local
          particulas[i].melhorPos = clusters;

          // se a posição atual da partícula for
          // melhor que a melhor posição global
          if(fo < particulas[melhorPt].melhorFO){
            melhorPt = i; // a partícula atual é definida como a melhor
            melhora = true; // é indicado que houve melhora
          }
        }

        for(int j = 0; j < k; j++){ // para cada cluster e velocidade
          // para cada dado do cluster e da velocidade
          for(int l = 0; l < d; l++){
            // é armazenado o dado da melhor posição local
            double pbest = particulas[i].melhorPos[j].data[l];
            // é armazenado o dado da melhor posição global
            double gbest = particulas[melhorPt].melhorPos[j].data[l];
            // é armazenado o dado da posição atual
            double xAt = particulas[i].clustersP[j].data[l];
            // é calculado o novo dado da velocidade de acordo com a fórmula
            double v = particulas[i].velocidade[j].data[l];
            v = v*w + c*r1*(pbest - xAt) + (c*r2*(gbest - xAt));
            // é incrementado o dado da velocidade 
            // no dado da posição da partícula
            particulas[i].clustersP[j].data[l] += v;
            // a velocidade é atualizada
            particulas[i].velocidade[j].data[l] = v;
          }
        }
      }

      if(melhora){ // se houve melhora 
        qt = 0; // a variável qt é zerada
      }else{ // se não
        qt++; // a variável qt é incrementada
      }
    }

    // se a melhor função objetivo da rodada 
    // for melhor que a de todas as rodadas
    if(particulas[melhorPt].melhorFO < melhorFuncaoObjetivo){
      // a melhor função objetivo da rodada é definida como a melhor de todas
      melhorFuncaoObjetivo = particulas[melhorPt].melhorFO;
      // a posição atual é definida como a melhor de todas
      melhorGrupoDeCluster = particulas[melhorPt].clustersP;
    }
  }

  // o vetor de clusters global é definido como o melhor
  // vetor de clusters do algoritmo realizado
  clusters = melhorGrupoDeCluster;
  agrupamento(); // é refeito o agrupamento dos pontos
  double sol = 0; // valor real da função objetivo

  for(int i = 0; i < n; i++){ // para cada ponto
    // é printado o ponto e seu respectivo grupo
    cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl;
    // é adicionada na função objetivo a distância ponto centro
    sol += calc(pontos[i], clusters[pontos[i].grupo], true)/((double) n);
  }
  // é printada a função objetivo do algoritmo
  cout << "Menor media de distancias: " << sol << endl;
}