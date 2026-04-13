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
        float topoC = 112 + (n - 1) * 32; 
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


void efetuaEventoClique(int matrizCartasJogo[10][21], undoMove *estadoUndoGlobal,SDL2Bases *args, SDL_Event event, SDL_Texture *imagensCartas[10][21]) {
    float posX = event.button.x , posY = event.button.y;
    int linhaClique = calculaPosXClique(posX), colunaClique = calculaPosYClique(matrizCartasJogo, linhaClique, posY);
    printf("linha = %d , coluna = %d\n", linhaClique, colunaClique);
    //Clicou no botao de sair do jogo
    if (dentroDoBotao(event, args, 100, 50, 400, 20)) {
        args->jogada = sair;
    }
    //Clicou no botao de desfazer a jogada
    else if (dentroDoBotao(event, args, 100, 50, 1500, 500)) {
        desfazerJogada(matrizCartasJogo, estadoUndoGlobal, imagensCartas);
    }
    //Clicou no botao de reeniciar o jogo
    else if (dentroDoBotao(event, args, 100, 50, 700, 20)) {
        reeniciaJogo(matrizCartasJogo, estadoUndoGlobal, args, imagensCartas);
    }
    //Verificar se clicou dentro da matriz
    else if (ePosicaoMatriz(linhaClique, colunaClique)) {
        int cartaClique = matrizCartasJogo[linhaClique][colunaClique];
        if (cartaPegavel(cartaClique, linhaClique, matrizCartasJogo)) {
            updateEstado(linhaClique, colunaClique, matrizCartasJogo, args);
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
    boolean eventoRelevante = ePosicaoMatriz(linha,coluna) && args->numCartasSelecionadas,
            cartaPodeSeColocar = cartaColocavel(matrizCartasJogo[linha][coluna],args->cartas[0]);
    if(eventoRelevante && cartaPodeSeColocar){
        colocaArrayCartas(matrizCartasJogo,estadoUndoGlobal,args, imagensCartas);
        adicionaJogadaUndoMove(matrizCartasJogo,linha,args,estadoUndoGlobal, imagensCartas);
    }
    else jogadaNaoRealizada(eventoRelevante,cartaPodeSeColocar,args);
}

void efetuaEventoMotion(int matrizCartasJogo[10][21],SDL2Bases * args){

}