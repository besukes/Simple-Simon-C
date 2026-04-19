#include"simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

// A Função offsetloop retorna um valor entre 0 e dist que sobe e desce ciclicamente.
// Tciclo serve para dizer a duração da interação toda , ou seja , se for 2 segundos e 2 ciclos então demora 1 segundo por cada ciclo.
double offsetloop(int tempo , double TCiclo, int dist){
    // a função fmod é para retornar o resto de divisão com float(preciso disto mas podemos dar tweak para nao usar)
    //https://www.tutorialspoint.com/c_standard_library/c_function_fmod.htm
   int tempopassado = fmod(tempo, 1000.0 * TCiclo);
   double t = tempopassado / ((1000.0 * TCiclo) / 2);
    if (t  < 1.0) {
         return t * dist;
    }
    else {
        return (2 - t) * dist;
    }
}


/* Função que desenha o fundo da respectiva janela de onde o utilizador se encontra */
void desenhaFundo(UserBase *args, SDL_Texture *imagensJogo[]) {

    SDL_Rect fundo = {0, 0, 1920, 1080};
    //Desenhar o fundo do menu inicial
    if (args->screen == menu) {
        SDL_RenderCopy(args->rendererBase, imagensJogo[0], NULL, &fundo);
    }
    //Desenhar o fundo do menu de temas
    else if (args->screen == temas) {
        SDL_RenderCopy(args->rendererBase, imagensJogo[18], NULL, &fundo); 
    }
    //Desenhar o fundo da tela de jogo
    else {
        SDL_RenderCopy(args->rendererBase, imagensJogo[7], NULL, &fundo);
    }
}
//Função feita para generalizar hovered effect
int isHoveredGeral (UserBase *args ,SDL_Rect *rect)
{
    return (args->mouseX >= rect->x  && args->mouseX <= rect->x+ rect->w 
            &&args->mouseY >= rect->y && args->mouseY <= rect->y + rect->h);
}
/* Renderiza texto centrado no x=960 (em 1920x1080 e scaled para outras resoluções) com sombra */
static void renderTextoCentrado(SDL_Renderer *r, TTF_Font *f,
                                const char *txt, SDL_Color cor,
                                int y, int escala)
{
    SDL_Surface *s = TTF_RenderText_Blended(f, txt, cor);
    SDL_Texture *tx = SDL_CreateTextureFromSurface(r, s);
    int w = s->w * escala, h = s->h * escala;
    SDL_FreeSurface(s);
    SDL_Rect sombra = {960 - w / 2 + 5, y + 5, w, h};
    SDL_Rect rect = {960 - w / 2, y, w, h};
    SDL_SetTextureColorMod(tx, 60, 45, 0);
    SDL_RenderCopy(r, tx, NULL, &sombra);
    SDL_SetTextureColorMod(tx, cor.r, cor.g, cor.b);
    SDL_RenderCopy(r, tx, NULL, &rect);
    SDL_DestroyTexture(tx);
}
//Função que faz efeito hover e efeito spin na carta de temas Balatro
/*O cálculo do angulo aqui é um pouco diferente , como 360 = 0 , então o que faço é , no primeiro tick de clique eu digo que VelB é 200 ,
e a cada tick de jogo este 200 é multiplicado por 0.99 , quando este velB chega a 0.04- , então para de "girar" e volta para o ang = 0 q é a 
posição inicial
O efeito de hover é o mesmo de sempre , é aquele "boolean" */
void desenhaEstilosGiroB (UserBase *args , SDL_Texture *imagensJogo[], SDL_Rect *tema)
{
    
    int Hovered = isHoveredGeral(args , tema);
        args->angB += args->velB;
        args->velB *= 0.99;
        if(args->velB < 0.04){
            args->angB = 0;
        }
        else Hovered = 1;
        if (Hovered)
        {
            tema->w += 60;tema->h += 60; tema->x -= 30; tema->y -= 30;
        }   
        SDL_RenderCopyEx(args->rendererBase, imagensJogo[20], NULL, tema ,args->angB , NULL , SDL_FLIP_NONE);
}
//Função que faz efeito hover e efeito spin na carta de temas Solitaire
void desenhaEstilosGiroS (UserBase *args , SDL_Texture *imagensJogo[], SDL_Rect *tema)
{
    
    int Hovered = isHoveredGeral(args , tema);
        args->angS += args->velS;
        args->velS *= 0.99;
        if(args->velS < 0.04){
            
            args->angS = 0;
        }
        else Hovered = 1;
        if (Hovered)
        {
            tema->w += 60;tema->h += 60; tema->x -= 30; tema->y -= 30;
        }
        
        SDL_RenderCopyEx(args->rendererBase, imagensJogo[21], NULL, tema ,args->angS , NULL , SDL_FLIP_NONE);
}

/*Função que desenha os botões do menu inicial no renderer*/
void desenhaBotoesMenu(SDL_Renderer * renderer , SDL_Texture * imagensJogo[]){
    SDL_Rect botaoJogar = { 810, 600, 300, 80 };
    SDL_Rect botaoTemas = { 810, 720, 300, 80 };
    SDL_Rect botaoSair  = { 810, 840, 300, 80 };
    SDL_RenderCopy(renderer, imagensJogo[2], NULL, &botaoJogar);
    SDL_RenderCopy(renderer, imagensJogo[1], NULL, &botaoSair);
    SDL_RenderCopy(renderer, imagensJogo[8], NULL, &botaoTemas);
}

/*Função que desenha os diversos botões do jogo*/
void botoes(UserBase *args, SDL_Texture *imagensJogo[])
{
    if (args->screen == jogo) {
        for (int i = 1; i < 5; i++) {
            SDL_Rect botao = { 350 + 330 * (i - 1), 1050, 280, 80 };
            SDL_RenderCopy(args->rendererBase, imagensJogo[i], NULL, &botao);
        }
    }
    else if (args->screen == menu) {
        desenhaBotoesMenu(args->rendererBase,imagensJogo);
    }
    else if (args ->screen == temas)
    {
        inicializaTema(args ,imagensJogo);                 
    }
}
void inicializaTema (UserBase *args , SDL_Texture *imagensJogo[])
{
        SDL_Rect balatrob = {270, 320, 375, 390};
        SDL_Rect solitaireb = {1300, 320, 400, 390};
        desenhaEstilosGiroB(args , imagensJogo ,&balatrob);
        desenhaEstilosGiroS(args, imagensJogo , &solitaireb);             
}

//Função feita para a lógica do hover ter a hitbox certa para cartas acima da primeira
int eUltimaCarta ( int row , int Trow , int passo , int Altura)
{
    if ( row < Trow)
    return passo;
    else
    return Altura;
}
//Função feita para reduzir o numero de coisas no pmccabe da função feita para reduzir o numero de coisas no pmccabe para a função desenhacartas, exótica++
void setaHover(int *extraW , int *extraH , int *destX , int *destY , int *destW , int *destH , double offset){
    *extraW = 5;
    *extraH = 10;

    *destX -= *extraW / 2;
    *destY -= *extraH / 2 + offset;

    *destW += *extraW;
    *destH += *extraH;
}
//Função feita para reduzir o número de coisas no pmccabe para a função desenhacartas, exótica
void hoverCarta(UserBase *args, int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21] , int col , int row , int *mousenacarta , 
int *extraW , int *extraH , int *destX , int *destY , int *destW , int *destH , double offset , int destWvalor , int destHvalor)
{
            int alturaCarta = eUltimaCarta(row, matrizJogo[col][0], 32, 190);
            int hoveredStack = (
                args->mouseX >= *destX && args->mouseX <= *destX + destWvalor &&
                args->mouseY >= *destY  && args->mouseY <= *destY + alturaCarta
            );
            int hovered = (
                args->mouseX >= *destX && args->mouseX <= *destX + destWvalor &&
                args->mouseY >= *destY && args->mouseY <= *destY + destHvalor
            );
            if (hoveredStack && cartaPegavel(matrizJogo[col][row], col, matrizJogo)) {
                *mousenacarta = 1;
            }
            
            if(args->numCartasSelecionadas == 0 && hovered && 
               cartaPegavel(matrizJogo[col][row], col, matrizJogo) && ( row == matrizJogo[col][0]) ){

               setaHover(extraW , extraH , destX , destY , destW , destH , offset);
            }
            else if(args->numCartasSelecionadas == 0 && cartaPegavel(matrizJogo[col][row], col, matrizJogo) && *mousenacarta ){
        
               setaHover(extraW , extraH , destX , destY , destW , destH , offset);
            }
}

/*Função que dado uma posição na matriz de uma carta e no seu respectivo valor, desenha a na janela do jogo , desenhando para todas as linhas e desde o indice 1
ate ao indice matrizJogo[col][0] que seria o número de cartas nessa mesma fila*/
void desenharCartas(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21], UserBase *args){
    int cartaW = 140, cartaH = 190, offsetX = 75, espacoX = 178, offsetY = 80, passo = 32 ;
    double offset = offsetloop(args->tempo, 2, 8);
    for (int col = 0; col < 10; col++) {
        int mousenacarta = 0;
        for (int row = 1; row <= matrizJogo[col][0]; row++) {
           int extraW = 0 , extraH = 0;
            SDL_Rect dest = {offsetX + col * espacoX,offsetY + row * passo, cartaW,cartaH};
            hoverCarta(args , matrizJogo , imagensCartas, col , row ,&mousenacarta , &extraW , &extraH , 
                &dest.x, &dest.y, &dest.w, &dest.h , offset, dest.w , dest.h);
            SDL_RenderCopyEx(args->rendererBase, imagensCartas[col][row], NULL, &dest, 0, NULL, SDL_FLIP_NONE);
        }
    } 
}
/*Função que desenha um retângulo azul em cima das cartas que podem ser movidas para outras filas, se o utilizador quiser uma dica*/
void desenhaDicasJogador(int matrizJogo[10][21],UserBase * args){
    SDL_SetRenderDrawBlendMode(args->rendererBase, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(args->rendererBase, 0, 0 , 255, 67);
    for(int i=0;i<args->dica.numDicas;i++){
        int linha = args->dica.filas[i];
        int numC = matrizJogo[linha][0];
        SDL_Rect b = {75+178*(linha),112+32*(numC-1),140,190};
        SDL_RenderFillRect(args->rendererBase,&b);
    }
}

/* Função que desenha os "botões" de sair , novo jogo , dica e de desfazer jogada , durante o jogo*/
void desenhaHandRow(UserBase *args, SDL_Texture *cards[], int numCards) {
    int cardW = 379,cardH = 529,spacing = (-30),totalWidth = numCards * cardW + (numCards - 1) * spacing,
        startX = (1920 - totalWidth) / 2 ,startY = 1080 - cardH + 250; 
    double offset = offsetloop(args->tempo,1, 10);
    for (int i = 0; i < numCards; i++) {
        int x = startX + i * (cardW + spacing),y = startY,w = cardW,h = cardH,
            hovered = (args->mouseX >= x + 30 && args->mouseX <= x -30 + w &&
                       args->mouseY >= y && args->mouseY <= y + h);
        if (hovered) {
            int scaleExtra = 40;
            w += scaleExtra;
            h += scaleExtra;
            x -= scaleExtra / 2;
            y -= scaleExtra + offset;
        }

        SDL_Rect dest = {x, y, w, h};
        SDL_RenderCopyEx(args->rendererBase, cards[i], NULL, &dest, 0 ,  NULL, SDL_FLIP_NONE);
    }
}



/*Função principal do módulo interfaceGrafica, que desenha o jogo consoante todas as nuances do mesmo , como se o jogador quiser uma dica, se o utilizador estiver
a segurar cartas, etc..*/
void desenharJogo(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21],SDL_Texture *imagensJogo[], UserBase *args, SDL_Event event,Mix_Chunk * arraySom[]) {
    SDL_SetRenderDrawColor(args->rendererBase, 0, 120, 0, 255);
    desenhaFundo(args, imagensJogo);
    desenharCartas(matrizJogo,imagensCartas,args);
    SDL_Texture *hand[4] = {
        imagensJogo[13],
        imagensJogo[14],
        imagensJogo[15],
        imagensJogo[16]
    };
    desenhaHandRow(args, hand, 4);
    if (args->filaSelecionada != -1 && args->numCartasSelecionadas > 0)
    {
        dragCartas(matrizJogo, imagensCartas, args,arraySom);
    }
    if(args->dica.querDica && args->dica.timeout>0){
        desenhaDicasJogador(matrizJogo,args);
        SDL_SetRenderDrawColor(args->rendererBase, 0, 120, 0, 255);
    }
}

// Função que retorna valores entre -amp e amp com uma frequência fornecida na chamada da função 
// Serve para dar um efeito de balanço em certos elementos do jogo
double calculoAngulo (int tempo , double freq , double amp){
    //Nao fazemos o tempo absoluto em termos da duracao dos ciclos para ter um efeito mais aleatorio
    double oscilacao = tempo /1000.0;
    //Precisamos do seno para a onda estar entre -1 e 1 e depois multiplicar por amplitude
    double onda = sin(oscilacao* freq);
    return onda * amp;
}
//Funçaõ que escreve o tema selecionado e faz uma animação
void selecaoTema (UserBase *args , SDL_Texture *imagensJogo[] , int estilo)
{
    
    SDL_Rect dest ;
    dest.w = 500;
    dest.h = 400;
    dest.x = (1920 - dest.w) / 2;
    int tempoatual = args->tempo;
    double offset = offsetloop(tempoatual, 1.5, 25);
    double ang = calculoAngulo(tempoatual, 10 ,5);
    dest.y = 325 + offset;
    SDL_RenderCopyEx(args->rendererBase, imagensJogo[12 + 7*estilo], NULL, &dest, ang, NULL, SDL_FLIP_NONE);
}

/* Função que desenha o logo do jogo no ecrã */
void desenhaLogo(UserBase *args, SDL_Texture *logo) {
    SDL_Rect dest ;
    dest.w = 800;
    dest.h = 400;
    dest.x = (1920 - dest.w) / 2;
    int tempoatual = args->tempo;
    double offset = offsetloop(tempoatual, 3.5, 75);
    double ang = calculoAngulo(tempoatual, 2.5 ,10);
    dest.y = 100 + offset;
    SDL_RenderCopyEx(args->rendererBase, logo, NULL, &dest, ang, NULL, SDL_FLIP_NONE);
}

/*Função que desenha o menu inicial do jogo*/
void desenhaMenu(UserBase * args , SDL_Texture *imagensJogo[] ,  SDL_Event event)
{
    SDL_SetRenderDrawColor(args->rendererBase, 0, 120, 0, 255);
    desenhaFundo(args, imagensJogo);
    desenhaLogo(args, imagensJogo[5]);
    botoes(args , imagensJogo); 
}


/* Desenha o menu de vitória para quando o utilizador vence */
void desenhaVitoria(UserBase *args, SDL_Texture *imagensJogo[])
{
    SDL_Renderer *ren = args->rendererBase;
    SDL_Rect fundo = {0, 0, 1920, 1080};
    SDL_RenderCopy(args->rendererBase, imagensJogo[19], NULL, &fundo);
    SDL_Texture *hand[2] = {imagensJogo[13], imagensJogo[14]};
    desenhaHandRow(args, hand, 2);
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    char str[30];
    sprintf(str, "Score: %d", args->score);
    renderTextoCentrado(ren, args->fonte, str,(SDL_Color){255, 255, 255, 255}, 475, 3);
}

/*Função que desenha o menu dos temas utilizando outras funções*/
void desenhaTemas(UserBase * args , SDL_Texture *imagensJogo[] ,  SDL_Event event)
{
    desenhaFundo(args, imagensJogo);
    botoes(args , imagensJogo); 
    SDL_Texture *hand[1] = {imagensJogo[13]};
    desenhaHandRow(args , hand , 1);
    if ( args-> estilo == balatro)
    selecaoTema(args, imagensJogo , 0);
    else
    selecaoTema(args, imagensJogo , 1);
}

/*Função que desenha as cartas que estão a ser arrastadas pelo utilizador utilizando o UserBase e as cartas que lá estão guardadas (apenas executa se
o args->mouseButtonDown ==1,i.e, o utilizador está a segurar o mouse , e se tiver uma fila selecionada(args->filaSelecionada != -1))*/
void dragCartas(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21], UserBase *args,Mix_Chunk * arraySom[]) {
    int cartaW = 140, cartaH = 190, passo = 32;
    double ang = calculoAngulo(args->tempo , 5 , 15);
    for (int i = 0; i < args->numCartasSelecionadas; i++) {
        SDL_Rect dest;
        dest.x = args->mouseX - 70;
        dest.y = args->mouseY + i * passo - 65;
        dest.w = cartaW;
        dest.h = cartaH;
        SDL_RenderCopyEx(args->rendererBase, args->imgs[i], NULL, &dest , ang, NULL, SDL_FLIP_NONE);
    }
    tocaPegaCarta(arraySom);
}
