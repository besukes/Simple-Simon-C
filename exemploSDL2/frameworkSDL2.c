#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//sudo apt-get install libsdl2-image-dev
//gcc frameworkSDL2.c -o teste -lSDL2 -lSDL2_image


SDL_Renderer * sdl_initializer(void){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Stu 67", 50, 25, 1280, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer;
}

void clean_sdl(SDL_Texture * image){
    // 5. Cleanup
    SDL_DestroyTexture(image); //temos que apagar a imagem da memoria da gpu
    IMG_Quit(); //informar a gpu que ja nao é preciso criar uma window
    SDL_Quit();
}

int main(void) {
    SDL_Renderer* renderer = sdl_initializer(); //sdl_initiliazer funcao criada por mim
    // 2. Load the PNG into a Texture
    // This helper function handles the Surface -> Texture conversion for you
    SDL_Texture* my_image = IMG_LoadTexture(renderer, "stuzao.png");
    SDL_Rect destination_rect = { 400, 150, 400, 300 };
    SDL_Event event;
    while (!(event.type == SDL_QUIT)) {
        SDL_PollEvent(&event);
        int mouseX, mouseY;
        // Verifica se o utilizador quer fechar a janela
        if(event.type== SDL_MOUSEBUTTONDOWN){
            // Verifica se foi o botão esquerdo
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseX = event.button.x;
                mouseY = event.button.y;
                
                printf("Clique detetado em: X=%d, Y=%d\n", mouseX, mouseY);
            }
        }
        SDL_RenderClear(renderer);
        // 4. Copy the texture to the renderer
        // NULL for the second argument means "use the entire source image"
        SDL_RenderCopy(renderer, my_image, NULL, &destination_rect);
        SDL_RenderPresent(renderer);
    }
    clean_sdl(my_image);
    return 0;
}


/* Exemplo que o GEMINI nos deu para por as cartas no ecra (Muito bom exemplo)
// Dentro do teu loop principal de renderização
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 21; j++) {
        // 1. Só desenha se existir uma textura carregada nessa posição
        if (imagensCartas[i][j] != NULL) {
            
            // 2. Define ONDE a carta vai aparecer no ecrã
            SDL_Rect destino;
            destino.x = i * 80;  // Afasta as colunas (ex: 80 pixéis cada)
            destino.y = j * 30;  // Afasta as cartas na pilha (ex: sobreposição de 30 px)
            destino.w = 70;      // Largura da carta
            destino.h = 100;     // Altura da carta

            // 3. Copia a textura do teu array para o renderer
            SDL_RenderCopy(renderer, imagensCartas[i][j], NULL, &destino);
        }
    }
}
*/
