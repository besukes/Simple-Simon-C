#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


void handleGameplay(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,UserBase * args,
SDL_Event event,SDL_Texture* imagensCartas[10][21],Mix_Chunk * arraySom[]){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            (*args).mouseButtonDown = 1;
            efetuaEventoClique(matrizCartasJogo,estadoUndoGlobal,args,event,imagensCartas,arraySom);
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT){
            (*args).mouseButtonDown = 0;
            efetuaEventoSoltar(matrizCartasJogo,estadoUndoGlobal,args,event , imagensCartas);
            resetArgs(args);
        }
    }
}

void handlemenu (UserBase * args, SDL_Event event){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            efetuaEventoCliqueMenu(args,event);
        }
    }
}


void inicializaTexturasJogo(SDL_Texture * imagensJogo[],SDL_Renderer * renderer){
    //imagensJogo[0] = IMG_LoadTexture(renderer,"assets/fundo.png")
    imagensJogo[1] = IMG_LoadTexture(renderer,"assets/Botoes/quit.png");
    imagensJogo[2] = IMG_LoadTexture(renderer,"assets/Botoes/NG.png");
    imagensJogo[3] = IMG_LoadTexture(renderer,"assets/Botoes/undo.png");
    imagensJogo[4] = IMG_LoadTexture(renderer,"assets/Botoes/dica.png");
}


void telaMenu (UserBase * args,SDL_Texture * imagensJogo[], SDL_Event event){
    desenhaMenu(args , imagensJogo , event);
    handlemenu(args,event);
}


void interfaceJogo(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21],
SDL_Texture * imagensJogo[],UserBase * args,SDL_Event event,Mix_Chunk * arraySom[]){
    atualizaEstadoDica(args);
    desenharJogo(matrizCartasJogo , imagensCartas , imagensJogo , args ,event,arraySom);
    handleGameplay(matrizCartasJogo,estadoUndoGlobal,args,event,imagensCartas,arraySom);
    verificaVitoria(matrizCartasJogo,args);
    //temos de fazer
    if(args-> jogada == vitoria);
}

void interfaceSimpleSimon(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21],
SDL_Texture * imagensJogo[],UserBase * args,Mix_Chunk * arraySom[]){
    SDL_Event event;
    inicializaTexturasJogo(imagensJogo,args->rendererBase);
    //enquanto o utilizador nao clicar no botao para sair ele continua no jogo
    while(event.type != SDL_QUIT && args->jogada!= sair){
        SDL_PollEvent(&event);
        SDL_RenderClear((*args).rendererBase);
        if(event.type == SDL_MOUSEMOTION){
            args->mouseX = event.motion.x;
            args->mouseY = event.motion.y;
        }
        if(args->screen == jogo){
            interfaceJogo(matrizCartasJogo,estadoUndoGlobal,imagensCartas,imagensJogo,args,event,arraySom);
        }
        else telaMenu(args,imagensJogo,event);
        SDL_RenderPresent((*args).rendererBase);
    }

}

            
int main(void){
    UserBase args = sdl_initializer();
    SDL_Texture* imagensJogo[10];
    SDL_Texture* imagensCartas[10][21];
    tocamusica();
    Mix_Chunk * arraySom[10];
    inicializaArraySom(arraySom);
    //o limite máximo teórico numa fila de cartas seria 21
    int matrizCartasJogo[10][21];
    undoMove estadoUndoGlobal = {0,{}};
    criarJogo(matrizCartasJogo,imagensCartas,args.rendererBase);
    interfaceSimpleSimon(matrizCartasJogo,&estadoUndoGlobal,imagensCartas,imagensJogo,&args,arraySom);
    clean_sdl(matrizCartasJogo,imagensJogo,imagensCartas,arraySom);
    return 0;
}
