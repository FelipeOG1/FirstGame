#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include "animation.h"
#include "animation_loader.h"




// TODO: Add a map with state and sdl_texture* so each animation work with their own PNG.

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

    std::map<int, Animation> playerAnims;
    for (auto const& [state, frame] : res.playerAnimations) {
        playerAnims[state] = Animation(frame.size(), 0.8f);
    }

    SDLState state;
    initState(&state);
        
    SDL_Texture* idltex = IMG_LoadTexture(state.renderer, "data/playerAnimations/player_standing.png");
    if (!idltex) {
        SDL_Log("No se pudo cargar la imagen: %s", SDL_GetError());
        return 1;
    }
    SDL_SetTextureScaleMode(idltex, SDL_SCALEMODE_NEAREST);

    uint64_t prevTime = SDL_GetTicks();
    bool running = true;
    int currentState = STANDING; // Forzado a STANDING

    while (running) { 
        uint64_t nowTime = SDL_GetTicks();  
        float deltaTime = (nowTime - prevTime) / 1000.0f; 
        
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
        }

        playerAnims[currentState].step(deltaTime);
        
        int frameIdx = playerAnims[currentState].currentFrame();
        
        if (res.playerAnimations[currentState].empty()) {
            SDL_Log("Error: El vector de frames para STANDING está vacío.");
            break;
        }

        Frame f = res.playerAnimations[currentState][frameIdx];

        SDL_SetRenderDrawColor(state.renderer, 20, 10, 30, 255);
        SDL_RenderClear(state.renderer);

        // Centramos al robot en la pantalla lógica (640x320)
        SDL_FRect src = { (float)f.x, (float)f.y, (float)f.w, (float)f.h };
        SDL_FRect dst = { 320.0f - f.w, 160.0f - f.h, f.w * 2.0f, f.h * 2.0f };

        SDL_RenderTextureRotated(state.renderer, idltex, &src, &dst, 0.0, nullptr, SDL_FLIP_NONE);

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


