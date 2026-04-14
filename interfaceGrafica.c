#include"simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

int escolhaDeResolucao(void){
    printf("Introduza o número da resolução que pretende utilizar\n(1)-1280x720;\n(2)-1600x900\n(3)-1920x1080\n");
    int u;
    scanf("%d",&u);
    return u;
}

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

SDL2Bases sdl_initializer(void){
    SDL_Init(SDL_INIT_VIDEO);
    int resolution=escolhaDeResolucao(),resX,resY;
    atribuiResolucao(&resX,&resY,resolution);
    SDL_Window* window = SDL_CreateWindow("Simple Simon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resX, resY, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //para nao precisar de dar scale as imagens no ecra
    SDL_RenderSetLogicalSize(renderer, 1920, 1080);
    // se nao der compile usar flags -std=c99 ou -std=c11
    SDL2Bases args={.rendererBase=renderer,.mouseButtonDown=0,.filaSelecionada=(-1),
        .numCartasSelecionadas=0,.cartas={},.resolucaoX=resX,.resolucaoY=resY,.jogada=valido ,.TelaAtual = 1};
    return args;
}

void clean_sdl(int matrizCartasJogo[10][21],SDL_Texture * image[],SDL_Texture * imagensCartas[10][21]){
    //temos que apagar a imagem da memoria da gpu
    for(int i=0;i<10;i++){
        SDL_DestroyTexture(image[i]);
        for(int j=1;j<=matrizCartasJogo[i][0];j++){
            SDL_DestroyTexture(imagensCartas[i][j]);
        }
    }
    IMG_Quit(); //informar a gpu que ja nao é preciso criar uma window
    SDL_Quit();
}

void desenhaFundo(SDL2Bases * args,SDL_Texture * imagensJogo[]){
    SDL_Rect fundo = {0, 0, 1920, 1080};
    SDL_RenderCopy(args->rendererBase, imagensJogo[0], NULL, &fundo);
}

void botoes(SDL2Bases * args,SDL_Texture * imagensJogo[]){
    SDL_Rect botaoSair = {400, 1000, 200, 50};
    SDL_Rect botaoReiniciar = {700, 1000, 200, 50};
    SDL_Rect botaoDesfazer = {1000, 1000, 200, 50};
    SDL_RenderCopy(args->rendererBase, imagensJogo[1], NULL, &botaoSair);
    SDL_RenderCopy(args->rendererBase, imagensJogo[2], NULL, &botaoReiniciar);
    SDL_RenderCopy(args->rendererBase, imagensJogo[3], NULL, &botaoDesfazer);
}


void desenharCartas(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21], SDL2Bases *args){
    int cartaW = 140, cartaH = 190, offsetX = 75, espacoX = 178, offsetY = 80, passo = 32;
    for (int col = 0; col < 10; col++) {
        for (int row = 1; row <= matrizJogo[col][0]; row++) {
            SDL_Rect dest;
            //A posicao dos rentangulos esta definida pelo canto esquerdo superior deste mesmo
            dest.x = offsetX + col * espacoX;
            dest.y = offsetY + row * passo; 
            dest.w = cartaW;
            dest.h = cartaH;
            SDL_RenderCopy(args->rendererBase, imagensCartas[col][row], NULL, &dest);
        }
    }
}

void desenharJogo(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21],SDL_Texture *imagensJogo[], SDL2Bases *args, SDL_Event event) {
    SDL_SetRenderDrawColor(args->rendererBase, 0, 120, 0, 255);
    // Fundo
    desenhaFundo(args, imagensJogo);
    desenharCartas(matrizJogo,imagensCartas,args);
    botoes(args,imagensJogo);
    if (args->filaSelecionada != -1 && args->numCartasSelecionadas > 0)
    {
        dragCartas(matrizJogo, imagensCartas, args);
    }
    SDL_RenderPresent(args->rendererBase);
}
void desenhaMenu(SDL2Bases * args , SDL_Texture *imagensJogo[] ,  SDL_Event event)
{
    desenhaFundo(args , imagensJogo);
    
}
void dragCartas(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21], SDL2Bases *args) {
    int cartaW = 140, cartaH = 190, passo = 32;
    for (int i = 0; i < args->numCartasSelecionadas; i++) {
        SDL_Rect dest;
        dest.x = args->mouseX - 70;
        dest.y = args->mouseY + i * passo - 65;
        dest.w = cartaW;
        dest.h = cartaH;
        SDL_RenderCopy(args->rendererBase, args->imgs[i], NULL, &dest);
    }
    tocaCartaPega();
}
void tocaCartaPega (void)
{
    Mix_Chunk* pgCarta = NULL;
    pgCarta = Mix_LoadWAV("sfx/CardDrop.mp3");
    Mix_VolumeChunk(pgCarta , 128);
    Mix_PlayChannel(1 , pgCarta, 0);
}