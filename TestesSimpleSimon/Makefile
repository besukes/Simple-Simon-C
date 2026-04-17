testesMain.o:testesMain.c
	gcc -Wall -ggdb -c testesMain.c
dicas.o:dicas.c
	gcc -Wall -ggdb -c dicas.c
handleJogadas.o:handleJogadas.c 
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c handleJogadas.c
eventos.o:eventos.c 
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c eventos.c
funcoesBase.o:funcoesBase.c
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c funcoesBase.c
testesSimpleSimon : testesMain.o dicas.o eventos.o funcoesBase.o handleJogadas.o
	gcc $^ -o $@ -lcunit
cleant:
	rm testesMain.o dicas.o eventos.o funcoesBase.o handleJogadas.o
