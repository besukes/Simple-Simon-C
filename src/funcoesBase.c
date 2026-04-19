#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<stdlib.h>
#include<time.h>


////////////////////////////////////Funções Importadas do GOLF/////////////////////////////////////////////////////////
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

/*Função que verifica se o jogador venceu o jogo(O jogador vence se em todas as filas não existirem cartas)*/
void verificaVitoria(int m[10][21],UserBase * args){
    int n=0;
    for(int i=0;i<10;i++) n+=m[i][0];
    n+= args->numCartasSelecionadas;
    //O jogo acabou se nao houverem cartas em nenhuma das 10 pilhas
    if(!n) {args->jogada=vitoria ; args->screen=win;}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Verifica se uma carta é pegável,i.e., se existem cartas por debaixo dessa mesma , então todas têm o mesmo naipe e valores consecutivos decrescentes*/
int cartaPegavel(int cartaClique, int linha, int mcj[10][21]) {
    int i;
    if (cartaClique == (-1)) return 0;
    int max = mcj[linha][0],naipe = (cartaClique - 1) / 13;
    for (i = max;i > 1 && (mcj[linha][i] - 1)/13 == naipe && cartaColocavel(mcj[linha][i-1],mcj[linha][i]); i--){
        if(mcj[linha][i]==cartaClique) return 1;
    }
    return (mcj[linha][i] == cartaClique);
}

/*Verifica se uma carta é colocável em cima da outra (O valor da carta que se vai colocar é imediatamente abaixo daquela onde vamos colocar)*/
int cartaColocavel(int cartaDeBaixo,int cartaDeCima){
    return((valorCarta(cartaDeBaixo)-valorCarta(cartaDeCima))==1);
}

/*Verifica se uma posição está dentro do botão , tendo em conta a coordenada esquerda superior do botao em termos de X e Y , como também os tamanhos do botão*/
int dentroDoBotao(SDL_Event e,float width,float height,float posX,float posY){
    int x=e.button.x,y=e.button.y;
    return ( (posX<=x && posX+width>=x) && (posY<=y && posY+height>=y));
}

/*Uma posição (l,c) está dentro da matriz jogo se estiver entre os limites da matriz respectiva*/
int ePosicaoMatriz(int l,int c){
    return (l>=0 && l<10 && c>=0 && c<21);
}

/*Reseta as informações do usuário que estão guardadas em args , de modo a representar um estado parado*/
void resetArgs(UserBase * args){
    args->filaSelecionada=(-1);
    args->numCartasSelecionadas=0;
    args->jogada=valido;
    args->mouseButtonDown=0;
}

/*Transforma o args para passar a informar às outras funções de desenhar que o utilizador não quer mais dicas*/
void resetDicaArgs(UserBase * args){
    args->dica.querDica=0;
    args->dica.numDicas=0;
    args->dica.timeout=0;
}

/*Calcula a última carta que o utilizador pode pegar numa fila , para isso todas as cartas até essa têm de ser imediatamente 1 valor inferior à seguinte e têm de 
ser do mesmo naipe*/
int calculaUltimaCartaPegavel(int matrizCartasJogo[10][21],int linha,int numCartas){
    if(numCartas==0) return (-1);
    int cartaFinal=matrizCartasJogo[linha][numCartas];
    for(int i=numCartas-1;i>0 && (matrizCartasJogo[linha][i] - 1)/13 == (cartaFinal - 1)/13 
    && (matrizCartasJogo[linha][i] - cartaFinal == 1);i--){
        cartaFinal = matrizCartasJogo[linha][i];
    }
    return cartaFinal;
}

/*Uma fila está completa se todas as cartas nela estiverem na ordem correta de K-Ás e forem todas do mesmo naipe*/
boolean verificaFilaCompleta(int matrizCartasJogo[10][21],int linha){
    boolean flag=1;
    int nCartas=matrizCartasJogo[linha][0],ultCartaFila=matrizCartasJogo[linha][nCartas];
    int naipe = (ultCartaFila - 1)/13;
    for(int i=nCartas-1;i>0 && flag;i--){
        if((matrizCartasJogo[linha][i] - 1 )/13 != naipe || !(cartaColocavel(matrizCartasJogo[linha][i],ultCartaFila))){
            flag=0;
        }  
        ultCartaFila=matrizCartasJogo[linha][i];
    }
    if(nCartas==13 && flag==1) return 1;
    return 0;
}

/*Função responsável por calcular o tempo que o utilizador tem em um dado jogo.*/
void tempoemjogo(UserBase * args)
{
    int dif = (args -> tempo - args -> Vjogo);
    args -> Vjogo = args -> tempo;
    if (args->screen == jogo)
    {
        args -> Tjogo += dif / 1000.0;
    }
}
/*Função responsável por apresentar a tela de vitoria e lidar com o Final Score do Utilizador.*/
void handleWINcon(UserBase * args)
{
    args->screen = win;
    if (args -> Tjogo <= 1)
        args -> score = 6000;
    else
    args -> score = (6000 - (args -> Tjogo * 10));
    if (args -> score < 0)
        args -> score = 0;
}