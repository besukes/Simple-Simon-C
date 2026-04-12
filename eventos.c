#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void efetuaEventoClique(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL2Bases * args,SDL_Event event , SDL_Texture * imagensCartas[10][21]){
    const float offset_CartaX=140*(args->resolucaoX)/1600,
                offset_CartaY=190*(args->resolucaoY)/900;
    int linhaClique= ((event.button).x)/offset_CartaX,
        colunaClique= ((event.button).y)/offset_CartaY;
    //Clicou no botao de SAIR
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