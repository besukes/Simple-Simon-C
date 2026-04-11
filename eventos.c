#include "simpleSimon.h"

void efetuaEventoClique(int matrizCartasJogo[10][21],int baralhosCompletos[],undoMove * estadoUndoGlobal,
SDL2Bases * args,SDL_Event event){
    const float offset_CartaX=60*(args->resolucaoX)/1600,
                offset_CartaY=40*(args->resolucaoY)/900;
    int linhaClique= ((event.button).x)/offset_CartaX,
        colunaClique= ((event.button).y)/offset_CartaY;
    //Clicou no botao de SAIR
    if(dentroDoBotao(event,args,100,50,400,20)){
        args->jogada=sair;
    }
    //Clicou no botao de UndoMove
    else if(dentroDoBotao(event,args,100,50,1500,500)){
        desfazerJogada(matrizCartasJogo,baralhosCompletos,estadoUndoGlobal);
    }
    //Clicou para reeniciar o jogo
    else if(dentroDoBotao(event,args,100,50,700,20)){
        reeniciaJogo(matrizCartasJogo,baralhosCompletos,estadoUndoGlobal,args);
    }
    //Clicou numa fila de cartas
    else if(ePosicaoMatriz(linhaClique,colunaClique)){
        int cartaClique = matrizCartasJogo[linhaClique][colunaClique];
        if(cartaPegavel(cartaClique,linhaClique,matrizCartasJogo)){
            updateEstado(linhaClique,colunaClique,matrizCartasJogo,args);
        }
    }
    
}

void efetuaEventoSoltar(int matrizCartasJogo[10][21],int baralhosCompletos[],undoMove * estadoUndoGlobal,
SDL2Bases * args,SDL_Event event){
    const float offset_x=60*(args->resolucaoX)/1600,
              offset_y=40*(args->resolucaoY)/900;
    int linha = ((event.button).x)/offset_x , 
        coluna= ((event.button).y)/offset_y;
    // boolean seria um int , 0 ou 1
    boolean eventoRelevante = ePosicaoMatriz(linha,coluna) && args->numCartasSelecionadas;
    if(eventoRelevante && cartaColocavel(matrizCartasJogo[linha][coluna],args->cartas[0])){
        colocaArrayCartas(matrizCartasJogo,baralhosCompletos,estadoUndoGlobal,args);
    }
}