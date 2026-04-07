//#include"golf.h"
#include<stdlib.h>
#include<time.h>

/*Função que pega no deck de cartas que foi baralhado previamente e coloca as cartas na matriz de maneira ordenada, como também no deck das cartas do baralho e da carta de descarte , criando assim um jogo onde as cartas estao aleatoriamente dispostas*/
void inicializaMatriz_e_ArrayJogo(int shuffledDeck[],int cartasJogo[7][6],int cartasBaralho[],int * cartaPrincipal,int numeroBaralho,int numeroCartasJogo){
        cartasBaralho[0]=numeroBaralho;
        *cartaPrincipal = shuffledDeck[0];
        for(int i=0;i<7;i++){
                cartasJogo[i][0]=numeroCartasJogo;
                for(int j=1;j<6;j++) cartasJogo[i][j] = shuffledDeck[i*5+j];
        }
        for(int i=1;i<17;i++) cartasBaralho[i]=shuffledDeck[35+i];
}

/*Dado um numero de 1-52 retorna o valor real de 1-13 da carta*/
int valorCarta(int carta){
        for(;carta>13;carta-=13);
        return carta;
}

/*Função que dado uma carta do baralho e uma carta selecionada pelo utilizador, verifica se a jogada é válida , ou não.*/
int cartaJogavel(int cartaPrincipal,int cartaSelecionada){
        int cartaS=valorCarta(cartaPrincipal),cartaP=valorCarta(cartaSelecionada);
        int dif=cartaS - cartaP;
        if(dif==1 || dif==(-1)) return 1;
        else return 0;
}

/*Dado um array com as cartas distribuidas de 1-52 baralha as cartas entre si*/
void shuffleCartas(int cartas[]){
	srand(time(NULL));
        for(int i=0;i<52;i++){
                int j=rand()%52;
                int temp = cartas[i];
                cartas[i]=cartas[j];
                cartas[j]=temp;
        }
}

/*Inicializa o array cartas para ser de 1-52*/
void preset(int cartas[]){
        for(int i=0;i<52;i++) cartas[i]=i+1;
}
