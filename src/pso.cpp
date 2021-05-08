
/*
  Arquivo usado para agrupar os pontos utilizando
  o algoritmo de Otimização por Enxame de Partículas
  (PSO)
*/

#include <bits/stdc++.h>
#include "../include/agrupamento.h"
#include "../include/pso.h"

using namespace std;

#define w 0.5 // valor que representa a constante de inércia
#define c 2.05 // valor que representa as constantes c1 e c2

struct vCluster{ // estrutura de uma velocidade
  vector<double> data; // dados da velocidade
};

struct particula{ // estrutura de uma partícula
  double melhorFO = INFINITY; // variável que guarda o melhor caso local da partícula
  vector<cluster> melhorPos; // variável que guarda a melhor posição da partícula
  vector<cluster> clustersP; // variável que guarda a posição atual da partícula
  vector<vCluster> velocidade; // variável que guarda as velocidades da partícula
};

void pso(){ // função que roda o PSO
  int n = pontos.size(); // variável que guarda o valor da quantidade de pontos
  int d = pontos[0].data.size(); // variável que guarda o valor da dimensão
  int k = clusters.size(); // variável que guarda o valor da quantidade de grupos
  int p = k*d*10; // a quantidade de partículas é definida
  clock_t tIni = clock(); // variável que guarda o instante de tempo em que a função foi iniciada
  vector<cluster> melhorGrupoDeCluster; // variável que guarda a melhor solução de todas as iterações do PSO
  double melhorFuncaoObjetivo = INFINITY; // variável que guarda o valor da melhor função objetivo de todas as iterações
  vector<particula> particulas (p); // o vetor de partículas é definido
  for(int i = 0; i < p; i++){  // para cada partícula
    particulas[i].clustersP.resize(k); // o vetor de clusters (posição) é definido com tamanho k
    particulas[i].velocidade.resize(k); // o vetor de velocidades é definido com tamanho k
    for(int j = 0; j < k; j++){ // para cada velocidade
      particulas[i].velocidade[j].data.resize(d); // o vetor de dados da velocidade é definido com tamanho d
    }
  }

  while(clock() - tIni < 10*CLOCKS_PER_SEC){ // enquanto o tempo de 10s não for atingido, o PSO é rodado várias vezes
    int melhorPt = 0; // variável que guarda a melhor partícula da rodada
    for(int i = 0; i < p; i++){ // para cada partícula
      particulas[i].melhorFO = INFINITY; // o valor da melhor função objetivo de cada partícula é definida com valor infinito
      vector<bool> usado (n, false); // vetor que indica se os diferentes pontos foram escolhidos para terem seus dados como os dados dos clusters ou não
      for(int j = 0; j < k; j++){ // para cada cluster e cada velocidade
        while(true){
          int x = rand()%n; // é sorteado um ponto (número de 0 a n - 1)
          if(!usado[x]){ // se o ponto sorteado não foi utilizado ainda
            usado[x] = true; // o ponto sorteado é marcado como utilizado
            particulas[i].clustersP[j].data = pontos[x].data; // os dados do cluster são definidos com os valores dos dados do ponto sorteado
            break; // o loop é quebrado
          }
        }
        particulas[i].clustersP[j].soma.resize(d, 0); // o vetor de soma do cluster é zerado
        particulas[i].clustersP[j].qt = 0; // a quantiadde de pontos no cluster é zerada
        for(int l = 0; l < d; l++){ // para cada dado da velocidade
          particulas[i].velocidade[j].data[l] = rand()%10; // a velocidade é definida com um valor aleatório
        }
      }
    }

    int qt = 0; // variável que conta há quantas iterações não há melhora

    while(clock() - tIni < 10*CLOCKS_PER_SEC and qt < 20){ // critério de parada: número máximo de 20 iterações sem melhora e tempo máximo de 10s
      double r1 = (rand()%100 + 1)/100.0; // o valor de r1 é sorteado
      double r2 = (rand()%100 + 1)/100.0; // o valor de r2 é sorteado
      bool melhora = false; // variável que indica se houve melhora ou não
      for(int i = 0; i < p; i++){ // para cada partícula
        clusters = particulas[i].clustersP; // o vetor global de clusters é definido como o vetor de clusters da partícula
        double fo = agrupamento(); // a função agrupamento é chamada e seu valor de retorno é armazenado
        if(fo < particulas[i].melhorFO){ // se a posição atual da partícula for melhor que a melhor posição local
          particulas[i].melhorFO = fo; // o valor da função objetivo recém-calculado é definido como o melhor local
          particulas[i].melhorPos = clusters; // tal posição é definida como a melhor local
          if(fo < particulas[melhorPt].melhorFO){ // se a posição atual da partícula for melhor que a melhor posição global
            melhorPt = i; // a partícula atual é definida como a melhor
            melhora = true; // é indicado que houve melhora
          }
        }

        for(int j = 0; j < k; j++){ // para cada cluster e velocidade
          for(int l = 0; l < d; l++){ // para cada dado do cluster e da velocidade
            particulas[i].velocidade[j].data[l] *= w; // o dado da velocidade atual é multiplicado pela inércia
            double pbest = particulas[i].melhorPos[j].data[l]; // é armazenado o dado da melhor posição local
            double gbest = particulas[melhorPt].melhorPos[j].data[l]; // é armazenado o dado da melhor posição global
            double xAt = particulas[i].clustersP[j].data[l]; // é armazenado o dado da posição atual
            particulas[i].velocidade[j].data[l] += c*r1*(pbest - xAt) + c*r2*(gbest - xAt); // é calculado o novo dado da velocidade de acordo com a fórmula v*w + c1*r1*pbest + c2*r2*gbest
            particulas[i].clustersP[j].data[l] += particulas[i].velocidade[j].data[l]; // é incrementado o dado da velocidade no dado da posição da partícula
          }
        }
      }
      if(melhora){ // se houve melhora 
        qt = 0; // a variável qt é zerada
      }else{ // se não
        qt++; // a variável qt é incrementada
      }
    }
    if(particulas[melhorPt].melhorFO < melhorFuncaoObjetivo){ // se a melhor função objetivo da rodada for melhor que a de todas as rodadas
      melhorFuncaoObjetivo = particulas[melhorPt].melhorFO; // a melhor função objetivo da rodada é definida como a melhor de todas
      melhorGrupoDeCluster = particulas[melhorPt].clustersP; // a posição atual é definida como a melhor de todas
    }
  }
  clusters = melhorGrupoDeCluster; // o vetor de clusters global é definido como o melhor vetor de clusters do algoritmo realizado
  agrupamento(); // é refeito o agrupamento dos pontos
  for(int i = 0; i < n; i++){ // para cada ponto
    cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl; // é printado o ponto e seu respectivo grupo
  }
  cout << "Menor media de distancias: " << melhorFuncaoObjetivo << endl; // é printado o valor da função objetivo
}