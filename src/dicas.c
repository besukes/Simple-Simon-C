#include "simpleSimon.h"
#include <SDL2/SDL.h>

/*Função que atualiza o estado das dicas. 
Caso o utilizador tenha clicado no botão de dica e ja tiver ultrapassado o tempo limite entao passa o bool querDicapara 0.
Caso o utilizador tenha clicado no botão de dica e ainda não tenha ultrapassado o tempo limite entao decrementa o timeout.*/
void atualizaEstadoDica(UserBase * args){
    if(args->dica.querDica && SDL_GetTicks() >= args->dica.timeout){
            args->dica.querDica=0;
            args->dica.numDicas=0;
    }
}

/*Função que , caso encontre uma posição que pode ser jogada , atualiza os argumentos do args.dica*/
void jogadorQuerDica(UserBase * args,int linha){
    args->dica.querDica=1;
    args->dica.filas[(args->dica.numDicas)++] = linha;
    args->dica.timeout=SDL_GetTicks() + 5000;
}

/*Função que percorre a matriz do jogo e , caso encontre uma posição onde o jogador possa jogar, chama a função jogadorQuerDica para atualizar os argumentos 
do args.dica .
De modo a otimizar , se para uma linha já tiver encontrado uma jogada, não continua a procurar.
Também é importante denotar que para cada fila pega no ultimo elemento pegável, porque é o único que pode ajudar a resolver o jogo.*/
void colocaDicaUtilizador(int matrizCartasJogo[10][21],UserBase *args){
    boolean b=1;
    for(int i=0;i<10;i++){
        int cartaP = calculaUltimaCartaPegavel(matrizCartasJogo,i,matrizCartasJogo[i][0]);
        for(int j=0;j<10 && b;j++){
            int num=matrizCartasJogo[j][0];
            if(num!=0 && cartaColocavel(matrizCartasJogo[j][num],cartaP)){
                jogadorQuerDica(args,i);
                b=0;
            }
        }
        b=1;
    }
}