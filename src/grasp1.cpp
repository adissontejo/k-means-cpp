/*
  Arquivo usado para agrupar os pontos utilizando
  o algoritmo GRASP (Versão 1)
*/

#include <bits/stdc++.h>
#include "../include/agrupamento.h"
#include "../include/kmedoids.h"
#include "../include/kmeans.h"
#include "../include/grasp1.h"

using namespace std;

#define tenSeconds 10*CLOCKS_PER_SEC

void grasp1(){ // função que roda o grasp 1
  int n = pontos.size();         // quantidade de pontos
  int d = pontos[0].data.size(); // dimensão
  int k = clusters.size();       // quantidade de clusters
  
  double melhorDist = INFINITY; // melhor distância de todas as iterações
  vector<ponto> melhorSolucao;  // melhor solução de todas as iterações
  // melhor definição de clusters de todas as iterações
  vector<cluster> melhoresClusters;
  clock_t tIni = clock(); // instante de tempo em que a função foi iniciada
  // porcentagem de chance de o algoritmo de agrupamento
  // escolher o segundo centro mais próximo para os pontos
  int pct = 0;

  while(clock() - tIni < tenSeconds){ // enquanto o tempo limite não é atingido
    int it = 0; // quantidade de iterações do algoritmo

    // enquanto o número de iterações e o tempo não atingem o limite
    while(it < pct + 10 and clock() - tIni < tenSeconds){
      // o kmedoids com uma porcentagem pct de chance de escolher o
      // segundo cluster mais próximo é executado como construção
      double dist = kmeans(pct);
      vector<ponto> solucaoAtual = pontos; // solução atualmente usada
      vector<cluster> clustersAtuais = clusters; // clusters atualmente usados
      // valor da função objetivo da solução atualmente usada
      double distAtual = dist;
      // variável que indica se houve melhora na busca local ou não
      bool melhora = true;
      // enquanto há melhora e o tempo limite não é atingido
      while(melhora and clock() - tIni < tenSeconds){
        melhora = false; // a variável melhora é setada como false
        int lista[n]; // a lista que será bagunçada e aleatoriezada é gerada
        
        for(int i = 0; i < n; i++){ // para cada ponto
          lista[i] = i; // o valor i da lista é definido como o valor do índice
        }

        for(int i = 0; i < n; i++){ // para cada ponto
          // o valor i da lista é trocado com outro valor aleatório da lista
          swap(lista[i], lista[rand()%n]);
        }

        // para cada ponto, com um máximo de 50 iterações
        for(int i = 0; i < min(n, 50); i++){
          int novoGrupo = rand()%k; // um novo grupo para o ponto é sorteado
          int p = lista[i]; // índice do ponto
          int antigo = pontos[p].grupo; // antigo grupo do ponto

          // enquanto o novo grupo sorteado é igual ao grupo antigo
          while(novoGrupo == antigo){
            novoGrupo = rand()%k; // um novo grupo é sorteado
          }

          // o grupo do ponto é definido como o grupo sorteado
          pontos[p].grupo = novoGrupo;
          // a quantidade de pontos no grupo antigo é diminuida
          clusters[antigo].qt--;
          // a quantidade de pontos no novo grupo é aumentada
          clusters[novoGrupo].qt++;
          
          for(int j = 0; j < d; j++){ // para cada dado do ponto e do cluster
            // o dado do ponto é removido do dado da soma do grupo antigo
            clusters[antigo].soma[j] -= pontos[p].data[j];
            // quantidade de pontos do cluster antigo
            double qtPontos = clusters[antigo].qt;
            // se a quantidade de pontos do cluster antigo for
            // diferente de 0 (como prevenção de divisões por 0)
            if(qtPontos != 0){
              // o dado do centro do cluster é definido como
              // a média dos dados de seus pontos
              clusters[antigo].data[j] = clusters[antigo].soma[j]/qtPontos;
            }

            //  quantidade de pontos do novo cluster
            qtPontos = clusters[novoGrupo].qt;
            // o dado do ponto é adicionado no dado da soma do novo grupo
            clusters[novoGrupo].soma[j] += pontos[p].data[j];
            // o dado do centro cluster é definido como
            // a média dos dados de seus pontos
            clusters[novoGrupo].data[j] = clusters[novoGrupo].soma[j]/qtPontos;
          }

          // o kmedoids é executado novamente (-2 é um valor que sinaliza
          // para que o kmedoids não inicialize novos valores de centros)
          dist = kmedoids(-2);

          if(dist < distAtual){ // se a busca local melhorou a solução atual
            // o valor da melhor função objetivo é atualizado
            // como o valor da função objetivo atual
            distAtual = dist;
            // a solução atual utilizada é definida como as configurações
            // de ponto realizadas no último agrupamento
            solucaoAtual = pontos;
            // os clusters atuais utilizados são definidos como as
            // configurações de clusters realizadas no último agrupamento
            clustersAtuais = clusters;
            melhora = true; // é indicado que houve melhora
            break; // o loop é quebrado
          }else{ // se não
            // o vetor de pontos global volta a ser
            // o vetor de pontos da solução atual
            pontos = solucaoAtual;
            // o vetor de clusters global volta a ser
            // o vetor de clusters atual
            clusters = clustersAtuais;
          }

        }
        
        // se a solução calculada nesta iteração for a melhor de todas
        if(distAtual < melhorDist){
          // a melhor função objetivo de todas é definida
          // como a função objetivo atual
          melhorDist = distAtual;
          // o vetor de pontos da melhor solução é definido
          // como o vetor da solução atual
          melhorSolucao = solucaoAtual;
          // o vetor de clusters da melhor solução é definido
          // como o vetor da solução atual
          melhoresClusters = clustersAtuais;
        }
      }
      it++; // o vetor da quantidade de iterações é incrementado
    }
    // a porcentagem de chance de um ponto escolher
    // o segundo centro mais próximo é aumentada
    pct += 10;

    // se a porcentagem passar de 50
    if(pct > 50){
      pct = 0; // a porcentagem volta para o 0
    }
  }

  for(int i = 0; i < n; i++){ // para cada ponto
    // é printado o ponto e seu respectivo grupo
    int grupo = melhorSolucao[i].grupo;
    cout << "Ponto " << i << " >> Grupo " << grupo << endl;
  }
  // é printada a função objetivo do algoritmo
  cout << "Menor soma de distancias: " << melhorDist << endl;
}