#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


int verificaVitoria(int m[10][21]){
    int n=0;
    for(int i=0;i<10;i++) n+=m[i][0];
    //O jogo acabou se nao houverem cartas em nenhuma das 10 pilhas
    return (!n);
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

