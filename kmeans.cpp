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

int n, d, k; // quantidade de pontos, dimens�o e quantidade de clusters
vector<ponto> pontos; // vetor dos pontos
vector<cluster> clusters; // vetor dos clusters

double calc(ponto a, cluster b){ // fun��o que calcula a dist�ncia euclidiana
  double total = 0;
  for(int i = 0; i < d; i++){
  	total += pow(a.data[i] - b.data[i], 2);
	}
	return sqrt(total);
}

void agrupar(){ // fun��o que roda o k-means
	srand (time(NULL));
	bool mudanca = true; // se houve mudan�a de grupos nos pontos ou n�o
	for(int i = 0; i < k; i++){ // defini��o dos clusters
		cluster a;
		while(true){
			int n = rand()%pontos.size(); // � gerado um n�mero aleat�rio de um ponto
			if(!pontos[n].usado){ // se os dados de tal ponto ainda n�o foram escolhidos como centro:
				pontos[n].usado = true; // tais dados s�o escolhidos
				a.data = pontos[n].data; // o centro do cluster recebe os dados do ponto
				a.soma.resize(d, 0); // o vetor de soma dos dados dos pontos do cluster � zerado
				break;
			}
		}
		clusters.push_back(a); // o cluster rec�m-definido � colocado no vetor de clusters
	}
	while(mudanca){ // enquanto h� mudan�as de cluster nos pontos
		mudanca = false;
		for(int i = 0; i < n; i++){  // � calculada a dist�ncia de cada ponto para cada centro
			int centro = -1; // vari�vel que guarda o �ndice do centro mais pr�ximo
			double menor = 0x3f3f3f3f; // vari�vel que guarda o valor da menor dist�ncia
			for(int j = 0; j < k; j++){
				double dist = calc(pontos[i], clusters[j]);
				if(dist < menor){ // se a dist�ncia rec�m calculada for menor que a menor dist�ncia at� ent�o:
					menor = dist; // tal dist�ncia � registrada como a menor
					centro = j; // tal centro � registrado como o mais pr�ximo
				}
			}
			int antigo = pontos[i].grupo; // vari�vel que armazena o antigo centro mais pr�ximo do ponto
			if(antigo != -1 and antigo != centro){ // se o cluster antigo for um cluster existente e for diferente do atual
				for(int j = 0; j < d; j++){ //os valores de soma do cluster antigo s�o atualizados
					clusters[antigo].soma[j] -= pontos[i].data[j];
				}
				clusters[antigo].qt--; // a quantidade de pontos � diminuida
			}
			if(antigo != centro){ // se o cluster antigo for diferente do atual
				for(int j = 0; j < d; j++){ // os valores de soma do cluster atual s�o atualizados
					clusters[centro].soma[j] += pontos[i].data[j];
				}
				clusters[centro].qt++; // a quantidade de pontos � aumentada
				pontos[i].grupo = centro; // o cluster do ponto � atualizado
				mudanca = true; // � registrado que houve mudan�as na atual etapa
			}
		}
		for(int i = 0; i < k; i++){ // os centros dos clusters s�o atualizados para a m�dia dos dados
			for(int j = 0; j < d; j++){
				clusters[i].data[j] = (double) clusters[i].soma[j]/clusters[i].qt;
			}
		}
	}
}

int main(){
  ios_base::sync_with_stdio(false);
	cin >> n >> d; // s�o lidas a quantidade de pontos e a dimens�o
	for(int i = 0; i < n; i++){ // s�o lidos n pontos com d dados cada
		ponto a;
		for(int j = 0; j < d; j++){
			double x;
			cin >> x;
			a.data.push_back(x);
		}
		pontos.push_back(a);
	}
	cin >> k; // � lida a quantidade de clusters 
	agrupar(); // � chamada a fun��o que roda o algoritmo k-means
	for(int i = 0; i < n; i++){ // os clusters de cada ponto s�o printados
		cout << "Cluster " << i << " >> Grupo " << pontos[i].grupo << endl;
	}
	for(int i = 0; i < k; i++){ // as quantidades de pontos de cada cluster s�o printadas
		cout << "Grupo " << i << " >> " << clusters[i].qt << " pontos\n";
	}
  return 0;
}

