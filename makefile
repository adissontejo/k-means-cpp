SRC = $(wildcard src/*.cpp) # todos os arquivos .cpp
_OBJS = $(patsubst src/%.cpp, %.o, $(SRC)) # são gerados nomes dos arquivos .o a partir de todos os arquivos .cpp
OBJS = $(addprefix bin/, $(_OBJS)) # é adicionado o prefixo bin/ nos nomes dos arquivos .o

.PHONY: all
all: # comando para compilar tudo novamente independentemente dos arquivos pré-existentes
	g++ src/*.cpp -O3 -o bin/clustering

clustering: $(OBJS) # comando que compila de acordo com os arquivos pré-existentes e gera novos se necessário
	g++ -O3 -o clustering $(OBJS)

# comandos para gerar o arquivo .o de cada arquivo .cpp

bin/agrupamento.o: include/agrupamento.h src/agrupamento.cpp
	g++ -c src/agrupamento.cpp -O3 -o bin/agrupamento.o

bin/kmeans.o: include/agrupamento.h include/kmeans.h src/kmeans.cpp
	g++ -c src/kmeans.cpp -O3 -o bin/kmeans.o

bin/pso.o: include/agrupamento.h include/pso.h src/pso.cpp
	g++ -c src/pso.cpp -O3 -o bin/pso.o

bin/genetico.o: include/agrupamento.h include/genetico.h src/genetico.cpp
	g++ -c src/genetico.cpp -O3 -o bin/genetico.o 

bin/kmedoids.o: include/agrupamento.h include/kmedoids.h src/kmedoids.cpp
	g++ -c src/kmedoids.cpp -O3 -o bin/kmedoids.o

bin/grasp.o: include/agrupamento.h include/kmedoids.h include/grasp.h src/grasp.cpp
	g++ -c src/grasp.cpp -O3 -o bin/grasp.o

bin/main.o: include/agrupamento.h include/kmeans.h include/pso.h include/genetico.h include/grasp.h src/main.cpp
	g++ -c src/main.cpp -O3 -o bin/main.o

.PHONY: clean # comando para limpar todos os arquivos .o com exceção do arquivo clustering
clean:
	rm -rf *.o *~clustering 