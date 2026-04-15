simpleSimon.o:simpleSimon.c
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c simpleSimon.c
audio.o:audio.c
	gcc -Wall -ggdb -lSDL2_mixer -c audio.c
dicas.o:dicas.c
	gcc -Wall -ggdb -c dicas.c
handleJogadas.o:handleJogadas.c 
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c handleJogadas.c
eventos.o:eventos.c 
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c eventos.c
interfaceGrafica.o:interfaceGrafica.c
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c interfaceGrafica.c
funcoesBase.o:funcoesBase.c
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c funcoesBase.c
criarJogo.o:criarJogo.c
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c criarJogo.c 
funcoesFundamentais.o:funcoesFundamentais.c
	gcc -Wall -ggdb -c funcoesFundamentais.c
simpleSimon:simpleSimon.o interfaceGrafica.o funcoesBase.o criarJogo.o funcoesFundamentais.o eventos.o handleJogadas.o audio.o dicas.o
	gcc -ggdb $^ -o $@ -lSDL2 -lSDL2_image -lSDL2_mixer
clean:
	rm simpleSimon.o interfaceGrafica.o funcoesBase.o criarJogo.o funcoesFundamentais.o simpleSimon eventos.o handleJogadas.o audio.o dicas.o
check:

	@command -v gcc >/dev/null 2>&1 || { echo "gcc not installed"; exit 1; }
	@command -v make >/dev/null 2>&1 || { echo "make not installed"; exit 1; }

	@pkg-config --exists sdl2 || { echo "SDL2 missing"; exit 1; }
	@pkg-config --exists SDL2_image || { echo "SDL2_image missing"; exit 1; }
	@pkg-config --exists SDL2_mixer || { echo "SDL2_mixer missing"; exit 1; }

	@echo "All dependencies OK"