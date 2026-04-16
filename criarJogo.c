#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


/*Função que inicializa as matrizes de cartas e texturas das primeiras 3 linhas (8 cartas cada)*/
int primeiras3Linhas(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int matrizCartasJogo[10][21], UserBase * args){
    int i=0;
    for(int l=0;l<3;l++){
        matrizCartasJogo[l][0] = 8;
        if (args->estilo == balatro)
        {
          for(int u=1;u<9;u++){
          char str[30];
          sprintf(str,"assets/Isoladas/%d.jpg",cartas[i]);
          imagensCartas[l][u]= IMG_LoadTexture(renderer,str);
          matrizCartasJogo[l][u]=cartas[i++];
          }
        }
        else if (args->estilo == solitaire)
        {
          for(int u=1;u<9;u++){
          char str[30];
          sprintf(str,"assets/solitaire/%d.png",cartas[i]);
          imagensCartas[l][u]= IMG_LoadTexture(renderer,str);
          matrizCartasJogo[l][u]=cartas[i++];
          }
        }
        
        
    }
    return i;
}

/* Função que inicializa as matrizes de cartas e texturas das restantes 7 linhas.
Esta função coloca cartas do array cartas na matrizJogo e nas de textura(dá LOAD às texturas), do indice 1 até ao indice 10-fila (Resultado fácil de compreender
ao olhar para o jogo corrido) */
int proximas7Linhas(int cartas[],SDL_Texture * mTexturas[10][21],SDL_Renderer * renderer,int i,int fila,int mJogo[10][21], UserBase * args){
    mJogo[fila][0]=(10-fila);
    for(int n=1;n<=(10-fila);n++){
        char str[30];
            if (args->estilo == balatro)
            {
            sprintf(str,"assets/Isoladas/%d.jpg",cartas[i]);
            mTexturas[fila][n]= IMG_LoadTexture(renderer,str);
            mJogo[fila][n]=cartas[i++];
            }
            else if (args->estilo == solitaire)
            {
            sprintf(str,"assets/solitaire/%d.png",cartas[i]);
            mTexturas[fila][n]= IMG_LoadTexture(renderer,str);
            mJogo[fila][n]=cartas[i++];
            }
    }
    return i;
}

/* Função que inicializa as matrizes de cartas e texturas das primeiras 1-3 linhas e das restantes 7 linhas , pois estas comportam se de forma diferente */
void initMatrizes(int cartas[],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer,int matrizCartasJogo[10][21], UserBase * args){
    int fila=3,i=primeiras3Linhas(cartas,imagensCartas,renderer,matrizCartasJogo, args);
    while(fila<10){
        i = proximas7Linhas(cartas,imagensCartas,renderer,i,fila,matrizCartasJogo, args);
        fila++;
    }
}

/* Função principal do módulo criarJogo.c , que cria o jogo, inicializando as matrizes e carregando as texturas das cartas para uma matriz congruente à do jogo*/
void criarJogo(int matrizCartasJogo[10][21],SDL_Texture * imagensCartas[10][21],SDL_Renderer * renderer, UserBase * args){
    int cartas[52];preset(cartas);
    shuffleCartas(cartas);
    initMatrizes(cartas,imagensCartas,renderer,matrizCartasJogo, args);
}
