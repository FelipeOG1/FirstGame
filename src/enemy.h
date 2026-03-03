#pragma once
#include "game_object.h"
#include <SDL3/SDL.h>

class Enemy : public GameObject {
    
public:
    Enemy(const std::unordered_map<Action, Animation>& anims) 
        : GameObject(anims) 
    {
        this->position = glm::vec2(100.0f, 30.0f); 
        this->size = glm::vec2(100.0f, 100.0f );     
        this->velocity = glm::vec2(200.0f, 0.0f);      
    }
       };

    
    


