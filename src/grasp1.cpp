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

#define tenMinutes CLOCKS_PER_SEC

vector<ponto> melhorSolucao; // melhor solução de todas as iterações

// função que calcula a distâsncia do método do cotovelo de acordo com a fórmula
double distCotovelo(double a0, double a6, double d, double k){
  double num = abs((a6 - a0)*k - 6*d + 8*a0 - 2*a6);
  double den = sqrt(pow(a6 - a0, 2) + 36);
  return num/den;
}

double calc(){ // função que roda o grasp 1
  int n = pontos.size();         // quantidade de pontos
  int d = pontos[0].data.size(); // dimensão
  int k = clusters.size();       // quantidade de clusters
  
  double melhorDist = INFINITY; // melhor distância de todas as iterações
  melhorSolucao = pontos;
  vector<ponto> solucaoAtual = pontos; // solução base de cada iteração

  clock_t tIni = clock(); // instante de tempo em que a função foi iniciada
  // porcentagem de chance de o algoritmo de agrupamento
  // escolher o segundo centro mais próximo para os pontos
  int pct = 0;

  while(clock() - tIni < tenMinutes){ // enquanto o tempo limite não é atingido
    int it = 0; // quantidade de iterações do algoritmo

    // enquanto o número de iterações e o tempo não atingem o limite
    while(it < pct + 10 and clock() - tIni < tenMinutes){
      // o k-means ou k-medoids com uma porcentagem pct de chance de escolher
      // o segundo cluster mais próximo é executado como construção
      // o uso do k-means e do k-medoids é revezado: caso o número da iteração
      // seja par, utiliza-se o k-means, caso contrário, o k-medoids
      double dist = (it%2 == 0 ? kmeans(pct) : kmedoids(pct));
      for(int i = 0; i < n; i++){ // para cada ponto
        // a solução atual é atualizada
        solucaoAtual[i].grupo = pontos[i].grupo;
      }
      vector<cluster> clustersAtuais = clusters; // clusters atualmente usados
      // valor da função objetivo da solução atualmente usada
      double distAtual = dist;
      // variável que indica se houve melhora na busca local ou não
      bool melhora = true;
      // enquanto há melhora e o tempo limite não é atingido
      while(melhora and clock() - tIni < tenMinutes){
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
          // como a mudança é apenas na inicialização, não há diferença
          //entre executar k-means ou k-medoids na fase de busca local
          dist = kmedoids(-2);

          if(dist < distAtual){ // se a busca local melhorou a solução atual
            // o valor da melhor função objetivo é atualizado
            // como o valor da função objetivo atual
            distAtual = dist;
            // a solução atual utilizada é definida como as configurações
            // de ponto realizadas no último agrupamento
            for(int j = 0; j < n; j++){
              solucaoAtual[j].grupo = pontos[j].grupo;
            }
            // os clusters atuais utilizados são definidos como as
            // configurações de clusters realizadas no último agrupamento
            clustersAtuais = clusters;
            melhora = true; // é indicado que houve melhora
            break; // o loop é quebrado
          }else{ // se não
            // o vetor de pontos global volta a ser
            // o vetor de pontos da solução atual
            for(int j = 0; j < n; j++){
              pontos[j].grupo = solucaoAtual[j].grupo;
            }
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
          for(int i = 0; i < n; i++){
            melhorSolucao[i].grupo = solucaoAtual[i].grupo;
          }
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

  return melhorDist;
}


// função que roda o grasp1 em 7 quantidades diferentes de
// clusters para verificar qual é a melhor quantidade de 
// acordo com o método do cotovelo
void grasp1(){
  int qt; // quantidade de clusters que será a melhor quantidade
  // função objetivo para k = 2, função objetivo para k = 8, melhor função
  // objetivo e melhor distância do método do cotovelo, respectivamente
  double a0, a6, melhorDist, melhorDistCot;
  // melhor solução obtida nas diferentes quantidades de clusters
  vector<ponto> melhorSol;

  // é armazenada a primeira execução com k = 2 (valor mínimo)
  clusters.resize(2);
  a0 = calc();
  melhorDist = a0;
  melhorDistCot = distCotovelo(a0, a6, a0, 2);
  melhorSol = melhorSolucao;
  qt = 2;

  // é armazenada a segunda execução com k = 8 (valor máximo)
  clusters.resize(8);
  a6 = calc();
  double distCot = distCotovelo(a0, a6, a6, 8);
  
  // se a segunda execução for melhor que a primeira, os melhores 
  // valores são definidos como os valores da segunda execução
  if(distCot > melhorDistCot){
    melhorDist = a6;
    melhorDistCot = distCot;
    melhorSol = melhorSolucao;
    qt = 8;
  }
  
  for(int i = 3; i <= 7; i++){ // variando de 3 até 7 clusters
    clusters.resize(i); // o vetor de cluster é definido com tamanho i
    // é armazenada a função objetivo da execução com i clusters
    double dist = calc();
    // é feito o cálculo da distância do método do cotovelo
    distCot = distCotovelo(a0, a6, dist, i);

    // se o cálculo feito for melhor que a melhor distância do método,
    // os melhores valores são definidos como os valores atuais
    if(distCot > melhorDistCot){
      melhorDist = dist;
      melhorDistCot = distCot;
      melhorSol = melhorSolucao;
      qt = i;
    }
  }
  cout << "Quantidade de clusters: " << qt << endl;
    for(int i = 0; i < melhorSol.size(); i++){
      cout << "Ponto " << i << " >> Grupo " << melhorSol[i].grupo << endl;
    }
  cout << "Media de distancias: " << melhorDist << endl;
}