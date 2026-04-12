#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Estas 3 funcoes que se seguem inicializam a matriz imagensCartas com as respectivas texturas que queremos
int primeiras3Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,
int matrizCartasJogo[10][21]){
    int i=0;
    for(int l=0;l<3;l++){
        matrizCartasJogo[l][0] = 8;
        for(int u=1;u<9;u++){
            char str[30];
            sprintf(str,"Cartas/Isoladas/%d.jpg",cartas[i]);
            imagensCartas[l][u]= IMG_LoadTexture(renderer,str);
            matrizCartasJogo[l][u]=cartas[i++];
        }
    }
    return i;
}

void proximas7Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int i,int fila,
int matrizCartasJogo[10][21]){
    matrizCartasJogo[fila][0]=(10-fila);
    for(int n=0;n<=(10-fila);n++){
        char str[30];
        sprintf(str,"Cartas/Isoladas/%d.jpg",cartas[i]);
        imagensCartas[fila][n]= IMG_LoadTexture(renderer,str);
        matrizCartasJogo[fila][n]=cartas[i++];
    }
}

void initMatrizes(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int matrizCartasJogo[10][21]){
    int fila=3,i=primeiras3Linhas(cartas,imagensCartas,renderer,matrizCartasJogo);
    while(fila<10){
        proximas7Linhas(cartas,imagensCartas,renderer,i,fila,matrizCartasJogo);
        fila++;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


void criarJogo(int matrizCartasJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer){
    int cartas[52];preset(cartas);
    shuffleCartas(cartas);
    initMatrizes(cartas,imagensCartas,renderer,matrizCartasJogo);
}
