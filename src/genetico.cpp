/*
  Arquivo usado para agrupar os pontos utilizando
  o algoritmo genético
*/

#include <bits/stdc++.h>
#include "../include/agrupamento.h"
#include "../include/genetico.h"


#define tenSeconds 10*CLOCKS_PER_SEC
struct gene{ // estrutura de um gene
  vector<cluster> clustersG; // vetor de clusters do gene
  int chance; // chance de um gene morrer na seleção natural
};

void genetico(){ // função que roda o algoritmo genético
  int n = pontos.size(); // quantidade de pontos
  int d = pontos[0].data.size(); // dimensão 
  int k = clusters.size(); // quantidade de clusters
  int g = k*d*10; // a quantidade de genes é definida

  clock_t tIni = clock(); // instante de tempo em que a função foi iniciada
  // valor da melhor função objetivo de todas as iterações
  double melhorFuncaoObjetivo = INFINITY;
  vector<cluster> melhorGrupoDeCluster; // melhor solução de todas as iterações
  vector<gene> genes(g); // é declarado o vetor de genes de tamanho g

  for(int i = 0; i < g; i++){ // para cada gene
    // o vetor de clusters do gene é definido com tamanho k
    genes[i].clustersG.resize(k);
  }

  // enquanto o tempo limite não for atingido
  while(clock() - tIni < tenSeconds){
    for(int i = 0; i < g; i++){ // para cada gene
      // vetor que indica se os pontos foram usados como dados dos genes ou não
      vector<bool> usado (n, false);

      for(int j = 0; j < k; j++){ // para cada cluster
        // o vetor de soma do cluster é zerado
        genes[i].clustersG[j].soma.resize(d, 0);

        while(true){
          int x = rand()%n; // é sorteado um ponto (número de 0 a n - 1)

          if(!usado[x]){ // se o ponto sorteado ainda não foi usado
            usado[x] = true; // é indicado que o ponto foi usado
            // o cluster recebe os dados do ponto
            genes[i].clustersG[j].data = pontos[x].data;
            break; // o loop é quebrado
          }
        }
      }
    }

    gene melhorGene; // melhor gene da iteração atual
    int qt = 0; // quantidade de gerações em que não há melhora
    bool melhora; // indica se houve ou não melhora
    double melhor = INFINITY; // melhor função objetivo da iteração atual
    
    // condição de parada: se não houver melhora há 20
    // gerações ou o tempo limite de 10s for atingido
    while(qt < 20 and clock() - tIni < tenSeconds){
      // soma de todos os valores das funções objetivas de cada gene
      double soma = 0;
      melhora = false; // a variável melhora é setada como false

      for(int i = 0; i < g; i++){ // para cada gene
        // o vetor de clusters global recebe o vetor de clusters do gene
        clusters = genes[i].clustersG;
        // a função de agrupamento é chamada e seu valor de retorno é armazenado
        double fo = agrupamento();
        soma += fo; // o valor da função objetivo é adicionado na variável soma
        // a chance de um gene morrer na seleção natural
        // é definida como o valor da função objetivo
        genes[i].chance = fo;

        // se a aptidão de tal gene for melhor
        // que a melhor até então registrada
        if(fo < melhor){
          melhor = fo; // tal aptidão é definida como a melhor
          melhorGene = genes[i]; // tal gene é definido como o melhor
          melhora = true; // é indicado que houve melhora
        }
      }

      if(!melhora){ // se não houve melhora
        qt++; // qt é incrementado
      }else{ // se não
        qt = 0; // qt é zerado
      }

      queue<int> subs; // fila que armazena os genes que serão substituídos
      // vetor que indica se tais genes foram substituídos ou não
      vector<bool> substituido (g, false);

      // total de iterações: metade da quantidade de genes
      for(int i = 0; i < g/2; i++){
        // é sorteado um valor entre 0 e o valor de soma
        int roleta = rand()%((int) soma);
        soma = 0; // a variável soma é zerada
        for(int j = 0; j < g; j++){ // para cada gene
          if(substituido[j]) // se o gene foi substituído
            continue; // o resto do for é ignorado
          // é adicionada à variável soma a aptidão/chance do gene
          soma += genes[j].chance;
          if(roleta < soma){ // se o número sorteado for menor que soma
            substituido[j] = true; // é indicado que o gene foi substituído
            subs.push(j); // o gene é adicionado à fila dos genes substituídos
            // a aptidão/chance do gene é removida da variável soma
            soma -= genes[j].chance;

            for(int l = j + 1; l < g; l++) // para cada gene restante
              // é adicionada à variável soma a aptidão/chance do gene
              soma += genes[l].chance;
            break;
          }
        } 
      }

      while(!subs.empty()){ // enquanto ainda há genes a serem substituídos
        // variável que armazena o índice de um gene substituído
        int novoGene = subs.front();
        // variáveis que guardam os índices dos pais do crossover
        int geneA, geneB;
        
        while(true){
          geneA = rand()%g; // é sorteado um pai
          if(!substituido[geneA]) // se o pai sorteado não foi substituído
            break; // o laço é quebrado
        }

        while(true){
          geneB = rand()%g; // é sorteado outro pai
          if(!substituido[geneB]) // se o pai sorteado não foi susbtituído
            break; // o laço é quebrado
        }

        subs.pop(); // o gene antigo que foi substituído é removido da fila
        
        for(int i = 0; i < k; i++){ // para cada cluster
          for(int j = 0; j < d; j++){ // para cada dado do cluster
            int bit = rand()%15; // é sorteado um bit entre 0 e 14
            // é selecionada a parte que vem antes 
            // do bit sorteado no dado do geneA
            double p1 = ((int) genes[geneA].clustersG[i].data[j])/(1 << bit);
            // é selecionada a parte que vem depois
            // do bit sorteado no dado do geneB
            double p2 = ((int) genes[geneB].clustersG[i].data[j])%(1 << bit);
            // é selecionada a parte decimal do dado do geneB
            double r = genes[geneB].clustersG[i].data[j] - ((int) genes[geneB].clustersG[i].data[j]);
            // o dado do novo gene é definido como a
            // junção das partes selecionadas
            genes[novoGene].clustersG[i].data[j] = p1*(1 << bit) + p2 + r;
          }
        }
      }

      for(int i = 0; i < g; i++){ // para cada gene
        int x = rand()%10; // é sorteado um número entre 0 e 9
        if(x == 0){ // se o número sorteado for igual a 0 (10% de chance)
          // o cluster em que a mutação ocorre é sorteado
          int mutacao = rand()%k;

          for(int j = 0; j < d; j++){ // para cada dado do cluster
            int bit = rand()%15; // é sorteado um bit entre 0 e 14
            int vInt = genes[i].clustersG[mutacao].data[j]; 
            // é obtida a parte decimal do valor
            double r = genes[i].clustersG[mutacao].data[j] - vInt;
            // o bit escolhido é invertido na parte inteira
            vInt ^= (1 << bit);
            // o gene modificado é definido como a junção das partes inteira e decimal
            genes[i].clustersG[mutacao].data[j] = vInt + r;
          }
        }
      }
    }

    // se o melhor valor da função objetivo da rodada atual
    // for melhor que o melhor de todas as rodadas
    if(melhor < melhorFuncaoObjetivo){
      // tal solução é definida como a melhor de todas
      melhorGrupoDeCluster = melhorGene.clustersG;
      // tal valor é definido como o melhor
      melhorFuncaoObjetivo = melhor;
    }
  }
  // o vetor de clusters global recebe o vetor
  // de clusters da melhor solução do algoritmo
  clusters = melhorGrupoDeCluster;
  agrupamento(); // é realizada a função de agrupamento novamente

  for(int i = 0; i < n; i++){ // para cada ponto
    // é printado o ponto e seu respectivo grupo
    cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl;
  }
  // é printada a função objetivo do algoritmo
  cout << "Menor soma de distancias: " << melhorFuncaoObjetivo << endl;
}