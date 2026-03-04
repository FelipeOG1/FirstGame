#pragma once
#include <unordered_map>
#include "animation.h"
#include "animation_loader.h"
#include "types.h"

class ResourceManager {

private:

    std::unordered_map<std::string, Action> playerConfigMap = {
        {"player_run_shot", Action::RUNSHOT},
        {"player_run",  Action::MOVE},
        {"player_stand", Action::IDLE},
        {"player_jump", Action::JUMP},
        {"player_shooting", Action::ATTACK}
    };
    std::unordered_map<std::string, Action> enemyConfigMap = {
        {"enemy_default", Action::IDLE},
        {"enemy_spinner", Action::ATTACK}
    };

    std::unordered_map<Action, Animation> playerAnimations;
    std::unordered_map<Action, Animation> enemyAnimations;


public:
    void loadPlayerResources(SDL_Renderer *renderer) {
        AnimationLoader loader;
        loader.loadAnimations(
            "data/playerAnimations",
            playerConfigMap,
            playerAnimations
        );

        for (auto& [action, animation]: playerAnimations) {
            animation.loadTexture(renderer);
        }
    }

    void loadEnemyResources(SDL_Renderer *renderer) {
        AnimationLoader loader;
        loader.loadAnimations(
            "data/enemyAnimations",
            enemyConfigMap,
            enemyAnimations 
        );
        for (auto& [action, animation]: enemyAnimations) {
            animation.loadTexture(renderer);
        }
    }



    std::unordered_map<Action, Animation>&getPlayerAnimations()  {
        return playerAnimations;
    }
    std::unordered_map<Action, Animation>&getEnemyAnimations()  {
        return enemyAnimations;
    }

};
