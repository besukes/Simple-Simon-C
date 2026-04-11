#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void handleGameplay(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL2Bases * args,
SDL_Event event,SDL_Texture* imagensCartas[10][21]){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            (*args).mouseButtonDown = 1;
            efetuaEventoClique(matrizCartasJogo,estadoUndoGlobal,args,event);
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT){
            (*args).mouseButtonDown = 0;
            //o utilizador possui uma fila selecionada e quer coloca-la num local,temos de verificar se e valido..
            if((*args).filaSelecionada!=(-1)){
                efetuaEventoSoltar(matrizCartasJogo,estadoUndoGlobal,args,event);
                // (*args).filaSelecionada = args->filaSelecionada
                args->filaSelecionada=(-1);
                args->numCartasSelecionadas=0;
            }
        }
    }
    else if(event.type == SDL_MOUSEMOTION && args->mouseButtonDown && args->numCartasSelecionadas){
        efetuaEventoMotion(matrizCartasJogo,args);
    }
}


void interfaceJogo(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21],
SDL_Texture * imagensJogo[],SDL2Bases * args){
    SDL_Event event;
    //enquanto o utilizador nao clicar no botao para sair ele continua no jogo
    while(event.type != SDL_QUIT && (*args).jogada!=sair){
        SDL_PollEvent(&event);
        SDL_RenderClear((*args).rendererBase);
        desenharJogo(matrizCartasJogo,imagensCartas,imagensJogo,args,event);
        SDL_RenderPresent((*args).rendererBase);
        handleGameplay(matrizCartasJogo,estadoUndoGlobal,args,event,imagensCartas);
    }
}


int main(void){
    SDL2Bases args = sdl_initializer();
    SDL_Texture* imagensJogo[10];
    SDL_Texture* imagensCartas[10][21];
    //o limite máximo teórico numa fila de cartas seria 21
    int matrizCartasJogo[10][21];
    undoMove estadoUndoGlobal = {0,{}};
    criarJogo(matrizCartasJogo,imagensCartas,args.rendererBase);
    interfaceJogo(matrizCartasJogo,&estadoUndoGlobal,imagensCartas,imagensJogo,&args);
    clean_sdl(imagensJogo,imagensCartas);
    return 0;
}
