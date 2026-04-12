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

int calculaPosYClique(int matrizCartasJogo[10][21],int posX,float posY){
    int n,numC=matrizCartasJogo[posX][0];
    float i=80 + 36*(numC-1);
    if(i+158>=posY && posY>=i) return numC;
    for(n=matrizCartasJogo[posX][0] - 1;n>=0;n--){
        if(i-36<=posY && posY<=i) return n;
        i-=36;
    }
    return (-1);
}


void efetuaEventoClique(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL2Bases * args,SDL_Event event , SDL_Texture * imagensCartas[10][21]){
    float scaleX=(args->resolucaoX)/1600,scaleY=(args->resolucaoY)/900,
          posX=(event.button.x),posY= (event.button.y);
    int linhaClique= calculaPosXClique(posX),
        colunaClique= calculaPosYClique(matrizCartasJogo,linhaClique,posY);
    //Clicou no botao de SAIR
    printf("linha = %d , coluna = %d ",linhaClique,colunaClique);
    if(dentroDoBotao(event,args,100,50,400,20)){
        args->jogada=sair;
    }
    //Clicou no botao de UndoMove
    else if(dentroDoBotao(event,args,100,50,1500,500)){
        desfazerJogada(matrizCartasJogo,estadoUndoGlobal , imagensCartas);
    }
    //Clicou para reeniciar o jogo
    else if(dentroDoBotao(event,args,100,50,700,20)){
        reeniciaJogo(matrizCartasJogo,estadoUndoGlobal,args,imagensCartas);
    }
    //Clicou numa fila de cartas
    else if(ePosicaoMatriz(linhaClique,colunaClique)){
        int cartaClique = matrizCartasJogo[linhaClique][colunaClique];
        if(cartaPegavel(cartaClique,linhaClique,matrizCartasJogo)){
            updateEstado(linhaClique,colunaClique,matrizCartasJogo,args);
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