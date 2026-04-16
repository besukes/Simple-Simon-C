#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


/*Esta função desfaz uma jogada , se esta jogada anteriormente realizada tiver completado uma fila , pois é um caso especial
Neste cenário , temos que restaurar as cartas que estavam na fila onde colocamos cartas e que foi completada , como também colocar as cartas que arrastamos
nas respectivas posições , e também aumentar os valores dos índices 0 nessas linhas da matriz , para representar o estado anterior*/
void desfazerFilaCompleta(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21]){
    int isp = estadoUndoGlobal->isp,
        linhaCompleta = estadoUndoGlobal->ultimasJogadas[isp].novaPos,
        linhaAnterior = estadoUndoGlobal->ultimasJogadas[isp].antigaPos,
        numCartasColocadas = estadoUndoGlobal->ultimasJogadas[isp].cartasMovidas;
    int i,m = matrizCartasJogo[linhaAnterior][0];
    //O numero da fila aumenta de 0 para 13 menos o numero de cartas que foram arrastadas
    matrizCartasJogo[linhaCompleta][0] = 13-numCartasColocadas;
    //Estas cartas sao as cartas que estavam na fila completa antes de ser completada
    for(i=1;i<=13-numCartasColocadas;i++){
        matrizCartasJogo[linhaCompleta][i] = estadoUndoGlobal->ultimasJogadas[isp].cartas[i-1];
        imagensCartas[linhaCompleta][i] = estadoUndoGlobal->ultimasJogadas[isp].imgs[i-1];
    }
    //Estas são as cartas que foram arrastadas ate à fila completa
    matrizCartasJogo[linhaAnterior][0]+=numCartasColocadas;
    for(int j=1;i<13;i++,j++){
        matrizCartasJogo[linhaAnterior][m+j] = estadoUndoGlobal->ultimasJogadas[isp].cartas[i];
        imagensCartas[linhaAnterior][m+j] = estadoUndoGlobal->ultimasJogadas[isp].imgs[i];
    }
}


/*Neste caso menos especial apenas temos de pegar na posição de onde as cartas foram arrastadas e colocá-las nesse mesmo sítio, diminuindo o índice 0 da matriz que
guarda o número de cartas nessa linha , no número de cartas que foram arrastadas , e também fazer o mesmo para a linha de onde as cartas vieram , mas agora incrementando*/
void desfazJogadaBasica(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21]){
    //Inicilizamos todas as variaveis que precisamos para desfazer a jogada , para facilitar a leitura
    int isp = estadoUndoGlobal->isp;
    int linhaAtual = estadoUndoGlobal->ultimasJogadas[isp].novaPos,
        linhaAntiga = estadoUndoGlobal->ultimasJogadas[isp].antigaPos,
        numCartas = estadoUndoGlobal->ultimasJogadas[isp].cartasMovidas,
        numCLantiga = matrizCartasJogo[linhaAntiga][0] + 1;
    int * arrayCartas=estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].cartas;
    //Para facilitar a leitura criamos uma variavel que e um apontador de memoria de uma posicao onde esta um apontador de memoria
    SDL_Texture * * images= (estadoUndoGlobal->ultimasJogadas[isp]).imgs;
    //A fila nao se completou com a jogada , ao desfazer a jogada simplesmente retiramos as cartas e pomos na outra fila
    matrizCartasJogo[linhaAtual][0]-=numCartas;
    for(int i=0;i<numCartas;i++){
        matrizCartasJogo[linhaAntiga][numCLantiga+i] = arrayCartas[i];
        imagensCartas[linhaAntiga][numCLantiga+i] = images[i];
        matrizCartasJogo[linhaAntiga][0]++;
    }
}

/*Função intermediária que verifica se é possível desfazer a última jogada , ou seja , o utilizador efetuou jogadas anterior a estas , e , se esse for o caso ,
verifica qual foi o tipo de jogada realizada anteriormente , pois existem nuances que devem ser atendidas respectivamente*/
int desfazerJogada(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21]){
    if(estadoUndoGlobal -> isp==0) return 1;
    else estadoUndoGlobal -> isp --;
    //SE a fila tiver sido completa nesta jogada entao e um caso especial , que deve ser tratado a parte..
    if(estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].filaPreenchida){
        desfazerFilaCompleta(matrizCartasJogo,estadoUndoGlobal,imagensCartas);
        return 0;
    }
    else{ 
        desfazJogadaBasica(matrizCartasJogo,estadoUndoGlobal,imagensCartas);
        return 0;
    }
}

/*Função que adiciona uma jogada ao histórico de jogadas que podem ser desfeitas , tendo em conta o tipo de jogada que foi realizada*/
void adicionaJogadaUndoMove(int matrizCartasJogo[10][21],int pos,UserBase * args,undoMove * estadoUndoGlobal,
SDL_Texture * imagensCartas[10][21],boolean filaCompleta){
    if(filaCompleta){
        rowCompleta(matrizCartasJogo,imagensCartas,pos,args,estadoUndoGlobal);
        estadoUndoGlobal->isp++;
    }
    else{
        rowNaoCompleta(pos,args,estadoUndoGlobal);
        estadoUndoGlobal->isp++;
    }
}

/*Se a fila tiver sido completada nesta jogada , então adicionamos todas as cartas da linha ao array do estadoUndoGlobal responsável por guardar as cartas e as
imagens , como também informamos que a fila foi preenchida , guardamos a fila de onde as cartas vieram e onde foram colocadas(fila que foi completada) e , depois
também dizemos quantas cartas é que pegamos da fila e arrastamos até à fila que foi completada*/
void rowCompleta(int mcj[10][21],SDL_Texture * img[10][21],int pos,UserBase * args,undoMove * estadoUndoGlobal){
    int isp = estadoUndoGlobal->isp;
    estadoUndoGlobal->ultimasJogadas[isp].antigaPos = args->filaSelecionada;
    estadoUndoGlobal->ultimasJogadas[isp].novaPos = pos;
    estadoUndoGlobal->ultimasJogadas[isp].cartasMovidas = args->numCartasSelecionadas;
    estadoUndoGlobal->ultimasJogadas[isp].filaPreenchida = 1;
     for(int i=0;i<13;i++){
        estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].cartas[i] = mcj[pos][i+1];
        estadoUndoGlobal->ultimasJogadas[estadoUndoGlobal->isp].imgs[i] = img[pos][i+1];
    }
}


/*Se a fila não tiver sido completada nesta jogada , então simplesmente informamos que a fila não foi preenchida , e guardamos as informações sobre a jogada, como
a nova posição das cartas , quantas cartas foram postas nessa nova posição , a posição antiga e também guardamos as próprias cartas e texturas*/
void rowNaoCompleta(int pos,UserBase * args,undoMove * estadoUndoGlobal){
    int numCartasJogadas=args->numCartasSelecionadas , isp = estadoUndoGlobal->isp;
    estadoUndoGlobal->ultimasJogadas[isp].antigaPos = args->filaSelecionada;
    estadoUndoGlobal->ultimasJogadas[isp].novaPos = pos;
    estadoUndoGlobal->ultimasJogadas[isp].cartasMovidas = numCartasJogadas;
    estadoUndoGlobal->ultimasJogadas[isp].filaPreenchida = 0;
    for(int i=0;i<numCartasJogadas;i++){
        estadoUndoGlobal->ultimasJogadas[isp].cartas[i] = args->cartas[i];
        estadoUndoGlobal->ultimasJogadas[isp].imgs[i] = args->imgs[i];
    }
}

/*Função que reenicia o jogo , simplesmente randomizando todas as cartas no baralho , executando a função criarJogo , como também dando clear ao renderer , destruindo as 
texturas que foram criadas (pois vão ser novamente criadas no criarJogo) , e também reeniciamos o args de modo a representar um estado inicial*/
void reeniciaJogo(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,UserBase * args,
SDL_Texture * imagensCartas[10][21]){
    estadoUndoGlobal->isp=0;
    args->filaSelecionada=(-1);
    args->numCartasSelecionadas=0;
    SDL_RenderClear(args->rendererBase);
    for(int i=0;i<10;i++){
        for(int j=1;j<=matrizCartasJogo[i][0];j++) SDL_DestroyTexture(imagensCartas[i][j]);
    }
    resetDicaArgs(args);
    criarJogo(matrizCartasJogo,imagensCartas,args->rendererBase , args);
}

/*Função executada quando o utilizador clica numa carta que pode pegar.
Oque esta função faz é indicar a linha onde o utilizador clicou e o número de cartas selecionadas pelo mesmo , como também colocando essas cartas e
imagens nos respectivos arrays do args , responsáveis por guardar essas informações*/
void updateEstado(int linhaClique, int colunaClique, int matrizCartasJogo[10][21], UserBase * args,SDL_Texture * imagens[10][21]) {
    args->filaSelecionada = linhaClique;
    args->numCartasSelecionadas = matrizCartasJogo[linhaClique][0] - colunaClique + 1;
    args->jogada = valido;
    int numC = matrizCartasJogo[linhaClique][0];
    int NumSelecionadas = args->numCartasSelecionadas;
    for(int i=0;i < NumSelecionadas; i++,numC--){
        args->cartas[NumSelecionadas - i -1] = matrizCartasJogo[linhaClique][numC];
        args->imgs[NumSelecionadas -i -1] = imagens[linhaClique][numC];
    }
    matrizCartasJogo[linhaClique][0]-= args->numCartasSelecionadas;
}

/*Esta função executa quando o utilizador arrasta uma carta para uma nova posição e esta jogada é válida.
Nesse sentido , coloca as cartas nessa nova posição da matriz , atualizando-a , como também faz isso mesmo para a matriz das texturas.
Também incrementamos o número de cartas nessa nova posição.
Se a fila tiver sido completada então a linha simplesmente "limpa-se" , ou apaga-se . Caso contrário mantemos o estado como está.*/
int colocaArrayCartas(int matrizCartasJogo[10][21],UserBase * args,SDL_Texture * imagensCartas[10][21],int linha){
    int numCartas = args->numCartasSelecionadas;
    int contacartas = matrizCartasJogo[linha][0];
    for (int i = 1; i <=numCartas; i++) {
        matrizCartasJogo[linha][contacartas +i] = args->cartas[i-1];
        imagensCartas[linha][contacartas + i] = args->imgs[i-1];
    }
    matrizCartasJogo[linha][0] += numCartas;
    boolean b=verificaFilaCompleta(matrizCartasJogo,linha);
    if (b) matrizCartasJogo[linha][0] = 0;
    return b;
}

/*Se a jogada não for válida (Por exemplo o utilizador tenta arrastar cartas para fora da janela ou para uma posição onde não há cartas , ou até
mesmo uma posição onde colocar as cartas é inválido) , então temos que retornar as cartas arrastadas à posição de origem ,incrementar o número de cartas dessa
posição de origem , e resetar o args , de modo a representar um estado parado.
Se a jogada for valida então guarda no args , se não guarda jogada inválida , caso contrário.*/
void jogadaNaoRealizada(int mcj[10][21],boolean eventoRelevante,boolean cartaPodeColocar,UserBase * args,SDL_Texture * imagens[10][21]){
    int filaCarta = args->filaSelecionada, tam= mcj[filaCarta][0];
    for(int i=0;i<args->numCartasSelecionadas;i++){
        mcj[filaCarta][tam+i+1] = args->cartas[i];
        imagens[filaCarta][tam+i+1] = args->imgs[i];
    }
    mcj[args->filaSelecionada][0]+=args->numCartasSelecionadas;
    args->filaSelecionada = (-1);
    args->numCartasSelecionadas = 0;
    if(eventoRelevante && !cartaPodeColocar ) args->jogada = invalida;
    else args->jogada=valido;
}

