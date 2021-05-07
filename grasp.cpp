#include <bits/stdc++.h>
#include "agrupamento.h"
#include "kmedoids.h"
#include "grasp.h"

using namespace std;

void grasp(){ // função que roda o grasp
  int n = pontos.size(); // definição das variáveis de tamanho
  int d = pontos[0].data.size();
  int k = clusters.size();
  double melhorDist = INFINITY;
  vector<ponto> melhorSolucao; 
  clock_t tIni = clock();
  int pct = 0; // porcentagem de escolher o segundo centro mais próximo
  while(clock() - tIni < 10*CLOCKS_PER_SEC){ // enquanto o tempo limite não é atingido
    int it = 0;
    while(it < pct + 10 and clock() - tIni < 10*CLOCKS_PER_SEC){ // enquanto o número de iterações e o tempo não atingem o limite
      double dist = kmedoids(pct); // o kmedoids com uma porcentagem pct de chance de escolher o segundo cluster mais próximo é executado como construção
      vector<ponto> solucaoAtual = pontos; // vetor que guarda a solução atualmente usada
      double distAtual = dist; // vetor que guarda a distância da soluçãoa atualmente usada
      bool melhora = true; // variável que indica se houve melhora na busca local ou não
      while(melhora and clock() - tIni < 10*CLOCKS_PER_SEC){ // enquanto há melhora e o tempo limite não é atingido
        melhora = false;
        int lista[n]; // a lista que será bagunçada e aleatoriezada é gerada
        for(int i = 0; i < n; i++){
          lista[i] = i;
        }
        for(int i = 0; i < n; i++){
          swap(lista[i], lista[rand()%n]);
        }
        for(int i = 0; i < min(n, 100); i++){
          int novoGrupo = rand()%k; // novo grupo aleatorizado para o ponto escolhido
          int p = lista[i];
          int antigo = pontos[p].grupo;
          while(novoGrupo == antigo){
            novoGrupo = rand()%k;
          }
          pontos[p].grupo = novoGrupo;
          clusters[antigo].qt--;
          clusters[novoGrupo].qt++;
          for(int j = 0; j < d; j++){ // os dados dos centros são atualizados
            clusters[antigo].soma[j] -= pontos[p].data[j];
            if(clusters[antigo].qt != 0){
              clusters[antigo].data[j] = (double) clusters[antigo].soma[j]/clusters[antigo].qt;
            }
            clusters[novoGrupo].soma[j] += pontos[p].data[j];
            clusters[novoGrupo].data[j] = (double) clusters[novoGrupo].soma[j]/clusters[novoGrupo].qt;
          }
          dist = kmedoids(-2); // o kmedoidos é executado novamente (-2 é um valor que sinaliza para que o kmedoids não inicialize novos valores de centros)
          if(dist < distAtual){ // se a busca local melhorou a solução atual
            distAtual = dist; // tal solução é tomada como atual
            solucaoAtual = pontos;
            melhora = true;
            break;
          }else{
            pontos = solucaoAtual;
          }
        }

        if(distAtual < melhorDist){ // se a solução calculada nesta iteração for a melhor
          melhorDist = distAtual;
          melhorSolucao = solucaoAtual;
        }
      }
      it++;
    }
    pct += 10;
  }
  for(int i = 0; i < n; i++){
    cout << "Ponto " << i << " >> Grupo " << melhorSolucao[i].grupo << endl;
  }
  cout << "Menor media de distancias: " << melhorDist << endl;
}