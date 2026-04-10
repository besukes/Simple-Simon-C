#include "simpleSimon.h"

void efetuaEventoClique(int matrizCartasJogo[10][21],int baralhosCompletos[],undoMove * estadoUndoGlobal,
SDL2Bases * args,SDL_Event event){
    const int offset_x=60*(args->resolucaoX),offset_y=40*(args->resolucaoY);
    int linhaClique= (event.button.x)/offset_x,colunaClique= (event.button.y)/offset_y;
}

void efetuaEventoSoltar(int matrizCartasJogo[10][21],int baralhosCompletos[],undoMove * estadoUndoGlobal,
SDL2Bases * args,SDL_Event event){

}