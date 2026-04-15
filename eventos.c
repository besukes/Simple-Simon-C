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


boolean verificaFilaCompleta(int matrizCartasJogo[10][21],int linha){
    boolean b=1;
    int nCartas=matrizCartasJogo[linha][0],ultCartaFila=matrizCartasJogo[linha][nCartas];
    for(int i=nCartas;i>1;i--) if(!(ultCartaFila/13 == (matrizCartasJogo[linha][i-1] - 1 )/13)) b=0;
    if(nCartas==13 && b==1) return 1;
    else return 0;
}



void cliqueCarta(int matrizCartasJogo[10][21],int linhaClique,int colunaClique,UserBase * args,SDL_Texture *imagensCartas[10][21]){
    int cartaClique = matrizCartasJogo[linhaClique][colunaClique];
    if(args->dica.querDica){
        args->dica.timeout=0;
        args->dica.querDica=0;
        args->dica.numDicas=0;
    }
    if (cartaPegavel(cartaClique, linhaClique, matrizCartasJogo)) {
        updateEstado(linhaClique, colunaClique, matrizCartasJogo, args,imagensCartas);
    }
}

void efetuaEventoClique(int matrizCartasJogo[10][21], undoMove *estadoUndoGlobal,UserBase *args, SDL_Event event, SDL_Texture *imagensCartas[10][21],Mix_Chunk * arraySom[]) {
    float posX = event.button.x , posY = event.button.y;
    int linhaClique = calculaPosXClique(posX), colunaClique = calculaPosYClique(matrizCartasJogo, linhaClique, posY);
    //Clicou no botao de sair do jogo
    if (dentroDoBotao(event, args, 100, 50, 450, 1000)) {
        args->screen = menu;
    }
    //Clicou no botao de desfazer a jogada
    else if (dentroDoBotao(event, args, 150, 50, 1050, 1000)) {
        desfazerJogada(matrizCartasJogo, estadoUndoGlobal, imagensCartas);
        undoSFX(arraySom);
    }
    //Clicou no botao de reeniciar o jogo
    else if (dentroDoBotao(event, args, 150, 50, 725, 1000)) {
        reeniciaJogo(matrizCartasJogo, estadoUndoGlobal, args, imagensCartas);
    }
    //Botao dica
    else if (dentroDoBotao(event, args, 100, 50, 1300, 1000)){
        colocaDicaUtilizador(matrizCartasJogo,args);
    }
    //Verificar se clicou dentro da matriz
    else if (ePosicaoMatriz(linhaClique, colunaClique)) {
        cliqueCarta(matrizCartasJogo,linhaClique,colunaClique,args,imagensCartas);
    }
}

void efetuaEventoCliqueMenu(UserBase * args, SDL_Event event){
    if (dentroDoBotao(event, args, 200, 50, 860, 500)) {
        args->screen = jogo;
    }
    if (dentroDoBotao(event, args, 150, 50, 880, 600)) {
        args->jogada = sair;
        
    }
}


void efetuaEventoSoltar(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,UserBase * args,SDL_Event event , SDL_Texture * imagensCartas[10][21]){
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
