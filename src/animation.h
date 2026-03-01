#pragma once
#include <vector>
#include <string>
#include "types.h"

class Animation {

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

    
};
