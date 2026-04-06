#include "simpleSimon.h"

int verificaVitoria(int * baralhosCompletos){
    int u=0;
    for(int i=0;i<4;i++) u+=*(baralhosCompletos+i);
    return (u==52);
}

int cartaPegavel(int cartaClique,int linhaMatriz,int matrizCartasJogo[10][21]){
    //Caso de não haver cartas nessa fila
    if(cartaClique==(-1)) return 0;
    int i,numeroCartasFila = matrizCartasJogo[linhaMatriz][0],naipe=cartaClique/13;
    for(i=numeroCartasFila;(matrizCartasJogo[linhaMatriz][i])/13 == naipe;i++);
    return (matrizCartasJogo[linhaMatriz][--i] == cartaClique);
}

//Pode se colocar uma carta em cima de outra caso 
int cartaColocavel(int cartaDeBaixo,int cartaDeCima){
    return((cartaDeBaixo-cartaDeCima)==1);
}
