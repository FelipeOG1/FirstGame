#include <SDL2/SDL.h>
#include <iostream>
#include <string>



void draw_white_box(SDL_Renderer* renderer, SDL_Rect* rect) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, rect); 

       
}

int main(int argc, char* argv[]) {
    
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to setup sdl";
    }
       

    SDL_Window* window = SDL_CreateWindow(
        "Hola mundo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    
        
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    

    SDL_Event event;
    bool running = true;

    SDL_Rect rect = {100, 200, 50, 50};

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false; 
            }
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);
        SDL_RenderClear(renderer);

        draw_white_box(renderer, &rect);
        
        SDL_RenderPresent(renderer);
        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
