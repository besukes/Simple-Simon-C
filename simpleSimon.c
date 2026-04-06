#include "simpleSinnon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int verificaVitoria(int * baralhosCompletos){
    int u=0;
    for(int i=0;i<4;i++) u+=*(baralhosCompletos+i);
    return (u==52);
}

int cartaPegavel(int cartaClique,int linhaMatriz,int matrizCartasJogo[10][21]){
    //Caso de não haver cartas nessa fila
    if(cartaClique==(-1)) return 0;
    int i,numeroCartasFila = matrizCartasJogo[linhaMatriz][0],naipe=cartaClique/13;
    for(i=numeroCartasFila;(matrizCartasJogo[linhaMatriz][i])/13 == naipe;i++);
    return (matrizCartasJogo[linhaMatriz][--i] == cartaClique);
}

//Pode se colocar uma carta em cima de outra caso 
int cartaColocavel(int cartaDeBaixo,int cartaDeCima){
    return((cartaDeBaixo-cartaDeCima)==1);
}



void interfaceJogo(int matrizCartasJogo[10][21],int baralhosCompletos[], undoMove estadoUndoGlobal,
SDL_Texture * imagensCartas[10][21],SDL_Texture * imagensJogo[]){
    
}


///////////////////////////////////////////////////////////////
int escolhaDeResolucao(){
    printf("Introduza o número da resolução que pretende utilizar\n(1)-1280x720;\n(2)-1600x900\n(3)-1920x1080");
    int u;
    scanf("%d",&u);
    return u;
}
void atribuiResolucao(int * resX,int * resY,int res){
    switch(res){
        case 1:
            *resX=1280;*resY=720;
        break;
        case 2:
            *resX=1600;*resY=900;
        break;
        case 3:
            *resX=1920;*resY=1080;
        break;
    }
}

SDL_Renderer * sdl_initializer(){
    SDL_Init(SDL_INIT_VIDEO);
    int resolution=escolhaDeResolucao(),resX,resY;
    atribuiResolucao(&resX,&resY,resolution);
    SDL_Window* window = SDL_CreateWindow("Simple Simon", 50*(resX/1920), 25*(resY/1080), resX, resY, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer;
}

void clean_sdl(SDL_Texture * image[]){
    for(int i=0;i<52;i++){
        SDL_DestroyTexture(image[i]); //temos que apagar a imagem da memoria da gpu
    }
    IMG_Quit(); //informar a gpu que ja nao é preciso criar uma window
    SDL_Quit();
}
//////////////////////////////////////////////////////////////
void preset(int cartas[]){

}
void presetStr(string cartasStr[]){

}
void baralhar(int cartas[],string cartasStr[]){
    
}


void criarJogo(int matrizCartasJogo[10][21],SDL_Texture * imagensCartas[10][21]){
    int cartas[52];preset(cartas);
    string cartasStr[52];presetStr(cartasStr);
    baralhar(cartas,cartasStr);
    inicializarMatrizes(matrizCartasJogo,imagensCartas);
}

int main(){
    SDL_Renderer * renderer = sdl_initializer();
    //precisamos de uma função que inicialize estes dois
    SDL_Texture * imagensJogo[10], * imagensCartas[10][21];
    //o limite máximo teórico numa fila de cartas seria 21
    int matrizCartasJogo[10][21], baralhosCompletos[4]={0};
    undoMove estadoUndoGlobal = {0,{}};
    criarJogo(matrizCartasJogo,imagensJogo);
    interfaceJogo(matrizCartasJogo,baralhosCompletos,estadoUndoGlobal,imagensCartas,imagensJogo);
    clean_sdl(imagensJogo);
    return 0;
}
