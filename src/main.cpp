#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

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

    state.window = SDL_CreateWindow("demo", w, h, SDL_WINDOW_RESIZABLE);
    
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
    int logW = 640;
    int logH = 320;

    SDL_SetRenderLogicalPresentation(state.renderer, logW, logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    SDL_FRect dst {
        .x = 0,
        .y = 10,
        .w = 32,
        .h = 32
    };

    SDL_Texture* idltex = IMG_LoadTexture(state.renderer, "data/player-stand-1.png");
    SDL_SetTextureScaleMode(idltex, SDL_SCALEMODE_NEAREST);
    
    
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


        
        // set backbuffer white 
        SDL_SetRenderDrawColor(state.renderer, 20, 10, 30, 255);
        SDL_RenderClear(state.renderer);
        SDL_RenderTexture(state.renderer, idltex, nullptr, &dst);
        
        // move back buffer to front 
        SDL_RenderPresent(state.renderer);
        
        
    }
    SDL_DestroyTexture(idltex);
    cleanup(&state);   


    return 0;

}


void cleanup(SDLState* state ) {
    
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    SDL_Quit();
}
