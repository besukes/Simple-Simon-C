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

//modulo interfaceGrafica.c
int escolhaDeResolucao(void);
void atribuiResolucao(int * resX,int * resY,int optn);
SDL_Renderer * sdl_initializer(void);
void clean_sdl(SDL_Texture * image[]);

//modulo criarJogo.c
void preset(int cartas[]);
void baralhar(int cartas[]);
void criarJogo(int matrizCartasJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer);
int primeiras3Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer);
void proximas7Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int numCartas,int * i,int fila);
void initTexturasCartas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer);
int inicializaPrimeiras3Linhas(int cartas[],int matrizCartasJogo[10][21],int * i);
void inicializaMatrizJogo(int cartas[],int matrizCartasJogo[10][21]);

//modulo funcoesFundamentais.c
void shuffleCartas(int cartas[]);
void preset(int cartas[]);

//modulo funcoesBase.c
int verificaVitoria(int * baralhosCompletos);
int cartaPegavel(int cartaClique,int linhaMatriz,int matrizCartasJogo[10][21]);
int cartaColocavel(int cartaDeBaixo,int cartaDeCima);
