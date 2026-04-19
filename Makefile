CC = gcc

CFLAGS = -Wall -ggdb -Iinclude
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

SRC = src/simpleSimon.c src/audio.c src/loadAssets.c src/dicas.c src/handleJogadas.c src/eventos.c src/interfaceGrafica.c src/funcoesBase.c src/criarJogo.c src/startAndCleanup.c
OBJ = $(SRC:src/%.c=build/%.o)

TARGET = simpleSimon

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm simpleSimon


testaHandleJogadas.o:testaHandleJogadas.c 
	gcc -Wall -ggdb -Iinclude -c TestesSimpleSimon/testaHandleJogadas.c
testaDicas.o:testaDicas.c
	gcc -Wall -ggdb -Iinclude -c TestesSimpleSimon/testaDicas.c
testaFBase.o:testaFBase.c
	gcc -Wall -ggdb -Iinclude -c TestesSimpleSimon/testaFBase.c
testesMain.o:testesMain.c
	gcc -Wall -ggdb -Iinclude -c TestesSimpleSimon/testesMain.c
dicas.o:dicas.c
	gcc -Wall -ggdb -c src/dicas.c
handleJogadas.o:handleJogadas.c 
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c src/handleJogadas.c
eventos.o:eventos.c 
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c src/eventos.c
funcoesBase.o:funcoesBase.c
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -c src/funcoesBase.c
testesSimpleSimon:dicas.o eventos.o funcoesBase.o handleJogadas.o testesMain.o testaFBase.o testaDicas.o testaHandleJogadas.o
	gcc $^ -o $@ -lcunit
cleant:
	rm testesSimpleSimon testesMain.o dicas.o eventos.o funcoesBase.o handleJogadas.o testaFBase.o testaHandleJogadas.o testaDicas.o



check:
	@command -v gcc >/dev/null 2>&1 || { echo "gcc not installed"; exit 1; }
	@command -v make >/dev/null 2>&1 || { echo "make not installed"; exit 1; }

	@pkg-config --exists sdl2 || { echo "SDL2 missing"; exit 1; }
	@pkg-config --exists SDL2_image || { echo "SDL2_image missing"; exit 1; }
	@pkg-config --exists SDL2_mixer || { echo "SDL2_mixer missing"; exit 1; }
	@pkg-config --exists SDL2_ttf || { echo "SDL2_ttf missing"; exit 1; }

	@echo "All dependencies OK"