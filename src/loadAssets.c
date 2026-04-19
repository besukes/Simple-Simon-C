#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


/*Função que inicializa o array de sons*/
void inicializaArraySom(Mix_Chunk * arraySom[]){
    arraySom[0] = Mix_LoadWAV("sfx/CardDrop.mp3");
    arraySom[1] = Mix_LoadWAV("sfx/undo1.mp3");
    arraySom[2] = Mix_LoadWAV("sfx/ng.mp3");
}

/*Função que carrega as texturas dos botões para um array de texturas de imagens do jogo*/
void botoesLoad(SDL_Texture * imagensJogo[],SDL_Renderer * renderer){
    imagensJogo[1] = IMG_LoadTexture(renderer,"assets/Botoes/quit.png");
    imagensJogo[2] = IMG_LoadTexture(renderer,"assets/Botoes/NG.png");
    imagensJogo[3] = IMG_LoadTexture(renderer,"assets/Botoes/undo.png");
    imagensJogo[4] = IMG_LoadTexture(renderer,"assets/Botoes/dica.png");
    imagensJogo[8] = IMG_LoadTexture(renderer,"assets/Botoes/themes.png");
    imagensJogo[11] = IMG_LoadTexture(renderer,"assets/Botoes/YTI.png");
    imagensJogo[12] = IMG_LoadTexture(renderer,"assets/Botoes/balatroTheme.png");
    imagensJogo[19] = IMG_LoadTexture(renderer,"assets/Botoes/solitaireTheme.png");
    imagensJogo[20] = IMG_LoadTexture(renderer, "assets/Botoes/CartaBalatro.png");
    imagensJogo[21] = IMG_LoadTexture(renderer, "assets/Botoes/CartaSolitaire.png");
}

/*Função responsável por inicializar as texturas dos botões do jogo*/
void inicializaTexturasJogo(SDL_Texture * imagensJogo[],SDL_Renderer * renderer){
    imagensJogo[0] = IMG_LoadTexture(renderer,"assets/background.jpg");
    botoesLoad(imagensJogo,renderer);
    imagensJogo[5] = IMG_LoadTexture(renderer,"assets/Logo.png");
    imagensJogo[6] = IMG_LoadTexture(renderer,"assets/Cards.png");
    imagensJogo[7] = IMG_LoadTexture(renderer,"assets/mesa.png");
    imagensJogo[9] = IMG_LoadTexture(renderer,"assets/CardsAll.png");
    imagensJogo[10] = IMG_LoadTexture(renderer,"assets/all_cards.png");
    imagensJogo[13] = IMG_LoadTexture(renderer,"assets/Carta1.png");
    imagensJogo[14] = IMG_LoadTexture(renderer,"assets/Carta2.png");
    imagensJogo[15] = IMG_LoadTexture(renderer,"assets/Carta3.png");
    imagensJogo[16] = IMG_LoadTexture(renderer,"assets/Carta4.png");
    imagensJogo[17] = IMG_LoadTexture(renderer,"assets/background2.jpg");
    imagensJogo[18] = IMG_LoadTexture(renderer,"assets/theme.png");
    imagensJogo[22] = IMG_LoadTexture(renderer,"assets/winScreen.png");


}

/* Função responsável por inicializar a fonte m6x11plus para ser usada pelo jogo*/
void inicializafonte(UserBase * args){
    TTF_Init();
    args->fonte = TTF_OpenFont("assets/TTF/m6x11plus.ttf", 24);
}