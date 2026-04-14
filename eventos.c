#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


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
    int numC = matrizCartasJogo[posX][0];
    if(numC==0 && 112 <= posY && posY <= 112 + 190) return 0;
    for (int n = 1; n <= numC; n++) {
        float topoC = 112 + (n - 1) * 32, fundoC; 
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
    //Clicou no botao de sair do jogo
    if (dentroDoBotao(event, args, 100, 50, 400, 1000)) {
        args->jogada = sair;
    }
    //Clicou no botao de desfazer a jogada
    else if (dentroDoBotao(event, args, 100, 50, 1000, 1000)) {
        desfazerJogada(matrizCartasJogo, estadoUndoGlobal, imagensCartas);
    }
    //Clicou no botao de reeniciar o jogo
    else if (dentroDoBotao(event, args, 100, 50, 700, 1000)) {
        reeniciaJogo(matrizCartasJogo, estadoUndoGlobal, args, imagensCartas);
    }
    //Verificar se clicou dentro da matriz
    else if (ePosicaoMatriz(linhaClique, colunaClique)) {
        int cartaClique = matrizCartasJogo[linhaClique][colunaClique];
        if (cartaPegavel(cartaClique, linhaClique, matrizCartasJogo)) {
            updateEstado(linhaClique, colunaClique, matrizCartasJogo, args,imagensCartas);
        }
    }
}

void efetuaEventoCliqueMenu(SDL2Bases * args, SDL_Event event){
    if (dentroDoBotao(event, args, 200, 50, 860, 500)) {
        args->screen = jogo;
    }
    if (dentroDoBotao(event, args, 200, 50, 860, 600)) {
        args->jogada = sair;
    }
}


boolean verificaFilaCompleta(int matrizCartasJogo[10][21],int linha){
    boolean b=1;
    int nCartas=matrizCartasJogo[linha][0],ultCartaFila=matrizCartasJogo[linha][nCartas];
    for(int i=nCartas;i>1;i--) if(!(ultCartaFila/13 == (matrizCartasJogo[linha][i-1] - 1 )/13)) b=0;
    if(nCartas==13 && b==1) return 1;
    else return 0;
}


void efetuaEventoSoltar(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL2Bases * args,SDL_Event event , SDL_Texture * imagensCartas[10][21]){
    float posX = event.button.x , posY = event.button.y;
    int linha = calculaPosXClique(posX), coluna = calculaPosYClique(matrizCartasJogo, linha, posY);
    // boolean seria um int , 0 ou 1
    // eventoRelevante de soltar , seria um evento onde o utilizador soltou o rato numa coluna de cartas
    boolean eventoRelevante = ePosicaoMatriz(linha,coluna) && args->numCartasSelecionadas,
            cartaPodeSeColocar = cartaColocavel(matrizCartasJogo[linha][coluna],args->cartas[0]) 
                || (ePosicaoMatriz(linha,coluna) && matrizCartasJogo[linha][0]==0);
    if(eventoRelevante && cartaPodeSeColocar){
        boolean b = colocaArrayCartas(matrizCartasJogo,args,imagensCartas,linha);
        adicionaJogadaUndoMove(matrizCartasJogo,linha,args,estadoUndoGlobal, imagensCartas,b);
    }
    else jogadaNaoRealizada(matrizCartasJogo,eventoRelevante,cartaPodeSeColocar,args,imagensCartas);
}
