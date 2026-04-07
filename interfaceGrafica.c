#include"simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
    SDL2Bases args={.rendererBase=renderer,.resolucaoX=resX,.resolucaoY=resY,.mouseButtonDown=0,.filaSelecionada=(-1)};
    return args;
}

void clean_sdl(SDL_Texture * image[],SDL_Texture * imagensCartas[10][21]){
    for(int i=0;i<10;i++){
        SDL_DestroyTexture(image[i]); //temos que apagar a imagem da memoria da gpu
    }
    IMG_Quit(); //informar a gpu que ja nao é preciso criar uma window
    SDL_Quit();
}

void desenharJogo(int matrizJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Texture * imagensJogo[],
SDL2Bases args,SDL_Event event){

}
