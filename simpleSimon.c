#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


void handleGameplay(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL2Bases * args,
SDL_Event event,SDL_Texture* imagensCartas[10][21]){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            (*args).mouseButtonDown = 1;
            efetuaEventoClique(matrizCartasJogo,estadoUndoGlobal,args,event , imagensCartas);
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
void handlemenu (SDL2Bases * args, SDL_Event event){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            efetuaEventoCliqueMenu(args,event);
        }
    }
}
void inicializaTexturasJogo(SDL_Texture * imagensJogo[],SDL_Renderer * renderer){
    //imagensJogo[0] = IMG_LoadTexture(renderer,"assets/fundo.png")
    imagensJogo[1] = IMG_LoadTexture(renderer,"assets/quit.png");
    imagensJogo[2] = IMG_LoadTexture(renderer,"assets/NG.png");
    imagensJogo[3] = IMG_LoadTexture(renderer,"assets/undo.png");
}
void telaUtilizador (int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21],
SDL_Texture * imagensJogo[],SDL2Bases * args, SDL_Event event)
{
    switch (args->screen)
    {
    case menu:
        desenhaMenu(args , imagensJogo , event);
        handlemenu(args,event);
    break;
    
    case jogo:
        verificaVitoria(matrizCartasJogo,args);
        desenharJogo(matrizCartasJogo , imagensCartas , imagensJogo , args ,event);
            //TEMOS DE FAZER
        if(args-> jogada==vitoria) ;
        handleGameplay(matrizCartasJogo,estadoUndoGlobal,args,event,imagensCartas);
    break;
    default:
    break;
    }
}

void interfaceJogo(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21],
SDL_Texture * imagensJogo[],SDL2Bases * args){
    SDL_Event event;
    inicializaTexturasJogo(imagensJogo,args->rendererBase);
    //enquanto o utilizador nao clicar no botao para sair ele continua no jogo
    tipoJogada jogada = (*args).jogada;
    while(event.type != SDL_QUIT && jogada!= sair){
        SDL_PollEvent(&event);
        if(event.type == SDL_MOUSEMOTION){
            args->mouseX = event.motion.x;
            args->mouseY = event.motion.y;
        }
        SDL_RenderClear((*args).rendererBase);
        telaUtilizador(matrizCartasJogo,estadoUndoGlobal,imagensCartas,imagensJogo,args,event);
        SDL_RenderPresent((*args).rendererBase);
    }

}

void tocamusica(void){
    Mix_Music *balatro = NULL;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    balatro = Mix_LoadMUS("musica/balatro.mp3");
    Mix_PlayMusic(balatro, -1); 
    Mix_VolumeMusic(64);
}

            
int main(void){
    SDL2Bases args = sdl_initializer();
    SDL_Texture* imagensJogo[10];
    SDL_Texture* imagensCartas[10][21];
    tocamusica();
    //o limite máximo teórico numa fila de cartas seria 21
    int matrizCartasJogo[10][21];
    undoMove estadoUndoGlobal = {0,{}};
    criarJogo(matrizCartasJogo,imagensCartas,args.rendererBase);
    interfaceJogo(matrizCartasJogo,&estadoUndoGlobal,imagensCartas,imagensJogo,&args);
    clean_sdl(matrizCartasJogo,imagensJogo,imagensCartas);
    return 0;
}
