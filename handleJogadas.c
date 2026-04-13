#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


void desfazerFilaCompleta(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21]){
    int isp = estadoUndoGlobal->isp,
        linhaCompleta = estadoUndoGlobal->ultimasJogadas[isp].novaPos,
        linhaAnterior = estadoUndoGlobal->ultimasJogadas[isp].antigaPos,
        numCartasColocadas = estadoUndoGlobal->ultimasJogadas[isp].cartasMovidas;
    int i,m = matrizCartasJogo[linhaAnterior][0];
    matrizCartasJogo[linhaCompleta][0] = 13-numCartasColocadas;
    for(i=1;i<=13-numCartasColocadas;i++){
        matrizCartasJogo[linhaCompleta][i] = estadoUndoGlobal->ultimasJogadas[isp].cartas[i];
        imagensCartas[linhaCompleta][i] = estadoUndoGlobal->ultimasJogadas[isp].imgs[i];
    }
    for(int j=1;i<13;i++,j++){
        matrizCartasJogo[linhaAnterior][m+j] = estadoUndoGlobal->ultimasJogadas[isp].cartas[i];
        imagensCartas[linhaAnterior][m+j] = estadoUndoGlobal->ultimasJogadas[isp].imgs[i];
    }
}

void desfazerJogada(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21]){
    int isp = -- (estadoUndoGlobal->isp);
    //SE a fila tiver sido completa nesta jogada entao e um caso especial , que deve ser tratado a parte..
    if(estadoUndoGlobal->ultimasJogadas[isp].filaPreenchida){
        desfazerFilaCompleta(matrizCartasJogo,estadoUndoGlobal,imagensCartas);
    }
    else{
        //Inicilizamos todas as variaveis que precisamos para desfazer a jogada , para facilitar a leitura
        int linhaAtual = estadoUndoGlobal->ultimasJogadas[isp].novaPos,
            linhaAntiga = estadoUndoGlobal->ultimasJogadas[isp].antigaPos,
            numCartas = estadoUndoGlobal->ultimasJogadas[isp].cartasMovidas,
            numCLantiga = matrizCartasJogo[linhaAntiga][0];
        int * arrayCartas=estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].cartas;
        //Para facilitar a leitura criamos uma variavel que e um apontador de memoria de uma posicao onde esta um apontador de memoria
        SDL_Texture * * images= (estadoUndoGlobal->ultimasJogadas[--estadoUndoGlobal->isp]).imgs;
        //A fila nao se completou com a jogada , ao desfazer a jogada simplesmente retiramos as cartas e pomos na outra fila
        matrizCartasJogo[linhaAtual][0]-=numCartas;
        for(int i=0;i<numCartas;i++){
            matrizCartasJogo[linhaAntiga][numCLantiga+i] = arrayCartas[i];
            imagensCartas[linhaAntiga][numCLantiga+i] = images[i];
            matrizCartasJogo[linhaAntiga][0]++;
        }
    }
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
    estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].cartasMovidas = args->numCartasSelecionadas;
    estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].filaPreenchida = 1;
     for(int i=0;i<13;i++){
        estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].cartas[i] = mcj[pos][i];
        estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].imgs[i] = img[pos][i];
    }
}

void rowNaoCompleta(int pos,SDL2Bases * args,undoMove * estadoUndoGlobal){
    int numCartasJogadas=args->numCartasSelecionadas , isp = estadoUndoGlobal->isp;
    estadoUndoGlobal->ultimasJogadas[isp].antigaPos = args->filaSelecionada;
    estadoUndoGlobal->ultimasJogadas[isp].novaPos = pos;
    estadoUndoGlobal->ultimasJogadas[isp].cartasMovidas = numCartasJogadas;
    estadoUndoGlobal->ultimasJogadas[isp].filaPreenchida = 0;
    for(int i=0;i<numCartasJogadas;i++){
        estadoUndoGlobal->ultimasJogadas[isp].cartas[i] = args->cartas[i];
        estadoUndoGlobal->ultimasJogadas[isp].imgs[i] = args->imgs[i];
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

void updateEstado(int linhaClique, int colunaClique, int matrizCartasJogo[10][21], SDL2Bases *args) {
    args->filaSelecionada = linhaClique;
    args->numCartasSelecionadas = matrizCartasJogo[linhaClique][0] - colunaClique + 1;
    args->jogada = valido;
}

void colocaArrayCartas(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL2Bases * args,
SDL_Texture * imagensCartas[10][21]){

}

void jogadaNaoRealizada(int matrizCartasJogo[10][21],SDL2Bases * args){

}

