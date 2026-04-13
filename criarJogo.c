#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


//Estas 3 funcoes que se seguem inicializam a matriz imagensCartas com as respectivas texturas que queremos
int primeiras3Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int matrizCartasJogo[10][21]){
    int i=0;
    for(int l=0;l<3;l++){
        matrizCartasJogo[l][0] = 8;
        for(int u=1;u<9;u++){
            char str[30];
            sprintf(str,"assets/Isoladas/%d.jpg",cartas[i]);
            imagensCartas[l][u]= IMG_LoadTexture(renderer,str);
            matrizCartasJogo[l][u]=cartas[i++];
        }
    }
    return i;
}

int proximas7Linhas(int cartas[],SDL_Texture * mTexturas[10][21],SDL_Renderer * renderer,int i,int fila,int mJogo[10][21]){
    mJogo[fila][0]=(10-fila);
    for(int n=1;n<=(10-fila);n++){
        char str[30];
        sprintf(str,"assets/Isoladas/%d.jpg",cartas[i]);
        mTexturas[fila][n]= IMG_LoadTexture(renderer,str);
        mJogo[fila][n]=cartas[i++];
    }
    return i;
}

void initMatrizes(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int matrizCartasJogo[10][21]){
    int fila=3,i=primeiras3Linhas(cartas,imagensCartas,renderer,matrizCartasJogo);
    while(fila<10){
        i = proximas7Linhas(cartas,imagensCartas,renderer,i,fila,matrizCartasJogo);
        fila++;
    }
}


void criarJogo(int matrizCartasJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer){
    int cartas[52];preset(cartas);
    shuffleCartas(cartas);
    initMatrizes(cartas,imagensCartas,renderer,matrizCartasJogo);
}
