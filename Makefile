simpleSimon.o:simpleSimon.c
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c simpleSimon.c
eventos.o:eventos.c 
	gcc -Wall -ggdb -c eventos.c
interfaceGrafica.o:interfaceGrafica.c
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c interfaceGrafica.c
funcoesBase.o:funcoesBase.c
	gcc -Wall -ggdb -c funcoesBase.c
criarJogo.o:criarJogo.c
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c criarJogo.c 
funcoesFundamentais.o:funcoesFundamentais.c
	gcc -Wall -ggdb -c funcoesFundamentais.c
simpleSimon:simpleSimon.o interfaceGrafica.o funcoesBase.o criarJogo.o funcoesFundamentais.o eventos.o
	gcc -ggdb $^ -o $@ -lSDL2 -lSDL2_image
clean:
	rm simpleSimon.o interfaceGrafica.o funcoesBase.o criarJogo.o funcoesFundamentais.o simpleSimon eventos.o
