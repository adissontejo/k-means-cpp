#include <bits/stdc++.h>

using namespace std;
struct ponto{ // estrutura do ponto
	vector<double> data; // dados do ponto
	int grupo = -1; // cluster do ponto
	bool usado = false; // se os dados do ponto foram selecionados como centro de um cluster ou n�o
};

struct cluster{ // estrutura do cluster
	vector<double> data; // dados do centro do cluster
	vector<double> soma; // soma dos dados dos pontos do cluster
	int qt = 0; // quantidade de pontos no cluster
};

vector<ponto> pontos; // vetor dos pontos

double calc(ponto a, cluster b){ // função que calcula a distância euclidiana
  double total = 0;
  for(int i = 0; i < a.data.size(); i++){
  	total += pow(a.data[i] - b.data[i], 2);
	}
	//return sqrt(total);
	return total;
}

void agrupar(int n, int d, int k){ // função que roda o k-means

	bool mudanca = true; // se houve mudança de grupos nos pontos ou não
	vector<cluster> clusters (k); // vetor dos clusters

	for(int i = 0; i < k; i++){ // definição dos clusters
		clusters[i].soma.resize(d, 0); // o vetor de soma dos dados dos pontos do cluster é zerado
		while(true){
			int n = rand()%pontos.size(); // É gerado um número aleatório de um ponto
			if(!pontos[n].usado){ // se os dados de tal ponto ainda não foram escolhidos como centro:
				pontos[n].usado = true; // tais dados são escolhidos
				clusters[i].data = pontos[n].data; // o centro do cluster recebe os dados do ponto				
				break;
			}
		}
	}
	
	while(mudanca){ // enquanto há mudanças de cluster nos pontos
		mudanca = false;
		for(int i = 0; i < n; i++){  // É calculada a distância de cada ponto para cada centro
			int centro = -1; // variável que guarda o índice do centro mais próximo
			double menor = INFINITY; // variável que guarda o valor da menor distância
			for(int j = 0; j < k; j++){
				double dist = calc(pontos[i], clusters[j]);
				if(dist < menor){ // se a distância recém calculada for menor que a menor distância até então:
					menor = dist; // tal distância é registrada como a menor
					centro = j; // tal centro é registrado como o mais próximo
				}
			}
			int antigo = pontos[i].grupo; // variável que armazena o antigo centro mais próximo do ponto
			if(antigo != -1 and antigo != centro){ // se o cluster antigo for um cluster existente e for diferente do atual
				for(int j = 0; j < d; j++){ //os valores de soma do cluster antigo são atualizados
					clusters[antigo].soma[j] -= pontos[i].data[j];
				}
				clusters[antigo].qt--; // a quantidade de pontos é diminuida
			}
			if(antigo != centro){ // se o cluster antigo for diferente do atual
				for(int j = 0; j < d; j++){ // os valores de soma do cluster atual são atualizados
					clusters[centro].soma[j] += pontos[i].data[j];
				}
				clusters[centro].qt++; // a quantidade de pontos é aumentada
				pontos[i].grupo = centro; // o cluster do ponto é atualizado
				mudanca = true; // é registrado que houve mudanças na atual etapa
			}
		}
		for(int i = 0; i < k; i++){ // os centros dos clusters são atualizados para a média dos dados
			for(int j = 0; j < d; j++){
				clusters[i].data[j] = (double) clusters[i].soma[j]/clusters[i].qt;
			}
		}
	}
	
	for(int i = 0; i < n; i++){ // os clusters de cada ponto são printados
		cout << "Cluster " << i << " >> Grupo " << pontos[i].grupo << endl;
	}

	for(int i = 0; i < k; i++){ // as quantidades de pontos de cada cluster são printadas
		cout << "Grupo " << i << " >> " << clusters[i].qt << " pontos\n";
	}

}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	srand (time(NULL));

	int n, d, k; // quantidade de pontos, dimensão e quantidade de clusters
	cin >> n >> d; // são lidas a quantidade de pontos, a dimensão e a quantidade de clusters
	pontos.resize(n); // é definido o tamanho do vetor pontos

	for(int i = 0; i < n; i++){ // são lidos n pontos com d dados cada
		pontos[i].data.resize(d); // é definido o tamanho do vetor de dados do ponto
		for(int j = 0; j < d; j++){
			cin >> pontos[i].data[j];
		}
	}

	cin >> k;

	agrupar(n, d, k); // É chamada a funçãoo que roda o algoritmo k-means

  return 0;
}

