#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
