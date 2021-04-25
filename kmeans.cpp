#include <bits/stdc++.h>

using namespace std;

struct ponto{
	vector<double> data;
	int grupo = -1;
	bool usado = false;
};

struct cluster{
	vector<double> data;
	vector<double> soma;
	int qt = 0;
};

int n, d, k;
vector<ponto> pontos;
vector<cluster> clusters;

double calc(ponto a, cluster b){
  double total = 0;
  for(int i = 0; i < d; i++){
  	total += pow(a.data[i] - b.data[i], 2);
	}
	return sqrt(total);
}

void agrupar(){
	srand (time(NULL));
	bool mudanca = true;
	for(int i = 0; i < k; i++){
		cluster a;
		while(true){
			int n = rand()%pontos.size();
			if(!pontos[n].usado){
				pontos[n].usado = true;
				a.data = pontos[n].data;
				a.soma.resize(d, 0);
				break;
			}
		}
		clusters.push_back(a);
	}
	while(mudanca){
		mudanca = false;
		for(int i = 0; i < n; i++){
			int centro = -1;
			double menor = 0x3f3f3f3f;
			for(int j = 0; j < k; j++){
				double dist = calc(pontos[i], clusters[j]);
				if(dist < menor){
					menor = dist;
					centro = j;
				}
			}
			int antigo = pontos[i].grupo;
			if(antigo != -1 and antigo != centro){
				for(int j = 0; j < d; j++){
					clusters[antigo].soma[j] -= pontos[i].data[j];
				}
				clusters[antigo].qt--;
			}
			if(antigo != centro){
				for(int j = 0; j < d; j++){
					clusters[centro].soma[j] += pontos[i].data[j];
				}
				clusters[centro].qt++;
				pontos[i].grupo = centro;
				mudanca = true;
			}
		}
		for(int i = 0; i < k; i++){
			for(int j = 0; j < d; j++){
				clusters[i].data[j] = (double) clusters[i].soma[j]/clusters[i].qt;
			}
		}
	}
}

int main(){
  ios_base::sync_with_stdio(false);
	cin >> n >> d;
	for(int i = 0; i < n; i++){
		ponto a;
		for(int j = 0; j < d; j++){
			double x;
			cin >> x;
			a.data.push_back(x);
		}
		pontos.push_back(a);
	}
	cin >> k;
	agrupar();
	for(int i = 0; i < n; i++){
		cout << i << " >> Grupo " << pontos[i].grupo << endl;
	}
	for(int i = 0; i < k; i++){
		cout << "Grupo: " << i << " >> " << clusters[i].qt << " pontos\n";
	}
  return 0;
}

