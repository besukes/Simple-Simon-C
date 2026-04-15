#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

typedef int numCarta;
typedef int filaEscolhida;
typedef int boolean;
typedef enum {invalida,sair,valido,vitoria} tipoJogada;
typedef enum {menu , jogo} UserScreen;

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

typedef struct dicaUtilizador{
    int numDicas;
    boolean querDica;
    int filas[10];
    int timeout;
} DicaStruct;

typedef struct sdl2graphics{
    SDL_Renderer * rendererBase;
    //int resolucaoX;
    //int resolucaoY;
    boolean mouseButtonDown;
    DicaStruct dica;
    filaEscolhida filaSelecionada;
    numCarta cartas[13];
    SDL_Texture * imgs[13];
    int numCartasSelecionadas;
    tipoJogada jogada;
    int mouseX;
    int mouseY;
    UserScreen screen;
}UserBase;


//modulo interfaceGrafica.c
int escolhaDeResolucao(void);
void atribuiResolucao(int * resX,int * resY,int optn);
UserBase sdl_initializer(void);
void clean_sdl(int matrizCartasJogo[10][21],SDL_Texture * image[],SDL_Texture * imagensCartas[10][21],Mix_Chunk * arraySom[]);
void desenhaFundo(UserBase * args,SDL_Texture * imagensJogo[]);
void desenharJogo(int matrizJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Texture * imagensJogo[],UserBase * args,SDL_Event event,Mix_Chunk * arraySom[]);
void dragCartas(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21], UserBase *args,Mix_Chunk * arraySom[]);
void botoes(UserBase * args,SDL_Texture * imagensJogo[]);
void desenhaMenu(UserBase * args , SDL_Texture * imagensJogo[] ,SDL_Event event);


//modulo criarJogo.c
void criarJogo(int matrizCartasJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer);
int primeiras3Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int matrizCartasJogo[10][21]);
int proximas7Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int i,int fila,int matrizCartasJogo[10][21]);
void initMatrizes(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int matrizCartasJogo[10][21]);


//modulo funcoesFundamentais.c
void shuffleCartas(int cartas[]);
void preset(int cartas[]);
int valorCarta(int carta);


//modulo funcoesBase.c
void verificaVitoria(int matrizCartasJogo[10][21],UserBase * args);
int cartaPegavel(int cartaClique,int linhaMatriz,int matrizCartasJogo[10][21]);
int cartaColocavel(int cartaDeBaixo,int cartaDeCima);
void resetArgs(UserBase * args);
int dentroDoBotao(SDL_Event e,UserBase * args,float width,float height,float posX,float posY);
int ePosicaoMatriz(int l,int c);
void resetArgs(UserBase * args);
void colocaDicaUtilizador(int matrizCartasJogo[10][21],UserBase *args);
int calculaUltimaCartaPegavel(int matrizCartasJogo[10][21],int linha,int numCartas);
void resetDicaArgs(UserBase * args);
boolean verificaFilaCompleta(int matrizCartasJogo[10][21],int linha);


//modulo eventos.c
void efetuaEventoClique(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,UserBase * args,SDL_Event event , SDL_Texture * images[10][21],Mix_Chunk * arraySom[]);
void efetuaEventoSoltar(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,UserBase * args,SDL_Event event , SDL_Texture * images[10][21]);
boolean verificaFilaCompleta(int matrizCartasJogo[10][21],int linha);
int calculaPosXClique(float posX);
int calculaPosYClique(int matrizCartasJogo[10][21], int posX, float posY);
void efetuaEventoCliqueMenu(UserBase * args, SDL_Event event);


//modulo handleJogadas.c
void desfazerFilaCompleta(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21]);
void desfazJogadaBasica(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21]);
int desfazerJogada(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal, SDL_Texture * imagensCartas[10][21]);
void adicionaJogadaUndoMove(int matrizCartasJogo[10][21], int pos, UserBase * args, undoMove * estadoUndoGlobal, SDL_Texture * imagensCartas[10][21],boolean filaCompleta);
void rowCompleta(int mcj[10][21], SDL_Texture * img[10][21], int pos, UserBase * args, undoMove * estadoUndoGlobal);
void rowNaoCompleta(int pos, UserBase * args, undoMove * estadoUndoGlobal);
void reeniciaJogo(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal, UserBase * args, SDL_Texture * imagensCartas[10][21]);
void updateEstado(int linhaClique, int colunaClique, int matrizCartasJogo[10][21], UserBase * args,SDL_Texture * imagensCartas[10][21]);
int colocaArrayCartas(int matrizCartasJogo[10][21],UserBase * args,SDL_Texture * imagensCartas[10][21],int linha);
void jogadaNaoRealizada(int mcj[10][21],boolean eventoRelevante,boolean cartaPodeColocar, UserBase * args,SDL_Texture * imagensCata[10][21]);


//modulo dicas.c
void jogadorPrecisaDica(UserBase * args,int linha);
void colocaDicaUtilizador(int matrizCartasJogo[10][21],UserBase *args);
void atualizaEstadoDica(UserBase * args);


//modulo audio.c
void tocamusica(void);
void inicializaArraySom(Mix_Chunk * arraySom[]);
void tocaPegaCarta (Mix_Chunk * arraySom[]);
void undoSFX (Mix_Chunk * arraySom[]);
