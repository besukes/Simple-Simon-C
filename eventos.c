#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*Função que calcula a posição X de onde o utilizador clicou , em termos da matriz do Jogo*/
int calculaPosXClique(float posX){
    float i=75;
    int n;
    for(n=0;n<10;n++){
        if(i<=posX && i+140>=posX) return n;
        i+=(140+38);
    }
    return (-1);
}

/*Função que calcula a posição Y de onde o utilizador clicou , em termos da matriz do Jogo , e da posição do X(Esta última é necessária pois precisamos saber
quantas cartas existem na linha)*/
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

/*Função que verifica se o utilizador clicou numa carta que pode pegar e , se o tiver feito , então atualiza o estado args para representar a jogada efetuada.
Também contém uma funcionalidade , esta função , de parar de mostrar dica de cartas , pois o utilizador ja clicou numa carta*/
void clicouCarta(int matrizCartasJogo[10][21],int linhaClique,int colunaClique,UserBase * args,SDL_Texture *imagensCartas[10][21],undoMove *estadoUndoGlobal){
    int cartaClique = matrizCartasJogo[linhaClique][colunaClique];
    //Muda o estado de args->dica para não mostrar mais dicas
    if(args->dica.querDica){
        args->dica.timeout=0;
        args->dica.querDica=0;
        args->dica.numDicas=0;
    }
    //Se o utilizador tiver 250 o array estadoUndoGlobal enche , portanto pede ao utilizador para tentar outras rotas
    if(estadoUndoGlobal->isp==250) args->jogada=tooLarge;
    else{//Se a carta for pegável, atualiza o estado
        if (cartaPegavel(cartaClique, linhaClique, matrizCartasJogo)) {
            updateEstado(linhaClique, colunaClique, matrizCartasJogo, args,imagensCartas);
        }   
    }

}

/*Função responsável por reduzir instruções na função efetuaEventoClique e para isso realiza as funções que tratam de anular uma jogada*/
void efetuaBotaoUndo(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal, SDL_Texture * imagensCartas[10][21],Mix_Chunk * arraySom[]){
    desfazerJogada(matrizCartasJogo, estadoUndoGlobal, imagensCartas);
    undoSFX(arraySom);
}

/*Função responsável por reduzir instruções na função efetuaEventoClique que realiza as funções respectivas para reeniciar o jogo*/
void efetuaBotaoReeniciar(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal, UserBase * args, SDL_Texture * imagensCartas[10][21],Mix_Chunk * arraySom[]){
    reeniciaJogo(matrizCartasJogo, estadoUndoGlobal, args, imagensCartas);
    ngSFX(arraySom);
}

/*  Função responsável por efetuar os eventos de clique do utilizador.
    É chamada quando o utilizador clica com o botão esquerdo no ecrã , e faz um monte de verificações para descobrir se a posição onde o utilizador clicou
é relevante , e , se for , então executa a respectiva instrução*/
void efetuaEventoClique(int matrizCartasJogo[10][21], undoMove *estadoUndoGlobal,UserBase *args, SDL_Event event, SDL_Texture *imagensCartas[10][21],Mix_Chunk * arraySom[]) {
    float posX = event.button.x , posY = event.button.y;
    int linhaClique = calculaPosXClique(posX), colunaClique = calculaPosYClique(matrizCartasJogo, linhaClique, posY);
    SDL_Point pontoMouse = {args->mouseX, args->mouseY};
    SDL_Rect botaoQuit = {275, 800, 325, 325},botaoNG = {625, 800, 335, 300},botaoUndo = {975, 800, 330, 300},botaoDica = {1325, 800, 330, 300};
    //Clicou no botão de sair do jogo
    if (SDL_PointInRect(&pontoMouse, &botaoQuit)) {
        args->screen = menu;
    }
    //Clicou no botão de desfazer a jogada
    else if (SDL_PointInRect(&pontoMouse, &botaoUndo)) {
        efetuaBotaoUndo(matrizCartasJogo, estadoUndoGlobal, imagensCartas,arraySom);
    }
    //Clicou no botão de reeniciar o jogo
    else if (SDL_PointInRect(&pontoMouse, &botaoNG)) {
        efetuaBotaoReeniciar(matrizCartasJogo, estadoUndoGlobal, args, imagensCartas,arraySom);
    }
    //Clicou no botão de pedir dica
    else if (SDL_PointInRect(&pontoMouse, &botaoDica) && !(args->dica.querDica)){
        colocaDicaUtilizador(matrizCartasJogo,args);
        args->jogada = vitoria;
    }
    //Verificar se clicou dentro da matriz
    else if (ePosicaoMatriz(linhaClique, colunaClique) && matrizCartasJogo[linhaClique][colunaClique] > 0) {
        clicouCarta(matrizCartasJogo,linhaClique,colunaClique,args,imagensCartas,estadoUndoGlobal);
    } 
}

/*Função responsável pelos eventos de clique na tela do Menu inicial*/
void efetuaEventoCliqueMenu(UserBase * args, SDL_Event event){
        SDL_Point pontoMouse = {args->mouseX, args->mouseY};
        SDL_Rect botaoJogar = {860, 500, 200, 50};
        SDL_Rect botaoTemas = {860, 600, 200, 50};
        SDL_Rect botaoSair = {860, 700, 200, 50};
    if (SDL_PointInRect(&pontoMouse, &botaoJogar)) {
        args->screen = jogo;
    }
    if (SDL_PointInRect(&pontoMouse, &botaoTemas)) {
        args->screen = temas;
    }
    if (SDL_PointInRect(&pontoMouse, &botaoSair)) {
        args->jogada = sair;
        
    }
}

/*Função responsável pelos eventos de clique na tela do Menu de escolher Temas*/
void efetuaEventoCliqueTemas(UserBase * args, SDL_Event event){
        SDL_Point pontoMouse = {args->mouseX, args->mouseY};
        SDL_Rect balatrob = {400, 100, 500, 300};
        SDL_Rect solitaireb = {1000, 100, 500, 300};
        SDL_Rect menu1 = {100 , 900 , 200 ,200};
    if (SDL_PointInRect(&pontoMouse, &balatrob)) 
        args->estilo = balatro;
    else if (SDL_PointInRect(&pontoMouse, &solitaireb)) 
        args->estilo = solitaire;
    else if (SDL_PointInRect(&pontoMouse, &menu1)) {
        args->screen = menu;
    }
}

/*Na tela de vitória , o utilizador pode clicar nos botões para voltar ao menu ou iniciar um novo jogo.
Esta função verifica os eventos de clique nessa tela e efetua as respectivas instruções relativamente à opção do jogador*/
void efetuaEventoCliqueWin(UserBase * args, SDL_Event event , int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal, SDL_Texture * imagensCartas[10][21],Mix_Chunk * arraySom[] ){
        SDL_Point pontoMouse = {args->mouseX, args->mouseY};
        SDL_Rect botaoMenu = {615, 800, 335, 300},botaoNewGame = {965, 800, 330, 300};
    //Ciclou no botão de voltar ao menu
    if (SDL_PointInRect(&pontoMouse, &botaoMenu)) {
        args->screen = menu;
        
    }
    //Clicou no botão de reeniciar o jogo
    else if (SDL_PointInRect(&pontoMouse, &botaoNewGame)) {
        args->screen = jogo;
        args->jogada = valido;
        efetuaBotaoReeniciar(matrizCartasJogo, estadoUndoGlobal, args, imagensCartas,arraySom);
    }
}

/*  Função responsável pelos eventos de soltar o rato.
    Semelhante à função de clique , esta também calcula a posição onde o utilizador tem o rato , mais precisamente , onde soltou o botão esquerdo e , 
se for um evento relevante(Soltou o rato numa posição da matriz e tinha cartas selecionadas) e poder colocar a carta na posição onde soltou , então altera o estado
respectivamente , caso contrário desfaz oque o clique fez (Coloca as cartas que estão a ser arrastadas de volta na posição da matriz e altera o args de modo a
representar um estado parado).
 */
void efetuaEventoSoltar(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,UserBase * args,SDL_Event event , SDL_Texture * imagensCartas[10][21]){
    float posX = event.button.x , posY = event.button.y;
    //Calculamos a posição onde o utilizador soltou o rato em termos da matriz
    int linha = calculaPosXClique(posX), coluna = calculaPosYClique(matrizCartasJogo, linha, posY);
    // boolean seria um int , 0 ou 1
    // eventoRelevante de soltar , seria um evento onde o utilizador soltou o rato numa coluna de cartas
    boolean eventoRelevante = ePosicaoMatriz(linha,coluna) && args->numCartasSelecionadas,
            cartaPodeSeColocar = cartaColocavel(matrizCartasJogo[linha][coluna],args->cartas[0]) 
                || (ePosicaoMatriz(linha,coluna) && matrizCartasJogo[linha][0]==0);
    //Se for um evento relevante e a carta puder ser colocada , então atualiza o estado e a matrizJogo , caso contrario desfaz oque o clique fez
    if(eventoRelevante && cartaPodeSeColocar){
        boolean b = colocaArrayCartas(matrizCartasJogo,args,imagensCartas,linha);
        adicionaJogadaUndoMove(matrizCartasJogo,linha,args,estadoUndoGlobal, imagensCartas,b);
    }
    else jogadaNaoRealizada(matrizCartasJogo,eventoRelevante,cartaPodeSeColocar,args,imagensCartas);
}
