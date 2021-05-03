#include <bits/stdc++.h>
#include "agrupamento.h"
#include "genetico.h"

struct gene{ // estrutura de um gene
  vector<cluster> clustersG;
  int aptidao;
};

void genetico(){ // função que roda o algoritmo genético
  int n = pontos.size(); // são declaradas as variáveis de tamanho
  int d = pontos[0].data.size();
  int k = clusters.size();
  int g = k*d*10; // a quantidade de genes é definida
  vector<gene> genes(g); // é declarado o vetor de genes de tamanho g
  
  for(int i = 0; i < g; i++){ // todos os genes são iniciados com valores aleatórios
    genes[i].clustersG.resize(k);
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
  double melhor = INFINITY, soma; // variável que armazena a melhor função objetiva e a soma de todas elas
  
  while(qt < 30){ // condição de parada: se não houver melhora há 30 gerações
    soma = 0;
    melhora = false;
    for(int i = 0; i < g; i++){ // é calculada a aptidão de cada gene
      clusters = genes[i].clustersG;
      double fo = agrupamento();
      genes[i].aptidao = (int) fo;
      soma += fo;
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
    vector<int> pais; // vetor que armazena os genes restantes que podem ser escolhidos como pais

    for(int i = 0; i < g; i++){ // é feita a seleção natural
      int x = rand()%((int) soma); // utilizando um método semelhante ao método da roleta, os genes que têm mais aptidão têm menos chance de serem substituídos
      if((x < genes[i].aptidao and qtSubs <= k/2) or pais.size() >= k/2){ // onde há um número pré-definido de metade substituições
        subs.push(i);
        qtSubs++;
      }else{
        pais.push_back(i);
      }
    }

    int geneA = pais[rand()%pais.size()];
    int geneB = pais[rand()%pais.size()];

    while(!subs.empty()){ // é feito o crossover
      int novoGene = subs.front();
      subs.pop();
      int ponto = rand()%k + 1; // o ponto de separação e encontro do crossover é definido
      for(int i = 0; i < ponto; i++){
        genes[novoGene].clustersG[i] = genes[geneA].clustersG[i];
      }
      for(int i = ponto; i < k; i++){
        genes[novoGene].clustersG[i] = genes[geneB].clustersG[i];
      }
    }

    for(int i = 0; i < g; i++){ // é feita a mutação
      int x = rand()%10; // cada mutação tem 10% de chance de ocorrer
      if(x == 0){
        int mutacao = rand()%k; // o cluster em que a mutação ocorre é definido
        for(int j = 0; j < d; j++){
          genes[i].clustersG[mutacao].data[j] += (rand()%2000)/100.0 - 10; // os dados do cluster variam até 10 para cima ou para baixo
        }
      }
    }
  }

  clusters = melhorGene.clustersG;
  agrupamento();
  for(int i = 0; i < n; i++){ // os pontos e seus respectivos grupos são printados
    cout << "Ponto " << i << " >> Grupo " << pontos[i].grupo << endl;
  }
  cout << "Menor media de distancias: " << melhor << endl;
}