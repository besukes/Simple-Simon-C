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


testaHandleJogadas.o: testes/testaHandleJogadas.c
	gcc -Wall -ggdb -Iinclude -c testes/testaHandleJogadas.c
testaDicas.o: testes/testaDicas.c
	gcc -Wall -ggdb -Iinclude -c testes/testaDicas.c
testaFBase.o: testes/testaFBase.c
	gcc -Wall -ggdb -Iinclude -lSDL2 -lSDL2_image -c testes/testaFBase.c
testesMain.o: testes/testesMain.c
	gcc -Wall -ggdb -Iinclude -c testes/testesMain.c
dicas.o: src/dicas.c
	gcc -Wall -ggdb -lSDL2 -lSDL2_image -Iinclude -c src/dicas.c
handleJogadas.o: src/handleJogadas.c
	gcc -Wall -ggdb -Iinclude -lSDL2 -lSDL2_image -c src/handleJogadas.c
eventos.o: src/eventos.c
	gcc -Wall -ggdb -Iinclude -lSDL2 -lSDL2_image -c src/eventos.c
funcoesBase.o: src/funcoesBase.c
	gcc -Wall -ggdb -Iinclude -lSDL2 -lSDL2_image -c src/funcoesBase.c
testesSimpleSimon: dicas.o eventos.o funcoesBase.o handleJogadas.o audio.o criarJogo.o testesMain.o testaFBase.o testaDicas.o testaHandleJogadas.o
	gcc $^ -o $@ -lcunit -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
audio.o: src/audio.c
	gcc -Wall -ggdb -Iinclude -c src/audio.c
criarJogo.o: src/criarJogo.c
	gcc -Wall -ggdb -Iinclude -c src/criarJogo.c
cleant:
	rm -f testesSimpleSimon testesMain.o dicas.o eventos.o funcoesBase.o handleJogadas.o audio.o criarJogo.o testaFBase.o testaHandleJogadas.o testaDicas.o

check:
	@command -v gcc >/dev/null 2>&1 || { echo "gcc not installed"; exit 1; }
	@command -v make >/dev/null 2>&1 || { echo "make not installed"; exit 1; }

	@pkg-config --exists sdl2 || { echo "SDL2 missing"; exit 1; }
	@pkg-config --exists SDL2_image || { echo "SDL2_image missing"; exit 1; }
	@pkg-config --exists SDL2_mixer || { echo "SDL2_mixer missing"; exit 1; }
	@pkg-config --exists SDL2_ttf || { echo "SDL2_ttf missing"; exit 1; }

	@echo "All dependencies OK"