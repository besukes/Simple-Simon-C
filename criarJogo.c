#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Estas 3 funcoes que se seguem inicializam a matriz imagensCartas com as respectivas texturas que queremos
int primeiras3Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer){
    int i=0;
    for(int l=0;l<3;l++){
        for(int u=1;u<9;u++){
            char str[8];
            sprintf(str,"Cartas/Isoladas/%d.jpg",cartas[i++]);
            imagensCartas[l][u]= IMG_LoadTexture(renderer,str);
        }
    }
    return i;
}

void proximas7Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int numCartas,int * i,int fila){
    for(int n=0;n<=numCartas;n++){
        char str[8];
            sprintf(str,"Cartas/Isoladas/%d.jpg",cartas[*(i++)]);
            imagensCartas[fila][n]= IMG_LoadTexture(renderer,str);
    }
}

void initTexturasCartas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer){
    int fila=3,cartasFila=7,i=primeiras3Linhas(cartas,imagensCartas,renderer);
    while(cartasFila>0){
        proximas7Linhas(cartas,imagensCartas,renderer,cartasFila--,&i,fila++);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


int inicializaPrimeiras3Linhas(int cartas[],int matrizCartasJogo[10][21],int * i){
    int j=0;
    for(;j<3;j++){
        matrizCartasJogo[j][0]=8;
        for(int u=1;u<9;u++){
            matrizCartasJogo[j][u]=cartas[*(i++)];
        }
    }
    return j;
}

void inicializaMatrizJogo(int cartas[],int matrizCartasJogo[10][21]){
    int i=0,j=inicializaPrimeiras3Linhas(cartas,matrizCartasJogo,&i),numCartas=7;
    do{
        matrizCartasJogo[j][0]=numCartas;
        for(int n=0;n<=numCartas;n++){
            matrizCartasJogo[j][n]=cartas[i++];
        }
        j++;
    }while((numCartas--)>0);
}

void criarJogo(int matrizCartasJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer){
    int cartas[52];preset(cartas);
    shuffleCartas(cartas);
    initTexturasCartas(cartas,imagensCartas,renderer);
    inicializaMatrizJogo(cartas,matrizCartasJogo);
}
