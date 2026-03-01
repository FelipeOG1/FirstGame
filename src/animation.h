#pragma once
#include <vector>
#include <string>
#include "types.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>
class Animation {

private:
    SDL_Texture* texture = nullptr;

public:
    float duration = 0.f;
    std::string spriteSheetPath;
    std::vector<Frame> frames;
    Animation() = default;


    bool empty() const {
        return frames.empty();
    }

    size_t frameCount() const {
        return frames.size();
    }

    void loadTexture(SDL_Renderer *renderer) {
        texture = IMG_LoadTexture(renderer, spriteSheetPath.c_str());
    }

    

    ~Animation() {
        if (texture) SDL_DestroyTexture(texture);
    }

    
};
