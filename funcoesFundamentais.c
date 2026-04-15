//#include"golf.h"
#include<stdlib.h>
#include<time.h>


/*Dado um numero de 1-52 retorna o valor real de 1-13 da carta*/
int valorCarta(int carta){
        for(;carta>13;carta-=13);
        return carta;
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
