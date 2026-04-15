#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void verificaVitoria(int m[10][21],UserBase * args){
    int n=0;
    for(int i=0;i<10;i++) n+=m[i][0];
    n+= args->numCartasSelecionadas;
    //O jogo acabou se nao houverem cartas em nenhuma das 10 pilhas
    if(!n) args->jogada=vitoria;
}


int cartaPegavel(int cartaClique, int linha, int mcj[10][21]) {
    int i;
    if (cartaClique == (-1)) return 0;
    int max = mcj[linha][0],naipe = (cartaClique - 1) / 13;
    for (i = max;i > 1 && (mcj[linha][i] - 1)/13 == naipe && cartaColocavel(mcj[linha][i-1],mcj[linha][i]); i--){
        if(mcj[linha][i]==cartaClique) return 1;
    }
    return (mcj[linha][i] == cartaClique);
}

//Pode se colocar uma carta em cima de outra caso 
int cartaColocavel(int cartaDeBaixo,int cartaDeCima){
    return((valorCarta(cartaDeBaixo)-valorCarta(cartaDeCima))==1);
}

int dentroDoBotao(SDL_Event e,UserBase * args,float width,float height,float posX,float posY){
    int x=e.button.x,y=e.button.y;
    return ( (posX<=x && posX+width>=x) && (posY<=y && posY+height>=y));
}

int ePosicaoMatriz(int l,int c){
    return (l>=0 && l<10 && c>=0 && c<21);
}

void resetArgs(UserBase * args){
    args->filaSelecionada=(-1);
    args->numCartasSelecionadas=0;
    args->jogada=valido;
    args->mouseButtonDown=0;
}

void resetDicaArgs(UserBase * args){
    args->dica.querDica=0;
    args->dica.numDicas=0;
    args->dica.timeout=0;
}

int calculaUltimaCartaPegavel(int matrizCartasJogo[10][21],int linha,int numCartas){
    if(numCartas==0) return (-1);
    int cartaFinal=matrizCartasJogo[linha][numCartas];
    for(int i=numCartas-1;i>0 && (matrizCartasJogo[linha][i] - 1)/13 == (cartaFinal - 1)/13 
    && (matrizCartasJogo[linha][i] - cartaFinal == 1);i--){
        cartaFinal = matrizCartasJogo[linha][i];
    }
    return cartaFinal;
}


boolean verificaFilaCompleta(int matrizCartasJogo[10][21],int linha){
    boolean bool=1;
    int nCartas=matrizCartasJogo[linha][0],ultCartaFila=matrizCartasJogo[linha][nCartas];
    int naipe = (ultCartaFila - 1)/13;
    for(int i=nCartas-1;i>0 && bool;i--){
        if((matrizCartasJogo[linha][i] - 1 )/13 != naipe || !(cartaColocavel(matrizCartasJogo[linha][i],ultCartaFila))){
            bool=0;
        }  
        ultCartaFila=matrizCartasJogo[linha][i];
    }
    if(nCartas==13 && bool==1) return 1;
    return 0;
}