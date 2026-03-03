#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include "animation.h"
#include "types.h"
#include "resource_manager.h"
#include "player.h"

struct SDLState {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int w, h, logW, logH;
    
};

void cleanup(SDLState* state);
int initState(SDLState* state);
int show_error_and_exit(SDLState* state);

int main(int argc, char* argv[]) {

    SDLState state;   
    initState(&state);
    ResourceManager resourceManager;
    resourceManager.loadPlayerResources(state.renderer);
    Player robot(resourceManager.getPlayerAnimations());
    

    
    uint64_t prevTime = SDL_GetTicks();
    bool running = true;

    const bool *key_states = SDL_GetKeyboardState(nullptr);
    
    robot.setStartingPosition(0, state.logH - robot.getHeight());
    
    while (running) {
        uint64_t currTime = SDL_GetTicks();

        float deltaTime = (currTime - prevTime) / 1000.0f;

        robot.update(deltaTime);

        SDL_Event e { 0 };
        while (SDL_PollEvent(&e)) {

            
            if (e.type == SDL_EVENT_QUIT) running = false;
            if (e.type == SDL_EVENT_WINDOW_RESIZED) {
                state.w = e.window.data1;
                state.h = e.window.data2;
            }

        }


        if (key_states[SDL_SCANCODE_D]) {
            robot.MoveRight(deltaTime);
        }

        if (key_states[SDL_SCANCODE_A]) {
            robot.MoveLeft(deltaTime);
        }
        if (key_states[SDL_SCANCODE_SPACE]) {
            robot.jump(deltaTime);
        }
        
        
        SDL_SetRenderDrawColor(state.renderer, 20, 10, 30, 255);
        SDL_RenderClear(state.renderer);
        robot.draw(state.renderer);
        SDL_RenderPresent(state.renderer);
        
        prevTime = currTime;


    }
    
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


