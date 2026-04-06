#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef int numCarta;

typedef struct ultimaJogada{
    numCarta carta;
    int novaPos;
    int antigaPos;
}lastMove;
typedef struct reverterJogada{
    int isp;
    lastMove ultimasJogadas[250];
}undoMove;

typedef struct str{
    char str[20];
}string;

//modulo interfaceGrafica.c
int escolhaDeResolucao();
void atribuiResolucao(int * resX,int * resY,int optn);
SDL_Renderer * sdl_initializer();
void clean_sdl(SDL_Texture * image[]);

//modulo criarJogo.c
void preset(int cartas[]);
void presetStr(string cartasStr[]);
void baralhar(int cartas[],string cartasStr[]);
void criarJogo(int matrizCartasJogo[10][21],SDL_Texture * imagensCartas[10][21]);

//modulo funcoesBase.c
int verificaVitoria(int * baralhosCompletos);
int cartaPegavel(int cartaClique,int linhaMatriz,int matrizCartasJogo[10][21]);
int cartaColocavel(int cartaDeBaixo,int cartaDeCima);
