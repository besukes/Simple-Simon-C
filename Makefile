simpleSimon.o: simpleSimon.c
  	gcc -Wall -ggdb -c simpleSimon.c -lSDL2 -lSDL2_image
interfaceGrafica.o: interfaceGrafica.c
	gcc -Wall -ggdb -c interfaceGrafica.c -lSDL2 -lSDL2_image
funcoesBase.o: funcoesBase.c
	gcc -Wall -ggdb -c funcoesBase.c
criarJogo.o: criarJogo.c
	gcc -Wall -ggdb -c criarJogo.c -lSDL2 -lSDL2_image
simpleSimon : simpleSimon.o interfaceGrafica.o funcoesBase.o criarJogo.o
  	gcc -ggdb $^ -o $@
clean:
  	rm simpleSimon.o interfaceGrafica.o funcoesBase.o criarJogo.o simpleSimon
