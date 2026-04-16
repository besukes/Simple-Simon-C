#include"simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>

/*Pergunta inicialmente ao utilizador a resolução que pretende utilizar no seu jogo*/
int escolhaDeResolucao(void){
    printf("Introduza o número da resolução que pretende utilizar\n(1)-1280x720;\n(2)-1600x900\n(3)-1920x1080\n");
    int u;
    scanf("%d",&u);
    return u;
}

/*Função que dado uma opção de resolução atribui os valores de largura e altura da janela*/
void atribuiResolucao(int * resX,int * resY,int optn){
    switch(optn){
        case 1:
            *resX=1280;*resY=720;
        break;
        case 2:
            *resX=1600;*resY=900;
        break;
        case 3:
            *resX=1920;*resY=1080;
        break;
        //passivel de mudancas
        default:
            *resX=1920;*resY=1080;
    }
}

/*Função que inicializa o SDL e cria a janela do jogo, tal como criar um tipo UserBase args e retorná-lo.
    Este UserBase contém toda a informação importante e necessária para o funcionamento do jogo e das suas funcionalidades*/
UserBase sdl_initializer(void){
    SDL_Init(SDL_INIT_VIDEO);
    int resolution=escolhaDeResolucao(),resX,resY;
    atribuiResolucao(&resX,&resY,resolution);
    SDL_Window* window = SDL_CreateWindow("Simple Simon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resX, resY, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //para nao precisar de dar scale as imagens no ecra
    SDL_RenderSetLogicalSize(renderer, 1920, 1080);
    // se nao der compile usar flags -std=c99 ou -std=c11
    UserBase args={.rendererBase=renderer,.mouseButtonDown=0,.filaSelecionada=(-1),.numCartasSelecionadas=0,
        .cartas={},.jogada=valido ,.screen = menu,.dica.querDica=0,.dica.numDicas=0,.dica.timeout=0, .estilo = balatro};
    return args;
}

/*No final da execução do programa, liberta a memória alocada para as texturas e apaga a window criada*/
void clean_sdl(int matrizCartasJogo[10][21],SDL_Texture * image[],SDL_Texture * imagensCartas[10][21],Mix_Chunk * arraySom[]){
    //temos que apagar a imagem da memoria da gpu
    for(int i=0;i<10;i++){
        SDL_DestroyTexture(image[i]);
        for(int j=1;j<=matrizCartasJogo[i][0];j++){
            SDL_DestroyTexture(imagensCartas[i][j]);
        }
        Mix_FreeChunk(arraySom[i]);
    }
    IMG_Quit(); //informar a gpu que ja nao é preciso criar uma window
    SDL_Quit();
}

/* Função que desenha o fundo do jogo ou menu */
void desenhaFundo(UserBase *args, SDL_Texture *imagensJogo[]) {

    SDL_Rect fundo = {0, 0, 1920, 1080};

    if (args->screen == menu || args->screen == temas) {
        SDL_RenderCopy(args->rendererBase, imagensJogo[0], NULL, &fundo);
    }
    else {
        SDL_RenderCopy(args->rendererBase, imagensJogo[7], NULL, &fundo);
    }
}

/*Função que desenha os diversos botões do jogo*/
void botoes(UserBase * args,SDL_Texture * imagensJogo[]){
    if(args->screen == jogo) {
        for(int i=1;i<5;i++){
            SDL_Rect botao = {400 + 300 *(i-1),1000,200,50};
            SDL_RenderCopy(args->rendererBase, imagensJogo[i], NULL, &botao);
        }
    }
    else if(args->screen == menu) {
        SDL_Rect botaoJogar = {860, 500, 200, 50};
        SDL_Rect botaoTemas = {860, 600, 200, 50};
        SDL_Rect botaoSair = {860, 700, 200, 50};
        SDL_RenderCopy(args->rendererBase, imagensJogo[2], NULL, &botaoJogar);
        SDL_RenderCopy(args->rendererBase, imagensJogo[1], NULL, &botaoSair);
        SDL_RenderCopy(args->rendererBase, imagensJogo[8], NULL, &botaoTemas);
    }
}

/*Função que dado uma posição na matriz de uma carta e no seu respectivo valor, desenha a na janela do jogo , desenhando para todas as linhas e desde o indice 1
ate ao indice matrizJogo[col][0] que seria o número de cartas nessa mesma fila*/
void desenharCartas(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21], UserBase *args){
    int cartaW = 140, cartaH = 190, offsetX = 75, espacoX = 178, offsetY = 80, passo = 32;
    for (int col = 0; col < 10; col++) {
        for (int row = 1; row <= matrizJogo[col][0]; row++) {
            SDL_Rect dest;
            //A posicao dos rentangulos esta definida pelo canto esquerdo superior deste mesmo
            dest.x = offsetX + col * espacoX;
            dest.y = offsetY + row * passo; 
            dest.w = cartaW;
            dest.h = cartaH;
            SDL_RenderCopy(args->rendererBase, imagensCartas[col][row], NULL, &dest);
        }
    }
}

/*Função que desenha um retângulo azul em cima das cartas que podem ser movidas para outras filas, se o utilizador quiser uma dica*/
void desenhaDicasJogador(int matrizJogo[10][21],UserBase * args){
    //SDL_SetRenderDrawColor(args->rendererBase, 0, 0 , 255, 255);
    SDL_SetRenderDrawBlendMode(args->rendererBase, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(args->rendererBase, 0, 0 , 255, 67);
    for(int i=0;i<args->dica.numDicas;i++){
        int linha = args->dica.filas[i];
        int numC = matrizJogo[linha][0];
        SDL_Rect b = {75+178*(linha),112+32*(numC-1),140,190};
        SDL_RenderFillRect(args->rendererBase,&b);
    }
}

/* Função que desenha o logo do jogo no ecrã */
void desenhaBotoesCartas(UserBase *args, SDL_Texture *logo) {
    SDL_Rect dest;
    dest.w = 1500;   
    dest.h = 1024;   
    dest.x = (1920 - dest.w) / 2; 
    dest.y = 600;   
    SDL_Point argsP = {args->mouseX, args->mouseY};
    SDL_RenderCopyEx(args->rendererBase, logo, NULL, &dest, 0.5, &argsP, SDL_FLIP_NONE);
}

/*Função principal do módulo interfaceGrafica, que desenha o jogo consoante todas as nuances do mesmo , como se o jogador quiser uma dica, se o utilizador estiver
a segurar cartas, etc..*/
void desenharJogo(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21],SDL_Texture *imagensJogo[], UserBase *args, SDL_Event event,Mix_Chunk * arraySom[]) {
    SDL_SetRenderDrawColor(args->rendererBase, 0, 120, 0, 255);
    desenhaFundo(args, imagensJogo);
    desenharCartas(matrizJogo,imagensCartas,args);
    desenhaBotoesCartas(args, imagensJogo[6]);
    if (args->filaSelecionada != -1 && args->numCartasSelecionadas > 0)
    {
        dragCartas(matrizJogo, imagensCartas, args,arraySom);
    }
    if(args->dica.querDica && args->dica.timeout>0){
        desenhaDicasJogador(matrizJogo,args);
        SDL_SetRenderDrawColor(args->rendererBase, 0, 120, 0, 255);
    }
}


double calculoAngulo (int tempo , double freq , double amp){
    //Nao fazemos o tempo absoluto em termos da duracao dos ciclos para ter um efeito mais aleatorio
    double oscilacao = tempo /1000.0;
    //Precisamos do seno para a onda estar entre -1 e 1 e depois multiplicar por 3.5(constante fixa)
    double onda = sin(oscilacao* freq);
    return onda * amp;
}

// Tciclos é o tempo em segundos por ciclo
double tempoloop(int tempo , double ciclos , double TCiclo){
    // a função fmod é para retornar o resto de divisão com float(preciso disto mas podemos dar tweak para nao usar)
    //https://www.tutorialspoint.com/c_standard_library/c_function_fmod.htm
   int tempopassado = fmod(tempo, 1000.0 * TCiclo);
   return tempopassado / ((1000.0 * TCiclo) / ciclos);
}

/* Função que desenha o logo do jogo no ecrã */
void desenhaLogo(UserBase *args, SDL_Texture *logo) {
    SDL_Rect dest ;
    dest.w = 800;
    dest.h = 400;
    dest.x = (1920 - dest.w) / 2;
    int tempoatual = args->tempo;
    double t = tempoloop(tempoatual, 2.0, 3.5);
    int offset;
    double ang = calculoAngulo(tempoatual, 2.5 ,10);
    if (t < 1.0) {
        offset = (t * 75); // pixeis q sobe e desce = 75 ,podes alterar.
    } else {
        offset = ((2-t) * 75);
    }
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

/*Função que desenha o menu dos temas utilizando outras funções*/
void desenhaTemas(UserBase * args , SDL_Texture *imagensJogo[] ,  SDL_Event event)
{
    desenhaFundo(args, imagensJogo);
    desenhaEstilos(args , imagensJogo , event);
    botoes(args , imagensJogo); 
}

/*Função que desenha todos os estilos de cartas presentes no jogo e deixam o utilizador escolher um deles*/
void desenhaEstilos(UserBase * args , SDL_Texture *imagensJogo[] ,  SDL_Event event)
{
    SDL_Rect balatrob = {400, 100, 500, 300};
    SDL_Rect solitaireb = {1000, 100, 500, 300};
    SDL_Rect menu = {100 , 900 , 200 ,200};
    SDL_Rect YTI = {675 , 600 , 600 ,200};
    SDL_Rect estilo = {675 , 800 , 600 ,200};
    SDL_RenderCopy(args->rendererBase, imagensJogo[9], NULL, &balatrob);
    SDL_RenderCopy(args->rendererBase, imagensJogo[10], NULL, &solitaireb);
    SDL_RenderCopy(args->rendererBase, imagensJogo[11], NULL, &YTI);
    SDL_RenderCopy(args->rendererBase, imagensJogo[1], NULL, &menu);
    if (args -> estilo == balatro)
    {
        SDL_RenderCopy(args->rendererBase, imagensJogo[12], NULL, &estilo);
    }
    else if (args -> estilo == solitaire)
    {
        SDL_RenderCopy(args->rendererBase, imagensJogo[13], NULL, &estilo);
    } 
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
