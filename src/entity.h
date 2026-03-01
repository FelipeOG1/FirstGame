#pragma once
#include "animation.h"
#include <vector>

class Entity {


public:
    std::vector<Animation> animations;
    
    enum class Action {
        IDLE,
        JUMP,
        ATACK,
        HURT,
        
    };

    


};
