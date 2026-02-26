#include <SDL3/SDL.h>
#include <iostream>


struct SDLState {
    SDL_Window* window;
    SDL_Renderer* renderer;
    
};

void cleanup(SDLState* state);

int main(int argc, char* argv[]) {
    SDLState state;
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Error initial", nullptr);
    
        return 1;
    }
    int w = 800;
    int h = 600;

    state.window = SDL_CreateWindow("demo", w, h, 0);
    
    if (!state.window){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Error creating window", nullptr);
        cleanup(&state);
        return 1;
        

    }

    
    state.renderer = SDL_CreateRenderer(state.window, nullptr);
    
    if (!state.renderer){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Error creating renderer", nullptr);
        cleanup(&state);
        return 1;
        
    }


    
    bool running = true;
    while (running) {
        
        SDL_Event e{ 0 };
        
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_QUIT:
                {
                    running = false;
                    break;
                }
            
            }           
        }
        
        SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
        SDL_RenderClear(state.renderer);


        SDL_RenderPresent(state.renderer);
        
        
    }
    
    cleanup(&state);   
    return 0;

}


void cleanup(SDLState* state ) {
    
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    SDL_Quit();
}
