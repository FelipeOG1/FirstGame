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
    float duration = 1.0f;
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
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    }

    SDL_Texture* getTexture() const {
        return texture;
    }


    ~Animation() {
        if (texture) SDL_DestroyTexture(texture);
    }

    
};
