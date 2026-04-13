#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// remover depois
#include <stdio.h>

int calculaPosXClique(float posX){
    float i=75;
    int n;
    for(n=0;n<10;n++){
        if(i<=posX && i+140>=posX) return n;
        i+=(140+38);
    }
    return (-1);
}

int calculaPosYClique(int matrizCartasJogo[10][21], int posX, float posY) {
    if (posX < 0) return (-1);
    int numC = matrizCartasJogo[posX][0];

    for (int n = 1; n <= numC; n++) {
        float topoC = 80 + (n - 1) * 32; 
        float fundoC;

        if (n == numC) {
            fundoC = topoC + 190;  
        } else {
            fundoC = topoC + 32;
        }

        if (posY >= topoC && posY <= fundoC) return n;
    }
    return (-1);
}


void efetuaEventoClique(int matrizCartasJogo[10][21], undoMove *estadoUndoGlobal,
                        SDL2Bases *args, SDL_Event event, SDL_Texture *imagensCartas[10][21]) {

    float posX = event.button.x;
    float posY = event.button.y;

    int linhaClique = calculaPosXClique(posX);
    int colunaClique = calculaPosYClique(matrizCartasJogo, linhaClique, posY);

    // evitar segfault antes de qualquer acesso a matriz
    if (linhaClique < 0 || colunaClique < 0) return;

    printf("linha = %d , coluna = %d\n", linhaClique, colunaClique);

    if (dentroDoBotao(event, args, 100, 50, 400, 20)) {
        args->jogada = sair;
    }
    else if (dentroDoBotao(event, args, 100, 50, 1500, 500)) {
        desfazerJogada(matrizCartasJogo, estadoUndoGlobal, imagensCartas);
    }
    else if (dentroDoBotao(event, args, 100, 50, 700, 20)) {
        reeniciaJogo(matrizCartasJogo, estadoUndoGlobal, args, imagensCartas);
    }
    else if (ePosicaoMatriz(linhaClique, colunaClique)) {
        int cartaClique = matrizCartasJogo[linhaClique][colunaClique];
        if (cartaPegavel(cartaClique, linhaClique, matrizCartasJogo)) {
            updateEstado(linhaClique, colunaClique, matrizCartasJogo, args);
        } else {
            args->filaSelecionada = linhaClique;
            args->numCartasSelecionadas = matrizCartasJogo[linhaClique][0] - colunaClique + 1;
            args->jogada = invalida;
        }
    }
}


void efetuaEventoSoltar(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL2Bases * args,SDL_Event event , SDL_Texture * imagensCartas[10][21]){
    const float offset_x=60*(args->resolucaoX)/1600,
              offset_y=40*(args->resolucaoY)/900;
    int linha = ((event.button).x)/offset_x , 
        coluna = ((event.button).y)/offset_y;
    // boolean seria um int , 0 ou 1
    // eventoRelevante de soltar , seria um evento onde o utilizador soltou o rato numa coluna de cartas
    boolean eventoRelevante = ePosicaoMatriz(linha,coluna) && args->numCartasSelecionadas;
    if(eventoRelevante && cartaColocavel(matrizCartasJogo[linha][coluna],args->cartas[0])){
        colocaArrayCartas(matrizCartasJogo,estadoUndoGlobal,args, imagensCartas);
        adicionaJogadaUndoMove(matrizCartasJogo,linha,args,estadoUndoGlobal, imagensCartas);
    }
    else jogadaNaoRealizada(matrizCartasJogo,args);
}

void efetuaEventoMotion(int matrizCartasJogo[10][21],SDL2Bases * args){

}