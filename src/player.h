#pragma once
#include "game_object.h"
#include <SDL3/SDL.h>

class Player : public GameObject {

private:
    float moving = 0.0f;
public:
    Player(const std::unordered_map<Action, Animation>& anims) 
        : GameObject(anims) 
    {
        this->position = glm::vec2(0.0f, 0.0f); 
        this->size = glm::vec2(100.0f, 100.0f );     
        this->velocity = glm::vec2(200.0f, 0.0f);      
        this->scale = 1.3;
    }

    void handleUserInput(float deltaTime) {
        const bool *key_states = SDL_GetKeyboardState(nullptr);
        moving = 0.0f;
        Action currentAction = getCurrentAction();

        if (key_states[SDL_SCANCODE_D]) moving += 1.0f;
        if (key_states[SDL_SCANCODE_A]) moving -= 1.0f;
        
        if (moving != 0.0f) {
            if (currentAction == Action::IDLE) setAction(Action::MOVE);
            this->direction = moving; 
            this->position.x += moving * this->velocity.x * deltaTime;
        } else {
            if (currentAction == Action::ATTACK) return;
            
            setAction(Action::IDLE);
            
        } 

    }

    bool is_moving() {
        return moving != 0.0f;
    }

    
   

       };

    

