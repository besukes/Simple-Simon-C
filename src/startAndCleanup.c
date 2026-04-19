#include"simpleSimon.h"
#include <SDL2/SDL.h>

/*Pergunta inicialmente ao utilizador a resolução que pretende utilizar no seu jogo*/
int escolhaDeResolucao(void){
    printf("Introduza o número da resolução que pretende utilizar\n(1)-1280x720;\n(2)-1600x900\n(3)-1920x1080\n");
    int u;
    scanf("%d",&u);
    return u;
}

/*Função que dado uma opção de resolução atribui os valores de largura e altura da janela*/
void atribuiResolucao(int * resX,int * resY,int optn){
    switch(optn){
        case 1:
            *resX=1280;*resY=720;
        break;
        case 2:
            *resX=1600;*resY=900;
        break;
        case 3:
            *resX=1920;*resY=1080;
        break;
        //passivel de mudancas
        default:
            *resX=1920;*resY=1080;
    }
}

/*Função que inicializa o SDL e cria a janela do jogo, tal como criar um tipo UserBase args e retorná-lo.
    Este UserBase contém toda a informação importante e necessária para o funcionamento do jogo e das suas funcionalidades*/
UserBase sdl_initializer(void){
    SDL_Init(SDL_INIT_VIDEO);
    int resolution=escolhaDeResolucao(),resX,resY;
    atribuiResolucao(&resX,&resY,resolution);
    SDL_Window* window = SDL_CreateWindow("Simple Simon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resX, resY, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //para não precisar de dar scale às imagens no ecrã
    SDL_RenderSetLogicalSize(renderer, 1920, 1080);
    // se nao der compile usar flags -std=c99 ou -std=c11
    UserBase args={.rendererBase=renderer,.mouseButtonDown=0,.filaSelecionada=(-1),.numCartasSelecionadas=0,
        .cartas={},.jogada=valido ,.screen = menu,.dica.querDica=0,.dica.numDicas=0,.dica.timeout=0, .estilo = balatro, .score=1};
    return args;
}

void freeArraySom(Mix_Chunk * arraySom[]){
    for(int i=0;i<3;i++){
        Mix_FreeChunk(arraySom[i]);
    }
}

/*No final da execução do programa, liberta a memória alocada para as texturas e apaga a window criada*/
void clean_sdl(int matrizCartasJogo[10][21],SDL_Texture * image[],SDL_Texture * imagensCartas[10][21],Mix_Chunk * arraySom[]){
    //temos que apagar a imagem da memoria da gpu
    for(int i=0;i<10;i++){
        for(int j=1;j<=matrizCartasJogo[i][0];j++){
            SDL_DestroyTexture(imagensCartas[i][j]);
        }
    }
    //era mais otimizado destruir no primeiro ciclo as imagens de 0-10 e depois o resto,
    //porem por causa das instrucoes nao podemos e portanto fica assim
    for(int i=0;i<22;i++){
        SDL_DestroyTexture(image[i]);
    }
    freeArraySom(arraySom);
    IMG_Quit(); //informar a gpu que ja nao é preciso criar uma window
    SDL_Quit();
}