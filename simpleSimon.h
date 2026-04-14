#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef int numCarta;
typedef int filaEscolhida;
typedef int boolean;
typedef enum {invalida,sair,valido} tipoJogada;

typedef struct ultimaJogada{
    numCarta cartas[13];
    SDL_Texture * imgs[13];
    int novaPos;
    int antigaPos;
    numCarta cartasMovidas;
    boolean filaPreenchida;
}lastMove;
typedef struct reverterJogada{
    int isp;
    lastMove ultimasJogadas[250];
}undoMove;


typedef struct sdl2graphics{
    SDL_Renderer * rendererBase;
    int resolucaoX;
    int resolucaoY;
    boolean mouseButtonDown;
    filaEscolhida filaSelecionada;
    numCarta cartas[13];
    SDL_Texture * imgs[13];
    int numCartasSelecionadas;
    tipoJogada jogada;
    int mouseX;
    int mouseY;
}SDL2Bases;


//modulo interfaceGrafica.c
int escolhaDeResolucao(void);
void atribuiResolucao(int * resX,int * resY,int optn);
SDL2Bases sdl_initializer(void);
void clean_sdl(SDL_Texture * image[],SDL_Texture * imagensCartas[10][21]);
void desenharJogo(int matrizJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Texture * imagensJogo[],
SDL2Bases * args,SDL_Event event);
void dragCartas(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21], SDL2Bases *args);

//modulo criarJogo.c
void preset(int cartas[]);
void baralhar(int cartas[]);
void criarJogo(int matrizCartasJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer);
int primeiras3Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int matrizCartasJogo[10][21]);
int proximas7Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int i,int fila,int matrizCartasJogo[10][21]);
void initMatrizes(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int matrizCartasJogo[10][21]);


//modulo funcoesFundamentais.c
void shuffleCartas(int cartas[]);
void preset(int cartas[]);
int valorCarta(int carta);

//modulo funcoesBase.c
int verificaVitoria(int matrizCartasJogo[10][21]);
int cartaPegavel(int cartaClique,int linhaMatriz,int matrizCartasJogo[10][21]);
int cartaColocavel(int cartaDeBaixo,int cartaDeCima);


//modulo eventos.c
void efetuaEventoClique(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL2Bases * args,SDL_Event event , SDL_Texture * images[10][21]);
void efetuaEventoSoltar(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL2Bases * args,SDL_Event event , SDL_Texture * images[10][21]);
void efetuaEventoMotion(int matrizCartasJogo[10][21], SDL2Bases * args);
int dentroDoBotao(SDL_Event e, SDL2Bases * args, float offsetX, float offsetY, float posX, float posY);
int ePosicaoMatriz(int l, int c);

//modulo handleJogadas.c
int desfazerJogada(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal, SDL_Texture * imagensCartas[10][21]);
void adicionaJogadaUndoMove(int matrizCartasJogo[10][21], int pos, SDL2Bases * args, undoMove * estadoUndoGlobal, SDL_Texture * imagensCartas[10][21]);
void rowCompleta(int mcj[10][21], SDL_Texture * img[10][21], int pos, SDL2Bases * args, undoMove * estadoUndoGlobal);
void rowNaoCompleta(int pos, SDL2Bases * args, undoMove * estadoUndoGlobal);
void reeniciaJogo(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal, SDL2Bases * args, SDL_Texture * imagensCartas[10][21]);
void updateEstado(int linhaClique, int colunaClique, int matrizCartasJogo[10][21], SDL2Bases * args,SDL_Texture * imagensCartas[10][21]);
void colocaArrayCartas(int matrizCartasJogo[10][21],SDL2Bases * args,SDL_Texture * imagensCartas[10][21],int linha);
void jogadaNaoRealizada(int mcj[10][21],boolean eventoRelevante,boolean cartaPodeColocar, SDL2Bases * args);