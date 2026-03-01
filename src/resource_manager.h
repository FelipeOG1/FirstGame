#pragma once
#include <unordered_map>
#include "animation.h"
#include "animation_loader.h"
#include "types.h"

class ResourceManager {

private:

    std::unordered_map<std::string, Action> playerConfigMap = {
        {"standing", Action::IDLE},
        {"running",  Action::MOVE},
    };

    std::unordered_map<Action, Animation> playerAnimations;

public:

    void loadPlayerResources() {
        AnimationLoader loader;
        loader.loadAnimations(
            "data/playerAnimations",
            playerConfigMap,
            playerAnimations
        );
    }

    const std::unordered_map<Action, Animation>& 
    getPlayerAnimations() const {
        return playerAnimations;
    }
};
