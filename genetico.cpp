#include <bits/stdc++.h>
#include "agrupamento.h"
#include "genetico.h"

struct gene{ // estrutura de um gene
  vector<cluster> clustersG;
  int chance;
};

void genetico(){ // função que roda o algoritmo genético
  int n = pontos.size(); // são declaradas as variáveis de tamanho
  int d = pontos[0].data.size();
  int k = clusters.size();
  int g = k*d*10; // a quantidade de genes é definida
  clock_t tIni = clock();
  double melhorFuncaoObjetivo = INFINITY;
  vector<cluster> melhorGrupoDeCluster;
  vector<gene> genes(g); // é declarado o vetor de genes de tamanho g
  for(int i = 0; i < g; i++){
    genes[i].clustersG.resize(k);
  }
  while(clock() - tIni < 10*CLOCKS_PER_SEC){ // enquanto o tempo limite não for atingido
    for(int i = 0; i < g; i++){ // todos os genes são iniciados com valores aleatórios
      vector<bool> usado (n, false);
      for(int j = 0; j < k; j++){
        genes[i].clustersG[j].soma.resize(d, 0);
        while(true){
          int x = rand()%n;
          if(!usado[x]){
            usado[x] = true;
            genes[i].clustersG[j].data = pontos[x].data;
            break;
          }
        }
      }
    }

    gene melhorGene; // variável que armazena o melhor gene
    int qt = 0; // variável que armazena há quantas gerações não há melhora
    bool melhora; // variável que representa se houve ou não melhora
    double melhor = INFINITY, soma; // variável que armazena a melhor função objetivo e a soma de todas elas
    
    while(qt < 20 and clock() - tIni < 10*CLOCKS_PER_SEC){ // condição de parada: se não houver melhora há 20 gerações ou o tempo limite de 10s for atingido
      soma = 0;
      melhora = false;
      for(int i = 0; i < g; i++){ // é calculada a aptidão de cada gene
        clusters = genes[i].clustersG;
        double fo = agrupamento();
        soma += fo;
        genes[i].chance = fo;
        if(fo < melhor){ // se a aptidão de tal gene for melhor que a melhor até então registrada
          melhor = fo; // tal aptidão e este gene são tidos como melhores
          melhorGene = genes[i];
          melhora = true;
        }
      }

      if(!melhora){ // se não houve melhora, qt é aumentado em 1
        qt++;
      }else{ // se houve melhora, qt é zerado
        qt = 0;
      }

      int qtSubs = 0; // quantidade de genes que foram substituídos
      queue<int> subs; // fila que armazena os genes que serão substituídos
      vector<bool> substituido (g, false); // vetor que indica se tais genes foram substituídos ou não

      for(int i = 0; i < g/2; i++){ // os genes que serão substituídos são sorteados de acordo com o método da roleta
        int roleta = rand()%((int) soma);
        soma = 0;
        for(int j = 0; j < g; j++){
          if(substituido[j])
            continue;
          soma += genes[j].chance;
          if(roleta < soma){
            substituido[j] = true;
            subs.push(j);
            soma -= genes[j].chance;
            for(int l = j + 1; l < g; l++)
              soma += genes[l].chance;
            break;
          }
        } 
      }

      while(!subs.empty()){ // é feito o crossover
        int novoGene = subs.front();
        int geneA, geneB;
        while(true){
          geneA = rand()%g;
          if(!substituido[geneA])
            break;
        }
        while(true){
          geneB = rand()%g;
          if(!substituido[geneB])
            break;
        }
        subs.pop();
        for(int i = 0; i < k; i++){
          for(int j = 0; j < d; j++){
            int bit = rand()%15; // é sorteado um bit entre 0 e 14
            double p1 = ((int) genes[geneA].clustersG[i].data[j])/(1 << bit); // é selecionada a parte que vem antes do bit sorteado no geneA
            double p2 = ((int) genes[geneB].clustersG[i].data[j])%(1 << bit); // é selecionada a parte que vem depois do bit sorteado no geneB
            double r = genes[geneB].clustersG[i].data[j] - ((int) genes[geneB].clustersG[i].data[j]); // é selecionada a parte decimal do geneB
            genes[novoGene].clustersG[i].data[j] = p1*(1 << bit) + p2 + r;
          }
        }
      }

      for(int i = 0; i < g; i++){ // é feita a mutação
        int x = rand()%10; // cada mutação tem 10% de chance de ocorrer
        if(x == 0){
          int mutacao = rand()%k; // o cluster em que a mutação ocorre é definido
          for(int j = 0; j < d; j++){
            int bit = rand()%15; // é sorteado um bit entre 0 e 14
            int vInt = genes[i].clustersG[mutacao].data[j]; // é obtida a parte inteira do valor
            double r = genes[i].clustersG[mutacao].data[j] - vInt; // é obtida a parte decimal do valor
            vInt ^= (1 << bit); // o bit escolhido é invertido na parte inteira
            genes[i].clustersG[mutacao].data[j] = vInt + r;
          }
        }
      }
    }
    if(melhor < melhorFuncaoObjetivo){
      melhorGrupoDeCluster = melhorGene.clustersG;
      melhorFuncaoObjetivo = melhor;
    }
  }
  clusters = melhorGrupoDeCluster;
  agrupamento();
  for(int i = 0; i < n; i++){ // os pontos e seus respectivos grupos são printados
    cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl;
  }
  cout << "Menor media de distancias: " << melhorFuncaoObjetivo << endl;
}