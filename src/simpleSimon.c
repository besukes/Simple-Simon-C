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

/*Se o utilizador tiver clicado no botão esquerdo do rato no menu inicial , então efetua a respectiva jogada*/
void handlemenu (UserBase * args, SDL_Event event){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            efetuaEventoCliqueMenu(args,event);
        }
    }
}

/*Se o utilizador tiver clicado no botão esquerdo do rato no menu temas , então efetua a respectiva jogada*/
void handletemas(UserBase * args, SDL_Event event){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            efetuaEventoCliqueTemas(args,event);
        }
    }
}

/*Quando o utilizador vencer o jogo e estiver na tela de vitória, então a função verifica se o utilizador clicou no botão esquerdo do rato e realiza a respectiva
jogada */
void handleVitoria(UserBase * args, SDL_Event event , int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal, SDL_Texture * imagensCartas[10][21],Mix_Chunk * arraySom[]){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            efetuaEventoCliqueWin(args,event,matrizCartasJogo,estadoUndoGlobal,imagensCartas,arraySom);
        }
    }
}



/*Se o utilizador estiver no menu , copia para o renderer as imagens do menu e verifica o que é que o usuário pretende fazer dependendo dos cliques do mesmo*/
void telaMenu (UserBase * args,SDL_Texture * imagensJogo[], SDL_Event event){
    desenhaMenu(args , imagensJogo , event);
    handlemenu(args,event);
}

/*Se o utilizador estiver no menu de temas então desenha o menu dos temas e as suas respectivas texturas como também verifica os eventos do clique nessa tela*/
void telaTemas(UserBase * args,SDL_Texture * imagensJogo[], SDL_Event event){
    desenhaTemas(args , imagensJogo , event);
    handletemas(args,event);
}

/*Se o utilizador estiver na tela de vitória então desenha a tela de vitória e verifica os eventos do clique nessa tela*/
void telaVitoria(UserBase * args,SDL_Texture * imagensJogo[], SDL_Event event , int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal, SDL_Texture * imagensCartas[10][21],Mix_Chunk * arraySom[]){
    desenhaVitoria(args , imagensJogo , event);
    handleVitoria(args,event,matrizCartasJogo,estadoUndoGlobal,imagensCartas,arraySom);
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
    if(args-> jogada == vitoria)
        handleWINcon(args);
}

/*Função responsável por verificar o estado da tela e chamar a função apropriada à mesma*/
void verificaEstadoTela(int matrizCartasJogo[10][21], undoMove * estadoUndoGlobal,SDL_Texture * imagensCartas[10][21],SDL_Texture * imagensJogo[],
UserBase * args,SDL_Event event,Mix_Chunk *arraySom[]){
    if(args->screen == jogo){
        interfaceJogo(matrizCartasJogo,estadoUndoGlobal,imagensCartas,imagensJogo,args,event,arraySom);
    }
    else if(args->screen == menu ){
        telaMenu(args,imagensJogo,event);
    }
    else if(args->screen == temas){
        telaTemas(args,imagensJogo,event);
    }
    else if(args->screen == win){
        telaVitoria(args,imagensJogo,event,matrizCartasJogo,estadoUndoGlobal,imagensCartas,arraySom);
    }   
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
        args->tempo = SDL_GetTicks();
        tempoemjogo(args);
        SDL_RenderClear((*args).rendererBase);
        if(event.type == SDL_MOUSEMOTION){
            args->mouseX = event.motion.x;
            args->mouseY = event.motion.y;
        }
        verificaEstadoTela(matrizCartasJogo,estadoUndoGlobal,imagensCartas,imagensJogo,args,event,arraySom);
        SDL_RenderPresent((*args).rendererBase);
    }

}

/*Função principal do jogo, responsável por inicializar o jogo de modo geral e todas as variáveis necessárias para a realização do mesmo ,
como também inicializa a janela , executa as funções que rodam o jogo e , por fim , apaga as texturas todas que criou e encerra o jogo*/
int main(void){
    UserBase args = sdl_initializer();
    SDL_Texture* imagensJogo[20];
    SDL_Texture* imagensCartas[10][21];
    tocamusica();
    Mix_Chunk * arraySom[10];
    inicializaArraySom(arraySom);
    inicializafonte(&args);
    //o limite máximo teórico numa fila de cartas seria 21
    int matrizCartasJogo[10][21];
    undoMove estadoUndoGlobal = {0,{}};
    criarJogo(matrizCartasJogo,imagensCartas,args.rendererBase, &args);
    interfaceSimpleSimon(matrizCartasJogo,&estadoUndoGlobal,imagensCartas,imagensJogo,&args,arraySom);
    clean_sdl(matrizCartasJogo,imagensJogo,imagensCartas,arraySom);
    return 0;
}
