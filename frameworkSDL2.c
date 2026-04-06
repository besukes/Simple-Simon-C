#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//sudo apt-get install libsdl2-image-dev
//gcc frameworkSDL2.c -o teste -lSDL2 -lSDL2_image


SDL_Renderer * sdl_initializer(){
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

int main() {
    SDL_Renderer* renderer = sdl_initializer(); //sdl_initiliazer funcao criada por mim
    // 2. Load the PNG into a Texture
    // This helper function handles the Surface -> Texture conversion for you
    SDL_Texture* my_image = IMG_LoadTexture(renderer, "stuzao.png");
    SDL_Rect destination_rect = { 400, 150, 400, 300 };
    SDL_Event e;
    while (!(e.type == SDL_QUIT)) {
        SDL_PollEvent(&e);
        SDL_RenderClear(renderer);
        // 4. Copy the texture to the renderer
        // NULL for the second argument means "use the entire source image"
        SDL_RenderCopy(renderer, my_image, NULL, &destination_rect);
        SDL_RenderPresent(renderer);
    }
    clean_sdl(my_image);
    return 0;
}
