#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void interfaceJogo(int matrizCartasJogo[10][21],int baralhosCompletos[], undoMove estadoUndoGlobal,
SDL_Texture * imagensCartas[10][21],SDL_Texture * imagensJogo[],SDL2Bases args){
    
}


int main(void){
    SDL2Bases args = sdl_initializer();
    //precisamos de uma função que inicialize estes dois
    SDL_Texture* imagensJogo[10];
    SDL_Texture* imagensCartas[10][21];
    //o limite máximo teórico numa fila de cartas seria 21
    int matrizCartasJogo[10][21], baralhosCompletos[4]={0};
    undoMove estadoUndoGlobal = {0,{}};
    criarJogo(matrizCartasJogo,imagensCartas,args.rendererBase);
    interfaceJogo(matrizCartasJogo,baralhosCompletos,estadoUndoGlobal,imagensCartas,imagensJogo,args);
    clean_sdl(imagensJogo,imagensCartas);
    return 0;
}
