#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void handleGameplay(int matrizCartasJogo[10][21],int baralhosCompletos[],undoMove * estadoUndoGlobal,SDL2Bases * args,
SDL_Event event){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            (*args).mouseButtonDown = 1;
            efetuaEventoClique(matrizCartasJogo,baralhosCompletos,estadoUndoGlobal,args,event);
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT){
            (*args).mouseButtonDown = 0;
            //o utilizador possui uma fila selecionada e quer coloca-la num local,temos de verificar se e valido..
            if((*args).filaSelecionada!=(-1)){
                efetuaEventoSoltar(matrizCartasJogo,baralhosCompletos,estadoUndoGlobal,args,event);
                // (*args).filaSelecionada = args->filaSelecionada
                args->filaSelecionada=(-1);
                args->numCartasSelecionadas=0;
            }
        }
    }
}


void interfaceJogo(int matrizCartasJogo[10][21],int baralhosCompletos[], undoMove * estadoUndoGlobal,
SDL_Texture * imagensCartas[10][21],SDL_Texture * imagensJogo[],SDL2Bases * args){
    SDL_Event event;
    //enquanto o utilizador nao clicar no botao para sair ele continua no jogo
    while(event.type != SDL_QUIT && (*args).jogada!=sair){
        SDL_PollEvent(&event);
        SDL_RenderClear((*args).rendererBase);
        desenharJogo(matrizCartasJogo,imagensCartas,imagensJogo,args,event);
        SDL_RenderPresent((*args).rendererBase);
        handleGameplay(matrizCartasJogo,baralhosCompletos,estadoUndoGlobal,args,event);
    }
}


int main(void){
    SDL2Bases args = sdl_initializer();
    SDL_Texture* imagensJogo[10];
    SDL_Texture* imagensCartas[10][21];
    //o limite máximo teórico numa fila de cartas seria 21
    int matrizCartasJogo[10][21], baralhosCompletos[4]={0};
    undoMove estadoUndoGlobal = {0,{}};
    criarJogo(matrizCartasJogo,imagensCartas,args.rendererBase);
    interfaceJogo(matrizCartasJogo,baralhosCompletos,&estadoUndoGlobal,imagensCartas,imagensJogo,&args);
    clean_sdl(imagensJogo,imagensCartas);
    return 0;
}
