#pragma once
#include "game_object.h"
#include <SDL3/SDL.h>

class Player : public GameObject {
    
public:
    Player(const std::unordered_map<Action, Animation>& anims) 
        : GameObject(anims) 
    {
        this->position = glm::vec2(0.0f, 0.0f); 
        this->size = glm::vec2(100.0f, 100.0f );     
        this->velocity = glm::vec2(200.0f, 0.0f);      }

    void handleUserInput(float deltaTime) {
        const bool *key_states = SDL_GetKeyboardState(nullptr);
        float moving = 0.0f;
        
        if (key_states[SDL_SCANCODE_D]) moving += 1.0f;
        if (key_states[SDL_SCANCODE_A]) moving -= 1.0f;

        
        if (moving != 0.0f) {
            setAction(Action::MOVE);
            this->direction = moving; 
            this->position.x += moving * this->velocity.x * deltaTime;
        } 
        else {
            setAction(Action::IDLE);
        }

        if (key_states[SDL_SCANCODE_SPACE]) {
            setAction(Action::JUMP);
        }
    }

       };

    
    


