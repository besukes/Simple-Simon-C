#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


typedef int numCarta;
typedef int filaEscolhida;
//Uma forma mais sugestiva de representar valores logicos , no fundo apenas sao inteiros que representam 0 ou 1
typedef int boolean;
//TipoJogada representa se o utilizador ganhou , saiu , realizou uma jogada válida ou inválida
typedef enum {invalida,sair,valido,vitoria,tooLarge} tipoJogada;
//Representa a tela atual do utilizador
typedef enum {menu , jogo ,temas , win} UserScreen;
// representa o estilo de carta do utilizador
typedef enum {balatro , solitaire} estiloCarta;


/*O struct ultimaJogada guarda informações sobre a última jogada realizada pelo jogador , como os números das cartas e suas respectivas texturas que ele moveu, 
a antiga posição dessas cartas , como também a nova , o número de cartas movidas e também uma informação se a fila foi ou não completa nessa jogada*/
typedef struct ultimaJogada{
    numCarta cartas[13];
    SDL_Texture * imgs[13];
    int novaPos;
    int antigaPos;
    numCarta cartasMovidas;
    boolean filaPreenchida;
}lastMove;

/*Um Estado Undo guarda um isp que indica quantas jogadas é que já foram realizadas , e também um array de lastMove , onde guarda as informações da
jogada anterior*/
typedef struct reverterJogada{
    int isp;
    lastMove ultimasJogadas[250];
}undoMove;

/*Este struct type guarda um "boolean" que informa se o jogador pretende ou não ter uma dica , guarda o número de dicas disponíveis ,as filas em que estão
presentes cartas jogáveis , como também um timer que informa o tempo restante para aparecer a dica no ecrã*/
typedef struct dicaUtilizador{
    int numDicas;
    boolean querDica;
    int filas[10];
    int timeout;
} DicaStruct;


/*Struct type importantissímo que guarda o renderer(onde colocamos as imagens antes de as apresentar na tela) , a informação se o rato está pressionado , se o
jogador quer uma dica( e se sim todas as informações de cartas que o podem ajudar a continuar a jogar), guarda também a fila selecionada pelo utilizador,
(por default , se o utilizador não estiver com uma fila selecionada então seria -1) guarda também o número de cartas que ele tem selecionado , se tiver , como
também as imagens dessas mesmas cartas e os seus números em dois arrays diferentes.
Consegue ainda guardar qual o tipo da jogada do utilizador , a tela onde está , e a posição do rato em X e em Y , caso seja relevante*/
typedef struct sdl2graphics{
    SDL_Renderer * rendererBase;
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
    int tempo;
    estiloCarta estilo;
    TTF_Font * fonte;
    int score;
}UserBase;


//modulo interfaceGrafica.c
int escolhaDeResolucao(void);
void atribuiResolucao(int * resX,int * resY,int optn);
UserBase sdl_initializer(void);
void clean_sdl(int matrizCartasJogo[10][21],SDL_Texture * image[],SDL_Texture * imagensCartas[10][21],Mix_Chunk * arraySom[]);
void desenhaFundo(UserBase * args, SDL_Texture * imagensJogo[]);
void desenharJogo(int matrizJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Texture * imagensJogo[],UserBase * args,SDL_Event event,Mix_Chunk * arraySom[]);
void dragCartas(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21], UserBase *args,Mix_Chunk * arraySom[]);
void botoes(UserBase * args,SDL_Texture * imagensJogo[]);
void desenhaMenu(UserBase * args , SDL_Texture * imagensJogo[] ,SDL_Event event);
void desenhaTemas(UserBase * args , SDL_Texture *imagensJogo[] ,  SDL_Event event);
void desenhaEstilos(UserBase * args , SDL_Texture *imagensJogo[] ,  SDL_Event event);
void desenhaVitoria(UserBase * args , SDL_Texture *imagensJogo[] ,  SDL_Event event);


//modulo criarJogo.c
void criarJogo(int matrizCartasJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer, UserBase * args);
int primeiras3Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int matrizCartasJogo[10][21], UserBase * args);
int proximas7Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int i,int fila,int matrizCartasJogo[10][21], UserBase * args);
void initMatrizes(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int matrizCartasJogo[10][21], UserBase * args);


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
void efetuaEventoCliqueTemas(UserBase * args, SDL_Event event);
void efetuaEventoCliqueWin(UserBase * args, SDL_Event event , int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal, SDL_Texture * imagensCartas[10][21],Mix_Chunk * arraySom[] );


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
void ngSFX (Mix_Chunk * arraySom[]);

//modulo loadAssets.c
void inicializaArraySom(Mix_Chunk * arraySom[]);
void botoesLoad(SDL_Texture * imagensJogo[],SDL_Renderer * renderer);
void inicializaTexturasJogo(SDL_Texture * imagensJogo[],SDL_Renderer * renderer);
void inicializafonte(UserBase * args);
