SRC = $(wildcard src/*.cpp) # todos os arquivos .cpp

# são gerados nomes dos arquivos .o a partir de todos os arquivos .cpp
OBJS = $(patsubst src/%.cpp, bin/%.o, $(SRC))

.PHONY: all
all: bin/clustering	

bin/clustering: bin $(OBJS) # gera o arquivo executável
	g++ -O3 -o bin/clustering $(OBJS)

#cria a pasta bin caso esta não exista ainda

bin:
	mkdir bin

# geram o arquivo .o de cada arquivo .cpp caso estes não existam ainda


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

bin/grasp1.o: include/agrupamento.h include/kmedoids.h include/grasp1.h src/grasp1.cpp
	g++ -c src/grasp1.cpp -O3 -o bin/grasp1.o

bin/grasp2.o: include/agrupamento.h include/kmedoids.h include/grasp2.h src/grasp2.cpp
	g++ -c src/grasp2.cpp -O3 -o bin/grasp2.o

bin/main.o: include/agrupamento.h include/kmeans.h include/pso.h include/genetico.h include/grasp1.h include/grasp2.h src/main.cpp
	g++ -c src/main.cpp -O3 -o bin/main.o

.PHONY: clean # comando para limpar todos os arquivos .o com exceção do arquivo clustering
clean:
	rm -rf *.o *~clustering 