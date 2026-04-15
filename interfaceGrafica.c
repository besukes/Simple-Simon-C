#include"simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

int escolhaDeResolucao(void){
    printf("Introduza o número da resolução que pretende utilizar\n(1)-1280x720;\n(2)-1600x900\n(3)-1920x1080\n");
    int u;
    scanf("%d",&u);
    return u;
}

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
        .cartas={},.jogada=valido ,.screen = menu,.dica.querDica=0,.dica.numDicas=0,.dica.timeout=0};
    return args;
}

void clean_sdl(int matrizCartasJogo[10][21],SDL_Texture * image[],SDL_Texture * imagensCartas[10][21]){
    //temos que apagar a imagem da memoria da gpu
    for(int i=0;i<10;i++){
        SDL_DestroyTexture(image[i]);
        for(int j=1;j<=matrizCartasJogo[i][0];j++){
            SDL_DestroyTexture(imagensCartas[i][j]);
        }
    }
    IMG_Quit(); //informar a gpu que ja nao é preciso criar uma window
    SDL_Quit();
}

void desenhaFundo(UserBase * args,SDL_Texture * imagensJogo[]){
    SDL_Rect fundo = {0, 0, 1920, 1080};
    SDL_RenderCopy(args->rendererBase, imagensJogo[0], NULL, &fundo);
}

void botoes(UserBase * args,SDL_Texture * imagensJogo[]){
    if(args->screen == jogo) {
        for(int i=1;i<5;i++){
            SDL_Rect botao = {400 + 300 *(i-1),1000,200,50};
            SDL_RenderCopy(args->rendererBase, imagensJogo[i], NULL, &botao);
        }
    }
    else if(args->screen == menu) {
        SDL_Rect botaoJogar = {860, 500, 200, 50};
        SDL_Rect botaoSair = {860, 600, 200, 50};
        SDL_RenderCopy(args->rendererBase, imagensJogo[2], NULL, &botaoJogar);
        SDL_RenderCopy(args->rendererBase, imagensJogo[1], NULL, &botaoSair);
    }
}


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

void desenharJogo(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21],SDL_Texture *imagensJogo[], UserBase *args, SDL_Event event,Mix_Chunk * arraySom[]) {
    SDL_SetRenderDrawColor(args->rendererBase, 0, 120, 0, 255);
    // Fundo
    desenhaFundo(args, imagensJogo);
    desenharCartas(matrizJogo,imagensCartas,args);
    botoes(args,imagensJogo);
    if(args->dica.querDica==1 && args->dica.timeout>0){
        for(int i=0;i<args->dica.numDicas;i++){
            SDL_Rect b = {75+178*i,112+32*matrizJogo[i][matrizJogo[i][0]],140,190};
            //queremos colocar aqui a cena por cima das cartas;
        }
    }
    if (args->filaSelecionada != -1 && args->numCartasSelecionadas > 0)
    {
        dragCartas(matrizJogo, imagensCartas, args,arraySom);
    }
}

void desenhaMenu(UserBase * args , SDL_Texture *imagensJogo[] ,  SDL_Event event)
{
    SDL_SetRenderDrawColor(args->rendererBase, 0, 120, 0, 255);
    desenhaFundo(args , imagensJogo);
    botoes(args , imagensJogo); 
}


void dragCartas(int matrizJogo[10][21], SDL_Texture *imagensCartas[10][21], UserBase *args,Mix_Chunk * arraySom[]) {
    int cartaW = 140, cartaH = 190, passo = 32;
    for (int i = 0; i < args->numCartasSelecionadas; i++) {
        SDL_Rect dest;
        dest.x = args->mouseX - 70;
        dest.y = args->mouseY + i * passo - 65;
        dest.w = cartaW;
        dest.h = cartaH;
        SDL_RenderCopy(args->rendererBase, args->imgs[i], NULL, &dest);
    }
    tocaPegaCarta(arraySom);
}



void tocaPegaCarta (Mix_Chunk * arraySom[])
{
    Mix_PlayChannel(1 , arraySom[0], 0);
    Mix_VolumeChunk(arraySom[0] , 128);
}

void undoSFX (Mix_Chunk * arraySom[])
{
    Mix_PlayChannel(1 , arraySom[1], 0);
    Mix_VolumeChunk(arraySom[1] , 128);
}