#include "simpleSimon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

/*Função responsável por lidar com a jogada do usuário no jogo.
Se este clicar no botão esquerdo do mouse , então executa a função efetuaEventoClique e indica no args que o botão esquerdo do rato foi pressionado.
Se este soltar o botão esquerdo do rato , então executa a função efetuaEventoSoltar e indica no args que o botão esquerdo do rato foi solto.*/
void handleGameplay(int matrizCartasJogo[10][21],undoMove * estadoUndoGlobal,UserBase * args,
SDL_Event event,SDL_Texture* imagensCartas[10][21],Mix_Chunk * arraySom[]){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            (*args).mouseButtonDown = 1;
            efetuaEventoClique(matrizCartasJogo,estadoUndoGlobal,args,event,imagensCartas,arraySom);
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT){
            (*args).mouseButtonDown = 0;
            efetuaEventoSoltar(matrizCartasJogo,estadoUndoGlobal,args,event , imagensCartas);
            resetArgs(args);
        }
    }
}

/*Se o utilizador tiver clicado no botão esquerdo do rato no menu , então efetua a respectiva jogada*/
void handlemenu (UserBase * args, SDL_Event event){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            efetuaEventoCliqueMenu(args,event);
        }
    }
}

/*Função responsável por inicializar as texturas dos botões do jogo*/
void inicializaTexturasJogo(SDL_Texture * imagensJogo[],SDL_Renderer * renderer){
    //imagensJogo[0] = IMG_LoadTexture(renderer,"assets/fundo.png")
    imagensJogo[1] = IMG_LoadTexture(renderer,"assets/Botoes/quit.png");
    imagensJogo[2] = IMG_LoadTexture(renderer,"assets/Botoes/NG.png");
    imagensJogo[3] = IMG_LoadTexture(renderer,"assets/Botoes/undo.png");
    imagensJogo[4] = IMG_LoadTexture(renderer,"assets/Botoes/dica.png");
}

/*Se o utilizador estiver no menu , copia para o renderer as imagens do menu e verifica o que é que o usuário pretende fazer dependendo dos cliques do mesmo*/
void telaMenu (UserBase * args,SDL_Texture * imagensJogo[], SDL_Event event){
    desenhaMenu(args , imagensJogo , event);
    handlemenu(args,event);
}

/*Caso o utilizador esteja na tela do jogo em si , o programa verifica se o utilizador pretende que lhe seja mostrado uma dica , coloca no renderer todas as
imagens necessárias , realiza os eventos que o utilizador realiza ao longo do jogo , e , por fim , também verifica se o jogo foi vencido e , se for , 
mostra um mensagem de vitória*/
void interfaceJogo(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21],
SDL_Texture * imagensJogo[],UserBase * args,SDL_Event event,Mix_Chunk * arraySom[]){
    atualizaEstadoDica(args);
    desenharJogo(matrizCartasJogo , imagensCartas , imagensJogo , args ,event,arraySom);
    handleGameplay(matrizCartasJogo,estadoUndoGlobal,args,event,imagensCartas,arraySom);
    verificaVitoria(matrizCartasJogo,args);
    //temos de fazer
    if(args-> jogada == vitoria);
}


/*Esta é a função responsável por controlar o fluxo do jogo.
Até o utilizador desejar sair seja pelo X na janela ou pelo botão de sair , este continua no jogo num ciclo que capta as interações deste mesmo com a janela
do jogo , e executa as respectivas funções tendo em conta a tela do utilizador.
Também fornece a essas funções os parâmetros necessários para a sua execução , como o "evento" que o utilizador realizou.
Por fim executa o SDL_RenderPresent para apresentar todas as imagens na tela*/
void interfaceSimpleSimon(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21],
SDL_Texture * imagensJogo[],UserBase * args,Mix_Chunk * arraySom[]){
    SDL_Event event;
    inicializaTexturasJogo(imagensJogo,args->rendererBase);
    //enquanto o utilizador nao clicar no botao para sair ele continua no jogo
    while(event.type != SDL_QUIT && args->jogada!= sair){
        SDL_PollEvent(&event);
        SDL_RenderClear((*args).rendererBase);
        if(event.type == SDL_MOUSEMOTION){
            args->mouseX = event.motion.x;
            args->mouseY = event.motion.y;
        }
        if(args->screen == jogo){
            interfaceJogo(matrizCartasJogo,estadoUndoGlobal,imagensCartas,imagensJogo,args,event,arraySom);
        }
        else telaMenu(args,imagensJogo,event);
        SDL_RenderPresent((*args).rendererBase);
    }

}

/*Função principal do jogo, responsável por inicializar o jogo de modo geral e todas as variáveis necessárias para a realização do mesmo ,
como também inicializa a janela , executa as funções que rodam o jogo e , por fim , apaga as texturas todas que criou e encerra o jogo*/
int main(void){
    UserBase args = sdl_initializer();
    SDL_Texture* imagensJogo[10];
    SDL_Texture* imagensCartas[10][21];
    tocamusica();
    Mix_Chunk * arraySom[10];
    inicializaArraySom(arraySom);
    //o limite máximo teórico numa fila de cartas seria 21
    int matrizCartasJogo[10][21];
    undoMove estadoUndoGlobal = {0,{}};
    criarJogo(matrizCartasJogo,imagensCartas,args.rendererBase);
    interfaceSimpleSimon(matrizCartasJogo,&estadoUndoGlobal,imagensCartas,imagensJogo,&args,arraySom);
    clean_sdl(matrizCartasJogo,imagensJogo,imagensCartas,arraySom);
    return 0;
}
