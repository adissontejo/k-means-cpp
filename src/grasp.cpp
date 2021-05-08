/*
  Arquivo usado para agrupar os pontos utilizando
  o algoritmo GRASP
*/

#include <bits/stdc++.h>
#include "../include/agrupamento.h"
#include "../include/kmedoids.h"
#include "../include/grasp.h"

using namespace std;

void grasp(){ // função que roda o grasp
  int n = pontos.size(); // variável que guarda o valor da quantidade de pontos
  int d = pontos[0].data.size(); // variável que guarda o valor da dimensão
  int k = clusters.size(); // variável que guarda o valor da quantidade de clusters
  double melhorDist = INFINITY; // variável que guarda a melhor distância de todas as iterações
  vector<ponto> melhorSolucao; // variável que guarda a melhor solução de todas as iterações
  clock_t tIni = clock(); // variável que guarda o valor do instante de tempo em que a função foi iniciada
  int pct = 0; // variável que guarda a porcentagem de chance de o algoritmo de agrupamento escolher o segundo centro mais próximo para os pontos
  while(clock() - tIni < 10*CLOCKS_PER_SEC){ // enquanto o tempo limite não é atingido
    int it = 0; // variável que guarda a quantidade de iterações do algoritmo
    while(it < pct + 10 and clock() - tIni < 10*CLOCKS_PER_SEC){ // enquanto o número de iterações e o tempo não atingem o limite
      double dist = kmedoids(pct); // o kmedoids com uma porcentagem pct de chance de escolher o segundo cluster mais próximo é executado como construção
      vector<ponto> solucaoAtual = pontos; // vetor que guarda a solução atualmente usada
      double distAtual = dist; // variável que guarda o valor da função objetivo da solução atualmente usada
      bool melhora = true; // variável que indica se houve melhora na busca local ou não
      while(melhora and clock() - tIni < 10*CLOCKS_PER_SEC){ // enquanto há melhora e o tempo limite não é atingido
        melhora = false; // a variável melhora é setada como false
        int lista[n]; // a lista que será bagunçada e aleatoriezada é gerada
        for(int i = 0; i < n; i++){ // para cada ponto
          lista[i] = i; // o valor i da lista é definido como seu próprio índice
        }
        for(int i = 0; i < n; i++){ // para cada ponto
          swap(lista[i], lista[rand()%n]); // o valor i da lista é trocado com outro valor aleatório da lista
        }
        for(int i = 0; i < min(n, 50); i++){ // para cada ponto, com um máximo de 50 iterações
          int novoGrupo = rand()%k; // um novo grupo para o ponto é atualizado
          int p = lista[i]; // variável que armazena o índice do ponto
          int antigo = pontos[p].grupo; // variável que armazena o antigo grupo do ponto
          while(novoGrupo == antigo){ // enquanto o novo grupo sorteado é igual ao grupo antigo
            novoGrupo = rand()%k; // um novo grupo é sorteado
          }
          pontos[p].grupo = novoGrupo; // o grupo do ponto é definido como o grupo sorteado
          clusters[antigo].qt--; // a quantidade de pontos no grupo antigo é diminuida
          clusters[novoGrupo].qt++; // a quantidade de pontos no novo grupo é aumentada
          for(int j = 0; j < d; j++){ // para cada dado do ponto e do cluster
            clusters[antigo].soma[j] -= pontos[p].data[j]; // o dado do ponto é removido do dado da soma do grupo antigo
            if(clusters[antigo].qt != 0){  // se a quantidade de pontos do cluster antigo for diferente de 0 (como prevenção de divisões por 0)
              clusters[antigo].data[j] = (double) clusters[antigo].soma[j]/clusters[antigo].qt; // o dado do centro cluster é definido como a média dos dados de seus pontos
            }
            clusters[novoGrupo].soma[j] += pontos[p].data[j]; // o dado do ponto é adicionado no dado da soma do novo grupo
            clusters[novoGrupo].data[j] = (double) clusters[novoGrupo].soma[j]/clusters[novoGrupo].qt; // o dado do centro cluster é definido como a média dos dados de seus pontos
          }
          dist = kmedoids(-2); // o kmedoidos é executado novamente (-2 é um valor que sinaliza para que o kmedoids não inicialize novos valores de centros)
          if(dist < distAtual){ // se a busca local melhorou a solução atual
            distAtual = dist; // o valor da melhor função objetivo é atualizado como o valor da função objetivo atual
            solucaoAtual = pontos; // a solução atual utilizada é definida como as configurações de ponto realizadas no último agrupamento
            melhora = true; // é indicado que houve melhora
            break; // o loop é quebrado
          }else{ // se não
            pontos = solucaoAtual; // o vetor de pontos global volta a ser o vetor de pontos da solução atual
          }
        }

        if(distAtual < melhorDist){ // se a solução calculada nesta iteração for a melhor de todas
          melhorDist = distAtual; // a melhor função objetivo de todas é definida como a função objetivo atual
          melhorSolucao = solucaoAtual; // o vetor de pontos da melhor solução é definido como o vetor da solução atual
        }
      }
      it++; // o vetor da quantidade de iterações é incrementado
    }
    pct += 10; // a porcentagem de chance de um ponto escolher o segundo centro mais próximo é aumentada
  }
  for(int i = 0; i < n; i++){ // para cada ponto
    cout << "Ponto " << i << " >> Grupo " << melhorSolucao[i].grupo << endl; // é printado o ponto e seu respectivo grupo
  }
  cout << "Menor media de distancias: " << melhorDist << endl; // é printado o valor da função objetivo do algoritmo
}