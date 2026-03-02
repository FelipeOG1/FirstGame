#pragma once
#include "animation.h"
#include <vector>
#include <unordered_map>
#include "animationInstance.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Player {

private:
    const std::unordered_map<Action, Animation>& animations;
    AnimationInstance currentAnimation;
    Action currentAction = Action::IDLE;
    bool facingLeft = false;
    float x = 0.0;
    float y = 0.0;
    
    float w = 100.0;
    float h = 100.0;
    
public:

    
    const float velocity = 200.0;

    Player(const std::unordered_map<Action, Animation>& anims)
        : animations(anims)
    {
        if (!animations.count(Action::IDLE))
            throw std::runtime_error("Falta animación IDLE");
        
        setAction(Action::IDLE);
        currentAnimation.setAnimation(&animations.at(currentAction));
    }

    void setAction(Action newAction) {
        if (currentAction != newAction) {

            if (!animations.count(newAction))
                throw std::runtime_error("Animación no encontrada");

            currentAction = newAction;
            currentAnimation.setAnimation(&animations.at(currentAction));
        }
    }
    void setStartingPosition(float x, float y) {
        this->x = x;
        this->y = y;
    }


    void update(float deltaTime) {
        currentAnimation.step(deltaTime);
    }

    const Frame& getCurrentFrame() const {
        return currentAnimation.getCurrentFrame();
    }

    const std::string& getCurrentSpriteSheet() const {
        return currentAnimation.getSpriteSheet();
    }

    Action getCurrentAction() const {
        return currentAction;
    }

   
    void draw(SDL_Renderer *renderer) {
        const Frame& f = getCurrentFrame();
        SDL_Texture* tex = currentAnimation.currentTexture();
        if (!tex) return;

        SDL_FRect src = { (float)f.x, (float)f.y, (float)f.w, (float)f.h };
        
        SDL_FRect dst = { 
        this->x,          
        this->y,                  
        this->w, 
        this->h
        };

        SDL_FlipMode flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderTextureRotated(renderer, tex, &src, &dst, 0.0, nullptr, flip);
    };


    void MoveRight(float deltaTime) {
        setAction(Action::MOVE);
        facingLeft = false;
        x += velocity * deltaTime;
    }

   
    void MoveLeft(float deltatime) {
        setAction(Action::MOVE);
        facingLeft = true;
        x -= velocity * deltatime;

    }

    void jump(float deltatime) {
        setAction(Action::JUMP);
        
        y -= velocity * deltatime;

    }


    float getHeight() const { return h; }
        
         
    };

        
    
