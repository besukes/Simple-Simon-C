#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int verificaVitoria(int * baralhosCompletos){
    int u=0;
    for(int i=0;i<4;i++) u+=*(baralhosCompletos+i);
    return (u==52);
}

int cartaPegavel(int cartaClique,int linhaMatriz,int matrizCartasJogo[10][21]){
    //Caso de não haver cartas nessa fila
    if(cartaClique==(-1)) return 0;
    int i,numeroCartasFila = matrizCartasJogo[linhaMatriz][0],naipe=cartaClique/13;
    for(i=numeroCartasFila;(matrizCartasJogo[linhaMatriz][i])/13 == naipe;i--);
    return (matrizCartasJogo[linhaMatriz][++i] == cartaClique);
}

//Pode se colocar uma carta em cima de outra caso 
int cartaColocavel(int cartaDeBaixo,int cartaDeCima){
    return((cartaDeBaixo-cartaDeCima)==1);
}

int dentroDoBotao(SDL_Event e,SDL2Bases * args,float offsetX,float offsetY,float posX,float posY){
    offsetX=offsetX*(args->resolucaoX)/1600,
    offsetY=offsetY*(args->resolucaoY)/900,
    posX=posX*(args->resolucaoX)/1600,
    posY=posY*(args->resolucaoY)/900;
    int x=e.button.x,y=e.button.y;
    return ( (posX-offsetX<=x && posX+offsetX>=x) && (posY-offsetY<=y && posY+offsetY>=y));
}

int ePosicaoMatriz(int l,int c){
    return (l>=0 && l<10 && c>=0 && c<20);
}
