#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


void desfazerJogada(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21]){
    int linhaAtual=estadoUndoGlobal->ultimasJogadas[--estadoUndoGlobal->isp].novaPos,
        linhaAntiga=estadoUndoGlobal->ultimasJogadas[--estadoUndoGlobal->isp].antigaPos,
        numCartas = estadoUndoGlobal->ultimasJogadas[--estadoUndoGlobal->isp].cartasMovidas;
    matrizCartasJogo[linhaAtual][0]-=numCartas;
    int * arrayCartas=estadoUndoGlobal->ultimasJogadas[--estadoUndoGlobal->isp].cartas,
          numLantiga = matrizCartasJogo[linhaAntiga][0];
          
    SDL_Texture * *images;
    images = (estadoUndoGlobal->ultimasJogadas[--estadoUndoGlobal->isp]).imgs;
    for(int i=0;i<numCartas;i++){
        matrizCartasJogo[linhaAntiga][numLantiga+i] = arrayCartas[i];
        imagensCartas[linhaAntiga][numLantiga+i] = images[i];
        matrizCartasJogo[linhaAntiga][0]++;
    }
    estadoUndoGlobal->isp --;
}

void adicionaJogadaUndoMove(int matrizCartasJogo[10][21],int pos,SDL2Bases * args,undoMove * estadoUndoGlobal,
SDL_Texture * imagensCartas[10][21]){
    boolean b = 1;
    int nCartas=matrizCartasJogo[pos][0],ant=matrizCartasJogo[pos][nCartas];
    for(int i=nCartas;i>0;i--){
            if(!((ant/13)==(matrizCartasJogo[pos][i-1]/13))) b=0;
        }
    if(nCartas==13 && b==1){
        rowCompleta(matrizCartasJogo,imagensCartas,pos,args,estadoUndoGlobal);
        estadoUndoGlobal->isp++;
    }
    else{
        rowNaoCompleta(pos,args,estadoUndoGlobal);
        estadoUndoGlobal->isp++;
    }
}

void rowCompleta(int mcj[10][21],SDL_Texture * img[10][21],int pos,SDL2Bases * args,undoMove * estadoUndoGlobal){
    estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].antigaPos = args->filaSelecionada;
    estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].novaPos = pos;
    estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].cartasMovidas = 13;
     for(int i=0;i<13;i++){
        estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].cartas[i] = mcj[pos][i];
        estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].imgs[i] = img[pos][i];
    }
}

void rowNaoCompleta(int pos,SDL2Bases * args,undoMove * estadoUndoGlobal){
    int numCartasJogadas=args->numCartasSelecionadas;
        estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].antigaPos = args->filaSelecionada;
        estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].novaPos = pos;
        estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].cartasMovidas = numCartasJogadas;;
    for(int i=0;i<numCartasJogadas;i++){
        estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].cartas[i] = args->cartas[i];
        estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].imgs[i] = args->imgs[i];
    }
}

void reeniciaJogo(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL2Bases * args,
SDL_Texture * imagensCartas[10][21]){
    estadoUndoGlobal->isp=0;
    args->filaSelecionada=(-1);
    args->numCartasSelecionadas=0;
    SDL_RenderClear(args->rendererBase);
    criarJogo(matrizCartasJogo,imagensCartas,args->rendererBase);
}

void updateEstado(int linhaClique,int colunaClique,int matrizCartasJogo[10][21],SDL2Bases * args){

}

void colocaArrayCartas(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL2Bases * args,
SDL_Texture * imagensCartas[10][21]){

}

void jogadaNaoRealizada(int matrizCartasJogo[10][21],SDL2Bases * args){

}

