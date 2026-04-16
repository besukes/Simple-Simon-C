#include <SDL2/SDL_mixer.h>


/*Função que toca a música de fundo do jogo*/
void tocamusica(void){
    Mix_Music *balatro = NULL;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    balatro = Mix_LoadMUS("musica/balatro.mp3");
    Mix_PlayMusic(balatro, -1); 
    Mix_VolumeMusic(67);
}

/*Função que inicializa o array de sons*/
void inicializaArraySom(Mix_Chunk * arraySom[]){
    arraySom[0] = Mix_LoadWAV("sfx/CardDrop.mp3");
    arraySom[1] = Mix_LoadWAV("sfx/undo1.mp3");
    arraySom[2] = Mix_LoadWAV("sfx/ng.mp3");
}
void ngSFX (Mix_Chunk * arraySom[])
{
    Mix_Chunk * p = arraySom[2];
    Mix_VolumeChunk(p , 128);
    Mix_PlayChannel(1 , p, 0);
}
/*Função que toca o som de pegar uma carta*/
void tocaPegaCarta (Mix_Chunk * arraySom[])
{
    Mix_Chunk * p = arraySom[0];
    Mix_VolumeChunk(p , 128);
    Mix_PlayChannel(1 , p, 0);
}

/*Função que toca um som ao clicar no botão de undo jogada*/
void undoSFX (Mix_Chunk * arraySom[])
{
    Mix_Chunk * p = arraySom[1];
    Mix_VolumeChunk(p , 128);
    Mix_PlayChannel(1 , p , 0);
}