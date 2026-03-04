#pragma once
#include "vector"
#include "memory"
#include "game_object.h"
#include "typeinfo"
#include "player.h"
#include "enemy.h"

class GameState {

    
private:
    std::vector<std::vector<std::unique_ptr<GameObject>>> layer;
    
    enum class LayerIndex {
        PLAYER_INDEX,
        ENEMY_INDEX,
        TILES_INDEX,
        
        
    };
    
    int _getCorrespondingIndex(const GameObject* entity) {
        LayerIndex layerIndex = LayerIndex::TILES_INDEX;
        
        if (typeid(*entity) == typeid(Player)) {
            layerIndex = LayerIndex::PLAYER_INDEX;
        } else if (typeid(*entity) == typeid(Enemy)) {
            layerIndex = LayerIndex::ENEMY_INDEX;
        }
        return static_cast<int>(layerIndex);
    }
    
public:
    GameState() {
        layer.resize(3) ;
    }
    void addEntity (std::unique_ptr<GameObject> entity) {
        int index = _getCorrespondingIndex(entity.get());
        layer[index].push_back(std::move(entity));
    }

};
