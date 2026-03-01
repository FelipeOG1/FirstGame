#pragma once
#include "animation.h"
#include <vector>
#include <unordered_map>
class Player {
   

private:
    Action curentAction = Action::IDLE;
    const std::unordered_map<Action, Animation>& animations;
    size_t currentFrameIdx = 0;
public:
    Player (const std::unordered_map<Action, Animation>& anims) : animations(anims) {};
    
    
   

};
