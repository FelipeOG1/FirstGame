#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include "animation.h"
#include "animation_loader.h"
struct SDLState {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int w, h, logW, logH;
    
};

void cleanup(SDLState* state);
int initState(SDLState* state);
int show_error_and_exit(SDLState* state);



struct Resources {
    std::map<int, std::vector<Frame>> playerAnimations;
    
    void loadAall() {
        AnimationLoader loader;
        playerAnimations = loader.getPlayerAnimations();
    }
};
int main(int argc, char* argv[]) {
    Resources res;
    res.loadAall();

    SDLState state;
    initState(&state);
        
    SDL_Texture* idltex = IMG_LoadTexture(state.renderer, "data/player-stand-1.png");
    SDL_SetTextureScaleMode(idltex, SDL_SCALEMODE_NEAREST);

    const bool* keys = SDL_GetKeyboardState(nullptr);
    
    float playerX = 0;
    float playerY = 0;
    
    const float floor = state.logH;
   
    uint64_t prevTime = SDL_GetTicks();

    bool running = true;

    bool rotateCharacter = false;   
    while (running) {
        
        uint64_t nowTime = SDL_GetTicks();  

        float deltaTime = (nowTime - prevTime) / 1000.0f; // convert to seconds
        
        SDL_Event e{ 0 };
        
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_QUIT:
                {
                    running = false;
                    break;
                }
                case SDL_EVENT_WINDOW_RESIZED:
                {
                    state.w = e.window.data1;
                    state.h = e.window.data2;
                    break;
                }
            
            }           
        }

        //handle movement
        float moveAmount = 0;
        
        if (keys[SDL_SCANCODE_A]) {
            moveAmount += -800.0f;
            rotateCharacter = true;
            
        }
        if (keys[SDL_SCANCODE_D]) {
            moveAmount += 800.0f;
            rotateCharacter = false;
        }

        playerX += moveAmount * deltaTime;

              
        // set backbuffer white 
        SDL_SetRenderDrawColor(state.renderer, 20, 10, 30, 255);
        SDL_RenderClear(state.renderer);
        
        const float spriteSize = 50;
   

        SDL_FRect dst {
        .x = playerX,
        .y = floor - (spriteSize - 10),
        .w = spriteSize,
        .h = spriteSize
        };



        SDL_RenderTextureRotated(state.renderer, idltex, nullptr, &dst, 0, nullptr, 
            (rotateCharacter) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
            
        

        SDL_RenderPresent(state.renderer);

        prevTime = nowTime;
        
        
    }
    SDL_DestroyTexture(idltex);
    cleanup(&state);   

    
    return 0;

}



int initState(SDLState* state) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        show_error_and_exit(state);
    }
    
    state->w = 1600;
    state->h = 900;
    
    state->logW = 640;
    state->logH = 320;

    state->window = SDL_CreateWindow("demo", state->w, state->h, SDL_WINDOW_RESIZABLE);
    
    if (!state->window){
        show_error_and_exit(state);

    }

    state->renderer = SDL_CreateRenderer(state->window, nullptr);
    
    if (!state->renderer){
        show_error_and_exit(state);
        
    }

    SDL_SetRenderLogicalPresentation(state->renderer, state->logW, state->logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return 0;
    
}

void cleanup(SDLState* state ) {
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    SDL_Quit();
}

int show_error_and_exit(SDLState* state) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Error creating renderer", nullptr);
    cleanup(state);
    std::exit(1);

}


